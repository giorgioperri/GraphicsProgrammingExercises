#version 330 core

// (todo) 03.X: Add the in variables here
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform vec3 Color = vec3(1);

void main()
{
	FragColor = dot(normalize(Normal), vec3(1)) * vec4(Color, 1);
	//FragColor = vec4(Position, 1);
}
