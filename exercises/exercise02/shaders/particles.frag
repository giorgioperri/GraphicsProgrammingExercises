#version 330 core

out vec4 FragColor;

in vec4 particleColor;


void main()
{
	vec2 pointCoord = gl_PointCoord * 2 - 1;
	float val = 1 - length(pointCoord);

	FragColor = vec4(particleColor.x, particleColor.y, particleColor.z, val * particleColor.w);
}
