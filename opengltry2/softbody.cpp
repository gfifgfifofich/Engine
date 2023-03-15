#include "engine/Components/Engine.h"

#include "engine/Components/Physics/SoftBody.h"



const int WorldSizeX = 500;
const int WorldSizeY = 1;

float Noize1[WorldSizeX][WorldSizeY];
float Noize2[WorldSizeX][WorldSizeY];
float BufferNoize[WorldSizeX][WorldSizeY];


float mod = 1000.0f;
float modx = 100.0f;
int  Smoooothness = 1;


int Stage = 1;
const int amount = 8;


float size = 100.0f;
float stiffness = 0.0f;

int substeps = 8;


void UpdateWorld()
{
	for (int i = 0; i < WorldSizeX; i++) BufferNoize[i][0] = Noize1[i][0];// Store last piece in buffer

	//Perlin noize
		//generate white noise
	for (int i = 1; i > 0; i--)
		for (int x = 0; x < WorldSizeX / (i); x++)
			for (int y = 0; y < WorldSizeY / (i); y++)
			{
				float noise = float(rand() % 10) / (15 + i);
				for (int px = 0; px < i; px++)
					for (int py = 0; py < i; py++)
						Noize1[(x * i) + px][(y * i) + py] = noise;
			}

	//Linearly interpolate values, for smoooooooooth
	for (int i = 0; i < Smoooothness; i++)
	{
		for (int x = 1; x < WorldSizeX - 1; x++)
			for (int y = 0; y < WorldSizeY; y++)
			{
				Noize2[x][y] = (Noize1[x - 1][y + 1] + Noize1[x][y + 1] + Noize1[x + 1][y + 1] +
					Noize1[x - 1][y] + Noize1[x][y] + Noize1[x + 1][y] +
					Noize1[x - 1][y - 1] + Noize1[x][y - 1] + Noize1[x + 1][y - 1]) / 9.0f;

			}
		for (int x = 0; x < WorldSizeX; x++)
			for (int y = 0; y < WorldSizeY; y++)
			{
				Noize1[x][y] = Noize2[x][y];
			}
	}


}

class application : public Engine
{
public:
	float g = 1000;

	SoftBody wheel1;
	SoftBody wheel2;

	SoftBody Body;

	cube floor;
	ball center;

