// PB = 261596

#include "engine/Components/Engine.h"
#include "engine/Components/Classes.h"



struct particle
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
};
const int particles_amount = 300;
const int particles_amount2 = 100;
particle particles[particles_amount];
particle Speedparticles[particles_amount2];




bool screenbooleans[3];
float screen_x = 0.0f;
float screen_y = 0.0f;
class Player : public RigidBody
{
public:
	void Process(float delta) override
	{
		float g = 600.0f;
		if (keys[GLFW_KEY_SPACE])
			g = 6000.0f;
		else g = 600.0f;

		if (keys[GLFW_KEY_D])
			body.velocity.x += 10;
		if (keys[GLFW_KEY_A])
			body.velocity.x -= 10;
		if (keys[GLFW_KEY_W])
			body.velocity.y += 20;
		body.velocity.y -= g * delta;

		for (int i = 0; i < particles_amount2; i++)
		{
			glm::vec2 randpos = glm::vec2(0.0f, 0.0f);
			if (Speedparticles[i].position.x < 0.0f|| sqrlength(Speedparticles[i].velocity)<100|| Speedparticles[i].velocity.x>0.0f)
			{

				glm::vec2 randpos = glm::vec2(rand() % 30 - 15, rand() % 30 - 15);
				Speedparticles[i].position = body.position + randpos;
				Speedparticles[i].velocity = -body.velocity * delta * float(rand() % 100) * 0.02f + randpos * 0.1f;
			}

			if (sqrlength(body.velocity) > 10000)DrawLine(Speedparticles[i].position, Speedparticles[i].position + Speedparticles[i].velocity, 2.0f, glm::vec4(1.0f, 0.2f, 0.04f, length(body.velocity) * 0.0005f));

			Speedparticles[i].position += Speedparticles[i].velocity;
		}



		PreProcess(delta);

	}
};
Player player;










int amount =30;

struct object
{
	std::vector <Triangle>Triangles;
	glm::vec2 migpos;
};


std::vector <object> Objects;


class application : public Engine
{
public:

	Player player;

	polygon currentShape;
	polygon UpSlope;
	polygon DownSlope;

	glm::vec2 UpSlopeLeftPoint;
	glm::vec2 DownSlopeLeftPoint;

	glm::vec2 UpSlopeRightPoint = glm::vec2(0.0f);
	glm::vec2 DownSlopeRightPoint = glm::vec2(0.0f);

	glm::vec2 LastPoint = glm::vec2(0.0f);
	
