#pragma once
#include "Ball.h"
class SoftBody
{
public:
	std::vector <ball> balls;

	glm::vec2 Force;

	float springLength = 1.0f;
	float absorption = 0.2f;
	float stiffness = 10000.0f;
	float friction = 0.0f;

	bool deformation = false;
	float deformationRadius = 35.0f;
	float deformationCoefficient = 0.3f;

	std::vector <glm::ivec3> springs;

	

	void Process(float dt);
};

