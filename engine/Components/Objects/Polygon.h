#pragma once

class SubTriangle
{
public:
	line l1 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	line l2 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	line l3 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
};
class Triangle
{
public:
	int Collision_Level = -1; // -1 - have no collision, >=0 - collision levels
	std::vector <SubTriangle> SubTriangles;

	line l1 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	line l2 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	line l3 = line(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
	glm::vec2 midlePosition = glm::vec2(0.0f);
	void Update_Shape()
	{
		SubTriangles.clear();
		midlePosition = glm::vec2(0.0f);
		midlePosition += l1.P1;
		midlePosition += l2.P1;
		midlePosition += l3.P1;
		midlePosition /= 3;

		for (int i = 0; i < 3; i++)
		{
			SubTriangle temp_tri;
			glm::vec2 p1 = l1.P1;
			glm::vec2 p2 = l2.P1;
			glm::vec2 p3 = l3.P1;

			temp_tri.l1 = line(p1, p2);
			temp_tri.l1.width = 1.0f;
			temp_tri.l2 = line(p2, p3);
			temp_tri.l2.width = 0.0f;
			temp_tri.l3 = line(p3, p1);
			temp_tri.l3.width = 0.0f;
			SubTriangles.push_back(temp_tri);

		}

	}


};



class polygon
{
public:
	int Collision_Level = -1; // -1 - do not collide, >=0 - collision levels
	std::vector <SubTriangle> triangles;

	std::vector <glm::vec2> points;

	glm::vec2 midle_point = glm::vec2(0.0f);

	SubTriangle temp_tri;

	void Update_Shape()
	{
		triangles.clear();
		midle_point = glm::vec2(0.0f);


		for (int i = 0; i < points.size(); i++)
		{
			midle_point += points[i];
		}
		midle_point /= points.size();
		

		for (int i = 0; i < points.size(); i++)
		{
			glm::vec2 p1;
			glm::vec2 p2;
			glm::vec2 p3;

			p1 = points[i];
			if (i + 1 < points.size()) p2 = points[i + 1];
			else p2 = points[0];
			p3 = midle_point;

			
			temp_tri.l1 = line(p1, p2);
			temp_tri.l1.width = 1.0f;
			temp_tri.l2 = line(p2, p3);
			temp_tri.l2.width = 0.0f;
			temp_tri.l3 = line(p3, p1);
			temp_tri.l3.width = 0.0f;
			triangles.push_back(temp_tri);

		}

	}

	void DrawOutline()
	{
		for (int i = 0; i < points.size(); i++)
		{
			
			if(i+1< points.size())DrawLine(points[i], points[i + 1], 2.0f);
			else DrawLine(points[i], points[0],2.0f);
		}
		
	}
	void DrawTriangles()
	{
		for (int i = 0; i < triangles.size(); i++)
		{
			DrawLine(triangles[i].l1.P1, triangles[i].l1.P2);
			DrawLine(triangles[i].l2.P1, triangles[i].l2.P2);
			DrawLine(triangles[i].l3.P1, triangles[i].l3.P2);
		}
	}

};