#include "engine/Components/Engine.h"


const float radius = 5;

const int Cellsx = 192/ (5 *0.1f);
const int Cellsy = 108 / (5 *0.1f) ;

float coolingspd = 0.1f;

float CellsSizex = (float)WIDTH / (float) Cellsx;
float CellsSizey = (float)HEIGHT / (float)Cellsy;

struct cell
{
	std::mutex m;
	std::vector <int> indexes;
	std::atomic<int> amount = 0;
	std::atomic<int> iter = 0;
};


class BallQuadTree
{
public:
	glm::vec2 Size = { 2000,1200 };
	glm::vec2 Position = { 0.0f,0.0f };

	std::vector <ball*> balls;

	BallQuadTree* Childs[4];

	cube quad;

	int Layers = 4;

	BallQuadTree(glm::vec2 size, glm::vec2 position, int layers)
	{
		Layers = layers;
		Position = position;
		Size = size;
		quad.position = position;
		quad.width = size.x;
		quad.height = size.y;
		if (layers <= 0)
			return;
		glm::vec2 hs = size * 0.5f;

		Childs[0] = new BallQuadTree(hs, position - hs, layers - 1);
		Childs[1] = new BallQuadTree(hs, position + hs, layers - 1);
		Childs[2] = new BallQuadTree(hs, position - glm::vec2(-hs.x,hs.y), layers - 1);
		Childs[3] = new BallQuadTree(hs, position + glm::vec2(-hs.x, hs.y), layers - 1);
		
	}

	void Insert(ball* b)
	{
		if (Layers <= 0)
		{
			balls.push_back(b);
			return;
		}

		
		if (CubeContainsBall(b, Childs[0]->quad))
			Childs[0]->Insert(b);
		else if (CubeContainsBall(b, Childs[1]->quad))
			Childs[1]->Insert(b);
		else if (CubeContainsBall(b, Childs[2]->quad))
			Childs[2]->Insert(b);
		else if (CubeContainsBall(b, Childs[3]->quad))
			Childs[3]->Insert(b);


		balls.push_back(b);
		return;
	}

	std::vector<ball*> Items()
	{
		std::vector<ball*> result;

		int s = result.size();
		result.resize(s + balls.size());
		for (int i = 0; i < balls.size(); i++)
			result[s + i] = balls[i];

		if (Layers > 0)
		{
			std::vector<ball*> c1 = Childs[0]->Items();
			s = result.size();
			result.resize(s + c1.size());
			for (int i = 0; i < c1.size(); i++)
				result[s + i] = c1[i];
			
			std::vector<ball*> c2 = Childs[1]->Items();
			s = result.size();
			result.resize(s + c2.size());
			for (int i = 0; i < c2.size(); i++)
				result[s + i] = c2[i];

			std::vector<ball*> c3 = Childs[2]->Items();
			s = result.size();
			result.resize(s + c3.size());
			for (int i = 0; i < c3.size(); i++)
				result[s + i] = c3[i];

			std::vector<ball*> c4 = Childs[3]->Items();
			s = result.size();
			result.resize(s + c4.size());
			for (int i = 0; i < c4.size(); i++)
				result[s + i] = c4[i];
		}

	}

	void Search(ball* b, std::vector<ball*>* result)
	{

		if (BtCCollisionCheck(b, quad))
		{
			/*
			int s = result->size();
			result->resize(s + balls.size());
			for (int i = 0; i < balls.size(); i++)
				(*result)[s + i] = balls[i];*/
			if (Layers > 0)
			{
				if (CubeContainsBall(b, Childs[0]->quad))
				{
					Childs[0]->Search(b, result);
				}
				else if (CubeContainsBall(b, Childs[1]->quad))
				{
					Childs[1]->Search(b, result);

				}
				else if (CubeContainsBall(b, Childs[2]->quad))
				{
					Childs[2]->Search(b, result);

				}
				else if (CubeContainsBall(b, Childs[3]->quad))
				{
					Childs[3]->Search(b, result);

				}
				/*else
				{
					std::vector<ball*> c1 = Items();
					s = result->size();
					result->resize(s + c1.size());
					for (int i = 0; i < c1.size(); i++)
						(*result)[s + i] = c1[i];
				}*/
			}
		}
		return;
	}


	void clear()
	{
		balls.clear();
		if (Layers > 0)
		{
			Childs[0]->clear();
			Childs[1]->clear();
			Childs[2]->clear();
			Childs[3]->clear();
		}
	}


