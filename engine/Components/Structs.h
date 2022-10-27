#pragma once
struct VerletObject
{
	float r = 10;
	glm::vec4 color = glm::vec4(1.0f);
	glm::vec2 ppos = glm::vec2(0.0f);
	glm::vec2 cpos = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 acceleration = glm::vec2(0.0f);
	float deltatime = 0.017f;
	void UpdatePos()
	{
		velocity = (cpos - ppos);

		ppos = cpos;


		cpos = cpos + velocity + (acceleration * deltatime * deltatime);


		acceleration = glm::vec2(0.0f);
	}

};
struct cube
{
	float width = 0.0f;
	float height = 0.0f;
	glm::vec2 position = glm::vec2(0.0f);
};

struct circle
{
	float r = 10.0f;
	glm::vec2 position = glm::vec2(0.0f);
};
struct ball
{
	float r = 10;
	float heat = 0.0f;
	glm::vec4 color = glm::vec4(1.0f);
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
};
