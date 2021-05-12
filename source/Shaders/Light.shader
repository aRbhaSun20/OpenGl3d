#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
// layout (location = 1) in vec2 aTexCoord;

// out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * aPos;
	// v_TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 FragColor;

// in vec2 v_TexCoord;

uniform vec3 u_lightColor;

void main()
{
	FragColor = vec4(u_lightColor, 1.0);
}