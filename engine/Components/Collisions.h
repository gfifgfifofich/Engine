#pragma once





std::vector <ball> balls;


std::vector <cube> Cubes;


ball CircleToStaticQuadCollision(ball b, cube quad)
{
    ball circle =b;
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
    return circle;
}



void BtBProcess(int i, float dt, float friction, bool ScreenCollision = true, bool QuadCollision = true)
{
	balls[i].position += balls[i].velocity * dt;
	balls[i].velocity -= balls[i].velocity * friction * dt;



	for (int a = 0; a < balls.size(); a++)
	{
		if (a > i)
		{
			glm::vec2 dif = balls[a].position - balls[i].position;
			if (sqrlength(dif) < (balls[i].r + balls[a].r) * (balls[i].r + balls[a].r))
			{
				//colidded blyat
				float dist = length(dif);
				float distancedifference = (balls[i].r + balls[a].r) - dist;

				// all the normals
				glm::vec2 n2 = dif / dist;
				glm::vec2 n1 = -n2;
				glm::vec2 CollisionLine = glm::vec2(-n1.y, n1.x);

				//positions first
				balls[i].position = balls[i].position + n1 * (distancedifference * 0.5f);
				balls[a].position = balls[a].position + n2 * (distancedifference * 0.5f);


				//velocities
				// "untached" component of velocity
				glm::vec2 velocity1 = DOT(balls[i].velocity, CollisionLine) * CollisionLine;
				glm::vec2 velocity2 = DOT(balls[a].velocity, -CollisionLine) * -CollisionLine;

				float energy1 = DOT(balls[i].velocity, n1);// basicly, a component of velocity, that is changed after collision
				float energy2 = DOT(balls[a].velocity, n2);

				if (balls[i].r != balls[a].r)
				{
					float mass1 = balls[i].r * balls[i].r * 3.14159f;
					float mass2 = balls[a].r * balls[a].r * 3.14159f;

					velocity1 -= n2 * (((mass1 - mass2) / (mass1 + mass2)) * energy1) + n1 * (((2 * mass2) / (mass1 + mass2)) * energy2);

					velocity2 -= n1 * (((mass2 - mass1) / (mass1 + mass2)) * energy2) + n2 * (((2 * mass1) / (mass1 + mass2)) * energy1);
				}
				else
				{
					velocity1 -= n1 * energy2;
					velocity2 -= n2 * energy1;
				}

				balls[i].velocity = velocity1;
				balls[a].velocity = velocity2;


			}
		}

	}
	if (QuadCollision)
		for (int a = 0; a < Cubes.size(); a++)
		{
			balls[i] = CircleToStaticQuadCollision(balls[i], Cubes[a]);
		}
	if (ScreenCollision)
	{
		// walls colisions 
		if (balls[i].position.y > HEIGHT - balls[i].r)
		{
			balls[i].position.y = HEIGHT - balls[i].r;
			balls[i].velocity -= balls[i].velocity * friction * dt;
			if (balls[i].velocity.y > 0)
				balls[i].velocity.y = -balls[i].velocity.y;
		}
		if (balls[i].position.y < 0 + balls[i].r)
		{
			balls[i].position.y = 0 + balls[i].r;
			balls[i].velocity -= balls[i].velocity * friction * dt;
			if (balls[i].velocity.y < 0)
				balls[i].velocity.y = -balls[i].velocity.y;
		}
		if (balls[i].position.x > WIDTH - balls[i].r)
		{
			balls[i].position.x = WIDTH - balls[i].r;
			balls[i].velocity -= balls[i].velocity * friction * dt;
			if (balls[i].velocity.x > 0)
				balls[i].velocity.x = -balls[i].velocity.x;
		}
		if (balls[i].position.x < 0 + balls[i].r)
		{
			balls[i].position.x = 0 + balls[i].r;
			balls[i].velocity -= balls[i].velocity * friction * dt;
			if (balls[i].velocity.x < 0)
				balls[i].velocity.x = -balls[i].velocity.x;
		}
	}

}