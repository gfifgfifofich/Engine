#pragma once
struct MegaStruct
{
	ball b;
	cube c;
};

class KinematicBody
{
public:
	MegaStruct body;
	glm::vec2* position;
	glm::vec4 Color = glm::vec4(1.0f);
	int type = 0;
	void init(int type,glm::vec4 color = glm::vec4(1.0f))
	{
		this->type = type;
		if (type == CIRCLE) 
		{
			body.b.Kinematic = true;
			position = &body.b.position;

			ballsptr.push_back(&body.b);
		}
		else if (type == QUAD)
		{
			position = &body.c.position;
			cubes.push_back(&body.c);
		}
	}
	void Draw()
	{
		if (type == CIRCLE)
			DrawCircle(body.b.position, body.b.r, Color);
		else if (type == QUAD)
			DrawCube(body.c.position, glm::vec2(body.c.width, body.c.height),glm::vec3(0.0f), Color);
	}
	void PreProcess(float dt)
	{
		Draw();
		body.b.rotationVelocity = 0.0f;
		body.b.rotation = 0.0f;
		body.b.RotationForce = 0.0f;
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
		DrawBall(body);
	}
	void PreProcess(float dt)
	{
		Draw();
		body.rotation += body.rotationVelocity*dt;
		body.rotationVelocity += body.RotationForce /body.mass* dt;

		body.position += body.velocity * dt;
	}

	virtual void Process(float dt)
	{
		PreProcess(dt);
	}
};


