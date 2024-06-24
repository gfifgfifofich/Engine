#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Texture;
uniform sampler2D BaseColor;
uniform sampler2D NormalMap;
uniform vec4 color = vec4(1.0f); 
uniform vec3 position; 
uniform vec2 CameraScale; 
uniform float volume; 
uniform float sizeZ = 2.0f; 

uniform float aspect; 
uniform vec2 scr;
void main()
{             
	vec2 scrSpace;
	vec3 Pos = position;
	Pos.x += 0.5f;
	Pos.y += 0.5f;
	Pos.x /= aspect;
	scrSpace.x =gl_FragCoord.x / scr.x;
	scrSpace.y =gl_FragCoord.y / scr.y;
	vec4 SurfaceNormal = texture(NormalMap,scrSpace).rgba;

	float diff = (Pos.z-SurfaceNormal.a)/sizeZ;

	vec2 lightpos = TexCoords + normalize(TexCoords - vec2(0.5f,0.5f)) * diff;

	lightpos.x = clamp(lightpos.x,0.0f,1.0f);
	lightpos.y = clamp(lightpos.y,0.0f,1.0f);

	vec4 LightColor = texture(Texture, lightpos).rgba;    
	LightColor *= color;
	vec4 BaseCol = texture(BaseColor, scrSpace).rgba;

	scrSpace.x /=aspect;
	scrSpace /= CameraScale;
	Pos.xy /= CameraScale;
	vec3 rel = normalize(vec3(Pos.xy-scrSpace,Pos.z-SurfaceNormal.a));

	vec4 Col;
	Col = clamp(dot(rel.xyz,SurfaceNormal.xyz),0.0f,1.0f)*LightColor*BaseCol;
	if(SurfaceNormal.x==0 && SurfaceNormal.y==0) Col=LightColor*BaseCol;
	Col = Col.rgba + volume*LightColor.rgba;
	FragColor = vec4(Col.rgb,min(Col.a,1.0f));
}