#pragma once


void BallToPolygonCollision(ball* b, polygon p, float roughness = 1.0f)
{
	for (int i = 0; i < p.triangles.size(); i++)
	{
		glm::vec2 normal1 = p.triangles[i].l1.normal * (b->r + p.triangles[i].l1.width);

		if (PointToLineSideCheck(b->position - normal1, p.triangles[i].l1) &&
			PointToLineSideCheck(b->position , p.triangles[i].l2) &&
			PointToLineSideCheck(b->position , p.triangles[i].l3))
		{
			line l = p.triangles[i].l1;



			glm::vec2 CP = b->position - l.normal * b->r;



			glm::vec2 PointOnLine;
			if ((l.P1.x - l.P2.x) * (l.P1.x - l.P2.x) > (l.P1.y - l.P2.y) * (l.P1.y - l.P2.y))
			{
				float dif_x = CP.x - l.P1.x;
				float rel_pos = dif_x / (l.P1.x - l.P2.x);
				float dif_y = (l.P1.y - l.P2.y) * rel_pos;
				PointOnLine = glm::vec2(dif_x, dif_y) + l.P1;
			}
			else
			{
				float dif_y = CP.y - l.P1.y;
				float rel_pos = dif_y / (l.P1.y - l.P2.y);
				float dif_x = (l.P1.x - l.P2.x) * rel_pos;
				PointOnLine = glm::vec2(dif_x, dif_y) + l.P1;
			}

			glm::vec2 newpos = PointOnLine + l.normal * (b->r + l.width * 0.5f);


			glm::vec2 LineVector = l.P1 - l.P2;
			glm::vec2 BodyVector = l.P1 - b->position;


			if (DOT(LineVector, BodyVector) <= sqrlength(LineVector) && DOT(LineVector, BodyVector) >= 0.0f)
			{
				b->position = newpos;
				glm::vec2 velocity = DOT(b->velocity, glm::vec2(-l.normal.y, l.normal.x)) * glm::vec2(-l.normal.y, l.normal.x);
				float energy1 = DOT(b->velocity, l.normal);
				velocity -= l.normal * energy1 * roughness;
				b->velocity = velocity;
			}
		}
		if (sqrlength(b->position - p.triangles[i].l1.P1) < b->r * b->r ||
			sqrlength(b->position - p.triangles[i].l2.P1) < b->r * b->r ||
			sqrlength(b->position - p.triangles[i].l3.P1) < b->r * b->r)
		{

			glm::vec2 dif = glm::vec2(0.0f);

			if (sqrlength(b->position - p.triangles[i].l1.P1) < b->r * b->r)
				dif = b->position - p.triangles[i].l1.P1;
			else if (sqrlength(b->position - p.triangles[i].l2.P1) < b->r * b->r)
				dif = b->position - p.triangles[i].l2.P1;
			else if (sqrlength(b->position - p.triangles[i].l3.P1) < b->r * b->r)
				dif = b->position - p.triangles[i].l3.P1;

			float dist = length(dif);
			float distancedifference = b->r - dist;

			glm::vec2 n1 = -dif / dist;
			glm::vec2 CollisionLine = glm::vec2(-n1.y, n1.x);

			float energy1 = DOT(b->velocity, n1);


			glm::vec2 velocity1 = DOT(b->velocity, CollisionLine) * CollisionLine;

			velocity1 -= n1 * energy1 * roughness;


			b->velocity = velocity1;
			b->position += (dif / dist) * distancedifference;

		}
	}
}