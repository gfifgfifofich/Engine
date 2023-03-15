// PB = 261596

#include "engine/Components/Engine.h"
#include "engine/Components/Classes.h"


float screenY = 0.0f;
bool started = true;

bool screenbooleans[3];
bool dead = false;



struct particle
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2 (0.0f);
};
const int particles_amount = 50;
const int Collision_particles_amount = 250;

particle particles[particles_amount];

particle CollisionParticles[Collision_particles_amount];

const int booster_amount = 1;
cube booster[booster_amount];




class Player : public KinematicBody
{
public:

	glm::vec2 velocity = glm::vec2(0.0f);
	float vel = 20.0f;
	float g = 1.25f;

	int last_i = 0;
	int particle_amount = 10;

	void Process(float delta) override
	{
		PreProcess(delta);



		if (keys[GLFW_KEY_D]) velocity.x = vel;
		else if (keys[GLFW_KEY_A]) velocity.x = -vel;
		else velocity.x = 0.0f;

		body.position += velocity*delta*58.8235f;
		velocity.y -= g * delta* 58.8235f;


		for(int i  = 0; i < cubes.size();i++)
			if (BtCCollisionCheck(body, cubes[i]) == 1)
			{
				started = true;
				//position.y = cubes[i].position.y + colider.r+ cubes[i].height;
				if(velocity.y<40) velocity.y = 40;
				for (int i = last_i; i < last_i+ particle_amount; i++)
				{
					CollisionParticles[i].position = body.position;
					CollisionParticles[i].velocity = glm::vec2(rand() % 50-25, rand() % 10 - 5 +10);
				}
				last_i += particle_amount;
				if (last_i >= Collision_particles_amount)last_i = 0;
			}


		for (int i = 0; i < booster_amount; i++) {
			int Chek = BtCCollisionCheck(body, booster[i]);
			if (Chek > 0 && Chek < 5)
			{
				started = true;
				//position.y = cubes[i].position.y + colider.r+ cubes[i].height;
				velocity.y = 100;
				cubes[1].position.y = booster[i].position.y + 3900;
				cubes[0].position.y = booster[i].position.y + 3900;
				for (int i = last_i; i < last_i + particle_amount; i++)
				{
					CollisionParticles[i].position = body.position;
					CollisionParticles[i].velocity = glm::vec2(rand() % 50 - 25, rand() % 10 - 5 + 100);
				}
				last_i += particle_amount;
				if (last_i >= Collision_particles_amount)last_i = 0;

			}
		}


		if (body.position.y- body.r < 0)
		{
			body.position.y = body.r;
			if (started) {
				dead = true;
				started = false;
			}
			velocity.y = 40;
		}

		if (body.position.x - body.r < 0)
		{
			body.position.x = body.r;
		}
		if (body.position.x + body.r > WIDTH)
		{
			body.position.x = WIDTH- body.r;
		}

	}

};

Player player;

int amount = 4; //of platforms



class application : public Engine
{
public:
	void On_Create() override
	{
		cube c;
		
		for (int i = 0; i < amount; i++)
		{
			c.height = 15.0f;
			c.width = 75.0f;
			c.position = glm::vec2(c.width + rand() % WIDTH - c.width , c.height + rand() % (2*HEIGHT) - c.height );
			if (!dead)
				cubes.push_back(c);
			else cubes[i] = c;
		}

		for (int i = 0; i < booster_amount; i++)
		{

			booster[i].height = 25.0f;
			booster[i].width = 25.0f;
			booster[i].position = glm::vec2(600,600);
		}
		if (!dead)
			player.init(glm::vec2(500, 100), 35);
		else 
		{
			player.body.position = glm::vec2(500, 100);
			std::cout << "max height - " << int(screenY) << "\n";
			screenY = 0;
		}

		BackgroundColor = glm::vec4(0.0f,1.0f,0.0f,1.0f);
		screenbooleans[1] = true;
		dead = false;
	}


