#version 400

out vec4 fragColor;

uniform sampler2D texture1;

void main()
{
    fragColor = vec4(0.6f,0.6f,0.6f,1.0f);
}