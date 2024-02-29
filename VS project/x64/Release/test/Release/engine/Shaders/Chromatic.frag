#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D image;

uniform vec2 point = vec2(0.5f); 
uniform float strength = 1.0f; 

void main()
{             
	
	vec2 offset = point -TexCoords ;
	offset *=strength*10.0f;
	
	vec3 result = texture(image, TexCoords).rgb;
	result.r = texture(image, TexCoords+offset*strength*0.01f).r;
	result.g = texture(image, TexCoords+offset*strength*0.02f).g;
	result.b = texture(image, TexCoords+offset*strength*0.03f).b;


	FragColor = vec4(result, 1.0);
}