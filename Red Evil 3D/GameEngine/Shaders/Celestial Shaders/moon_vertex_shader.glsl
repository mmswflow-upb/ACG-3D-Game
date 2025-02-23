#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

out vec2 textureCoord;


uniform mat4 MVP;

void main()
{
	
	gl_Position = MVP * vec4(pos, 1.0f);
}