#include "engine/Components/Engine.h"
#include <glm/gtx/extended_min_max.hpp>


class Box
{
public:

	float roughness = 1.0f;
	float bounciness = 0.0f;

	float mass = 1.0f;

	glm::vec2 position = {0.0f,0.0f};
	glm::vec2 velocity = {0.0f,0.0f};
	glm::vec2 Force = {0.0f,0.0f};
	glm::vec2 Scale = {1.0f,1.0f};

	float Rotation = pi*0.0f;
	float RotationVelocity = pi*0.0f;
	float RotationForce = 0.0f;

	void Process(float dt)
	{
		position += velocity * dt;
		velocity += Force * dt / mass;

		Rotation += RotationVelocity * dt;
		RotationVelocity += RotationForce * dt / mass;
	}

};
void BoxToPointCollision(Box* b, glm::vec2 point)
{
	float roughness = b->roughness;
	float bounciness = b->bounciness;
	glm::vec2 xvec = { cos(b->Rotation), sin(b->Rotation) };
	glm::vec2 yvec = { -xvec.y, xvec.x };

	glm::vec2 p1 = xvec * b->Scale.x  + yvec * b->Scale.y + b->position; // left up
	glm::vec2 p2 = xvec * b->Scale.x  - yvec * b->Scale.y + b->position; // left down
	glm::vec2 p3 = -xvec * b->Scale.x + yvec * b->Scale.y + b->position; // right up
	glm::vec2 p4 = -xvec * b->Scale.x - yvec * b->Scale.y + b->position; // right down



	glm::vec2 v1 = p1 - p2; //"up" vector;
	glm::vec2 v2 = p2 - p1; //"down" vector;
	glm::vec2 v3 = p3 - p1; //"right" vector;
	glm::vec2 v4 = p1 - p3; //"left" vector;



	if (DOT(point - p2, v1) > 0.0f &&
		DOT(point - p1, v2) > 0.0f &&
		DOT(point - p1, v3) > 0.0f &&
		DOT(point - p3, v4) > 0.0f)
	{ //collision
		float l1 = sqrlength(point - p1);
		float l2 = sqrlength(point - p2);
		float l3 = sqrlength(point - p3);
		float l4 = sqrlength(point - p4);

		

		glm::vec2 cp1 = { 0.0f,0.0f };
		glm::vec2 cp2 = { 0.0f,0.0f };

		glm::vec2 UnrotatedPoint = Rotate(point - b->position, -b->Rotation);

		bool plane1, plane2;// y = x, y=-x;
		glm::vec2 relpos = UnrotatedPoint ;
		relpos.x *= b->Scale.y / b->Scale.x;
		if (relpos.y < relpos.x)
			plane1 = false;// under
		else
			plane1 = true; // above
		if (relpos.y < -relpos.x)
			plane2 = false;// under
		else
			plane2 = true; // above


		bool invertRV = false;

		if (plane1 && !plane2)
		{//left
			cp1 = p3;
			cp2 = p4;
			if (UnrotatedPoint.y > 0.0f) invertRV = true;
		}
		if (plane1 && plane2)
		{//up 
			cp1 = p3;
			cp2 = p1;
			if (UnrotatedPoint.x > 0.0f) invertRV = true;
		}
		if (!plane1 && plane2)
		{//right 
			cp1 = p1;
			cp2 = p2;
			if (UnrotatedPoint.y < 0.0f) invertRV = true;
		}
		if (!plane1 && !plane2)
		{//down 
			cp1 = p2;
			cp2 = p4;
			if (UnrotatedPoint.x < 0.0f) invertRV = true;
		}



		glm::vec2 CollisionLine = Normalize(cp2 - cp1);
		glm::vec2 norm = {-CollisionLine.y, CollisionLine.x};


		if (invertRV)
		{
			CollisionLine = -CollisionLine;
			norm = -norm;
		}


		

		glm::vec2 CollisionPoint = DOT(norm, cp1 - point) * norm + point;


		float CollisionPointDist = length(CollisionPoint - b->position);
		glm::vec2 CPnorm = (CollisionPoint - b->position) / CollisionPointDist;
		CPnorm = { -CPnorm.y,CPnorm.x };

		

		glm::vec2 Pointvelocity = b->RotationVelocity * 2 * pi * CollisionPointDist * -CPnorm  + b->velocity;

		

		float energy = DOT(Pointvelocity, norm);//for regular elastic collision
		glm::vec2 velocity = DOT(Pointvelocity, CollisionLine) * CollisionLine;//for regular elastic collision
		//velocity -= norm * energy ;//regular elastic collision
		
		float Benergy = DOT(b->velocity, norm);//for regular elastic collision
		glm::vec2 Bvelocity = DOT(b->velocity, CollisionLine) * CollisionLine;//for regular elastic collision
		Bvelocity -= norm * Benergy * bounciness;//regular elastic collision

		/*if (invertRV)
			b->RotationVelocity =length(Pointvelocity) / (2 * pi * CollisionPointDist  + length(Bvelocity));
		else			
			b->RotationVelocity = -length(Pointvelocity) / (2 * pi * CollisionPointDist + length(Bvelocity));*/

		//DrawLine(CollisionPoint, CollisionPoint + Pointvelocity, 2.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), false, CubeNormalMapTexture, 10);

		//glm::vec2 nvel = Normalize(b->velocity);

		float sine =  Pointvelocity.x * CPnorm.y - Pointvelocity.y * CPnorm.x;

		if(invertRV)
			b->RotationVelocity += -sine / (2 * pi * CollisionPointDist);
		else
			b->RotationVelocity += sine / (2 * pi * CollisionPointDist);
			
	



		b->velocity = Bvelocity + Pointvelocity  * (1.0f - roughness);


		b->position -= DOT(norm, cp1 - point) * norm;
	}
	




}


