#pragma once
class KinematicBody
{
public:
	ball body;
	glm::vec4 Color = glm::vec4(1.0f);
	void init(glm::vec2 position, float radius,glm::vec4 color = glm::vec4(1.0f))
	{
		body.position = position;
		body.r = radius;
		body.Kinematic = true;
		ballsptr.push_back(&body);
	}
	void Draw()
	{
		DrawCircle(body.position, body.r, 1.0f, Color);
	}
	void PreProcess(float dt)
	{
		Draw();
	}

	virtual void Process(float dt)
	{
		PreProcess(dt);
	}
};




class RigidBody
{
public:
	ball body;
	glm::vec4 Color = glm::vec4(1.0f);
	void init(glm::vec2 position, float radius, glm::vec4 color = glm::vec4(1.0f))
	{
		body.position = position;
		body.r = radius;
		body.Kinematic = false;
		ballsptr.push_back(&body);
	}
	void Draw()
	{
		DrawCircle(body.position, body.r, 1.0f, Color);
	}
	void PreProcess(float dt)
	{
		Draw();
		body.position += body.velocity * dt;
	}

	virtual void Process(float dt)
	{
		PreProcess(dt);
	}
};


