#version 330 core
uniform sampler2D Texture;
uniform mediump vec3 uBaseColor;
uniform mediump float uFilledPercen;
uniform float scaleProcess;

in  vec2 vTexCoord;
in  vec2 centreCoord;


void main()
{
    precision mediump float;
	
	vec4 textureColor = texture2D(Texture, vTexCoord);
    
	if(textureColor.a == 0.0)
	{
		discard;
	}
	
    float PI = 3.1415;    
    
    float angle = (atan(centreCoord.x, centreCoord.y) ) + PI ;
    
    angle = 2.0*PI - angle; // revert clockwise
    float fillPercen = uFilledPercen *scaleProcess;
    if( angle > (fillPercen * 2.0*PI )  )
    {
    	discard;
    }
	vec3 backgroundColor = vec3(0);
    vec3 color = mix( backgroundColor, uBaseColor, step(angle,(fillPercen * 2.0*PI )));
    gl_FragColor = vec4(color.rgb,textureColor.a);
	

}