	bool Switch = false;
	void On_Create() override
	{

		player.init(glm::vec2(500.0f, 700.0f), 15);

		UpSlope.Load("upslope.pol");
		DownSlope.Load("downslope.pol");

		UpSlope.midle_point /= 1.0f;
		for (int i = 0; i < UpSlope.points.size(); i++)
		{
			UpSlope.points[i] /= 1.0f;
			UpSlopeLeftPoint = UpSlope.points[0];
		}
		for (int i = 0; i < UpSlope.points.size(); i++)
		{
			UpSlope.points[i] -= UpSlopeLeftPoint;

			if (UpSlope.points[i].x > UpSlopeRightPoint.x)
				UpSlopeRightPoint = UpSlope.points[i];
		}
		UpSlope.midle_point -= UpSlopeLeftPoint;
		UpSlope.Update_Shape(false);


		DownSlope.midle_point /= 1.0f;
		for (int i = 0; i < DownSlope.points.size(); i++)
		{
			DownSlope.points[i] /= 1.0f;
			DownSlopeLeftPoint = DownSlope.points[0];
		}
		for (int i = 0; i < DownSlope.points.size(); i++)
		{
			DownSlope.points[i] -= DownSlopeLeftPoint;
			if (DownSlope.points[i].x > DownSlopeRightPoint.x)
				DownSlopeRightPoint = DownSlope.points[i];
		}

		DownSlope.midle_point -= DownSlopeLeftPoint;
		DownSlope.Update_Shape(false);

		for (int i = 0; i < amount; i++)
		{

			if (Switch)
			{
				currentShape = UpSlope;
				Switch = !Switch;
			}
			else
			{
				currentShape = DownSlope;
				Switch = !Switch;
			}
			currentShape.midle_point.y += 400;
			currentShape.midle_point += LastPoint;
			for (int a = 0;  a< currentShape.points.size(); a++)
			{
				currentShape.points[a].y += 400;
				currentShape.points[a] += LastPoint;
			}

			currentShape.Update_Shape(false);
			
			object obj;
			obj.migpos = currentShape.midle_point;
			for (int a = 0; a < currentShape.triangles.size(); a++)
			{
				SubTriangle sudt = currentShape.triangles[a];
				Triangle tempTri(sudt.l1.P1, sudt.l2.P1, sudt.l3.P1);
				obj.Triangles.push_back(tempTri);
			}
			Objects.push_back(obj);
			if (Switch)
			{
				LastPoint += DownSlopeRightPoint;
			}
			else
			{
				LastPoint += UpSlopeRightPoint;
			}
		}



		/*for (int i = 0; i < lineamount; i++)
		{
			if (FragmentCouner <= 0)
			{
				randomNumber = (rand() % 10 - 5) * 2.0f;
				FragmentCouner = 35;
			}
			FragmentCouner--;

			float new_y =sin( (step * (distance) - screen_x)*0.5f ) * (ruoghness + randomNumber);
			
			
			glm::vec2 p1 = glm::vec2(step * (i - 1) - screen_x, 400 + last_y - screen_y);
			glm::vec2 p2 = glm::vec2(step * (i)-screen_x, 400 + new_y - screen_y);
			line l(p1,p2);
			l.Calculate_normal();
			Triangle t(p1, p2, (p1 + p2) * 0.5f - 500.0f * l.normal);

			Triangles.push_back(t);
			last_y = new_y;
			distance += 1;
		}*/


		for (int i = 0; i < particles_amount; i++)
		{
			particles[i].position = glm::vec2(rand() % WIDTH + WIDTH, rand() % (2 * HEIGHT) - HEIGHT);
		}
		for (int i = 0; i < particles_amount2; i++)
		{
			Speedparticles[i].position = player.body.position;
		}

		DrawingOrder = false;

		BackgroundColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		screenbooleans[1] = true;
	}