	~BallQuadTree()
	{
		if (Layers <= 0)
			return;
		Childs[0]->~BallQuadTree();
		Childs[1]->~BallQuadTree();
		Childs[2]->~BallQuadTree();
		Childs[3]->~BallQuadTree();
		free(Childs[0]);
		free(Childs[1]);
		free(Childs[2]);
		free(Childs[3]);
	}
};

const int objAmount = 10000;

cell cells[Cellsx][Cellsy];


//ParticleEmiter pm;
ball objects[objAmount];
float Temperatures[objAmount];


ball megaball;

//VerletObject objects [objAmount];

unsigned int noizes[10];
unsigned int peepoo;
BallQuadTree bqt({ 960.0f ,540.0f }, { 1920.0f * 0.5f,1080 * 0.5f }, 6);

std::vector<std::thread> threads;
std::mutex* mutexes;
std::condition_variable* cvs;


std::vector<std::thread> threads2;
std::mutex* mutexes2;
std::condition_variable* cvs2;

bool stop = false;
std::mutex ProcessWait;
std::atomic<int> threadsDone = 0;
float subdt = 0.0f;

void Store(int thr)
{
	std::unique_lock<std::mutex> lm(mutexes2[thr]);
	cvs2[thr].wait(lm);

	int step = objAmount / threadcount;

	int sx = 0;
	int ex = 0;

	sx = step * thr;
	ex = step * (thr + 1);

	if (thr == 0)
		sx = 1;
	if (thr == threadcount - 1)
		ex = objAmount - 1;


	for (int i = sx; i < ex; i++)
	{
		BtBCollision(&megaball, &objects[i], 0.999f);
		Temperatures[i] -= subdt * Temperatures[i] * Temperatures[i] * coolingspd;
		if (Temperatures[i] < 0.1f)Temperatures[i] = 0.1f;
		glm::vec2 grav = glm::vec2(0.0f, -250.0f);


		objects[i].Force = (grav);
		objects[i].Process(subdt);



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

		int x = (int)objects[i].position.x / CellsSizex;
		int y = (int)objects[i].position.y / CellsSizey;

		if (x >= 0 && x < Cellsx && y >= 0 && y < Cellsy)
		{
			cells[x][y].m.lock();
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
			cells[x][y].m.unlock();
		}
	}
	threadsDone += 1;

}

void PB(int thr)
{
	std::unique_lock<std::mutex> lm(mutexes[thr]);
	cvs[thr].wait(lm);

	int step = Cellsx / threadcount;

	int sx = 0;
	int ex = 0;



	sx = step * thr;
	ex = step * (thr + 1);

	if (thr == 0)
		sx = 1;
	if (thr == threadcount - 1)
		ex = Cellsx - 1;

	//std::cout << "thr " << thr << "   sx=" << sx<< "   ex="<<ex<<'\n';
	for (int x = sx; x < ex; x++)
		for (int y = 1; y < Cellsy - 1; y++)
		{
			//std::vector <int> tmp;

			int tmp[100];
			int tmpiter = 0;;
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++)
					for (int i = 0; i < cells[x + dx][y + dy].iter; i++)
					{
						tmp[tmpiter] = cells[x + dx][y + dy].indexes[i];
						tmpiter++;
					}

			for (int i = 0; i < tmpiter; i++)
				for (int a = i + 1; a < tmpiter; a++)
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

					glm::vec2 vel1 = objects[tmp[i]].velocity;
					glm::vec2 vel2 = objects[tmp[a]].velocity;

					BtBCollision(&objects[tmp[i]], &objects[tmp[a]], 0.999f);

					if (vel1 != objects[tmp[i]].velocity)
					{
						Temperatures[tmp[i]] += sqrlength(objects[tmp[i]].velocity - vel1) * 0.001f;
						Temperatures[tmp[a]] += sqrlength(objects[tmp[i]].velocity - vel2) * 0.001f;
					}
				}
			tmpiter = 0;
		}
	threadsDone+=1;
}

void ProcessStore(int thr)
{
	while (!stop)
	{
		Store(thr);
	}
}

void ProcessBalls(int thr)
{
	while (!stop)
	{
		PB(thr);
	}
}

