#pragma once
class KinematicBody
{
public:
	ball colider;
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec4 Color = glm::vec4(1.0f);
	void init(glm::vec2 position, float radius,glm::vec4 color = glm::vec4(1.0f))
	{
		colider.position = position;
		this->position = position;
		colider.r = radius;
		colider.Kinematic = true;
		ballsptr.push_back(&colider);
	}
	void Draw()
	{
		DrawCircle(colider.position, colider.r, 1.0f, Color);
	}
	void PreProcess(float dt)
	{
		Draw();
		colider.position = position;
	}

	virtual void Process(float dt)
	{
		PreProcess(dt);
	}
};




class RigidBody
{
public:
	ball colider;
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec4 Color = glm::vec4(1.0f);
	void init(glm::vec2 position, float radius, glm::vec4 color = glm::vec4(1.0f))
	{
		colider.position = position;
		colider.r = radius;
		colider.Kinematic = false;
		ballsptr.push_back(&colider);
	}
	void Draw()
	{
		DrawCircle(colider.position, colider.r, 1.0f, Color);
	}
	void PreProcess(float dt)
	{
		Draw();
		colider.position += colider.velocity * dt;
		velocity = colider.velocity;
	}

	virtual void Process(float dt)
	{
		PreProcess(dt);
	}
};