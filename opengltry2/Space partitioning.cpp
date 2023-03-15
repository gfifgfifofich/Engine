#include "engine/Components/Engine.h"


const int Cellsx = 128*4.0f;
const int Cellsy =98 *4.0f ;


float CellsSizex = (float)WIDTH / (float) Cellsx;
float CellsSizey = (float)HEIGHT / (float)Cellsy;

struct cell
{
	std::vector <int> indexes;
	int amount = 0;
	int iter = 0;
};

const int objAmount = 5000;

cell cells[Cellsx][Cellsy];

int tmp[100];
int tmpiter = 0;;

ParticleEmiter pm;

class application : public Engine
{
	


	//VerletObject objects [objAmount];
	ball objects[objAmount];

	unsigned int noizes[10];
	unsigned int peepoo;

	void On_Create() override
	{
		for (int i = 0; i < 10; i++)
		{
			GenNoizeTexture(&noizes[i], 100, 1, 5);
			pm.textures.push_back(noizes[i]);
		}
		/*LoadTexture("container.jpg", &noizes[0]);
		pm.textures.push_back(noizes[0]);

		LoadTexture("awesomeface.png", &noizes[1]);
		pm.textures.push_back(noizes[1]);*/
		LoadTexture("Screenshot_1.png", &peepoo);

		pm.EndSize = glm::vec2(100, 100);
		pm.EndColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

		pm.ShowWindow = true;
		pm.Type = "LINE";
		//VerletObject b;
		ball b;
		CellsSizex = (float)WIDTH / (float)Cellsx;
		CellsSizey = (float)HEIGHT / (float)Cellsy;

		for (int i = 0; i < objAmount; i++)
		{
			/*b.ppos = glm::vec2(rand() % WIDTH , rand() % HEIGHT );
			b.cpos = b.ppos;*/
			b.position= glm::vec2(rand() % WIDTH, rand() % HEIGHT);
			//b.velocity = glm::vec2(rand() % 100 - 100* 0.5f, rand() % 100 - 100 * 0.5f);
			b.r = 2.5;
			objects[i] = b;
		}
		CameraPosition = glm::vec2(WIDTH*0.5f,HEIGHT * 0.5f);

		std::cout << "x= " << Cellsx << " y= " << Cellsy<< "\n";
		std::cout << "sx= " << CellsSizex << " sy= " << CellsSizey << "\n";
		std::cout << "Scrsizex = " << CellsSizex * Cellsx << " Scrsizey = " << CellsSizey* Cellsy << "\n";
		std::cout << "TrueScrsizex = " << WIDTH << " TrueScrsizey = " << HEIGHT << "\n";
		BackgroundColor = glm::vec4(0.0f);
	}
	int amopunt = 3;
	void On_Update() override
	{
		ImGui::Begin("data");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate);
		ImGui::Text("balls Amount %i",objAmount);
		ImGui::SliderInt("Amount ", &amopunt,0,100);


		float subdt = 0.017f / 4;
		glm::vec2 mid = glm::vec2(0.0f);
		mid = MousePosition;

		if (JustPressedLMB)
			pm.Spawn(MousePosition, amopunt);

