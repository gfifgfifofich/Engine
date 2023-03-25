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
	vec3 SurfaceNormal = texture(NormalMap,scrSpace).rgb;
	vec4 LightColor = texture(Texture, TexCoords).rgba * color;    
	vec4 BaseCol = texture(BaseColor, scrSpace).rgba;

	scrSpace.x *=aspect;


	vec3 rel = normalize(vec3(Pos-scrSpace,0.0f));



	vec4 Col;
	
	if(SurfaceNormal.z==2.0f) // -> generated Normal map
		{
			Col = clamp(dot(rel.xy,SurfaceNormal.xy),0.0f,1.0f)*LightColor *BaseCol;
		}
	else if(SurfaceNormal.z!=0.0f)
		{
			SurfaceNormal.x = SurfaceNormal.x*2.0f-1.0f;
			SurfaceNormal.y = SurfaceNormal.y*2.0f-1.0f;
			Col = clamp(dot(rel.xy,SurfaceNormal.xy),0.0f,1.0f)*LightColor *BaseCol;
		}
	else Col=LightColor *BaseCol;
	
	FragColor =  Col + volume*LightColor;


}