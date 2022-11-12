#pragma once
struct cube
{
	int Collision_Level = -1; // -1 - do not collide, >=0 - collision levels
	float width = 0.0f;
	float height = 0.0f;
	glm::vec2 position = glm::vec2(0.0f);
};
