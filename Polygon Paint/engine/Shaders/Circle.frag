#version 330 core
in vec4 fColor;
in vec4 PosRadEdg;
out vec4 color;

vec4 pogcol = fColor;



vec2 scr=  vec2(1280.0f,920.0f);
void main()
{
	
	vec4 c = fColor;
	vec2 position = vec2(PosRadEdg.x,PosRadEdg.y);
	float radius = PosRadEdg.z;
	float edge = PosRadEdg.w;


	float UVtrans = scr.x/scr.y;
	vec2 UV = gl_FragCoord.xy * UVtrans; //Correct UV !!! POGGERS ALERT !!!

	color = vec4(UV.x/scr.x,UV.y/scr.y,0.0f,1.0f);
	
	
	vec2 pos2 = position* UVtrans ;

	float r = radius *UVtrans ;

	vec2 dif = UV-pos2;
	float l = (dif.x*dif.x+dif.y*dif.y);

	float dist = sqrt(l);
	float smoooth = smoothstep(r+edge,r,dist);

	color = vec4(c.x*smoooth,c.y*smoooth,c.z*smoooth,c.w*smoooth);
   
	
}