void On_Create()
{
	for (int i = 0; i < 10; i++)
	{
		GenNoizeTexture(&noizes[i], 100, 1, 5);
		//pm.textures.push_back(noizes[i]);
	}
	/*LoadTexture("container.jpg", &noizes[0]);
	pm.textures.push_back(noizes[0]);

	LoadTexture("awesomeface.png", &noizes[1]);
	pm.textures.push_back(noizes[1]);*/
	LoadTexture("Screenshot_1.png", &peepoo);

	

	/*pm.EndSize = glm::vec2(100, 100);
	pm.EndColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

	pm.ShowWindow = true;
	pm.Type = "LINE";*/
	//VerletObject b;
	ball b;
	CellsSizex = (float)WIDTH / (float)Cellsx;
	CellsSizey = (float)HEIGHT / (float)Cellsy;

	for (int i = 0; i < objAmount; i++)
	{
		/*b.ppos = glm::vec2(rand() % WIDTH , rand() % HEIGHT );
		b.cpos = b.ppos;*/
		b.position = glm::vec2(rand() % WIDTH, rand() % HEIGHT);
		//b.velocity = glm::vec2(rand() % 100 - 100* 0.5f, rand() % 100 - 100 * 0.5f);
		b.r = radius;
		objects[i] = b;
		Temperatures[i] = 0.0f;
	}
	megaball.r = 100.0f;
	megaball.mass = 100.0f;
	megaball.position = glm::vec2(WIDTH * 0.5f, -HEIGHT * 2.5f);
	megaball.velocity = glm::vec2(250, -2500);

	CameraPosition = glm::vec2(WIDTH * 0.5f, HEIGHT * 0.5f);

	std::cout << "x= " << Cellsx << " y= " << Cellsy << "\n";
	std::cout << "sx= " << CellsSizex << " sy= " << CellsSizey << "\n";
	std::cout << "Scrsizex = " << CellsSizex * Cellsx << " Scrsizey = " << CellsSizey * Cellsy << "\n";
	std::cout << "TrueScrsizex = " << WIDTH << " TrueScrsizey = " << HEIGHT << "\n";
	BackgroundColor = glm::vec4(0.0f);
	//AmbientLight = 0.01f;
	//bloomIntensity = 1.0f;


	mutexes2 = new std::mutex[threadcount];
	cvs2 = new std::condition_variable[threadcount];

	mutexes = new std::mutex[threadcount];
	cvs = new std::condition_variable[threadcount];
	for (int i = 0; i < threadcount; i++)
	{
		threads.push_back(std::thread(ProcessBalls, i));
		threads2.push_back(std::thread(ProcessStore, i));
	}


	glfwSwapInterval(0);
	VSync = false;


}

int amopunt = 3;
float dt = 0.0f;
int substeps = 16;

