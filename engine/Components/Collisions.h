#pragma once





std::vector <ball*> ballsptr;
std::vector <cube> cubes;

// collision ball-cube, but cube's velocity/position is unchanged
void CircleToStaticQuadCollision(ball* b, cube quad)
{
    ball circle =*b;
    glm::vec2 posdifference = quad.position - circle.position;

    if (posdifference.x > quad.width)
        posdifference.x = quad.width;
    else if (posdifference.x < -quad.width)
        posdifference.x = -quad.width;
    if (posdifference.y > quad.height)
        posdifference.y = quad.height;
    else if (posdifference.y < -quad.height)
        posdifference.y = -quad.height;

    glm::vec2 distvec = (quad.position - posdifference) - circle.position;
    float dist = distvec.x * distvec.x + distvec.y * distvec.y;
    if (dist < circle.r * circle.r)
    {
        bool plane1, plane2;// y = x, y=-x;
        glm::vec2 relpos = circle.position - quad.position;
        if (relpos.y < relpos.x)
            plane1 = false;// under
        else
            plane1 = true; // above
        if (relpos.y < -relpos.x)
            plane2 = false;// under
        else
            plane2 = true; // above



        if (plane1 && plane2) {
            circle.position.y = quad.position.y - posdifference.y + circle.r;//up 2
            circle.position.x = quad.position.x - posdifference.x;
            circle.velocity.y *= -1;
        }
        if (!plane1 && !plane2) {
            circle.position.y = quad.position.y - posdifference.y - circle.r;//down 4
            circle.position.x = quad.position.x - posdifference.x;
            circle.velocity.y *= -1;
        }
        if (!plane1 && plane2) {
            circle.position.x = quad.position.x - posdifference.x + circle.r;//right 3
            circle.position.y = quad.position.y - posdifference.y;
            circle.velocity.x *= -1;
        }
        if (plane1 && !plane2) {
            circle.position.x = quad.position.x - posdifference.x - circle.r;//left 1
            circle.position.y = quad.position.y - posdifference.y;
            circle.velocity.x *= -1;
        }

    }
    *b =circle;
}


// proper, physically correct collision of 2 balls
void BtBCollision(ball* b1, ball* b2)
{


	
	glm::vec2 dif = b2->position - b1->position;
	if (sqrlength(dif) < (b1->r + b2->r) * (b1->r + b2->r))
	{
		//colidded blyat
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
bool BtBCollisionCheck(ball b1,ball b2)
{
	
	glm::vec2 dif = b1.position - b2.position;
	if (sqrlength(dif) < (b1.r + b2.r) * (b1.r + b2.r))
		return true;
	else
		return false;
}
/*Ball-Cuad collision chek
returns int from 0 to 3, represents 4 sides of cuad clocwise
else, returns -1 (if no collision)
like this:
    0
  3 c 1
    2
*/
int BtCCollisionCheck(ball b, cube c)
{


	glm::vec2 posdifference = c.position - b.position;

	if (posdifference.x > c.width)
		posdifference.x = c.width;
	else if (posdifference.x < -c.width)
		posdifference.x = -c.width;

	if (posdifference.y > c.height)
		posdifference.y = c.height;
	else if (posdifference.y < -c.height)
		posdifference.y = -c.height;

	glm::vec2 distvec = (c.position - posdifference) - b.position;
	float dist = distvec.x * distvec.x + distvec.y * distvec.y;
	if (dist < b.r * b.r)
	{
		bool plane1, plane2;// y = x, y=-x;
		glm::vec2 relpos = b.position - c.position;
		relpos.y /= c.height;
		relpos.x /= c.width;
		if (relpos.y < relpos.x)
			plane1 = false;// under y=x
		else
			plane1 = true; // above y=x
		if (relpos.y < -relpos.x)
			plane2 = false;// under y=-x
		else
			plane2 = true; // above y=-x

		if (plane1 && plane2) {
			return 1;//up 0
		}
		else if (!plane1 && plane2) {
			return 2;//right 1
		}
		else if (!plane1 && !plane2) {
			return 3;//down 2
		}
		else if (plane1 && !plane2) {
			return 4;//left 3
		}
		else return 0;
	}
}