void BoxToTriangleCollision(Box* b, Triangle tri)
{
	
	BoxToPointCollision(b, tri.points[0]);
	BoxToPointCollision(b, tri.points[1]);
	BoxToPointCollision(b, tri.points[2]);
	

	glm::vec2 xvec = { cos(b->Rotation), sin(b->Rotation) };
	glm::vec2 yvec = { -xvec.y, xvec.x };

	float roughness = b->roughness;
	float bounciness = b->bounciness;

	glm::vec2 Points[4] = { xvec * b->Scale.x + yvec * b->Scale.y + b->position, // left up
	xvec * b->Scale.x - yvec * b->Scale.y + b->position, // left down
	-xvec * b->Scale.x + yvec * b->Scale.y + b->position, // right up
	-xvec * b->Scale.x - yvec * b->Scale.y + b->position }; // right down

	float RotVelChange = 0.0f;
	glm::vec2 PosChange = {0.0f,0.0f};
	glm::vec2 VelChange = { 0.0f,0.0f };

	int colisionCount = 0;

	
	for (int a = 0; a < 4; a++)
	{
		for (int i = 0; i < tri.SubTriangles.size(); i++)
		{
			glm::vec2 norm = tri.SubTriangles[i].l1.normal;

			if (PointToLineSideCheck(Points[a] - norm, tri.SubTriangles[i].l1) &&
				PointToLineSideCheck(Points[a], tri.SubTriangles[i].l2) &&
				PointToLineSideCheck(Points[a], tri.SubTriangles[i].l3))
			{

				colisionCount++;

				glm::vec2 CollisionLine = { norm.y,-norm.x };

				glm::vec2 CollisionPoint = DOT(norm, tri.SubTriangles[i].l1.P1 - Points[a]) * norm + Points[a];

				//DrawCircle(CollisionPoint, 10, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

				float CollisionPointDist = length(CollisionPoint - b->position);
				glm::vec2 CPnorm = (CollisionPoint - b->position) / CollisionPointDist;
				CPnorm = { -CPnorm.y,CPnorm.x };



				glm::vec2 Pointvelocity = b->RotationVelocity * 2 * pi * CollisionPointDist * CPnorm + b->velocity;



				float energy = DOT(Pointvelocity, norm);//for regular elastic collision
				glm::vec2 velocity = DOT(Pointvelocity, CollisionLine) * CollisionLine;//for regular elastic collision
				velocity -= norm * energy ;//regular elastic collision

				float Benergy = DOT(b->velocity, norm);//for regular elastic collision
				glm::vec2 Bvelocity = DOT(b->velocity, CollisionLine) * CollisionLine;//for regular elastic collision
				Bvelocity -= norm * Benergy * bounciness;//regular elastic collision


				float sine = Pointvelocity.x * CollisionLine.y - Pointvelocity.y * CollisionLine.x;

				if (DOT({ -b->velocity.y, b->velocity.x }, Points[a] - b->position) > 0.0f)
					RotVelChange += sine / (2 * pi * CollisionPointDist);
				else
					RotVelChange += -sine / (2 * pi * CollisionPointDist);

				/*if (DOT({ -b->velocity.y, b->velocity.x }, Points[a] - b->position)>0.0f)
					RotVelChange += length(Pointvelocity) / (2 * pi * CollisionPointDist + length(Bvelocity));
				else
					RotVelChange += -length(Pointvelocity) / (2 * pi * CollisionPointDist + length(Bvelocity));
				*/


				VelChange +=  Bvelocity + Pointvelocity * 0.5f * (1.0f - roughness) - b->velocity;
				PosChange += DOT(norm, tri.SubTriangles[i].l1.P1 - Points[a]) * norm;


			}
		}
	}
	if (colisionCount > 0)
	{
		b->velocity += VelChange / (float)colisionCount;
		b->RotationVelocity += RotVelChange;
		b->position += PosChange / (float)colisionCount;
	}

}


