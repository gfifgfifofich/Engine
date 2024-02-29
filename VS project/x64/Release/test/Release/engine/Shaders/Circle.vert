#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aPoggersColor;
layout (location = 2) in mat4 aMat;

out vec4 fColor;
out vec2 UV;


uniform vec2 scr;
vec4 pos;
void main()
{
    pos = aMat*vec4(aPos.x,aPos.y,0.0f,1.0f);
    pos.x /=scr.x;
    pos.x *=scr.y;
    gl_Position =  pos ;
    fColor = aPoggersColor;
    UV = aPos.zw;
}  