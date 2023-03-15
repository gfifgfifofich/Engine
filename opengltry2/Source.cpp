
#include "engine/Components/Engine.h"
#include <thread>

float force_coef = 1.0f;

float g = 000.0f;
float friction = 0.998f;

bool acceletrationlines = false;



struct VerletObject
{
	float r = 10;
	float friction = friction;

	glm::vec4 color = glm::vec4(1.0f);
	glm::vec2 ppos = glm::vec2(0.0f);
	glm::vec2 cpos = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 acceleration = glm::vec2(0.0f);
	float deltatime = dt_of_sim;
	void UpdatePos()
	{
		velocity = (cpos - ppos) *friction;

		ppos = cpos;


		cpos = cpos + velocity + (acceleration * deltatime * deltatime);


		acceleration = glm::vec2(0.0f);
	}

};


struct rope
{
	std::vector <VerletObject> joints;
	int size = 0;

	glm::vec4 color = glm::vec4(1.0f);

	void Create(int siz, glm::vec2 start, glm::vec2 end)
	{
		size = siz;
		joints.clear();
		float oneovsize = 1.0f / siz;
		for (int i = 0; i < siz; i++)
		{
			VerletObject a;
			float state = i * oneovsize;


			glm::vec2 avec2 = start * (1 - state) + end * state;
			//std::cout << "i = " << i << "   x = " << avec2.x << "   y = " << avec2.y << "   state = "<<state << std::endl;
			a.cpos = avec2;
			a.ppos = a.cpos;
			joints.push_back(a);
		}
	}
};





rope Rope1;
class application : public Engine
{


	void On_Create() override
	{

		Rope1.Create(5, glm::vec2(590, 240), glm::vec2(580, 640));
		substeps = 5;
	}

	glm::vec4 testColor = glm::vec4(1.0f);


	

	void On_Update() override
	{
		ImGui::Begin("SceneSettings");


		ImGui::SliderFloat("Speed of Sim", &dt_of_sim, 0.001f, 0.3f);

		ImGui::SliderInt("substeps/frame", &substeps, 1, 50);
		
		ImGui::SliderFloat("coeficient", &force_coef, 0.1, 1000);

		ImGui::SliderFloat(" g", &g, 0, 10000);
		


		// color
		ImGui::SliderFloat(" colr r", &testColor.x, 0, 10);
		ImGui::SliderFloat(" colr g", &testColor.y, 0, 10);
		ImGui::SliderFloat(" colr b", &testColor.z, 0, 10);
		ImGui::SliderFloat(" colr a", &testColor.w, 0, 2);

		if (ImGui::Button("acceleration lines"))
		{
			acceletrationlines = !acceletrationlines;
		}

		//ImGui::Text("Balls count %i", Balls.size());

		if (ImGui::Button("Show Main Settings Window"))
			SettingsWindow = !SettingsWindow;
		
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate);
		
		ImGui::End();

		//DrawCircle(glm::vec2(WIDTH * 0.5, HEIGHT * 0.5), 0, 100.01f, testColor);


		
		if (keys[GLFW_KEY_SPACE])
		{
			friction = 0.9f;
		}
		else friction = 0.998f;
		
		





		for (int s = 0; s < substeps; s++)
		{
			for (int i = 0; i < Rope1.size; i++)
			{
				Rope1.joints[i].deltatime = dt_of_sim/substeps;
				Rope1.joints[i].friction = friction;
				if (i != 0 )
				{
					for (int a = 0; a < Rope1.size; a++)
					{
						if (a != i)
						{
							glm::vec2 dif = Rope1.joints[i].cpos - Rope1.joints[a].cpos;
							float distsqr = dif.x * dif.x + dif.y * dif.y;

							if (distsqr < (Rope1.joints[i].r + Rope1.joints[a].r) * (Rope1.joints[i].r + Rope1.joints[a].r))
							{

								float dist = sqrt(distsqr);
								glm::vec2 normalizeddif = dif / dist;
								float distance_difference = Rope1.joints[i].r + Rope1.joints[a].r - dist;

								Rope1.joints[i].cpos += normalizeddif * distance_difference*0.5f;
								Rope1.joints[a].cpos -= normalizeddif * distance_difference * 0.5f;

							}

							
						}
					}

					glm::vec2 Force = glm::vec2(0.0f);

					Rope1.joints[i].acceleration += glm::vec2(0.0f, -g);
					//float f1 = length(Rope1.joints[i].cpos - (Rope1.joints[i - 1].cpos + glm::vec2(Rope1.joints[i - 1].r * 2.01f, 0.f))  );
					/*float f2 = 0.0f;
					if( i != Rope1.size - 1)
						 f2 = length(Rope1.joints[i].cpos - Rope1.joints[i + 1].cpos);*/
					glm::vec2 target = glm::vec2(0.0f);

					if (i==1)  target = glm::vec2(Rope1.joints[i - 1].r * 3.05f, Rope1.joints[i - 1].r * 3.05f);
					else 
					{
						target = (Normalize(Rope1.joints[i - 1].cpos - Rope1.joints[i - 2].cpos)*Rope1.joints[i - 1].r *3.05f);
						//DrawCircle(Rope1.joints[i].cpos + target, 10.0f,0.001f,glm::vec4(1.0f,i,0.5f,1.0f));
					}
					glm::vec2 dif = (Rope1.joints[i - 1].cpos + target);


					glm::vec2 POg = (Rope1.joints[i].cpos - dif);


					Force = ( -POg) * force_coef;// +f2 * -Normalize(Rope1.joints[i].cpos - Rope1.joints[i + 1].cpos)) * force_coef;//  


					Rope1.joints[i].acceleration += Force* friction;
					if (i - 1>=0)
						Rope1.joints[i-1].acceleration -= Force* friction;

					if (acceletrationlines)
					{
						DrawLine(Rope1.joints[i].cpos, Rope1.joints[i].cpos + Rope1.joints[i].acceleration *0.01f, 0.1f, glm::vec4(1.0f, i/2.5f, (5-i) / 2.5f, 1.0f));
					}
					
				}

				/*if (i == Rope1.size - 1)
				{
					Rope1.joints[i].cpos = MousePosition;
				}*/
				if (i == 0)
				{
					Rope1.joints[i].cpos = glm::vec2(590, 540);
				}
				Rope1.joints[i].UpdatePos();
			}
		}




		
		for (int i = 0; i < Rope1.size; i++)
		{
			
				
			
			if(i != Rope1.size-1)
			{
				DrawLine(Rope1.joints[i].cpos, Rope1.joints[i + 1].cpos,0.5f, testColor);
			}
			else
			{
				DrawLine(Rope1.joints[i].cpos, Rope1.joints[i].cpos, 0.5f, testColor);
			}
				DrawCircle(Rope1.joints[i].cpos, Rope1.joints[i].r, 2.1f, testColor);

		}

	}

};

int main()
{



	application app;
	app.init();


	return 0;
}