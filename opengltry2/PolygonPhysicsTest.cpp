#include "engine/Components/Engine.h"

polygon poly;
void On_Create()
{

	poly.Load("polygon.pol");
	poly.Update_MidlePos();
	poly.Update_Shape();
	poly.bounciness = 0.5f;
	poly.roughness = 0.5f;
}
bool PolygonToPointCollision(polygon* p, glm::vec2 point)
{
	int i = 0;
	while (i < p->triangles.size())
	{
		if (PointToLineSideCheck(point, p->triangles[i].lines[0]) &&
			PointToLineSideCheck(point, p->triangles[i].lines[1]) &&
			PointToLineSideCheck(point, p->triangles[i].lines[2]))
		{

			//if(p->colors.size()>0)
			//	p->colors[0] = { 0.0f,1.0f,1.0f,1.0f };
			//else
			//	p->colors.push_back({ 0.0f, 1.0f, 1.0f, 1.0f });

			int sti = 0;
			while (true)
				if (PointToLineSideCheck(point, p->triangles[i].SubTriangles[sti].l1) &&
					PointToLineSideCheck(point, p->triangles[i].SubTriangles[sti].l2) &&
					PointToLineSideCheck(point, p->triangles[i].SubTriangles[sti].l3))
					break;
				else
				{
					sti++;
					if (sti > 2) 
					{
						sti = 2;
						break;
					}
				}
			
			//Collision at triangle [i]

			line l = p->triangles[i].SubTriangles[sti].l1;





			glm::vec2 PointOnLine;
			// if difference X is greater than dif Y 
			/*if ((l.P1.x - l.P2.x) * (l.P1.x - l.P2.x) > (l.P1.y - l.P2.y) * (l.P1.y - l.P2.y))
			{
				float dif_x = point.x - l.P1.x;
				float rel_pos = dif_x / (l.P1.x - l.P2.x);
				float dif_y = (l.P1.y - l.P2.y) * rel_pos;
				PointOnLine = glm::vec2(dif_x, dif_y) + l.P1;
			}
			else
			{
				float dif_y = point.y - l.P1.y;
				float rel_pos = dif_y / (l.P1.y - l.P2.y);
				float dif_x = (l.P1.x - l.P2.x) * rel_pos;
				PointOnLine = glm::vec2(dif_x, dif_y) + l.P1;
			}*/

			PointOnLine = DOT(glm::vec2( - l.normal.y, l.normal.x), point - l.P1) * glm::vec2(-l.normal.y, l.normal.x) + l.P1;

			// difference between pol.position and the collision point
			glm::vec2 dif = PointOnLine - p->midlePosition;

			float dl = length(dif);
			glm::vec2 dn = dif/dl;
			glm::vec2 dnorm = -glm::vec2(-dn.y, dn.x);



			glm::vec2 n1 = l.normal;
			glm::vec2 CollisionLine = glm::vec2(-n1.y, n1.x);


			float vl = length(p->Velocity);






			glm::vec2 Pointvelocity =(p->Velocity + Rotate(dif,pi*0.5f) * p->RotationVelocity);

			//DrawLine(PointOnLine, p->midlePosition , 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			//DrawLine(PointOnLine, PointOnLine + Pointvelocity, 1.0f, glm::vec4(0.0f, 2.0f, 0.0f, 1.0f));


			

			float energy = DOT(Pointvelocity, n1);
			glm::vec2 velocity = DOT(Pointvelocity, CollisionLine) * CollisionLine * p->roughness;
			velocity -= n1 * energy * p->bounciness;
			float angle = get_relative_angle_between_points(velocity, -dif);


			p->RotationVelocity = DOT(velocity, -dn) / dl * sin(angle ) * pi;
			p->Velocity = velocity * cos(angle);



			angle = get_relative_angle_between_points(p->Force, dif);


			p->RotationForce = DOT(p->Force, dn) * sin(angle) * pi*0.5f* p->bounciness;



			p->Position += point - PointOnLine;

			return true;
		}
		else
		{
			if (p->colors.size() > 0)
				p->colors[0] = { 1.0f,1.0f,1.0f,1.0f };
			else
				p->colors.push_back({ 1.0f, 1.0f, 1.0f, 1.0f });
		}
		i++;
	}
	return false;
}

void On_Update()
{
	


	for (int s = 0; s < 10; s++) 
	{
		DrawCircle(MousePosition, 5.0f);
		poly.Force = { 0.0f, -1000.0f };
		PolygonToPointCollision(&poly, MousePosition);


		/*for (int i = 0; i < 3; i++)
		{
			DrawCircle(glm::vec2(poly.midlePosition.x - 50 + i * 50, -200.0f), 5.0f);
			PolygonToPointCollision(&poly, glm::vec2(poly.midlePosition.x - 50 + i * 50, -200.0f));
		}*/

		for (int i = 0; i < poly.Transofromedpoints.size(); i++)
		{
			DrawCircle(glm::vec2(poly.Transofromedpoints[i].x , -200.0f), 5.0f);
			PolygonToPointCollision(&poly, glm::vec2(poly.Transofromedpoints[i].x , -200.0f));
		}

		if (JustPressedkey[GLFW_KEY_SPACE])
		{
			poly.Position *= 0.0f;
			poly.Velocity *= 0.0f;
			poly.Rotation *= 0.0f;
			poly.RotationVelocity *= 0.0f;
		}

		poly.Process(delta*0.1f);
		poly.RotationForce = 0.0f;
		poly.DrawTriangles();
	}

}

int main()
{
	initEngine();

}
/*

			*/