	void On_Update() override
	{

		



		player.Process(delta);
		float dif = 0.0f;
		if (player.body.position.y > HEIGHT * 0.6f)
		{
			dif = (player.body.position.y - HEIGHT * 0.6f);
			screenY += dif;

			if (BackgroundColor.r < 1.0f && !screenbooleans[1] && !screenbooleans[2])
			{
				BackgroundColor.r += dif * 0.0001f;
				BackgroundColor.g -= dif * 0.0001f;
				BackgroundColor.b -= dif * 0.0001f;
				screenbooleans[0] = true;
			}
			else screenbooleans[0] = false;

			if (BackgroundColor.g < 1.0f && !screenbooleans[2] && !screenbooleans[0])
			{
				BackgroundColor.r -= dif * 0.0001f;
				BackgroundColor.g += dif * 0.0001f;
				BackgroundColor.b -= dif * 0.0001f;
				screenbooleans[1] = true;
			}
			else screenbooleans[1] = false;

			if (BackgroundColor.b < 1.0f && !screenbooleans[1] && !screenbooleans[0])
			{
				BackgroundColor.r -= dif * 0.0001f;
				BackgroundColor.g -= dif * 0.0001f;
				BackgroundColor.b += dif * 0.0001f;
				screenbooleans[2] = true;
			}
			else screenbooleans[2] = false;
			
			
			if (BackgroundColor.r < 0) BackgroundColor.r = 0;
			if (BackgroundColor.g < 0) BackgroundColor.g = 0;
			if (BackgroundColor.b< 0) BackgroundColor.b = 0;
			
			player.body.position.y -=  dif;


			for (int i = 0; i < booster_amount; i++)
			{
				booster[i].position.y -= dif;
				if (booster[i].position.y < 0)
				{
					booster[i].position = glm::vec2(cubes[i].width * 2 + rand() % int(WIDTH - 3 * cubes[i].width),  5000);
				}
			}

			for (int i = 0; i < particles_amount; i++)
			{
				particles[i].velocity.y = -1.5*dif;
				if (particles[i].position.y < 0)
				{
					particles[i].position = glm::vec2( rand() % WIDTH , rand() % (HEIGHT)+HEIGHT);
				}
			}
			



			for (int i = 0; i < cubes.size(); i++)
			{
				cubes[i].position.y -= dif;
				if (cubes[i].position.y < 0)
				{
					float maxY = 0.0f;
					for (int a = 0; a < cubes.size(); a++)
					{
						if (cubes[a].position.y > maxY)
							maxY = cubes[a].position.y;
					}

					cubes[i].position = glm::vec2(cubes[i].width*2 + rand() % int(WIDTH - 3*cubes[i].width), maxY + 500 );
				}
			}
		}

		
		if (dif <= 0.0f)
		{
			for (int i = 0; i < particles_amount; i++)
			{
				particles[i].velocity.y = 0.0f;
				particles[i].position = glm::vec2(rand() % WIDTH, rand() % (HEIGHT));
			}
		}
		if (dead)
		{
			On_Create();
		}
		player.Color = glm::vec4(BackgroundColor.g, BackgroundColor.b, BackgroundColor.r, BackgroundColor.a);
		for (int i = 0; i < Collision_particles_amount; i++)
		{
			CollisionParticles[i].position += CollisionParticles[i].velocity*delta * 58.8f;
			CollisionParticles[i].position.y -= dif;
			CollisionParticles[i].velocity.y -= 1.25f;

			DrawLine(CollisionParticles[i].position, CollisionParticles[i].position + CollisionParticles[i].velocity, 2.5f, glm::vec4(BackgroundColor.b, BackgroundColor.r, BackgroundColor.g, 4.5f));
		}
		for (int i = 0; i < cubes.size(); i++)
		{
			DrawCube(cubes[i].position, glm::vec2(cubes[i].width, cubes[i].height), glm::vec3(0.0f), player.Color);
		}
		for (int i = 0; i < booster_amount; i++)
		{
			DrawCube(booster[i].position, glm::vec2(booster[i].width, booster[i].height), glm::vec3(0.0f), glm::vec4(player.Color.r, player.Color.g, player.Color.b,5.0f));
		}
		for (int i = 0; i < particles_amount; i++)
		{
			particles[i].position +=particles[i].velocity*delta*58.8f;
			DrawLine(particles[i].position, particles[i].position+ particles[i].velocity,5.0f, glm::vec4(BackgroundColor.b, BackgroundColor.r, BackgroundColor.g, 0.25f));
		}
		
	}
};

int main()
{
	application app;
	app.init();
	return 0;
}