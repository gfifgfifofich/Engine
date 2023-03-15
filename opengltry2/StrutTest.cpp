#include "engine/Components/Engine.h"




class application : public Engine
{
	cube floor;
	cube lwall;
	cube rwall;
	
	box b;
	box b2;
	unsigned int texture;
	void On_Create() override
	{
		LoadTexture("container.jpg", &texture);
		floor.position = glm::vec2(0.0f,-500.0f);
		floor.height = 100;
		floor.width = 1000;

		lwall.position = glm::vec2(-650.0f, 0.0f);
		lwall.height = 1000;
		lwall.width = 100;

		rwall.position = glm::vec2(650.0f, 0.0f);
		rwall.height = 1000;
		rwall.width = 100;

		b.init(glm::vec2(0.0f, 300), glm::vec2(40));
		b.roughness = 1.0f;
		b.bounciness = 2.0f;

		b2 = b;
		b2.init(glm::vec2(0.0f, 500), glm::vec2(250));


		DrawingOrder = true;
	}
	void On_Update() override
	{
		b.Force = glm::vec2(0.0f, -1000.0f);
		b2.Force = glm::vec2(0.0f, -1000.0f);

		if (buttons[GLFW_MOUSE_BUTTON_1])
			b.Force += (MousePosition - b.position)*10.0f;
		b.Process(delta);
		b2.Process(delta);


		BoxToBoxCollision(&b, &b2);
		for (int i = 0; i < 4; i++)
		{
			BallToStaticQuadCollision(&b.balls[i], floor);
			BallToStaticQuadCollision(&b.balls[i], rwall);
			BallToStaticQuadCollision(&b.balls[i], lwall);

			BallToStaticQuadCollision(&b2.balls[i], floor);
			BallToStaticQuadCollision(&b2.balls[i], rwall);
			BallToStaticQuadCollision(&b2.balls[i], lwall);

		}
		DrawCube(floor);
		DrawCube(rwall);
		DrawCube(lwall);

		DrawTexturedQuad(b.position, b.size,texture,glm::vec3(0.0f,0.0f, get_angle_between_points(b.position, 0.5f * (b.balls[0].position + b.balls[1].position))));
		DrawTexturedQuad(b2.position, b2.size,texture,glm::vec3(0.0f,0.0f, get_angle_between_points(b2.position, 0.5f * (b2.balls[0].position + b2.balls[1].position))));
	}
};
int main()
{
	application app;
	app.init();
	return 0;
}