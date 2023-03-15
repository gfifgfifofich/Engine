#include "engine/Components/Engine.h"


class Player : public KinematicBody
{
public:
	glm::vec2 velocity = glm::vec2(0.0f);
	ParticleEmiter rockParticles;
	
	void Process(float dt) override
	{
		PreProcess(dt);
		rockParticles.InitialVelocity = velocity*0.25f + glm::vec2(0.0f,100);

		glm::vec2 velocityrandomness = velocity;
		if (velocity.x < 0.0f) velocityrandomness.x *= -1;
		if (velocity.y < 0.0f) velocityrandomness.y *= -1;
		rockParticles.VelocityRandomness = glm::vec4(-velocityrandomness.x * 0.5f, velocityrandomness.x * 0.5f, -velocityrandomness.y * 0.5f, velocityrandomness.y * 0.5f);

		if (body.c.CollisionSides[0]) velocity.y = 0.0f;

		velocity.y -= 1000 * dt;
		
		
		if (body.c.CollisionSides[2]) velocity.y = 0.0f;
		if (body.c.CollisionSides[1]) velocity.x = 0.0f;
		if (body.c.CollisionSides[3]) velocity.x = 0.0f;

		if (keys[GLFW_KEY_W] && body.c.CollisionSides[2])
		{
			velocity.y = 350;

			rockParticles.InitialVelocity = glm::vec2(0.0f, 450);
			rockParticles.VelocityRandomness = glm::vec4(-100* 0.5f, 100 * 0.5f, -100 * 0.5f, 100 * 0.5f);
			rockParticles.Spawn(glm::vec2(position->x , position->y - body.c.height), 20);
		}
		if (keys[GLFW_KEY_W] && body.c.CollisionSides[1]) 
		{
			velocity = glm::vec2(-600, 300);
			rockParticles.InitialVelocity = glm::vec2(-150, 600) * 0.75f;
			rockParticles.VelocityRandomness = glm::vec4(-150, 150, -100, 100) * 0.75f;
			rockParticles.Spawn(glm::vec2(position->x + body.c.width, position->y ), 10);
		}
		if (keys[GLFW_KEY_W] && body.c.CollisionSides[3])
		{
			velocity = glm::vec2(600, 300);
			rockParticles.InitialVelocity = glm::vec2(150, 600) * 0.75f;
			rockParticles.VelocityRandomness = glm::vec4(-150 , 150 , -100 , 100 )*0.75f;
			rockParticles.Spawn(glm::vec2(position->x - body.c.width, position->y), 10);

		}
		if (keys[GLFW_KEY_D] && velocity.x <500) velocity.x += 5000 * dt;
		if (keys[GLFW_KEY_A] && velocity.x > -500) velocity.x -= 5000 * dt;
		
		
		
		if (velocity.x < 25 && velocity.x>-25) velocity.x = 0;
		else if (!keys[GLFW_KEY_D] && !keys[GLFW_KEY_A]) 
		{
			velocity.x *= 0.9;
			rockParticles.InitialVelocity = velocity * 1.25f + glm::vec2(0.0f, 100);
			if (body.c.CollisionSides[2])
				rockParticles.Spawn(glm::vec2(position->x, position->y - body.c.height),2);
		}
		else if (body.c.CollisionSides[2])
			rockParticles.Spawn(glm::vec2(position->x, position->y - body.c.height),1);
		
		
		if (velocity.y < -1000) velocity.y = -1000;



		*position = *position + velocity * dt;
		body.c.CollisionSides[0] = false;
		body.c.CollisionSides[1] = false;
		body.c.CollisionSides[2] = false;
		body.c.CollisionSides[3] = false;
	}
};
struct tile
{
	cube body;
	glm::vec4 color;

};

const unsigned int WorldSizeX = 100;
const unsigned int WorldSizeY = 100;
tile tiles[WorldSizeX][WorldSizeY];
float step = 50.0f;
ParticleEmiter Sparks;
glm::vec4 colors[WorldSizeX][WorldSizeY];

