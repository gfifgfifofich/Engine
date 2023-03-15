#pragma once
class box
{
public:
	ball balls[4];

	float roughness = 1.0f;
	float bounciness = 3.0f;

	glm::vec2 Force = glm::vec2(0.0f);
	glm::vec2 position = glm::vec2(0.0f);

	glm::vec2 size = glm::vec2(100.0f);

	bool colided = false;

	void init(glm::vec2 position, glm::vec2 size)
	{
		this->size = size;

		balls[0].position = position + glm::vec2(size.x, size.y);
		balls[1].position = position + glm::vec2(size.x, -size.y);
		balls[2].position = position + glm::vec2(-size.x, -size.y);
		balls[3].position = position + glm::vec2(-size.x, size.y);
	}

	void Process(float dt, bool DrawStruts = false)
	{
		position = glm::vec2(0.0f);
		for (int i = 0; i < 4; i++)
		{
			balls[i].roughness = roughness;
			balls[i].bounciness = bounciness;
			balls[i].FixedRotation = true;
			balls[i].Force += Force;
			balls[i].Process(delta);
			balls[i].Force = glm::vec2(0.0f);

			balls[i].r = 0.1;

			position += balls[i].position;
		}
		position *= 0.25f;
		float diaglength = sqrt(size.y * 2.0f * size.y * 2.0f + size.x * 2.0f * size.x * 2.0f);
		for (int i = 0; i < 4; i++)
		{
			Strut(&balls[0], &balls[1], size.y * 2.0f, DrawStruts);
			Strut(&balls[0], &balls[2], diaglength, DrawStruts);
			Strut(&balls[0], &balls[3], size.x * 2.0f, DrawStruts);

			Strut(&balls[1], &balls[3], diaglength, DrawStruts);
			Strut(&balls[1], &balls[2], size.x * 2.0f, DrawStruts);

			Strut(&balls[2], &balls[3], size.y * 2.0f, DrawStruts);
		}
		colided = false;
	}

};