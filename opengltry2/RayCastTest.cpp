#include "engine/Components/Engine.h"



const int amount = 100;
Ray r[amount];

class application : public Engine
{
	cube c;
	ball b;
	void On_Create() override
	{
		b.r = 110.0f;
		for (int i = 0; i < amount; i++)
		{
			glm::vec2 vec = Rotate({ 1.0f,0.0f }, pi / amount * 2.0f * i);
			r[i] = Ray(vec * 10.0f, vec, 500, 100);
			r[i].iterations = 10;
		}
		c.width = 100;
		c.height = 100;
	}
	void On_Update() override
	{
		c.position = MousePosition;
		b.position = MousePosition;
		DrawCube(c);
		DrawCircle(b,glm::vec4(1.0f,1.0f,0.0f,1.0f));
		for (int i = 0; i < amount; i++)
		{
			r[i].Update();
			CastRayToQuad(&r[i], c);
			CastRayToBall(&r[i], b);

			DrawLine(r[i].ClosestPoint, r[i].position, 1.0f, glm::vec4(1.0f, 1.0f, 100.0f, 1.0f));
		}
		

	}
};
int main()
{
	application app;
	app.init();
	return 0;
}
