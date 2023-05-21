#include "engine/Components/Engine.h"


std::vector<Triangle> t;
const int amount = 100;
ball balls[amount];
Triangle tri(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

int substeps = 4;
class application : public Engine
{
public:
	bool JustPressedLMB = false;

	RigidBody b;
	int counter = 0;
	ball Staticball1;
	ball Staticball2;

	cube c1;
	cube c2;

	Triangle t1 = tri;
	Triangle t2=tri;

	ParticleEmiter Sparker; 
	
	void On_Create() override
	{
		float r = 5.0f;
		



		Sparker.acceleration = glm::vec2(0.0f, -2500.0f);
		Sparker.InitialVelocity = glm::vec2(0.0f, 0.0f);
		Sparker.VelocityRandomness = glm::vec4(-100.0f, 100.0f, -100.0f, 100.0f);

		Sparker.lifetime = 1.0f;

		Sparker.StartSize = glm::vec2(3.0f, 3.0f);
		Sparker.EndSize = glm::vec2(0.0f);

		Sparker.StartColor = glm::vec4(2.0f, 0.2f, 0.04f, 0.1f) * 10.0f;
		Sparker.EndColor = glm::vec4(1.0f, 0.2f, 0.04f, 0.0f) *10.0f;

		Sparker.InitialRotation = 1.67f;
		Sparker.RotationVelocity = 0.05f;
		Sparker.RotationRandomness = 10.0f;
		Sparker.RotationAcceleration = 0.01f;

		Sparker.Type = "QUAD";
		ParticleEmiters.push_back(&Sparker);


		Staticball1.Kinematic = true;
		Staticball1.position = glm::vec2(0.0f, 300.0f);
		Staticball1.r = 100.0f;
		Staticball1.color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
		ballsptr.push_back(&Staticball1);

		Staticball2.Kinematic = true;
		Staticball2.position = glm::vec2(WIDTH , 300);
		Staticball2.r = 100.0f;
		Staticball2.color = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
		ballsptr.push_back(&Staticball2);

		c1.position = glm::vec2(300.0f, 600.0f);
		c1.height = 200;
		c1.width = 100;
		
		c2.position = glm::vec2(WIDTH - 300.0f, 600.0f);
		c2.height = 100;
		c2.width = 200;

		cubes.push_back(&c1);
		cubes.push_back(&c2);


		tri.points[0] = glm::vec2(-200.0f, 400.0f);
		tri.points[1] = glm::vec2(850.0f, -100.0f);
		tri.points[2] = glm::vec2(-200.0f, -300.0f);
		tri.Update_Shape();
		t1=tri;

		tri.points[0] = glm::vec2(WIDTH - 850.0f, -100.0f);
		tri.points[1] = glm::vec2(WIDTH + 200.0f, 400.0f);
		tri.points[2] = glm::vec2(WIDTH +200.0f, -300.0f);
		tri.Update_Shape();
		t2=tri;

		for (int i = 0; i < amount; i++)
		{
			ball b;
			b.r = r;
			b.position = glm::vec2(r + rand() % WIDTH - r * 2, HEIGHT * 0.5f + rand() % int(HEIGHT*0.5f) );
			b.velocity = glm::vec2(rand() % 10 - 5, rand() % 10 - 5);
			balls[i] = b;
			ballsptr.push_back(&balls[i]);
		}
		b.init(glm::vec2(500, 500), 50);
		b.body.roughness = 0.0f;
		substeps = 4;
		b.Color= glm::vec4(2.0f, 0.2f, 0.04f, 0.1f) * 10.0f;
	}
	int n = 1;

	

	void On_Update() override
	{
		CameraPosition = b.body.position;

		ImGui::Begin("Info");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("ParticlesAmount %i", Sparker.Particles.size());
		ImGui::SliderInt("amount",&n,0,100);

		


		float velocity = 10.0f;
		if (keys[GLFW_KEY_LEFT_SHIFT]) velocity = 100.0f;
		if (keys[GLFW_KEY_W]) b.body.velocity.y += velocity;
		if (keys[GLFW_KEY_S]) b.body.velocity.y -= velocity;
		if (keys[GLFW_KEY_D]) b.body.velocity.x += velocity;
		if (keys[GLFW_KEY_A]) b.body.velocity.x -= velocity;
		if (keys[GLFW_KEY_X]) CameraScale *= 0.99f;
		if (keys[GLFW_KEY_Z]) CameraScale *= 1.01f;


		DrawCircle(Staticball1.position, Staticball1.r,  Staticball1.color);
		DrawCircle(Staticball2.position, Staticball2.r,  Staticball2.color);
		DrawCube(c1.position, glm::vec2(c1.width, c1.height));
		DrawCube(c2.position, glm::vec2(c2.width, c2.height));



	
		

		for (int k = 0; k < n; k++)
		{
			Sparker.Spawn(b.body.position + glm::vec2((rand() % int(b.body.r * 2) - b.body.r), (rand() % int(b.body.r * 2) - b.body.r)));
		}

		for (int i = 0; i < amount; i++)
		{
			balls[i].velocity.y += -100.0f * delta;

			balls[i].position += balls[i].velocity* delta;
			for (int k = 0; k < n; k++)
			{
				Sparker.Spawn(balls[i].position + glm::vec2((rand() % int(balls[i].r * 2) - balls[i].r), (rand() % int(balls[i].r * 2) - balls[i].r)));
			}
			for (int a = 0; a < t.size(); a++)
			{
				glm::vec2 prevel = balls[i].velocity;
				BallToTriangleCollision(&balls[i], t[a]);
				
				
			}
			BallToTriangleCollision(&balls[i], t1);
			BallToTriangleCollision(&balls[i], t2);

			DrawCircle(balls[i].position, balls[i].r);
			// walls colisions 
			if (balls[i].position.y > HEIGHT - balls[i].r)
			{
				balls[i].position.y = HEIGHT - balls[i].r;
				if (balls[i].velocity.y > 0)
					balls[i].velocity.y =0.0;
			}
			if (balls[i].position.y < 0 + balls[i].r)
			{
				balls[i].position.y = 0 + balls[i].r;
				if (balls[i].velocity.y < 0)
					balls[i].velocity.y = 0.0;
			}
			if (balls[i].position.x > WIDTH - balls[i].r)
			{
				balls[i].position.x = WIDTH - balls[i].r;
				if (balls[i].velocity.x > 0)
					balls[i].velocity.x = 0.0;
			}
			if (balls[i].position.x < 0 + balls[i].r)
			{
				balls[i].position.x = 0 + balls[i].r;
				if (balls[i].velocity.x < 0)
					balls[i].velocity.x = 0.0;
			}
		}
		
		

		
		
		if (keys[GLFW_KEY_SPACE])
		{
			t.clear();
			counter = 0;
			b.body.position =glm::vec2(500, 500);
		}
		
		

		b.Process(delta);
		BallToTriangleCollision(&b.body, t1);
		BallToTriangleCollision(&b.body, t2);
		t1.DrawOutline();
		t2.DrawOutline();
		for (int i = 0; i < t.size(); i++) 
		{
			BallToTriangleCollision(&b.body, t[i]);
			t[i].DrawOutline();
			//t[i].DrawNormals();
		}


		glm::vec2 posi = glm::vec2(1860.0f - CameraPosition.x, 1020.0f - CameraPosition.y);


		posi.x = b.body.position.x ;
		posi.y = b.body.position.y ;


		RenderText("This is sample text", 25.0f , 25.0f , 1.0f, glm::vec4(0.5, 0.8f, 0.2f, 1.0f),true);
		
		
		
	}
};

int main()
{
	application app;
	app.init("app" , 1920, 1080, true);
	return 0;
}