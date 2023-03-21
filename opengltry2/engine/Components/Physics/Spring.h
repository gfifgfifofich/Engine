#pragma once

void Spring(point* p1, point* p2, glm::vec2 Difference, float stiffness, float absorption = 0.0f)
{

	glm::vec2 Change1 = Difference * 0.5f * stiffness;
	glm::vec2 Change2 = -Difference * 0.5f * stiffness;
	glm::vec2 norm = Normalize(p2->position - p1->position);


	glm::vec2 vel1 = p1->velocity - p2->velocity;
	glm::vec2 vel2 = p2->velocity - p1->velocity;


	glm::vec2 axis1 = DOT(vel1, norm) * norm;
	glm::vec2 axis2 = DOT(vel2, norm) * norm;
	

	p1->Force += Change1 - axis1 * absorption;
	p2->Force += Change2 - axis2 * absorption;

}



void SpringBetweenBalls(ball* a, ball* b, float springLength, float stiffness, float absorption = 0.0f)
{
	glm::vec2 posdif = b->position - a->position;

	glm::vec2 Difference = posdif - Normalize(posdif) * springLength;



	point p1;
	p1.position = a->position;
	p1.velocity = a->velocity;
	p1.Force = a->Force;
	point p2;
	p2.position = b->position;
	p2.velocity = b->velocity;
	p2.Force = b->Force;
	Spring(&p1, &p2, Difference, stiffness, absorption);

	a->position = p1.position ;
	a->velocity = p1.velocity;
	a->Force = p1.Force;
	b->position = p2.position;
	b->velocity = p2.velocity;
	b->Force = p2.Force;
}



void FixedSpringBetweenBalls(ball* a, ball* b, glm::vec2 SpringVector, float stiffness, float absorption = 0.0f)
{
	glm::vec2 posdif = b->position - a->position;

	glm::vec2 Difference = posdif - SpringVector;

	point p1;
	p1.position = a->position;
	p1.velocity = a->velocity;
	p1.Force = a->Force;
	point p2;
	p2.position = b->position;
	p2.velocity = b->velocity;
	p2.Force = b->Force;
	Spring(&p1, &p2, Difference, stiffness, absorption);

	a->position = p1.position;
	a->velocity = p1.velocity;
	a->Force = p1.Force;
	b->position = p2.position;
	b->velocity = p2.velocity;
	b->Force = p2.Force;
}



void SpringBetweenPoints(point* a, point* b, float springLength, float stiffness, float absorption = 0.0f)
{
	glm::vec2 posdif = b->position - a->position;
	glm::vec2 SpringVector = Normalize(posdif) * springLength;

	glm::vec2 Difference = posdif - SpringVector;

	Spring(a, b, Difference, stiffness, absorption);

}

void SpringBallToPoint(ball* a, point* b, float springLength, float stiffness, float absorption = 0.0f)
{
	glm::vec2 posdif = b->position - a->position;
	glm::vec2 SpringVector = Normalize(posdif) * springLength;

	glm::vec2 Difference = posdif - SpringVector;

	point p1;
	p1.position = a->position;
	p1.velocity = a->velocity;
	p1.Force = a->Force;
	Spring(&p1, b, Difference, stiffness, absorption);

	a->position = p1.position;
	a->velocity = p1.velocity;
	a->Force = p1.Force;
}


