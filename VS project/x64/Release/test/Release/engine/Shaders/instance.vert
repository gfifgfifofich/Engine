#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 2) in vec4 aPoggersColor;
layout (location = 3) in mat4 aMat;
//layout (location = 6) in vec4 aPoggersColor;

out vec4 fColor;

vec4 pos;
uniform mat4 transform;

uniform vec2 scr;
void main()
{
    pos = aMat*vec4(aPos,0.0f,1.0f);
    pos.x /=scr.x;
    pos.x *=scr.y;
    gl_Position =  pos;
    fColor = aPoggersColor;
}  