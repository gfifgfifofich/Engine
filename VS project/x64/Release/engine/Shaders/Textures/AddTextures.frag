#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

uniform vec2 proportions = vec2(1.0f,1.0f);

void main()
{
	FragColor = vec4(texture(Texture1,TexCoords).rgb*proportions.x+texture(Texture2,TexCoords).rgb*proportions.y,1.0f);
}