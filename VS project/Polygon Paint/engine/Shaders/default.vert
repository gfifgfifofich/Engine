#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aOffset;

out vec4 fColor;
vec4 pos;
uniform mat4 transform;
vec2 scr=  vec2(1280.0f,920.0f);
void main()
{
    pos = transform*vec4(aPos,0.0f,1.0f);
    pos.x /=scr.x/scr.y;
    gl_Position =  pos - vec4(0.101,0.0,0.0,0.0);
    fColor = aColor;
}  