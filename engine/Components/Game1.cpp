
#include "engine/Components/Engine.h"
#include "engine/Components/Classes.h"

float force_coef = 1.0f;

bool acceletrationlines = false;

const int amount = 1000;
const int camount = 0;
float heat[amount];

std::vector <ball> balls;


class application : public Engine
{

	void On_Create() override
	{



		ball b;
		float r = 5.0f;
		for (int i = 0; i < amount; i++)
		{
			b.r = r + (rand() % 10 - 5) / 2.0f;
			b.position = glm::vec2(r + rand() % WIDTH - r * 2, r + rand() % HEIGHT - r * 2);
			b.velocity = glm::vec2(rand() % 10 - 5, rand() % 10 - 5);
			heat[i] = 1.0f;
			balls.push_back(b);
		}
		for (int i = 0; i < balls.size(); i++)
			ballsptr.push_back(&balls[i]);

		cube cub;
		for (int i = 0; i < camount; i++)
		{
			cub.position = glm::vec2(r + rand() % WIDTH - r * 2, r + rand() % HEIGHT - r * 2);;
			cub.height = 10.0f;
			cub.width = 10.0f;
			Cubes.push_back(cub);
		}

		BackgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		substeps = 8;
		dt_of_sim = 1.000f;
		friction = 0.011f;
		g = glm::vec2(0.0f, 0.5f);
		acceletrationlines = true;
		DrawingOrder = 0;
	}

	void On_Update() override
	{
		ImGui::Begin("SceneSettings");

		ImGui::SliderFloat("Speed of Sim", &dt_of_sim, 0.001f, 5.0f);

		ImGui::SliderInt("substeps/frame", &substeps, 1, 8);

		ImGui::SliderFloat("friction", &friction, 0.0, 1.0f);

		ImGui::SliderFloat("g", &g.y, -10, 10);

		if (ImGui::Button("acceleration lines"))
		{
			acceletrationlines = !acceletrationlines;
		}

		if (ImGui::Button("Show Main Settings Window"))
			SettingsWindow = !SettingsWindow;

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate);

		ImGui::End();



		float subtime = dt_of_sim / substeps;
		for (int s = 0; s < substeps; s++)
			for (int i = 0; i < amount; i++)
			{
				balls[i].velocity -= g * subtime;
				glm::vec2 PastVel = balls[i].velocity;

				balls[i].position += balls[i].velocity * subtime;
				balls[i].velocity -= balls[i].velocity * friction * subtime;
				for (int a = 0; a < balls.size(); a++)
				{
					if (a > i)
					{
						BtBCollision(&balls[i], &balls[a]);
					}
				}
				for (int a = 0; a < Cubes.size(); a++)
				{
					CircleToStaticQuadCollision(&balls[i], Cubes[a]);
				}
				// walls colisions 
				if (balls[i].position.y > HEIGHT - balls[i].r)
				{
					balls[i].position.y = HEIGHT - balls[i].r;
					if (balls[i].velocity.y > 0)
						balls[i].velocity.y = -balls[i].velocity.y;
				}
				if (balls[i].position.y < 0 + balls[i].r)
				{
					balls[i].position.y = 0 + balls[i].r;
					if (balls[i].velocity.y < 0)
						balls[i].velocity.y = -balls[i].velocity.y;
				}
				if (balls[i].position.x > WIDTH - balls[i].r)
				{
					balls[i].position.x = WIDTH - balls[i].r;
					if (balls[i].velocity.x > 0)
						balls[i].velocity.x = -balls[i].velocity.x;
				}
				if (balls[i].position.x < 0 + balls[i].r)
				{
					balls[i].position.x = 0 + balls[i].r;
					if (balls[i].velocity.x < 0)
						balls[i].velocity.x = -balls[i].velocity.x;
				}
				heat[i] += length(PastVel - balls[i].velocity) * 0.025f - heat[i] * 0.1f * subtime;
				if (heat[i] <= 0.0f)
				{
					heat[i] = 0.0f;
				}
				balls[i].color = glm::vec4(heat[i], heat[i] * 0.2, heat[i] * 0.04, 1.0f);
			}



		for (int i = 0; i < amount; i++)
		{
			DrawCircle(balls[i].position, balls[i].r, heat[i] * 0.1, balls[i].color);
			if (acceletrationlines)
			{
				DrawLine(balls[i].position, balls[i].position - balls[i].velocity * 1.0f, balls[i].r * 0.75, balls[i].color);
			}
		}
		for (int i = 0; i < camount; i++)
		{
			DrawCube(Cubes[i].position, glm::vec2(Cubes[i].width, Cubes[i].height));
		}
	}
};

int main()
{
	application app;
	app.init();
	return 0;
}