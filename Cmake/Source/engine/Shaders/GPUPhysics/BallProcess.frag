#version 330 core
in vec2 TexCoords;
out vec4 FragValue;

uniform int BallsCount = 1;
uniform float delta = 0.017f;
uniform float Radius = 1.0f;
uniform vec2 force = vec2(0.0f);

uniform sampler2D Balls; 



vec4 GetBall(int i)
{
	return texture(Balls,vec2( (float(i+0.5f) / BallsCount),0.0f));
}


vec4 Run()
{
	vec4 ball = texture(Balls, TexCoords + vec2(0.3f,0.0f));
    ball.z += force.x;  // velocity += force
    ball.w += force.y;  // velocity += force
    ball.x += ball.z;//pos+=velocity
    ball.y += ball.w;//pos+=velocity
    return ball;
}

void main()
{
	//FragValue = texture(weights,vec2( (gl_FragCoord.y / inSize),(gl_FragCoord.x / outSize) )).r;
	//FragValue = GetIn(int(gl_FragCoord.x));
	//FragValue = GetWeight(int(gl_FragCoord.x));
	//FragValue = GetBias(int(gl_FragCoord.x));
	FragValue = Run();
}