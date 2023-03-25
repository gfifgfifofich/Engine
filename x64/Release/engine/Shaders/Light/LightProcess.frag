#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Texture;
uniform sampler2D BaseColor;
uniform sampler2D NormalMap;
uniform vec4 color = vec4(1.0f); 
uniform vec2 position; 
uniform vec2 scale; 
uniform float volume; 

uniform vec3 scr; 

void main()
{             
	vec2 scrSpace;
	vec2 Pos = position+0.5f;
	float aspect = scr.z;
	Pos.x *=aspect;

	scrSpace.x =gl_FragCoord.x / scr.x;
	scrSpace.y =gl_FragCoord.y / scr.y;
	vec2 SurfaceNormal = texture(NormalMap,scrSpace).rg;
	vec4 LightColor = texture(Texture, TexCoords).rgba * color;    
	vec4 BaseCol = texture(BaseColor, scrSpace).rgba;     

	scrSpace.x *=aspect;


	vec2 rel = normalize(Pos-scrSpace);

	FragColor = clamp(dot(rel,SurfaceNormal),0.0f,1.0f)*LightColor *BaseCol + volume*LightColor;// +PrevColor;


	
	/*
	vec2 dif = scrSpace - Pos;
	float dist = dif.x*dif.x+dif.y*dif.y;
	
	
	if(sqrt(dist)<0.1f)
		FragColor = vec4(1.0f);
	else
		FragColor = vec4(SurfaceNormal,0.0f,1.0f);
	*/
}