#pragma once


void BallToPolygonCollision(ball* b, polygon p)
{
	float roughness = b->roughness > p.roughness ? p.roughness : b->roughness;

	for (int i = 0; i < p.triangles.size(); i++)
	{
		glm::vec2 normal1 = p.triangles[i].l1.normal * (b->r + p.triangles[i].l1.width);

		if (PointToLineSideCheck(b->position - normal1, p.triangles[i].l1) &&
			PointToLineSideCheck(b->position, p.triangles[i].l2) &&
			PointToLineSideCheck(b->position, p.triangles[i].l3))
		{
			line l = p.triangles[i].l1;



			glm::vec2 CP = b->position - l.normal * b->r;// collision point



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

			glm::vec2 newpos = PointOnLine + l.normal * (b->r + l.width * 1.0f);


			glm::vec2 LineVector = l.P1 - l.P2;
			glm::vec2 BodyVector = l.P1 - b->position;


			if (DOT(LineVector, BodyVector) <= sqrlength(LineVector) && DOT(LineVector, BodyVector) >= 0.0f)
			{
				BallToPointCollision(b, PointOnLine, roughness);
			}
		}
		else if (sqrlength(b->position - p.triangles[i].l1.P1) < b->r * b->r)BallToPointCollision(b, p.triangles[i].l1.P1,roughness);
		else if	(sqrlength(b->position - p.triangles[i].l2.P1) < b->r * b->r)BallToPointCollision(b, p.triangles[i].l2.P1, roughness);
		else if	(sqrlength(b->position - p.triangles[i].l3.P1) < b->r * b->r)BallToPointCollision(b, p.triangles[i].l3.P1, roughness);
		
	}
}



void BallToTriangleCollision(ball* b, Triangle p)
{
	float roughness = b->roughness > p.roughness ? p.roughness : b->roughness;

	for (int i = 0; i < p.SubTriangles.size(); i++)
	{
		glm::vec2 normal1 = p.SubTriangles[i].l1.normal * (b->r + p.SubTriangles[i].l1.width);

		if (PointToLineSideCheck(b->position - normal1, p.SubTriangles[i].l1) &&
			PointToLineSideCheck(b->position, p.SubTriangles[i].l2) &&
			PointToLineSideCheck(b->position, p.SubTriangles[i].l3))
		{
			line l = p.SubTriangles[i].l1;



			glm::vec2 CP = b->position - l.normal * b->r; // collision point



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
			glm::vec2 newpos = PointOnLine + l.normal * (b->r + l.width * 1.0f);


			glm::vec2 LineVector = l.P1 - l.P2;
			glm::vec2 BodyVector = l.P1 - b->position;


			if (DOT(LineVector, BodyVector) <= sqrlength(LineVector) && DOT(LineVector, BodyVector) >= 0.0f)
			{
				BallToPointCollision(b, PointOnLine, roughness);
			}
		}
		else if (sqrlength(b->position - p.SubTriangles[i].l1.P1) < b->r * b->r)BallToPointCollision(b, p.SubTriangles[i].l1.P1, roughness);
		else if (sqrlength(b->position - p.SubTriangles[i].l2.P1) < b->r * b->r)BallToPointCollision(b, p.SubTriangles[i].l2.P1, roughness);
		else if (sqrlength(b->position - p.SubTriangles[i].l3.P1) < b->r * b->r)BallToPointCollision(b, p.SubTriangles[i].l3.P1, roughness);
		
	}
}