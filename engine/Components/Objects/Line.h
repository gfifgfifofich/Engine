#pragma once

class line
{
public:
	float width = 1.0f;
	glm::vec2 P1 = glm::vec2(0.0f);
	glm::vec2 P2 = glm::vec2(0.0f);
	glm::vec2 normal = glm::vec2(0.0f);

	line(glm::vec2 p1, glm::vec2 p2)
	{
		P1 = p1;
		P2 = p2;
		glm::vec2 d = P2 - P1;
		normal = glm::vec2(-d.y, d.x) / length(d);
	}

	void Calculate_normal()
	{
		glm::vec2 d = P2 - P1;
		normal = glm::vec2(-d.y, d.x) / length(d);
	}
};


