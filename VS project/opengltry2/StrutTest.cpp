#include "engine/Components/Engine.h"



cube dafloor;
cube lwall;
cube rwall;

ball b1;
ball b2;




DecorativeRope r;

void On_Create()
{
	dafloor.position = glm::vec2(0.0f, -500.0f);
	dafloor.height = 100;
	dafloor.width = 1000;

	lwall.position = glm::vec2(-650.0f, 0.0f);
	lwall.height = 1000;
	lwall.width = 100;

	rwall.position = glm::vec2(650.0f, 0.0f);
	rwall.height = 1000;
	rwall.width = 100;
	b1.mass = 1;
	b2.mass = 1;
	b2.position = { 100.0f,0.0f };

	r.Init(&b1,&b2,200);
	r.Force = { 0.0f,-100.0f };
	b1.Force = { 0.0f,-250.0f };
	b2.Force = { 0.0f,-250.0f };
	b2.roughness = 1.0f;
	b2.bounciness = 0.1f;
	b1.roughness = 1.0f;
	b1.bounciness = 0.1f;
}
void On_Update()
{
	if(buttons[GLFW_MOUSE_BUTTON_1])
		b2.velocity += (MousePosition - b2.position);

	if (buttons[GLFW_MOUSE_BUTTON_2])
		b1.velocity += (MousePosition - b1.position);

	MRope(&b1, &b2, 200);
	b1.Process(delta);
	b2.Process(delta);
	r.Process(delta);
	r.Draw();
	
	BallToStaticQuadCollision(&b1, dafloor);
	BallToStaticQuadCollision(&b2, dafloor);

	BallToStaticQuadCollision(&b1, lwall);
	BallToStaticQuadCollision(&b2, lwall);

	BallToStaticQuadCollision(&b1, rwall);
	BallToStaticQuadCollision(&b2, rwall);

	DrawCube(dafloor);
	DrawCube(rwall);
	DrawCube(lwall);

	DrawBall(b1);
	DrawBall(b2);

}
int main()
{
	initEngine();

	return 0;
}