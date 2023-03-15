#include "engine/Components/Engine.h"
class application : public Engine
{

	ball a;
	ball b;

	float len = 200.0f;

	void On_Create() override
	{

		a.position.x = 0;
		a.position.y = 0;

		b.position.x = 300;
		b.position.y = 0;

		a.r = 25;
		b.r = 25;
	}
	float absorp = 0.0f;
	void On_Update() override
	{
		ImGui::Begin("a");
		ImGui::SliderFloat("abs", &absorp, 0.0f, 1.0f);
		a.Force = glm::vec2(0.0f);
		b.Force = glm::vec2(0.0f);

		//glm::vec2 dif = a.position - b.position;
		//
		//glm::vec2 offset = dif - Normalize(dif) * len;


		//a.Force -= offset;
		//b.Force += offset;

		SpringBetweenBalls(&a, &b,len,3.0f,absorp);


		a.Process(delta);
		b.Process(delta);

		DrawCircle(a);
		DrawCircle(b);
	}
};


int main()
{
	application app;
	app.init();
	return 0;
}