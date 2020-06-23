// ComputerGraphicSS3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <memory>

#include "EngineSrc/Variant/variant.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "EngineSrc/Sence/Screen.h"
#include "EngineSrc/GlobalDefine.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

/*
void initSence();
void RenderSence();
*/

unsigned int VBO, VAO, IBO;
unsigned int shaderProgram;
int main()
{
	
	// init glfw 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "E3G3_OpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("ERROR!!!!  Can not create windows");
		glfwTerminate();
		return -1;
	}

	// set current context
	glfwMakeContextCurrent(window);

	// set callback for framebuffer size
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

	// glad: load openGL function poiter
	bool gladLoadDone = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!gladLoadDone)
	{
		printf("ERROR!!! Fail to load GLAD");
		return -1;
	}

	Screen* screen = Screen::GetIstance();

	screen->InitScreen();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		screen->Update(0.016f);


		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		screen->Render();
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}  

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

/*
// init data
void initSence()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 -0.5f, 0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
	1, 2, 3    // second triangle
	};

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";

	
	std::ifstream stream("default.vert.hlsl", std::ios::in | std::ios::binary | std::ios::ate);
	char* shaderData =0;
	int size = 0;
	if (stream.is_open())
	{
		size = stream.tellg();
		shaderData = new char[size +1];
		shaderData[size] = '\0';
		stream.seekg(0,std::ios::beg);
		stream.read(shaderData, size);
		stream.close();
	}

	
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderData, NULL);
	glCompileShader(vertexShader);
	delete[] shaderData;

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf( "ERROR!!! SHADER::VERTEX::COMPILATION_FAILED\n");
		printf("ERROR!!! %s \n", infoLog);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR!!! SHADER::FRAGMENT::COMPILATION_FAILED\n");
	}

	
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR!!! SHADER::Link FAIL\n");
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


}

// render sence
void RenderSence()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
*/