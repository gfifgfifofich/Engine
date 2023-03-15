#pragma once
struct cube
{
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	float width = 0.0f;
	float height = 0.0f;
	bool CollisionSides[4];
	float roughness = 1.0f;
	glm::vec2 position = glm::vec2(0.0f);
};
