#version 330 core

layout (location = 0) in vec2 ParticlePosition;
layout (location = 1) in float size;
layout (location = 2) in float birth;
layout (location = 3) in float duration;
layout (location = 4) in vec4 Color;
layout (location = 5) in vec2 Velocity;

out vec4 particleColor;

float age;

// (todo) 02.X: Add uniforms
uniform float CurrentTime;
uniform vec2 Gravity;

void main()
{
	age = CurrentTime - birth;

	if(age > duration) {
		gl_PointSize = 0;
	} else {
		gl_PointSize = size;
	}

	particleColor = Color;

	gl_Position = vec4(ParticlePosition + Velocity * age + (0.5 * (Gravity * age * age)), 0.0, 1.0);
}
