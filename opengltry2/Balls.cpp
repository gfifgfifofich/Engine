
#include "engine/Components/Engine.h"
#include <thread>

float force_coef = 1.0f;
float CentralCharge = 0.0f;
bool acceletrationlines = false;


struct VerletObject
	{
		float r = 10;
		float charge = 1.0f;
		glm::vec4 color = glm::vec4(1.0f);
		glm::vec2 ppos = glm::vec2(0.0f);
		glm::vec2 cpos = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		glm::vec2 acceleration = glm::vec2(0.0f);
		float deltatime = dt_of_sim;
		void UpdatePos()
		{
			velocity = (cpos - ppos);
	
			ppos = cpos;
	
	
			cpos = cpos + velocity + (acceleration * deltatime * deltatime);
	
	
			acceleration = glm::vec2(0.0f);
		}
	
	};

struct staticball
{
	glm::vec2 pos = glm::vec2(0.0f);
	glm::vec4 color = glm::vec4(1.0f);
	float r = 10;
	float charge = 2.0f;
	float chargeForce = 1.0f;
};
std::vector <VerletObject> Balls;
std::vector <staticball> StaticBalls;




class application : public Engine
{

	

	void On_Create() override 
	{
		VerletObject a;
		a.cpos = glm::vec2(640, 540);
		a.ppos = glm::vec2(640, 540);
		Balls.push_back(a);

		staticball b;

		//b.pos = glm::vec2(-900.0f, 460.0f);
		//b.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		//b.r = 1000.0f;
		//b.charge = 25;
		//b.chargeForce = 2500;
		//StaticBalls.push_back(b);

		b.pos = glm::vec2(640.0f, 460.0f);
		b.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		b.r = 200.0f;
		b.charge = 20;
		b.chargeForce = 0;
		//StaticBalls.push_back(b);
	}
	
	glm::vec4 testColor = glm::vec4(0.0f);

	int substeps = 1;

	void On_Update() override
	{
		ImGui::Begin("SceneSettings");


		ImGui::SliderFloat("Speed of Sim", &dt_of_sim, 0.001f, 0.3f);

		ImGui::SliderInt("substeps/frame", &substeps, 1, 5);

		ImGui::SliderFloat("EM force", &force_coef, 0.1, 5000);

		ImGui::SliderFloat("Centrall Charge", &CentralCharge, -20000, +20000);


		// color
		ImGui::SliderFloat(" colr r", &testColor.x, 0, 10);
		ImGui::SliderFloat(" colr g", &testColor.y, 0, 10);
		ImGui::SliderFloat(" colr b", &testColor.z, 0, 10);
		ImGui::SliderFloat(" colr a", &testColor.w, 0, 2);

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

		DrawCircle(glm::vec2(WIDTH * 0.5, HEIGHT * 0.5), 0, testColor);
		               

		if (keys[GLFW_KEY_SPACE])
		{
			VerletObject a;
			a.cpos = glm::vec2(640+ (rand() % 1000) / 10 - 50, 540+ (rand() % 1000) / 10 - 50);
			a.ppos = a.cpos;
			a.charge = (rand() % 1000) / 100 - 5;
			Balls.push_back(a);
		}



		for (int i = 0; i < Balls.size(); i++)
		{

			Balls[i].deltatime = dt_of_sim / substeps;
			Balls[i].UpdatePos();


			for (int a = 0; a < Balls.size(); a++)
			{
				if (a != i)
				{
					glm::vec2 dif = Balls[i].cpos - Balls[a].cpos;
					float distsqr = dif.x * dif.x + dif.y * dif.y;
					float dist = sqrt(distsqr);
					glm::vec2 normalizeddif = dif / dist;

					if (distsqr < (Balls[i].r + Balls[a].r) * (Balls[i].r + Balls[a].r))
					{

						float distance_difference = Balls[i].r + Balls[a].r - dist;

						Balls[i].cpos += normalizeddif * distance_difference * 0.5f;
						Balls[a].cpos -= normalizeddif * distance_difference * 0.5f;

						float charge = (Balls[a].charge + Balls[i].charge) * 0.5f;
						Balls[a].charge = charge;
						Balls[i].charge = charge;
					}

					float force = force_coef * Balls[a].charge * Balls[i].charge / distsqr;
					glm::vec2 vecforce = normalizeddif * force ;



					Balls[a].acceleration -= vecforce;
					Balls[i].acceleration += vecforce;
				}
			}
			bool wallcolided = false;
			if (Balls[i].cpos.y > HEIGHT - Balls[i].r)
			{
				Balls[i].cpos.y = HEIGHT - Balls[i].r;
				wallcolided = true;
			}

			if (Balls[i].cpos.y < 0 + Balls[i].r)
			{
				Balls[i].cpos.y = 0 + Balls[i].r;
				wallcolided = true;
			}

			if (Balls[i].cpos.x > WIDTH - Balls[i].r)
			{
				Balls[i].cpos.x = WIDTH - Balls[i].r;
				wallcolided = true;
			}
			if (Balls[i].cpos.x < 0 + Balls[i].r)
			{
				Balls[i].cpos.x = 0 + Balls[i].r;
				wallcolided = true;
			}
			if (wallcolided)
			{
				Balls[i].charge -= 0.01;
			}





			for (int a = 0; a < StaticBalls.size(); a++)
			{
				glm::vec2 dif = Balls[i].cpos - StaticBalls[a].pos;
				float distsqr = dif.x * dif.x + dif.y * dif.y;
				float dist = sqrt(distsqr);
				glm::vec2 normalizeddif = dif / dist;

				if (distsqr < (Balls[i].r + StaticBalls[a].r) * (Balls[i].r + StaticBalls[a].r))
				{
					float dist = sqrt(distsqr);

					float distance_difference = Balls[i].r + StaticBalls[a].r - dist;

					glm::vec2 normalizeddif = dif / dist;

					Balls[i].cpos += normalizeddif * distance_difference * 0.5f;
					if (StaticBalls[a].charge != 0)
						Balls[i].charge += StaticBalls[a].charge;
				}

				float force = force_coef * (CentralCharge * Balls[i].charge) / distsqr;

				Balls[i].acceleration += normalizeddif * force;
			}


		}
		

		
		

		for (int a = 0; a < StaticBalls.size(); a++)
		{
			if (CentralCharge > 0)
				DrawCircle(StaticBalls[a].pos, StaticBalls[a].r, glm::vec4(CentralCharge/20000, 0.0f, 0.0f, 1.0f));

			if (CentralCharge == 0)
				DrawCircle(StaticBalls[a].pos, StaticBalls[a].r,  glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			if (CentralCharge < 0)
				DrawCircle(StaticBalls[a].pos, StaticBalls[a].r,  glm::vec4(0.0f, 0.0f, -CentralCharge/20000, 1.0f));
		}

		for (int i = 0; i < Balls.size(); i++)
		{
			if (Balls[i].charge>0)
				DrawCircle(Balls[i].cpos, Balls[i].r,glm::vec4(Balls[i].charge/20,0.0f,0.0f,1.0f));

			if (Balls[i].charge < 0)
				DrawCircle(Balls[i].cpos, Balls[i].r, glm::vec4(0.0f, 0.0f, Balls[i].charge /-10,1.0f));

			if (acceletrationlines)
				DrawLine(Balls[i].cpos, Balls[i].cpos + Balls[i].acceleration * 0.1f, 0.1f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		}

	}
	
};

int main()
{
	


	application app;
	app.init();
	
	
	return 0;
}