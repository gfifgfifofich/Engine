#pragma once
// proper, physically correct collision of 2 balls
void BtBCollision(ball* b1, ball* b2)
{



	glm::vec2 dif = b2->position - b1->position;
	if (sqrlength(dif) < (b1->r + b2->r) * (b1->r + b2->r))
	{
		float dist = length(dif);
		float distancedifference = (b1->r + b2->r) - dist;

		// all the normals
		glm::vec2 n2 = dif / dist;
		glm::vec2 n1 = -n2;
		glm::vec2 CollisionLine = glm::vec2(-n1.y, n1.x);

		//positions first
		b1->position = b1->position + n1 * (distancedifference * 0.5f);
		b2->position = b2->position + n2 * (distancedifference * 0.5f);


		//velocities
		// "untached" component of velocity
		glm::vec2 velocity1 = DOT(b1->velocity, CollisionLine) * CollisionLine;
		glm::vec2 velocity2 = DOT(b2->velocity, -CollisionLine) * -CollisionLine;

		float energy1 = DOT(b1->velocity, n1);// basicly, a component of velocity, that is changed after collision
		float energy2 = DOT(b2->velocity, n2);

		if (b1->r != b2->r)
		{
			float mass1 = b1->r * b1->r * 3.14159f;
			float mass2 = b2->r * b2->r * 3.14159f;

			velocity1 -= n2 * (((mass1 - mass2) / (mass1 + mass2)) * energy1) + n1 * (((2 * mass2) / (mass1 + mass2)) * energy2);

			velocity2 -= n1 * (((mass2 - mass1) / (mass1 + mass2)) * energy2) + n2 * (((2 * mass1) / (mass1 + mass2)) * energy1);
		}
		else
		{
			velocity1 -= n1 * energy2;
			velocity2 -= n2 * energy1;
		}

		if (!b1->Kinematic) b1->velocity = velocity1;

		if (!b2->Kinematic) b2->velocity = velocity2;


	}

}

//Check if b1 collides with b2
bool BtBCollisionCheck(ball b1, ball b2)
{

	glm::vec2 dif = b1.position - b2.position;
	if (sqrlength(dif) < (b1.r + b2.r) * (b1.r + b2.r))
		return true;
	else
		return false;
}