	void On_Update() override
	{
		
		player.Process(delta);
		glm::vec2 dif = player.body.position - glm::vec2(WIDTH * 0.5f, HEIGHT * 0.5f);

		/*spike.DrawOutline();
		pit.DrawOutline();

		DrawCircle(pitRightPoint, 10, 2.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawCircle(spikeRightPoint, 10, 2.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));*/

		for (int i = 0; i < Objects.size(); i++)
		{
			for (int a = 0; a < Objects[i].Triangles.size(); a++)
			{
				BallToTriangleCollision(&player.body, Objects[i].Triangles[a], 0.0f);
				Objects[i].Triangles[a].DrawOutline();
				//DrawLine(Tri[i].lines[0].P1 - glm::vec2(1.0f, 0.0f), Tri[i].lines[0].P2 + glm::vec2(1.0f, 0.0f), Tri[i].lines[0].width, glm::vec4(BackgroundColor.g, BackgroundColor.b, BackgroundColor.r, 1.0f));
			}
		}
		if (player.body.position.x > WIDTH * 0.5f)
		{


			

			if (BackgroundColor.r < 1.0f && !screenbooleans[1] && !screenbooleans[2])
			{
				BackgroundColor.r += dif.x * 0.0001f;
				BackgroundColor.g -= dif.x * 0.0001f;
				BackgroundColor.b -= dif.x * 0.0001f;
				screenbooleans[0] = true;
			}
			else screenbooleans[0] = false;

			if (BackgroundColor.g < 1.0f && !screenbooleans[2] && !screenbooleans[0])
			{
				BackgroundColor.r -= dif.x * 0.0001f;
				BackgroundColor.g += dif.x * 0.0001f;
				BackgroundColor.b -= dif.x * 0.0001f;
				screenbooleans[1] = true;
			}
			else screenbooleans[1] = false;

			if (BackgroundColor.b < 1.0f && !screenbooleans[1] && !screenbooleans[0])
			{
				BackgroundColor.r -= dif.x * 0.0001f;
				BackgroundColor.g -= dif.x * 0.0001f;
				BackgroundColor.b += dif.x * 0.0001f;
				screenbooleans[2] = true;
			}
			else screenbooleans[2] = false;


			if (BackgroundColor.r < 0) BackgroundColor.r = 0;
			if (BackgroundColor.g < 0) BackgroundColor.g = 0;
			if (BackgroundColor.b < 0) BackgroundColor.b = 0;



			player.body.position -= dif;
			screen_x += dif.x;
			screen_y += dif.y;
			LastPoint -= dif;
			for (int i = 0; i < Objects.size(); i++)
			{
				Objects[i].migpos -= dif;
				for (int a = 0; a < Objects[i].Triangles.size(); a++)
				{
					Objects[i].Triangles[a].points[0] -= dif;
					Objects[i].Triangles[a].points[1] -= dif;
					Objects[i].Triangles[a].points[2] -= dif;
					Objects[i].Triangles[a].Update_Shape();
				}
				if (Objects[i].migpos.x < -500.0f)
				{
					Objects[i] = Objects[Objects.size() - 1];
					Objects.pop_back();

					if (Switch)
					{
						currentShape = UpSlope;
						Switch = !Switch;
					}
					else
					{
						currentShape = DownSlope;
						Switch = !Switch;
					}
					currentShape.midle_point.y += 400;
					currentShape.midle_point += LastPoint;
					for (int a = 0; a < currentShape.points.size(); a++)
					{
						currentShape.points[a].y += 400;
						currentShape.points[a] += LastPoint;
					}

					currentShape.Update_Shape(false);

					object obj;
					obj.migpos = currentShape.midle_point;
					for (int a = 0; a < currentShape.triangles.size(); a++)
					{
						SubTriangle sudt = currentShape.triangles[a];
						Triangle tempTri(sudt.l1.P1, sudt.l2.P1, sudt.l3.P1);
						obj.Triangles.push_back(tempTri);
					}
					Objects.push_back(obj);

					if (Switch)
					{
						LastPoint += DownSlopeRightPoint;
					}
					else
					{
						LastPoint += UpSlopeRightPoint;

					}
				}
			}






		}

		for (int i = 0; i < particles_amount; i++)
		{
			particles[i].position += particles[i].velocity;
			if (player.body.position.x >= WIDTH * 0.5f)
			{
				particles[i].velocity = -dif;
			}
			else particles[i].velocity = glm::vec2(0.0f);

			if (particles[i].position.x < 0.0f)
				particles[i].position = glm::vec2(rand() % WIDTH +WIDTH, rand() % (4*HEIGHT)-2*HEIGHT + dif.y*10);
			DrawLine(particles[i].position, particles[i].position + particles[i].velocity, 2.0f, glm::vec4(BackgroundColor.b, BackgroundColor.r, BackgroundColor.g, 0.5f));

		}
		player.Color = glm::vec4(BackgroundColor.g, BackgroundColor.b, BackgroundColor.r, 1.0f);
		
		if (player.body.position.x- player.body.r < 0.0f)
		{
			player.body.position.x = player.body.r;
			player.body.velocity.x *= -1;
		}
		if (player.body.position.x + player.body.r > WIDTH)
		{
			player.body.position.x = WIDTH- player.body.r;
			player.body.velocity.x *= -1;
		}
		if (player.body.position.y + player.body.r > HEIGHT)
		{
			player.body.position.y = HEIGHT - player.body.r;
		}
	}
};

int main()
{
	application app;
	app.init();
	return 0;
}