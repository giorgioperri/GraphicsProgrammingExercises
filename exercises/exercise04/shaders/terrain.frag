#version 330 core

in vec3 WorldPosition;
in vec3 WorldNormal;
in vec2 TexCoord;
in float Height;

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

float chooseTextureByHeight(in vec2 range, in float height);

void main()
{
	vec4 finalTexture;

	vec4 dirtTexture = texture(DirtTexture, TexCoord * ColorTextureScale);
	vec4 grassTexture = texture(GrassTexture, TexCoord * ColorTextureScale);
	vec4 rockTexture = texture(RockTexture, TexCoord * ColorTextureScale);
	vec4 snowTexture = texture(SnowTexture, TexCoord * ColorTextureScale);

	float dirt = chooseTextureByHeight(DirtHeight, Height);
	float grass = chooseTextureByHeight(GrassHeight, Height);
	float rock = chooseTextureByHeight(RockHeight, Height);
	float snow = chooseTextureByHeight(SnowHeight, Height);

	finalTexture = mix(dirtTexture, grassTexture, grass);
	finalTexture = mix(finalTexture, rockTexture, rock);
	finalTexture = mix(finalTexture, snowTexture, snow);

	FragColor = finalTexture * Color;
}

float chooseTextureByHeight(in vec2 range, in float height)
{
	if(height <= range.x)
		return (0.0);
	else if(height >= range.y)
		return (1.0);
	else
		return ((height - range.x) / (range.y - range.x));
}