#version 330 core

in vec3 WorldPosition;
in vec3 WorldNormal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 Color;

uniform sampler2D GrassTexture;
uniform sampler2D DirtTexture;
uniform sampler2D RockTexture;
uniform sampler2D SnowTexture;

uniform vec2 ColorTextureScale;

uniform vec2 GrassHeight;
uniform vec2 DirtHeight;
uniform vec2 RockHeight;
uniform vec2 SnowHeight;

void main()
{
	vec4 colTexture = texture(GrassTexture, TexCoord * ColorTextureScale);
	FragColor = colTexture * Color;
}
