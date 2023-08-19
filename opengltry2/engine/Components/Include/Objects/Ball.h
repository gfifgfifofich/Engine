#pragma once

struct point
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 Force = glm::vec2(0.0f);
	float mass = 1.0f;

	void Process(float dt);
	
};
//A simpler wersion of ball(no velocity, color ect.)
struct circle
{
	float r = 10.0f;
	glm::vec2 Position = glm::vec2(0.0f);
	glm::vec2 Velocity = glm::vec2(0.0f);
};


class ball
{
public:
	bool lighted = false;
	int Shaderid = -1;
	int Textureid = -1;
	int NormalMapId = -1;
	int id = -1;
	int type = -1;
	int Z_Index = 0;
	unsigned int Source = 0;
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels


	float r = 10;
	glm::vec4 color = glm::vec4(1.0f);
	glm::vec2 GroundVector = glm::vec2(0.0f, 0.0f);// stores last collision, helpfull for springs



	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 Force = glm::vec2(0.0f);

	float rotation = 0.0f;
	float rotationVelocity = 0.0f;
	float rotationForce = 0.0f;

	float mass = 1.0f;
	float roughness = 1.0f;
	float bounciness = 1.0f;

	bool FixedRotation=false;

	bool del = false;
	bool Kinematic = false;

	bool colided = false;

	void Process(float dt);
};
static std::vector <ball*> ballsptr;

