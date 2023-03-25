#pragma once


struct point
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 Force = glm::vec2(0.0f);
	float mass = 1.0f;

	void Process(float dt)
	{
		glm::vec2 AccumulatorPosition[4];
		glm::vec2 AccumulatorVelocity[4];

		float massdivisor = 1.0f / mass;

		// k1
		AccumulatorVelocity[0] = Force * massdivisor;
		AccumulatorPosition[0] = velocity;

		// k2
		AccumulatorVelocity[1] = Force * massdivisor + 0.5f * dt * AccumulatorVelocity[0];
		AccumulatorPosition[1] = velocity + 0.5f * dt * AccumulatorPosition[0];

		// k3
		AccumulatorVelocity[2] = Force * massdivisor + 0.5f * dt * AccumulatorVelocity[1];
		AccumulatorPosition[2] = velocity + 0.5f * dt * AccumulatorPosition[1];
		// k4
		AccumulatorVelocity[3] = Force * massdivisor + dt * AccumulatorVelocity[2];
		AccumulatorPosition[3] = velocity + dt * AccumulatorPosition[2];

		float invdt6 = (dt / 6.0f);

		position += invdt6 * (AccumulatorPosition[0] + 2.0f * AccumulatorPosition[1] + 2.0f * AccumulatorPosition[2] + AccumulatorPosition[3]);
		velocity += invdt6 * (AccumulatorVelocity[0] + 2.0f * AccumulatorVelocity[1] + 2.0f * AccumulatorVelocity[2] + AccumulatorVelocity[3]);

	}
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
	int Textureid = -1;

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

	void Process(float dt)
	{
		glm::vec2 AccumulatorPosition[4];
		glm::vec2 AccumulatorVelocity[4];

		float AccumulatorRotation[4];
		float AccumulatorRotationVelocity[4];
		
		float massdivisor = 1.0f / mass;

		// k1
		AccumulatorVelocity[0] =  Force * massdivisor;
		AccumulatorRotationVelocity[0] = rotationForce * massdivisor;
		AccumulatorPosition[0] =velocity;
		AccumulatorRotation[0] = rotationVelocity;

		// k2
		AccumulatorVelocity[1] = Force * massdivisor + 0.5f * dt * AccumulatorVelocity[0];
		AccumulatorRotationVelocity[1] = rotationForce * massdivisor + 0.5f * dt * AccumulatorRotationVelocity[0];
		AccumulatorPosition[1] = velocity + 0.5f * dt * AccumulatorPosition[0];
		AccumulatorRotation[1] = rotationVelocity + 0.5f * dt * AccumulatorRotation[0];

		// k3
		AccumulatorVelocity[2] = Force * massdivisor + 0.5f * dt * AccumulatorVelocity[1];
		AccumulatorRotationVelocity[2] = rotationForce * massdivisor + 0.5f * dt * AccumulatorRotationVelocity[1];
		AccumulatorPosition[2] = velocity + 0.5f * dt * AccumulatorPosition[1];
		AccumulatorRotation[2] = rotationVelocity + 0.5f * dt * AccumulatorRotation[1];

		// k4
		AccumulatorVelocity[3] = Force * massdivisor + dt * AccumulatorVelocity[2];
		AccumulatorRotationVelocity[3] = rotationForce * massdivisor + dt * AccumulatorRotationVelocity[2];
		AccumulatorPosition[3] =  velocity + dt * AccumulatorPosition[2];
		AccumulatorRotation[3] =  rotationVelocity + dt * AccumulatorRotation[2];

		float invdt6 = (dt / 6.0f);

		position += invdt6 * (AccumulatorPosition[0] + 2.0f * AccumulatorPosition[1] + 2.0f * AccumulatorPosition[2] + AccumulatorPosition[3]);
		velocity += invdt6 * (AccumulatorVelocity[0] + 2.0f * AccumulatorVelocity[1] + 2.0f * AccumulatorVelocity[2] + AccumulatorVelocity[3]);
		rotation += invdt6 * (AccumulatorRotation[0] + 2.0f * AccumulatorRotation[1] + 2.0f * AccumulatorRotation[2] + AccumulatorRotation[3]);
		rotationVelocity += invdt6 *(AccumulatorRotationVelocity[0] + 2.0f * AccumulatorRotationVelocity[1] + 2.0f * AccumulatorRotationVelocity[2] + AccumulatorRotationVelocity[3]);
		
		
		/*position += velocity *dt;
		velocity += Force/mass * dt;
		rotation += rotationVelocity * dt;
		rotationVelocity += rotationForce/mass * dt;*/
	}

};