float ScreenShake = 0.0f;

std::vector<ball> explosions;
std::vector<ball> debris;
float debriCleanUpInitTime = 3.0f;
float debriCleanUpTimer = 0.0f;
bool garbajCollecor = true;

void CrushTile(int x, int y)
{
	if (tiles[x][y].color.r == 1.0f)
	{
		glm::vec2 Pos = tiles[x][y].body.position;
		ball mouseball;
		mouseball.position = Pos;
		mouseball.r = 150;
		explosions.push_back(mouseball);
		DrawCircle(Pos, mouseball.r, glm::vec4(1.0f, 0.2f, 0.04f, 0.1f) * 10.0f);
		ChromaticPoint = Pos;

	}
	ScreenShake += 0.51;
	ball b;
	b.position.x = tiles[x][y].body.position.x - step * 0.5f;
	b.position.y = tiles[x][y].body.position.y - step * 0.5f;
	b.r = 5+rand()%20*0.1;
	b.Collision_Level = 1;
	b.Collision_Mask = 1;
	for (int i = 0; i < 5; i++)
	{
		b.velocity = glm::vec2(rand() % 1000 - 500, rand() % 1000 - 500);
		debris.push_back(b);
	}
	tiles[x][y].body.Collision_Level = -1;
	Sparks.Spawn(tiles[x][y].body.position, 30);
}
class application : public Engine
{
public:
	
