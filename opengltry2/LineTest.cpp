#include "engine/Components/Engine.h"

class application : public Engine
{
public:
	RigidBody b;
	

	void On_Create() override
	{
		b.init(glm::vec2(500, 500), 50);
	}
	void On_Update() override
	{
		b.body.velocity.y -= 10.0f;


		line l(glm::vec2(0.0f, 0.0f), MousePosition);
		line l2(glm::vec2(WIDTH, 0.0f), MousePosition);
		line l3(MousePosition,glm::vec2(WIDTH, HEIGHT));
		line l4(glm::vec2(0.0f, HEIGHT), MousePosition);

		BallToLineCollision(&b.body, l4);
		BallToLineCollision(&b.body, l3);

		if (PointToLineSideCheck(b.body.position, l))
			DrawLine(glm::vec2(0.0f, 0.0f), MousePosition, 2.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		else 
			DrawLine(glm::vec2(0.0f, 0.0f), MousePosition, 2.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		

		if (PointToLineSideCheck(b.body.position, l2))
			DrawLine(glm::vec2(WIDTH, 0.0f), MousePosition, 2.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		else
			DrawLine(glm::vec2(WIDTH, 0.0f), MousePosition, 2.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		

		if (PointToLineSideCheck(b.body.position, l3))
			DrawLine(glm::vec2(WIDTH, HEIGHT), MousePosition, 2.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		else
			DrawLine(glm::vec2(WIDTH, HEIGHT), MousePosition, 2.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		

		if (PointToLineSideCheck(b.body.position, l4))
			DrawLine(glm::vec2(0.0f, HEIGHT), MousePosition, 2.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		else
			DrawLine(glm::vec2(0.0f, HEIGHT), MousePosition, 2.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));



		b.Process(delta);
	}
};

int main()
{
	application app;
	app.init();
	return 0;
}