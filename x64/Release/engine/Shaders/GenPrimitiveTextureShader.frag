#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform int Type;
vec4 fColor = vec4(1.0f);

void main()
{
	
	if(Type ==0)
	{
		vec2 uv = TexCoords *2.0f - vec2(1.0f);
		float dist = uv.x*uv.x+uv.y*uv.y;
	
		if(dist>0.99f)
			color= vec4(fColor.rgb,fColor.a * smoothstep(1.0f,0.0f,(dist-0.99f)*100.0f));
		else 
			color= fColor;
	}
	else 
	{
		color= fColor;
	}
}