	cube quad1;
	Player player;
	void On_Create() override
	{
		//generate white noise
		for (int i =1; i > 0; i--)
			for (int x = 0; x < WorldSizeX / (i); x++)
				for (int y = 0; y < WorldSizeY / (i); y++)
				{
					float noise = float(rand() % 10 )/ (15 + i);
					for (int px = 0;px<i;px++)
						for (int py = 0;py<i;py++)
							tiles[(x*i)+px][(y * i) +py].color += glm::vec4(noise, noise, noise, 1.0f);
				}

		//Linearly interpolate values, for smoooooooooth
		for (int i = 0; i < 5; i++) 
		{
			for (int x = 1; x < WorldSizeX - 1; x++)
				for (int y = 1; y < WorldSizeY - 1; y++)
				{
					colors[x][y].r = (tiles[x - 1][y + 1].color.r + tiles[x][y + 1].color.r + tiles[x + 1][y + 1].color.r +
								    tiles[x - 1][y].color.r + tiles[x][y].color.r + tiles[x + 1][y].color.r +
									tiles[x - 1][y - 1].color.r + tiles[x][y - 1].color.r + tiles[x + 1][y - 1].color.r) / 9.0f;
					colors[x][y] = glm::vec4(colors[x][y].r, colors[x][y].r, colors[x][y].r, 1.0f);
					
				}
			for (int x = 0; x < WorldSizeX; x++)
				for (int y = 0; y < WorldSizeY; y++)
				{
					tiles[x][y].color = colors[x][y];
				}
		}

		for(int x = 0; x < WorldSizeX;x++)
			for (int y = 0; y < WorldSizeY; y++)
			{
				tile t;
				cube TileCube;
				if (tiles[x][y].color.b < 0.28f) 
				{
					TileCube.Collision_Level = -1;
				}
				else 
				{
					TileCube.Collision_Level = 1;
				}
				t.color = tiles[x][y].color;
				TileCube.Collision_Mask = -1;
				TileCube.height = step;
				TileCube.width = step;
				TileCube.position = glm::vec2(step * x - step* WorldSizeX*0.5f, -step * (y-20));
				t.body = TileCube;
				tiles[x][y] = t;
				cubes.push_back(&tiles[x][y].body);
			}


		player.init(QUAD, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		player.body.c.width = 22.5;
		player.body.c.height = 22.5;
		player.body.c.position = glm::vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
		player.body.c.Collision_Level = 1;
		player.body.c.Collision_Mask = 1;



		player.rockParticles.acceleration = glm::vec2(0.0f, -500.0f);
		player.rockParticles.StartSize = glm::vec2(2.5f,2.5f);
		player.rockParticles.EndSize = glm::vec2(0.0f,0.0f);
		player.rockParticles.InitialVelocity = glm::vec2(0.0f,200.0f);
		player.rockParticles.StartColor = glm::vec4(0.7f,0.7f,0.7f,1.0f);
		player.rockParticles.EndColor = glm::vec4(0.7f,0.7f,0.7f,0.0f);
		player.rockParticles.Type = "LINE";


		Sparks.acceleration = glm::vec2(0.0f, -500.0f);
		Sparks.StartSize = glm::vec2(2.5f, 2.5f);
		Sparks.EndSize = glm::vec2(0.0f, 0.0f);
		Sparks.InitialVelocity = glm::vec2(0.0f, 200.0f);
		Sparks.VelocityRandomness = glm::vec4(-100.0f, 100.0f,-100,100);
		Sparks.StartColor = glm::vec4(10.0f, 0.2f, 0.04f, 10.0f)*0.2f;
		Sparks.EndColor = glm::vec4(0.7f, 0.7f, 0.7f, 0.0f);
		Sparks.Type = "LINE";
		ParticleEmiters.push_back(&Sparks);

		ParticleEmiters.push_back(&player.rockParticles);
	}

	void On_Update() override
	{

		ImGui::Begin("info");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
					1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
		ImGui::Checkbox("DrawColiders", &DrawCubicColiders);
		ImGui::Checkbox("HDR", &HDR);
		ImGui::Checkbox("Auto Clearing debris", &garbajCollecor);
		ImGui::Text("debris amount %i", debris.size());
		ImGui::End();




		//Camera processing
		ScreenShake *= 0.9;
		ChromaticStrength = ScreenShake * 0.005f;
		if (ScreenShake < 0.3f)
			ScreenShake = 0.0f;
		CameraPosition = player.body.c.position  + glm::vec2(rand() % 10, rand() % 10) * ScreenShake;
		if (keys[GLFW_KEY_X])
			CameraScale *= 1.01f;
		if (keys[GLFW_KEY_Z])
			CameraScale *= 0.99f;
		

		// Explosion Processing
		for (int i = 0; i < explosions.size(); i++)
		{
			glm::vec2 P = glm::vec2(explosions[i].position.x / step + WorldSizeX * 0.5f, -1 * explosions[i].position.y / step + 20);
			P = glm::vec2((int)P.x, (int)P.y);

			for (int x = P.x - explosions[i].r/step-1; x < P.x + explosions[i].r / step+1; x++)
				for (int y = P.y - explosions[i].r / step-1; y < P.y + explosions[i].r / step+1; y++)
					if(BtCCollisionCheck(explosions[i], tiles[x][y].body) && tiles[x][y].body.Collision_Level != -1)
						CrushTile(x, y);
		}
		for (int i = 0; i < explosions.size(); i++)
		{
			explosions.pop_back();
		}


		//debris processing
		int subst = 2;
		for(int i = 0; i<subst;i++)
		for (int i = 0; i < debris.size(); i++)
		{
			debris[i].position += debris[i].velocity * delta / (float)subst;
			debris[i].velocity.y -= 500*delta/ subst;

			glm::vec2 P = glm::vec2(debris[i].position.x / step + WorldSizeX * 0.5f, -1 * debris[i].position.y / step + 20);
			P = glm::vec2((int)P.x, (int)P.y);
			for (int x = P.x - 3; x < P.x + 3; x++)
				for (int y = P.y - 3; y < P.y + 3; y++)
					if (x > 0 && x < WorldSizeX && y>0 && y < WorldSizeY)
					if(tiles[x][y].body.Collision_Level==1)
						BallToStaticQuadCollision(&debris[i], tiles[x][y].body);
			for (int a = 0; a < debris.size(); a++)
				if (a > i)
					BtBCollision(&debris[i], &debris[a],0.6f);
			DrawCircle(debris[i].position, debris[i].r);
		}


		//debris Cleaning
		if (garbajCollecor) 
		{
			debriCleanUpTimer -= delta;
			if (debris.size() > 0 && debriCleanUpTimer <= 0.0f)
			{
				debris[0] = debris[debris.size() - 1];
				debris.pop_back();
			}
			else if (debris.size() == 0)
				debriCleanUpTimer = debriCleanUpInitTime;
			while (debris.size() > 1500)
				debris.pop_back();
		}


		// TNT Cursor
		if (buttons[GLFW_MOUSE_BUTTON_2])
		{
			glm::vec2 Pos = *player.position + (MousePosition - glm::vec2(WIDTH * 0.5f, HEIGHT * 0.5f)) / CameraScale.x;
			ball mouseball;
			mouseball.position = Pos;
			mouseball.r = 1;
			DrawCircle(Pos, mouseball.r, glm::vec4(1.0f, 0.2f, 0.04f, 0.1f) * 10.0f);
			for (int x = 0; x < WorldSizeX; x++)
				for (int y = 0; y < WorldSizeY; y++)
					if (BtCCollisionCheck(mouseball, tiles[x][y].body) && tiles[x][y].body.Collision_Level != -1)//Pos.x >= 0 && Pos.x < WorldSizeX && Pos.y >= 0 && Pos.y < WorldSizeY && 
					{
						tiles[x][y].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					}
		}


		//"Destructive Cursor"
		if (buttons[GLFW_MOUSE_BUTTON_1])
		{
			glm::vec2 Pos = *player.position + (MousePosition - glm::vec2(WIDTH*0.5f,HEIGHT * 0.5f))/CameraScale.x;
			glm::vec2 P = Pos ;

			ball mouseball;
			mouseball.position = Pos;
			mouseball.r = 1;
			P = glm::vec2((Pos.x) / step + WorldSizeX * 0.5f, -1 * (Pos.y) / step + 20);
			P = glm::vec2((int)P.x, (int)P.y);
			DrawCircle(Pos, mouseball.r, glm::vec4(1.0f, 0.2f, 0.04f, 0.1f)*10.0f);
			for (int x = P.x-3;x< P.x+3;x++)
			for (int y = P.y - 3;y< P.y + 3;y++)
				if(x>0&&x<WorldSizeX &&y>0&&y<WorldSizeY)
					if (BtCCollisionCheck(mouseball, tiles[x][y].body) && tiles[x][y].body.Collision_Level != -1)//Pos.x >= 0 && Pos.x < WorldSizeX && Pos.y >= 0 && Pos.y < WorldSizeY && 
					{
						CrushTile(x, y);
					}
		}
		

		//reset world
		if (keys[GLFW_KEY_SPACE])
		{
			*player.position = glm::vec2(WorldSizeX / 2 * step, 25 * step);
			for (int x = 0; x < WorldSizeX; x++)
				for (int y = 0; y < WorldSizeY; y++)
				{
					tiles[x][y].body.Collision_Level = 1;
				}
		}

		// World drawing
		for (int x = 0; x < WorldSizeX; x++)
			for (int y = 0; y < WorldSizeY; y++)
			{
				/*if(tiles[x][y].body.Collision_Level==1 &&
					tiles[x][y].body.position.x - CameraPosition.x > -1000 &&
					tiles[x][y].body.position.x - CameraPosition.x < WIDTH+1000 &&
					tiles[x][y].body.position.y - CameraPosition.y > -1000 &&
					tiles[x][y].body.position.y - CameraPosition.y < HEIGHT+1000 )*/
				if (tiles[x][y].body.Collision_Level == 1)
					DrawCube(tiles[x][y].body.position, glm::vec2(tiles[x][y].body.width, tiles[x][y].body.height), glm::vec3(0.0f), tiles[x][y].color);
			}
		player.Process(delta);


	}
};

int main()
{
	application app;
	app.init("terrario",1920,1080,true);
	return 0;
}