void On_Update()
{


	//for (int a = 0; a < 4; a++)
	//{
	//	for (int b = 0; b < 4; b++)
	//	{
	//		for (int c = 0; c < 4; c++)
	//		{
	//			for (int d = 0; d < 4; d++)
	//			{
	//				for (int e = 0; e < 4; e++)
	//				{
	//					for (int f = 0; f < 4; f++)
	//					{
	//						/*for (int g = 0; g < 4; g++)
	//						{
	//							DrawCircle(bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Childs[e]->Childs[f]->Childs[g]->Position, 1);
	//						}*/
	//						DrawCube(bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Childs[e]->Childs[f]->quad.position,
	//							glm::vec2(bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Childs[e]->Childs[f]->quad.width, bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Childs[e]->Childs[f]->quad.height)*0.75f,0.0f,glm::vec4(1.0f,1.0f,1.0f,0.1f));
	//						//DrawCircle(bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Childs[e]->Childs[f]->Position, 2);
	//					}
	//					//DrawCircle(bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Childs[e]->Position, 4);
	//				}
	//				//DrawCircle(bqt.Childs[a]->Childs[b]->Childs[c]->Childs[d]->Position, 8);
	//			}
	//			//DrawCircle(bqt.Childs[a]->Childs[b]->Childs[c]->Position, 16);
	//		}
	//		//DrawCircle(bqt.Childs[a]->Childs[b]->Position, 32);
	//	}
	//	//DrawCircle(bqt.Childs[a]->Position, 64);
	//}
	if (keys[GLFW_KEY_0])
		CameraScale *= 0.99f;
	ImGui::Begin("data");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate);
	ImGui::Text("balls Amount %i", objAmount);
	ImGui::SliderInt("substeps", &substeps, 1, 16);
	ImGui::SliderFloat("dt ", &dt, 0.001, 0.034f);


	subdt = dt / substeps;
	glm::vec2 mid = glm::vec2(0.0f);
	mid = MousePosition;

	

	megaball.Force = { 0.0f,0.0f };
	if (keys[GLFW_KEY_W])
		megaball.Force.y = 100000;
	if (keys[GLFW_KEY_S])
		megaball.Force.y = -100000;
	if (keys[GLFW_KEY_D])
		megaball.Force.x = 100000;
	if (keys[GLFW_KEY_A])
		megaball.Force.x = -100000;
	if (keys[GLFW_KEY_LEFT_SHIFT])
		megaball.Force *= 100.0f;
	megaball.Force.y -= 2500.0f;


	if (keys[GLFW_KEY_SPACE])
	{
		megaball.position = glm::vec2(WIDTH * 0.0f, HEIGHT * 1.0f);
		megaball.velocity = glm::vec2(5000, -5000);
		for (int i = 0; i < objAmount; i++)
			Temperatures[i] = 0.1f;
	}


	/*for (int i = 0; i < objAmount; i++)
		bqt.Insert(&objects[i]);

	for (int i = 0; i < objAmount; i++)
	{
		if (BalltoPointCollisionCheck(objects[i], MousePosition))
		{
			DrawCircle(objects[i], glm::vec4(0.0f, 3.0f, 0.0f, 1.0f), false, NULL, 1000);

			std::vector<ball*> res;

			bqt.Search(&objects[i],&res);

			for(int a=0;a<res.size();a++)
				DrawCircle(*res[a], glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), false, NULL, 1000);

		}
	}

	bqt.clear();*/
	for (int s = 0; s < substeps; s++)
	{
		//std::cout << "mod x = " << mid.x << " y = " << mid.y << "\n";
		megaball.Process(subdt);
		
	
		threadsDone = 0;

		for (int i = 0; i < threadcount; i++)
		{
			std::unique_lock<std::mutex> lm(mutexes2[i]);
			cvs2[i].notify_one();
		}
		while (threadsDone != threadcount);

		threadsDone = 0;

		for (int i = 0; i < threadcount; i++)
		{
			std::unique_lock<std::mutex> lm(mutexes[i]);
			cvs[i].notify_one();
		}
		while(threadsDone!=threadcount);



		for (int x = 0; x < Cellsx; x++)
			for (int y = 0; y < Cellsy; y++)
			{
				//DrawCube(glm::vec2(x * CellsSizex, y * CellsSizey), glm::vec2(CellsSizex, CellsSizey), glm::vec3(0.0f), glm::vec4(1.0f, 0.0f, 0.0f, cells[x][y].size() / 100.0f));
				cells[x][y].iter = 0;
			}




	}
	DrawLight(megaball.position, glm::vec2(1000.0f), glm::vec4(1.0f), 0.0f, 0.0f);
	DrawCircle(megaball, glm::vec4(2.0f, 0.4f, 0.08f, 1.0f));
	DrawLine(megaball.position, megaball.position - megaball.velocity * 0.1f, megaball.r, glm::vec4(2.0f, 0.4f, 0.08f, 1.0f));

	for (int i = 0; i < objAmount; i++)
	{//DrawTexturedQuad(objects[i].position, glm::vec2(objects[i].r), peepoo , glm::vec3(0.0f), glm::vec4(0.0f, 0.0f, 20.0f, 1.0f));
		if (Temperatures[i] < 0.1f)Temperatures[i] = 0.1f;
		if (Temperatures[i] > 10000.1f)Temperatures[i] = 10000.1f;
		DrawCircle(objects[i].position, objects[i].r, glm::vec4(2.0f * Temperatures[i] * 0.002f, 0.4f * Temperatures[i] * 0.002f, 0.08f * Temperatures[i] * 0.002f, 1.0f), true);
		DrawLine(objects[i].position, objects[i].position - objects[i].velocity * 0.02f, objects[i].r, glm::vec4(2.0f * Temperatures[i] * 0.002f, 0.4f * Temperatures[i] * 0.002f, 0.08f * Temperatures[i] * 0.002f, 1.0f));
		//DrawCircle(objects[i].position, objects[i].r, glm::vec4(1.0f,1.0f,1.0f,1.0f), true);
	}
	//pm.Process(delta);

}

int main()
{


	initEngine("pog",1920,1020);

	
	stop = true;

	for (int i = 0; i < threads.size(); i++)
	{

		std::unique_lock<std::mutex> lm2(mutexes2[i]);
		cvs2[i].notify_one();



		std::unique_lock<std::mutex> lm(mutexes[i]);
		cvs[i].notify_one();
		threads2[i].join();
		threads[i].join();

	}
	//std::cout << "input screen width";
	//int wi = 0;
	//std::cin >> wi;
	//std::cout << "input screen height";
	//int he = 0;
	//std::cin >> he;
	//bool fs = false;
	//std::cout << "Full screen? (1-yes/0-no)";
	//std::cin >> fs;
	//initEngine("Space Partitioning test", wi, he, fs);
	return 0;
}