	void On_Create() override
	{//initialize
		
		floor.position -= 4000.0f;

		floor.width = 5000.0f;
		floor.height = 5000.0f;

		center.roughness = 0.1f;
		center.bounciness = 0.1f;
		center.r = 10.0f;
		center.FixedRotation = true;

		ball b;
		b.roughness = 0.1f;
		b.bounciness = 0.1f;
		b.r = 10.0f;
		b.FixedRotation = true;
		b.mass = 0.1f;
		for (int i = 0; i < amount; i++)
		{
			wheel1.balls.push_back(b);
			float angle = (i * 2 * pi) / amount;
			wheel1.balls[i].position = Rotate(glm::vec2(size, 0.0f), angle) + glm::vec2(2900, 450);
		}
		b.position = glm::vec2(2900, 450);
		wheel1.balls.push_back(b);

		

		if (wheel1.balls.size() == 4)
		{
			wheel1.springs.push_back(glm::ivec3(0, 1, 100));
			wheel1.springs.push_back(glm::ivec3(0, 2, 141));
			wheel1.springs.push_back(glm::ivec3(0, 3, 100));

			wheel1.springs.push_back(glm::ivec3(1, 3, 141));
			wheel1.springs.push_back(glm::ivec3(1, 2, 100));

			wheel1.springs.push_back(glm::ivec3(2, 3, 100));
		}
		if(wheel1.balls.size() ==9)
		{
			wheel1.springs.push_back(glm::ivec3(0, 2, 100 * sqrt(2)));
			wheel1.springs.push_back(glm::ivec3(0, 3, 100 * 2));
			wheel1.springs.push_back(glm::ivec3(0, 5, 100 * 2));
			wheel1.springs.push_back(glm::ivec3(0, 6, 100 * sqrt(2)));

			wheel1.springs.push_back(glm::ivec3(1, 3, 100 * sqrt(2)));
			wheel1.springs.push_back(glm::ivec3(1, 4, 100 * 2));
			wheel1.springs.push_back(glm::ivec3(1, 6, 100 * 2));
			wheel1.springs.push_back(glm::ivec3(1, 7, 100 * sqrt(2)));

			wheel1.springs.push_back(glm::ivec3(2, 4, 100 * sqrt(2)));
			wheel1.springs.push_back(glm::ivec3(2, 5, 100 * 2));
			wheel1.springs.push_back(glm::ivec3(2, 7, 100 * 2));
			wheel1.springs.push_back(glm::ivec3(2, 0, 100 * sqrt(2)));

			wheel1.springs.push_back(glm::ivec3(3, 5, 100 * sqrt(2)));
			wheel1.springs.push_back(glm::ivec3(3, 6, 100 * 2));

			wheel1.springs.push_back(glm::ivec3(4, 6, 100 * sqrt(2)));
			wheel1.springs.push_back(glm::ivec3(4, 7, 100 * 2));

			wheel1.springs.push_back(glm::ivec3(5, 7, 100 * sqrt(2)));

			wheel1.springs.push_back(glm::ivec3(0, 1, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(1, 2, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(2, 3, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(3, 4, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(4, 5, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(5, 6, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(6, 7, 100 * 0.73));
			wheel1.springs.push_back(glm::ivec3(7, 0, 100 * 0.73));


			wheel1.springs.push_back(glm::ivec3(0, 8, 100));
			wheel1.springs.push_back(glm::ivec3(1, 8, 100));
			wheel1.springs.push_back(glm::ivec3(2, 8, 100));
			wheel1.springs.push_back(glm::ivec3(3, 8, 100));
			wheel1.springs.push_back(glm::ivec3(4, 8, 100));
			wheel1.springs.push_back(glm::ivec3(5, 8, 100));
			wheel1.springs.push_back(glm::ivec3(6, 8, 100));
			wheel1.springs.push_back(glm::ivec3(7, 8, 100));



		}
		wheel2 = wheel1;

		for (int i = 0; i < wheel2.balls.size(); i++)
			wheel2.balls[i].position += glm::vec2(400, 0.0f);


		b.mass = 1.0f;

		float bodyLenght = 500;
		b.position = glm::vec2(2850, 530);
		Body.balls.push_back(b);
		b.position = glm::vec2(2850, 630);
		Body.balls.push_back(b);
		b.position = glm::vec2(2850+ bodyLenght, 530);
		Body.balls.push_back(b);
		b.position = glm::vec2(2850+ bodyLenght, 630);
		Body.balls.push_back(b);

		glm::vec2 m = glm::vec2(0.0f);
		for (int i = 0; i < Body.balls.size(); i++)
			m += Body.balls[i].position;
		m /= Body.balls.size();
		b.position = m;
		Body.balls.push_back(b);


		b.position = m + glm::vec2(0.0f,100.0f);
		Body.balls.push_back(b);
		b.position = m - glm::vec2(0.0f, 100.0f);
		Body.balls.push_back(b);


		float diaglenght = sqrt(bodyLenght * bodyLenght + 100 * 100);

		Body.springs.push_back(glm::ivec3(0, 1, 100));
		Body.springs.push_back(glm::ivec3(0, 2, diaglenght));
		Body.springs.push_back(glm::ivec3(0, 3, bodyLenght));

		Body.springs.push_back(glm::ivec3(1, 3, diaglenght));
		Body.springs.push_back(glm::ivec3(1, 2, bodyLenght));

		Body.springs.push_back(glm::ivec3(2, 3, 100));

		Body.springs.push_back(glm::ivec3(0, 4, diaglenght * 0.4f));
		Body.springs.push_back(glm::ivec3(1, 4, diaglenght * 0.4f));
		Body.springs.push_back(glm::ivec3(2, 4, diaglenght * 0.4f));
		Body.springs.push_back(glm::ivec3(3, 4, diaglenght * 0.4f));

		Body.springs.push_back(glm::ivec3(0, 5, length(Body.balls[0].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(1, 5, length(Body.balls[1].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(2, 5, length(Body.balls[2].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(3, 5, length(Body.balls[3].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(4, 5, 100));

		Body.springs.push_back(glm::ivec3(0, 6, length(Body.balls[0].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(1, 6, length(Body.balls[1].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(2, 6, length(Body.balls[2].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(3, 6, length(Body.balls[3].position - Body.balls[5].position)));
		Body.springs.push_back(glm::ivec3(4, 6, 100));
		Body.springs.push_back(glm::ivec3(5, 6, 200));

		Body.absorption = 2.0f;
		Body.deformation = true;
		Body.deformationCoefficient = 1.0f;
		Body.deformationRadius = 10.0f;
		//Perlin noize
		//generate white noise
		for (int i = 1; i > 0; i--)
			for (int x = 0; x < WorldSizeX / (i); x++)
				for (int y = 0; y < WorldSizeY / (i); y++)
				{
					float noise = float(rand() % 10) / (15 + i);
					for (int px = 0; px < i; px++)
						for (int py = 0; py < i; py++)
							Noize1[(x * i) + px][(y * i) + py] = noise;
				}

		//Linearly interpolate values, for smoooooooooth
		for (int i = 0; i < Smoooothness; i++)
		{
			for (int x = 1; x < WorldSizeX - 1; x++)
				for (int y = 0; y < WorldSizeY; y++)
				{
					Noize2[x][y] = (Noize1[x - 1][y + 1] + Noize1[x][y + 1] + Noize1[x + 1][y + 1] +
						Noize1[x - 1][y] + Noize1[x][y] + Noize1[x + 1][y] +
						Noize1[x - 1][y - 1] + Noize1[x][y - 1] + Noize1[x + 1][y - 1]) / 9.0f;

				}
			for (int x = 0; x < WorldSizeX; x++)
				for (int y = 0; y < WorldSizeY; y++)
				{
					Noize1[x][y] = Noize2[x][y];
					BufferNoize[x][y] = Noize2[x][y];
				}
		}

		//Drawing order, (circles, then quads -> quads above circles)
		substeps = 32;
		DrawingOrder = false;
		//dt_of_sim = 0.0f;
	}

	glm::ivec3 tmp;
	int iter=0;

	float absorption = 1.0f;
	float stiffnes = 10000.0f;

	void On_Update() override
	{

		glm::vec2 md = glm::vec2(0.0f);

		
		if (buttons[GLFW_MOUSE_BUTTON_2])
		{
			/*for(int i=0;i< wheel1.balls.size();i++)
				wheel1.balls[i].velocity -= wheel1.balls[i].position - MousePosition;
			for (int i = 0; i < wheel2.balls.size(); i++)
				wheel2.balls[i].velocity -= wheel2.balls[i].position - MousePosition;*/

			for (int i = 0; i < Body.balls.size(); i++)
				md += Body.balls[i].position ;
			md /= Body.balls.size();
			md -= MousePosition;
		}

		ImGui::Begin("pog");
		ImGui::SliderFloat(" stiffness", &wheel1.stiffness,0.0f,100000.0f);
		ImGui::SliderFloat(" absorption", &wheel1.absorption,0.0f,10.0f);
		ImGui::SliderFloat(" friction", &wheel1.friction,0.0f,10.0f);
		ImGui::SliderFloat(" g", &g,0.0f,1000.0f);
		ImGui::SliderFloat("size", &wheel1.springLength,0.0f,5.0f);
		ImGui::SliderFloat("dt", &dt_of_sim,0.0f,0.1f);

		ImGui::SliderFloat("stiffnes2", &stiffnes,0.0f,10000.0f);
		ImGui::SliderFloat("absorption2", &absorption,0.0f,10.0f);


		ImGui::SliderFloat("Body stiffnes", &Body.stiffness, 0.0f, 10000.0f);
		ImGui::SliderFloat("Body absorption", &Body.absorption, 0.0f, 10.0f);

		wheel2.stiffness = wheel1.stiffness;
		wheel2.absorption = wheel1.absorption;
		wheel2.friction = wheel1.friction;
		wheel2.springLength = wheel1.springLength;

		float subdt = dt_of_sim / substeps;
		//stiffness = 0.1f/subdt;

		for (int s = 0; s < substeps; s++)
		{

			//if (amount == 4)// if square
			//{
			//	SpringBetweenBalls(&balls[0], &balls[1], size, stiffness, absorption);
			//	SpringBetweenBalls(&balls[0], &balls[3], size, stiffness, absorption);
			//	SpringBetweenBalls(&balls[0], &balls[2], sqrt(size * size * 2.0f), stiffness, absorption);

			//	SpringBetweenBalls(&balls[1], &balls[3], sqrt(size * size * 2.0f), stiffness, absorption);
			//	SpringBetweenBalls(&balls[1], &balls[2], size, stiffness, absorption);

			//	SpringBetweenBalls(&balls[2], &balls[3], size, stiffness, absorption);

			//}




			wheel1.Force = glm::vec2(0.0f, -g);
			wheel2.Force = glm::vec2(0.0f, -g);
			Body.Force = glm::vec2(0.0f, -g) - md*25.0f;
			wheel1.Process(subdt);
			wheel2.Process(subdt);
			Body.Process(subdt);

			//SpringBetweenBalls(&wheel1.balls[8], &wheel2.balls[8], 250, stiffnes, absorption);


			SpringBetweenBalls(&wheel1.balls[8], &Body.balls[4], 250, stiffnes, absorption);
			SpringBetweenBalls(&wheel1.balls[8], &Body.balls[1], 150, stiffnes, absorption);
			//SpringBetweenBalls(&wheel1.balls[8], &Body.balls[0], 100, stiffnes, absorption);

			SpringBetweenBalls(&wheel2.balls[8], &Body.balls[4], 250, stiffnes, absorption);
			SpringBetweenBalls(&wheel2.balls[8], &Body.balls[3], 150, stiffnes, absorption);
			//SpringBetweenBalls(&wheel2.balls[8], &Body.balls[2], 100, stiffnes, absorption);

			DrawSpring(wheel1.balls[8].position, Body.balls[4].position, 250);
			DrawSpring(wheel1.balls[8].position, Body.balls[1].position, 150);

			DrawSpring(wheel2.balls[8].position, Body.balls[4].position, 250);
			DrawSpring(wheel2.balls[8].position, Body.balls[3].position, 150);

			for (int i = 0; i < wheel1.balls.size(); i++)
				BallToStaticQuadCollision(&wheel1.balls[i], floor);

			for (int i = 0; i < wheel2.balls.size(); i++)
				BallToStaticQuadCollision(&wheel2.balls[i], floor);

			for (int i = 0; i < Body.balls.size(); i++)
				BallToStaticQuadCollision(&Body.balls[i], floor);

			//FixedSpringBetweenBalls(&balls[0], &balls[1], Normalize(Rotate(balls[0].position - balls[amount - 1].position, angle)) * size * 2.0f * pi / (float)amount, stiffness * subdt,0.2f);
			//FixedSpringBetweenBalls(&balls[amount - 1], &balls[0], Normalize(Rotate(balls[amount - 1].position - balls[amount - 2].position, angle)) * size * 2.0f * pi / (float)amount, stiffness * subdt, 0.2f);

			for (int x = 1; x < WorldSizeX; x++)
			{
				DrawLine(glm::vec2(((float)(x + (Stage - 1) * WorldSizeX) - 1.0f) * modx, BufferNoize[x - 1][0] * mod), glm::vec2((float)(x + (Stage - 1) * WorldSizeX) * modx, BufferNoize[x][0] * mod), 2.0f);

				line l1(glm::vec2(((float)(x + (Stage - 1) * WorldSizeX) - 1.0f) * modx, BufferNoize[x - 1][0] * mod), glm::vec2((float)(x + (Stage - 1) * WorldSizeX) * modx, BufferNoize[x][0] * mod));

				DrawLine(glm::vec2(((float)(x + Stage * WorldSizeX) - 1.0f) * modx, Noize1[x - 1][0] * mod), glm::vec2((float)(x + Stage * WorldSizeX) * modx, Noize1[x][0] * mod), 2.0f);

				line l2(glm::vec2(((float)(x + Stage * WorldSizeX) - 1.0f) * modx, Noize1[x - 1][0] * mod), glm::vec2((float)(x + Stage * WorldSizeX) * modx, Noize1[x][0] * mod));

				for (int i = 0; i < wheel1.balls.size(); i++)
				{
					BallToGroundLineCollision(&wheel1.balls[i], l1);
					BallToGroundLineCollision(&wheel1.balls[i], l2);
					BallToGroundLineCollision(&wheel2.balls[i], l1);
					BallToGroundLineCollision(&wheel2.balls[i], l2);
				}
				for (int i = 0; i < Body.balls.size(); i++)
				{
					BallToGroundLineCollision(&Body.balls[i], l1);
					BallToGroundLineCollision(&Body.balls[i], l2);
				}

			}

		}

		if (JustPressedLMB && keys[GLFW_KEY_LEFT_ALT])
		{
			ball b;
			b.position = MousePosition;
			b.roughness = 0.1f;
			b.bounciness = 0.1f;
			b.r = 10.0f;
			b.FixedRotation = true;
			Body.balls.push_back(b);
		}
		//Body.springs.push_back(glm::ivec3(0, 5, length(Body.balls[0].position - Body.balls[5].position)));
		if (JustPressedLMB && keys[GLFW_KEY_LEFT_SHIFT])
		{
			ball b;
			b.position = MousePosition;
			b.roughness = 0.1f;
			b.bounciness = 0.1f;
			b.r = 10.0f;
			b.FixedRotation = true;
			Body.balls.push_back(b);
			for (int i = 0; i < Body.balls.size()-1; i++)
				Body.springs.push_back(glm::ivec3(i, Body.balls.size()-1, length(Body.balls[i].position - Body.balls[Body.balls.size()-1].position)));
		}

		if (JustPressedLMB && keys[GLFW_KEY_LEFT_CONTROL])
		{
			if (iter == 0)
			{
				bool b = false;
				for(int i =0;i< Body.balls.size();i++)
					if (BalltPointCollisionCheck(Body.balls[i], MousePosition))
						if (!b) 
						{
							tmp.x = i;
							b = true;
							iter++;
						}
			}
			else if (iter == 1)
			{
				bool b = false;
				for (int i = 0; i < Body.balls.size(); i++)
					if (BalltPointCollisionCheck(Body.balls[i], MousePosition))
						if (!b && tmp.x != i)
						{
							tmp.y = i;
							tmp.z = length(Body.balls[i].position - Body.balls[tmp.x].position);
							Body.springs.push_back(tmp);
							b = true;
							iter = 0;
						}

			}
		}


		// Update world
		if (CameraPosition.x - 1000.0f > Stage * modx * WorldSizeX)
		{
			Stage++;
			UpdateWorld();
		}
		//Camera
		glm::vec2 mid= glm::vec2(0.0f);

		for (int i = 0; i < wheel1.balls.size(); i++)
			mid += wheel1.balls[i].position;
		
		for (int i = 0; i < wheel2.balls.size(); i++)
			mid += wheel2.balls[i].position;

		for (int i = 0; i < Body.balls.size(); i++)
			mid += Body.balls[i].position;

		mid /= wheel1.balls.size() + wheel2.balls.size() + Body.balls.size();
		CameraPosition = mid;




		float velocity = 50000.0f;
		if (keys[GLFW_KEY_D])
		{
			for (int i = 0; i < wheel1.balls.size(); i++)
				if ( i!=8)//sqrlength(wheel1.balls[i].velocity) < 1000000 &&
				{
					glm::vec2 velvec = wheel1.balls[8].position - wheel1.balls[i].position;
					wheel1.balls[i].Force += Normalize(glm::vec2(-velvec.y, velvec.x)) * velocity;
				}
			for (int i = 0; i < wheel2.balls.size(); i++)
				if (i != 8)//sqrlength(wheel2.balls[i].velocity) < 1000000 && 
				{
					glm::vec2 velvec = wheel2.balls[8].position - wheel2.balls[i].position;
					wheel2.balls[i].Force += Normalize(glm::vec2(-velvec.y, velvec.x)) * velocity;
				}
		}
		if (keys[GLFW_KEY_A])
		{
			for (int i = 0; i < wheel1.balls.size(); i++)
				if ( i != 8)//sqrlength(wheel1.balls[i].velocity) < 1000000 &&
				{
					glm::vec2 velvec = wheel1.balls[8].position - wheel1.balls[i].position;
					wheel1.balls[i].Force += Normalize(glm::vec2(velvec.y, -velvec.x)) * velocity;
				}
			for (int i = 0; i < wheel2.balls.size(); i++)
				if (i != 8)//sqrlength(wheel2.balls[i].velocity) < 1000000 && 
				{
					glm::vec2 velvec = wheel2.balls[8].position - wheel2.balls[i].position;
					wheel2.balls[i].Force += Normalize(glm::vec2(velvec.y, -velvec.x)) * velocity;
				}
		}

		if (keys[GLFW_KEY_W])
			wheel1.springLength = 1.65f;
		else wheel1.springLength = 1.0f;

		DrawCube(floor);

		for (int i = 0; i < wheel1.balls.size(); i++)
			DrawBall(wheel1.balls[i]);
		for (int i = 0; i < wheel1.springs.size(); i++)
		{

			float dif = length(wheel1.balls[wheel1.springs[i].x].position - wheel1.balls[wheel1.springs[i].y].position) - wheel1.springs[i].z;

			glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

			dif /= (wheel1.springs[i].z* wheel1.springLength) * 0.25f;
			if (dif > 0)
			{
				color.r += dif;
				color.g -= dif;
				color.b -= dif;
				if (color.g < 0)color.g = 0;
				if (color.b < 0)color.b = 0;
			}
			else
			{
				color.b += -dif;
				color.g -= -dif;
				color.r -= -dif;
				if (color.g < 0)color.g = 0;
				if (color.r < 0)color.r = 0;
			}

			DrawLine(wheel1.balls[wheel1.springs[i].x].position, wheel1.balls[wheel1.springs[i].y].position, 1.0f,color);
		}


		for (int i = 0; i < wheel2.balls.size(); i++)
			DrawBall(wheel2.balls[i]);
		for (int i = 0; i < wheel2.springs.size(); i++)
		{
			float dif = length(wheel2.balls[wheel2.springs[i].x].position - wheel2.balls[wheel2.springs[i].y].position) - wheel2.springs[i].z;

			glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

			dif /= (wheel2.springs[i].z * wheel2.springLength) * 0.25f;
			if (dif > 0)
			{
				color.r += dif;
				color.g -= dif;
				color.b -= dif;
				if (color.g < 0)color.g = 0;
				if (color.b < 0)color.b = 0;
			}
			else
			{
				color.b += -dif;
				color.g -= -dif;
				color.r -= -dif;
				if (color.g < 0)color.g = 0;
				if (color.r < 0)color.r = 0;
			}

			DrawLine(wheel2.balls[wheel2.springs[i].x].position, wheel2.balls[wheel2.springs[i].y].position, 1.0f, color);
		}


		for (int i = 0; i < Body.balls.size(); i++)
			DrawBall(Body.balls[i]);
		for (int i = 0; i < Body.springs.size(); i++)
		{

			float dif = length(Body.balls[Body.springs[i].x].position - Body.balls[Body.springs[i].y].position) - Body.springs[i].z;

			glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

			dif /= (Body.springs[i].z * Body.springLength) * 0.25f;
			if (dif > 0)
			{
				color.r += dif;
				color.g -= dif;
				color.b -= dif;
				if (color.g < 0)color.g = 0;
				if (color.b < 0)color.b = 0;
			}
			else
			{
				color.b += -dif;
				color.g -= -dif;
				color.r -= -dif;
				if (color.g < 0)color.g = 0;
				if (color.r < 0)color.r = 0;
			}

			DrawLine(Body.balls[Body.springs[i].x].position, Body.balls[Body.springs[i].y].position, 1.0f, color);
		}
	/*	if (amount == 8) 
		{
			DrawTriangle(bod.balls[0].position, bod.balls[1].position, bod.balls[3].position);
			DrawTriangle(bod.balls[2].position, bod.balls[1].position, bod.balls[3].position);

			DrawTriangle(bod.balls[7].position, bod.balls[0].position, bod.balls[3].position);
			DrawTriangle(bod.balls[7].position, bod.balls[3].position, bod.balls[4].position);

			DrawTriangle(bod.balls[4].position, bod.balls[7].position, bod.balls[5].position);
			DrawTriangle(bod.balls[7].position, bod.balls[6].position, bod.balls[5].position);
		}*/

	}
};
int main()
{
	application app;
	app.init("app", 1920, 1080, true);
	return 0;
}