		for (int i = 0; i < objAmount; i++) 
		{
			//pm.Spawn(objects[i].position, amopunt);

			if (keys[GLFW_KEY_1])
			{
				std::cout << "ball x = " << objects[i].position.x << " y = " << objects[i].position.y << "\n";
			}
		}/*
		for(int i=0;i< amopunt;i++)
			pm.Spawn(glm::vec2(rand() % WIDTH,rand()%200), 3);*/
		for (int s = 0; s < 4; s++) 
		{
			//std::cout << "mod x = " << mid.x << " y = " << mid.y << "\n";

			for (int i = 0; i < objAmount; i++)
			{

				glm::vec2 grav = (mid - objects[i].position)*0.00001f;
				
				float l = length(grav);
				grav /= l;
				if (l > 200 * 0.00001f)
					l = 0.001f / (l * l);
				else l = 0.0f;
				objects[i].Force = (grav *l);

			/*	objects[i].deltatime = subdt;
				objects[i].UpdatePos();*/
				objects[i].Process(subdt);

				DrawCircle(objects[i].position, objects[i].r, glm::vec4(4.0f, 0.8f, 0.16f, 1.0f));


				if (objects[i].position.x + objects[i].r > WIDTH)
				{
					objects[i].position.x = WIDTH - objects[i].r;
					//objects[i].ppos.x = WIDTH - objects[i].r;
					objects[i].velocity.x *= -0.0;
				}
				if (objects[i].position.x - objects[i].r < 0)
				{
					objects[i].position.x = objects[i].r;
					//objects[i].ppos.x = objects[i].r;
					objects[i].velocity.x *= -0.0;
				}
				if (objects[i].position.y - objects[i].r < 0)
				{
					objects[i].position.y = objects[i].r;
					//objects[i].ppos.y = objects[i].r;
					objects[i].velocity.y *= -0.0;
				}
				if (objects[i].position.y + objects[i].r > HEIGHT)
				{
					objects[i].position.y = HEIGHT - objects[i].r;
					//objects[i].ppos.y = HEIGHT - objects[i].r;
					objects[i].velocity.y *= -0.0;
				}

				int x = objects[i].position.x / CellsSizex;
				int y = objects[i].position.y / CellsSizey;
				
				if (x >= 0 && x < Cellsx && y >= 0 && y < Cellsy)
				{


					if (cells[x][y].iter >= cells[x][y].amount)
					{
						cells[x][y].indexes.push_back(i);
						cells[x][y].amount++;
					}
					else
					{
						cells[x][y].indexes[cells[x][y].iter] = i;
					}
					cells[x][y].iter++;
				}
			}
			for (int x = 1; x < Cellsx-1; x++)
				for (int y = 1; y < Cellsy-1; y++)
				{
					//std::vector <int> tmp;

					for (int dx = -1; dx <= 1; dx++)
						for (int dy = -1; dy <= 1; dy++)
							for (int i = 0; i < cells[x + dx][y + dy].iter; i++)
							{
								tmp[tmpiter] = cells[x + dx][y + dy].indexes[i];
								tmpiter++;
							}

					for (int i = 0; i < tmpiter; i++)
						for (int a = i+1; a < tmpiter; a++)
						{


							/*glm::vec2 dif = objects[tmp[a]].cpos - objects[tmp[i]].cpos;
							if (dif.x * dif.x + dif.y * dif.y < (objects[tmp[i]].r + objects[tmp[a]].r) * (objects[tmp[i]].r + objects[tmp[a]].r))
							{
								float dist = length(dif);
								float distancedifference = (objects[tmp[i]].r + objects[tmp[a]].r) - dist;
								glm::vec2 n1 = dif / dist;
								objects[tmp[i]].cpos -= distancedifference*n1 * 0.5f;
								objects[tmp[a]].cpos += distancedifference * n1 * 0.5f;


							}*/
							BtBCollision(&objects[tmp[i]], &objects[tmp[a]],0.999f);
						}
					tmpiter = 0;
				}

			for (int x = 0; x < Cellsx; x++)
				for (int y = 0; y < Cellsy; y++)
				{
					//DrawCube(glm::vec2(x * CellsSizex, y * CellsSizey), glm::vec2(CellsSizex, CellsSizey), glm::vec3(0.0f), glm::vec4(1.0f, 0.0f, 0.0f, cells[x][y].size() / 100.0f));
					cells[x][y].iter = 0;
				}

		
			

		}
		


		//for (int i = 0; i < objAmount; i++)
			//DrawTexturedQuad(objects[i].position, glm::vec2(objects[i].r), peepoo);// , glm::vec3(0.0f), glm::vec4(0.0f, 0.0f, 20.0f, 1.0f));

			//DrawCircle(objects[i].position, objects[i].r, glm::vec4(2.0f,0.4f,0.08f,1.0f));

		pm.Process(delta);

	}
};

int main()
{


	application app;
	app.init("pog",1280,980);
	return 0;
}