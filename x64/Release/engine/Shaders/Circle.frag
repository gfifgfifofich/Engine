#version 330 core
in vec4 fColor;
in vec2 UV;

out vec4 color;

vec4 pogcol = fColor;

void main()
{
	
	vec4 c = fColor;

	vec2 uv = UV *2.0f - vec2(1.0f);
	float dist = uv.x*uv.x+uv.y*uv.y;
	if (dist<=0.99f)
		color = fColor;
	else
	{
		dist -=1.0f;
		if(dist<0.0f)
		{
			dist *=-1.0f;
			color = vec4(fColor.rgb,dist*20.0f);
		}
		else discard;
	}
}