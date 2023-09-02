#version 330 core

// Output data
out vec4 FragColor;
uniform vec3 color;

void main()
{
	FragColor = vec4(color, 1.0f);
}
