#pragma once
//A simpler wersion of ball(no velocity, color ect.)
struct circle
{
	float r = 10.0f;
	glm::vec2 position = glm::vec2(0.0f);
};

struct ball
{
	float r = 10;
	glm::vec4 color = glm::vec4(1.0f);
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	bool del = false;
	bool Kinematic = false;
};