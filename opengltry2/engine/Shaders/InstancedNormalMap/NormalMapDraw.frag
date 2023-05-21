#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform sampler2D Texture;

uniform bool generated = false;

void main()
{
	vec4 SurfaceNormal =  texture(Texture, TexCoords.xy);
	if(SurfaceNormal.z==1)
		discard;
	else
	{
		if(!generated)
		{
			SurfaceNormal.x = SurfaceNormal.x*2.0f-1.0f;
			SurfaceNormal.y = SurfaceNormal.y*2.0f-1.0f;
		}
		if(TexCoords.z!=0.0f)
		{
			vec4 col = SurfaceNormal;
			SurfaceNormal.xy = vec2(cos(TexCoords.z)*col.x - sin(TexCoords.z)*col.y, sin(TexCoords.z)*col.x + cos(TexCoords.z)*col.y);
			FragColor = SurfaceNormal;
		}
		else
			FragColor = SurfaceNormal;
	}

}