#pragma once
void SpringBetweenBalls(ball* a, ball* b,float springLength, float stiffness)
{
	glm::vec2 posdif = b->position - a->position;
	glm::vec2 SpringVector = Normalize(posdif) * springLength;

	glm::vec2 Difference = posdif - SpringVector;

	float m1 = a->mass;
	float m2 = b->mass;
	if (m1 == m2)
	{
		a->position += Difference * 0.5f * stiffness;
		b->position -= Difference * 0.5f * stiffness;

		a->velocity += Difference * 0.5f * stiffness;
		b->velocity -= Difference * 0.5f * stiffness;
	}
	else
	{

		if (m1 < m2)
		{
			float ratio = m1 / m2;
			ratio *= ratio;
			a->position += Difference * 0.5f * stiffness * (1.0f - ratio);
			b->position -= Difference * 0.5f * stiffness * ratio;

			a->velocity += Difference * 0.5f * stiffness * (1.0f - ratio);
			b->velocity -= Difference * 0.5f * stiffness * ratio;
		}
		else
		{
			float ratio = m2 / m1;
			ratio *= ratio;
			a->position += Difference * 0.5f * stiffness * ratio;
			b->position -= Difference * 0.5f * stiffness * (1.0f - ratio);

			a->velocity += Difference * 0.5f * stiffness * ratio;
			b->velocity -= Difference * 0.5f * stiffness * (1.0f - ratio);
		}
	}

}
void FixedSpringBetweenBalls(ball* a, ball* b, glm::vec2 SpringVector, float stiffness)
{
	glm::vec2 posdif = b->position - a->position;

	glm::vec2 Difference = posdif - SpringVector;

	float m1 = a->mass;
	float m2 = b->mass;
	if (m1 == m2)
	{
		a->position += Difference * 0.5f * stiffness;
		b->position -= Difference * 0.5f * stiffness;

		a->velocity += Difference * 0.5f * stiffness;
		b->velocity -= Difference * 0.5f * stiffness;
	}
	else
	{
		float m1 = a->mass;
		float m2 = b->mass;

		if (m1 < m2)
		{
			float ratio = m1 / m2;
			ratio *= ratio;
			a->position += Difference * 0.5f * stiffness * (1.0f - ratio);
			b->position -= Difference * 0.5f * stiffness * ratio;

			a->velocity += Difference * 0.5f * stiffness * (1.0f - ratio);
			b->velocity -= Difference * 0.5f * stiffness * ratio;
		}
		else
		{
			float ratio = m2 / m1;
			ratio *= ratio;
			a->position += Difference * 0.5f * stiffness * ratio;
			b->position -= Difference * 0.5f * stiffness * (1.0f - ratio);

			a->velocity += Difference * 0.5f * stiffness * ratio;
			b->velocity -= Difference * 0.5f * stiffness * (1.0f - ratio);
		}
	}
}



void SpringBetweenPoints(point* a, point* b, float springLength, float stiffness)
{
	glm::vec2 posdif = b->position - a->position;
	glm::vec2 SpringVector = Normalize(posdif) * springLength;

	glm::vec2 Difference = posdif - SpringVector;

	float m1 = a->mass;
	float m2 = b->mass;
	if (m1 == m2)
	{
		a->position += Difference * 0.5f * stiffness;
		b->position -= Difference * 0.5f * stiffness;

		a->velocity += Difference * 0.5f * stiffness;
		b->velocity -= Difference * 0.5f * stiffness;
	}
	else
	{
		float m1 = a->mass;
		float m2 = b->mass;

		if (m1 < m2)
		{
			float ratio = m1 / m2;
			ratio *= ratio;
			a->position += Difference * 0.5f * stiffness * (1.0f - ratio);
			b->position -= Difference * 0.5f * stiffness * ratio;

			a->velocity += Difference * 0.5f * stiffness * (1.0f - ratio);
			b->velocity -= Difference * 0.5f * stiffness * ratio;
		}
		else
		{
			float ratio = m2 / m1;
			ratio *= ratio;
			a->position += Difference * 0.5f * stiffness * ratio;
			b->position -= Difference * 0.5f * stiffness * (1.0f - ratio);

			a->velocity += Difference * 0.5f * stiffness * ratio;
			b->velocity -= Difference * 0.5f * stiffness * (1.0f - ratio);
		}
	}

}