void BoxToStaticQuadCollision(Box* b, cube quad)
{
	glm::vec2 xvec = { cos(b->Rotation), sin(b->Rotation) };
	glm::vec2 yvec = { -xvec.y, xvec.x };

	glm::vec2 points[4] = { xvec * b->Scale.x + yvec * b->Scale.y + b->position, // left up
	xvec * b->Scale.x - yvec * b->Scale.y + b->position,// left down
	-xvec * b->Scale.x + yvec * b->Scale.y + b->position, // right up
	-xvec * b->Scale.x - yvec * b->Scale.y + b->position }; // right down

	for (int i = 0; i < 4; i++)
	{
		glm::vec2 posdifference = quad.position - points[i];

		if (posdifference.x > quad.width)
			posdifference.x = quad.width;
		else if (posdifference.x < -quad.width)
			posdifference.x = -quad.width;
		if (posdifference.y > quad.height )
			posdifference.y = quad.height ;
		else if (posdifference.y < -quad.height )
			posdifference.y = -quad.height ;


		bool plane1, plane2;// y = x, y=-x;
		glm::vec2 relpos = points[i] - quad.position;
		relpos.x *= quad.height / quad.width;
		if (relpos.y < relpos.x)
			plane1 = false;// under
		else
			plane1 = true; // above
		if (relpos.y < -relpos.x)
			plane2 = false;// under
		else
			plane2 = true; // above


		if (plane1 && !plane2)
		{//left
			b->position.x = quad.position.x - quad.width;
		}
		if (plane1 && plane2)
		{//up 
			b->position.y = quad.position.y + quad.height;
		}
		if (!plane1 && plane2)
		{//right 
			b->position.x = quad.position.x + quad.width;
		}
		if (!plane1 && !plane2)
		{//down 
			b->position.y = quad.position.y - quad.height;
		}
		posdifference = quad.position - points[i];

		if (posdifference.x > quad.width)
			posdifference.x = quad.width;
		else if (posdifference.x < -quad.width)
			posdifference.x = -quad.width;
		if (posdifference.y > quad.height)
			posdifference.y = quad.height;
		else if (posdifference.y < -quad.height)
			posdifference.y = -quad.height;

		BoxToPointCollision(b, posdifference);
	}

	BoxToPointCollision(b, quad.position + glm::vec2(quad.width, quad.height));
	BoxToPointCollision(b, quad.position + glm::vec2(quad.width, -quad.height));
	BoxToPointCollision(b, quad.position + glm::vec2(-quad.width, quad.height));
	BoxToPointCollision(b, quad.position + glm::vec2(-quad.width, -quad.height));

}

	Box box;
	cube c;
	polygon pol;
	void On_Create()
	{
		pol.add_Point(glm::vec2(1.0f,0.0f),true);
		pol.add_Point(glm::vec2(0.0f,-1.0f),true);
		pol.add_Point(glm::vec2(-1.0f,0.0f),true);
		c.width = 200.0f;
		c.height = 200.0f;

		box.Scale = { 50.0f,50.0f };
		box.position = { 0.0f,0.0f };
		box.Force.y = -1000;
		pol.colors.push_back(glm::vec4(1.0f));
	}
	void On_Update() 
	{
		//c.position = MousePosition;
		float size = 100.0f;
		pol.points[0] = MousePosition + glm::vec2(1.0f, 0.0f) * size;
		pol.points[1] = MousePosition + glm::vec2(0.0f, -2.0f) * size;
		pol.points[2] = MousePosition + glm::vec2(-1.0f, 0.0f) * size;
		pol.Update_Shape();
		if (keys[GLFW_KEY_R])
		{

			box.Scale = { 50.0f,50.0f };
			box.position = { 0.0f,0.0f };
			box.velocity = { 0.0f,0.0f };
			box.RotationVelocity = pi*0.0f;
			box.Rotation = pi*0.01f;

		}

		box.Process(delta);

		//pol.DrawTrianglesOutlines();
		//pol.DrawTriangles();
		//BoxToStaticQuadCollision(&box, c);
		//BoxToTriangleCollision(&box, pol.triangles[0]);
		BoxToPointCollision(&box, MousePosition);
		DrawCircle(MousePosition, 10);
		DrawCube(box.position, box.Scale, box.Rotation);
		//DrawCube(c);
	}
int main()
{

	initEngine();
	return 0;
}
