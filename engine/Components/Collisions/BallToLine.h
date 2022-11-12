#pragma once


bool PointToLineSideCheck(glm::vec2 p, line l)
{
	// right from line
	if (DOT(p - l.P1, l.normal) <= 0.0f) return true;
	//left from line
	else return false;
}


void BallToLineCollision(ball* b, line l, float Roghness = 1.0f)
{
	glm::vec2 CP = b->position - l.normal * b->r ;
	bool inRange_x = false;
	bool inRange_y = false;

	if (l.P1.x < l.P2.x) { if (CP.x >= l.P1.x && CP.x <= l.P2.x) inRange_x = true; }
	else { if (CP.x <= l.P1.x && CP.x >= l.P2.x) inRange_x = true; }

	if (l.P1.y < l.P2.y) {if (CP.y >= l.P1.y && CP.y <= l.P2.y) inRange_y = true;}
	else { if (CP.y <= l.P1.y && CP.y >= l.P2.y) inRange_y = true; }

	if (inRange_x && inRange_y)
	{
		if (PointToLineSideCheck(CP - l.normal * (l.width * 0.5f), l) || PointToLineSideCheck(b->position - l.normal * (l.width * 0.5f), l))
		{
			glm::vec2 PointOnLine;
			if ((l.P1.x - l.P2.x) * (l.P1.x - l.P2.x) > (l.P1.y - l.P2.y) * (l.P1.y - l.P2.y))
			{
				float dif_x = CP.x - l.P1.x;
				float rel_pos = dif_x / (l.P1.x - l.P2.x);
				float dif_y = (l.P1.y - l.P2.y) * rel_pos;
				PointOnLine = glm::vec2(dif_x, dif_y) + l.P1;
				if (l.P1.x < l.P2.x)
				{
					if ((PointOnLine).x > l.P2.x)
						PointOnLine = l.P2;
					if ((PointOnLine).x < l.P1.x)
						PointOnLine = l.P1;
				}
				else
				{
					if ((PointOnLine).x < l.P2.x)
						PointOnLine = l.P2;
					if ((PointOnLine).x > l.P1.x)
						PointOnLine = l.P1;
				}
			}
			else
			{
				float dif_y = CP.y - l.P1.y;
				float rel_pos = dif_y / (l.P1.y - l.P2.y);
				float dif_x = (l.P1.x - l.P2.x) * rel_pos;
				PointOnLine = glm::vec2(dif_x, dif_y) + l.P1;
				if (l.P1.y < l.P2.y)
				{
					if ((PointOnLine).y > l.P2.y)
						PointOnLine = l.P2;
					if ((PointOnLine).y < l.P1.y)
						PointOnLine = l.P1;
				}
				else
				{
					if ((PointOnLine).y < l.P2.y)
						PointOnLine = l.P2;
					if ((PointOnLine).y > l.P1.y)
						PointOnLine = l.P1;
				}
			}


				b->position = PointOnLine + l.normal * (b->r + l.width*0.5f);



			glm::vec2 velocity = DOT(b->velocity, glm::vec2(-l.normal.y, l.normal.x)) * glm::vec2(-l.normal.y, l.normal.x);
			float energy1 = DOT(b->velocity, l.normal);

			velocity -= l.normal * energy1 * Roghness;
			b->velocity = velocity;

		}
	}

}

//void BallToLineCollision(ball* b, line l, float Roghness = 1.0f)
//{
//	glm::vec2 Collision_Point = b->position - l.normal * b->r;
//
//	if (Collision_Point.x >= l.P1.x && Collision_Point.x <= l.P2.x)
//	{
//
//
//		float dif_x = Collision_Point.x - l.P1.x;
//		float rel_pos = dif_x / (l.P1.x - l.P2.x);
//		float new_y = (l.P1.y - l.P2.y) * rel_pos;
//
//		if (Collision_Point.y - l.P1.y <= new_y + l.width)
//		{
//
//			glm::vec2 velocity = DOT(b->velocity, glm::vec2(-l.normal.y, l.normal.x)) * glm::vec2(-l.normal.y, l.normal.x);
//
//			float energy1 = DOT(b->velocity, l.normal);// basicly, a component of velocity, that is changed after collision
//			velocity -= l.normal * energy1 * Roghness;
//			b->velocity = velocity;
//
//			b->position = glm::vec2(dif_x, new_y) + l.P1 + l.normal * (b->r + l.width*0.5f);
//		}
//	}
//
//}