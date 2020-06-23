#version 330 core
uniform sampler2D Texture;

in  vec2 vTexCoord;
out vec4 gl_FragColor;

void main()
{
    precision lowp float;

    vec4 color = texture2D(Texture, vTexCoord);
    gl_FragColor = color;
}
