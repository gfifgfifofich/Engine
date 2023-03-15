#pragma once


struct point
{
	float mass;
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
};

//A simpler wersion of ball(no velocity, color ect.)
struct circle
{
	float r = 10.0f;
	glm::vec2 position = glm::vec2(0.0f);
};


struct ball
{
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	float r = 10;
	glm::vec4 color = glm::vec4(1.0f);
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	float rotation = 0.0f;
	float rotationVelocity = 0.0f;

	float RotationForce = 0.0f;
	float Force = 0.0f;
	float mass = 1.0f;
	float roughness = 1.0f;

	bool del = false;
	bool Kinematic = false;
};