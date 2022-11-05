#pragma once




void BallToLineCollision(ball* b, line l, float Roghness = 1.0f)
{
	glm::vec2 Collision_Point = b->position - l.normal * b->r;

	if (Collision_Point.x >= l.P1.x && Collision_Point.x <= l.P2.x)
	{
		glm::vec2 Collision_Point = b->position - l.normal * b->r;


		float dif_x = Collision_Point.x - l.P1.x;

		float rel_pos = dif_x / (l.P1.x - l.P2.x);
		float new_y = (l.P1.y - l.P2.y) * rel_pos;

		if (Collision_Point.y - l.P1.y <= new_y + l.width)
		{

			glm::vec2 velocity = DOT(b->velocity, glm::vec2(-l.normal.y, l.normal.x)) * glm::vec2(-l.normal.y, l.normal.x);

			float energy1 = DOT(b->velocity, l.normal);// basicly, a component of velocity, that is changed after collision
			velocity -= l.normal * energy1 * Roghness;
			b->velocity = velocity;

			b->position = glm::vec2(dif_x, new_y) + l.P1 + l.normal * (b->r + l.width*0.5f);
		}
	}

}