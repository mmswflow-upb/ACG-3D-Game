#version 400

in vec2 textureCoord; 

out vec4 fragColor;


void main()
{
	//Yellow Color for Bullets
	float ambientStrength = 1.0f;
	vec3 objectColor = vec3(1.0f, 1.0f, 0.f);

	vec3 result = objectColor;
	fragColor = vec4(result, 1.0f);
}