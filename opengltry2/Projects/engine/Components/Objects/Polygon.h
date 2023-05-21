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
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	std::vector <SubTriangle> SubTriangles;
	float roughness = 1.0f;

	line lines[3] = { lines[0]= line(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
					  lines[1]= line(glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
					  lines[2]= line(glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f))  };


	glm::vec2 points[3];
	glm::vec2 midlePosition = glm::vec2(0.0f);
	void Update_Shape()
	{
		SubTriangles.clear();
		
		midlePosition = points[0] + points[1] + points[2];
		midlePosition /= 3;

		lines[0] = line(points[0], points[1]);
		lines[1] = line(points[1], points[2]);
		lines[2] = line(points[2], points[0]);

		if (!(PointToLineSideCheck(midlePosition, lines[0]) &&
			PointToLineSideCheck(midlePosition, lines[1]) &&
			PointToLineSideCheck(midlePosition, lines[2])))
		{
			glm::vec2 swaper = points[1];
			points[1] = points[2];
			points[2] = swaper;
			lines[0] = line(points[0], points[1]);
			lines[1] = line(points[1], points[2]);
			lines[2] = line(points[2], points[0]);
		}




		for (int i = 0; i < 3; i++)
		{
			SubTriangle temp_tri;
			glm::vec2 p1 = lines[i].P1;
			glm::vec2 p2 = lines[0].P1;
			glm::vec2 p3 = midlePosition;
			if (i + 1 < 3) p2 = lines[i + 1].P1;


			temp_tri.l1 = line(p1, p2);
			temp_tri.l1.width = 1.0f;
			temp_tri.l2 = line(p2, p3);
			temp_tri.l2.width = 0.0f;
			temp_tri.l3 = line(p3, p1);
			temp_tri.l3.width = 0.0f;





			SubTriangles.push_back(temp_tri);

		}

	}

	Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
	{
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		lines[0] = line(p1, p2);
		lines[1] = line(p2, p3);
		lines[2] = line(p3, p1);
		Update_Shape();
	}


	void DrawOutline()
	{
		DrawLine(points[0], points[1], 2.0f);
		DrawLine(points[1], points[2], 2.0f);
		DrawLine(points[2], points[0], 2.0f);
	}
	void DrawNormals()
	{
		glm::vec2 mid1 = points[0] + points[1];
		mid1 *=0.5f;
		glm::vec2 mid2 = points[1] + points[2];
		mid2 *= 0.5f;
		glm::vec2 mid3 = points[2] + points[0];
		mid3 *= 0.5f;


		DrawLine(mid1, mid1 + lines[0].normal * 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawLine(mid2, mid2 + lines[1].normal * 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawLine(mid3, mid3 + lines[2].normal * 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
};


// Should be defined clockwise
class polygon
{
public:
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	float roughness = 1.0f;
	std::vector <SubTriangle> triangles;

	std::vector <glm::vec2> points;

	glm::vec2 midle_point = glm::vec2(0.0f);

	SubTriangle temp_tri;

	void Update_Shape(bool updateMidlePosition = true)
	{
		triangles.clear();
		if (updateMidlePosition)
		{
			midle_point = glm::vec2(0.0f);


			for (int i = 0; i < points.size(); i++)
			{
				midle_point += points[i];
			}
			midle_point /= points.size();
		}

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


	void SaveAs(std::string name)
	{
		std::ofstream SaveFile(name);

		SaveFile << "m";
		std::string str = std::to_string(midle_point.x);
		SaveFile << str;
		SaveFile << " ";
		str = std::to_string(midle_point.y);
		SaveFile << str;
		SaveFile << "\n";


		for (int i = 0; i < points.size(); i++)
		{
			SaveFile << "p";
			std::string str = std::to_string(points[i].x);
			SaveFile << str;
			SaveFile << " ";

			str = std::to_string(points[i].y);
			SaveFile << str;

			SaveFile << "\n";
		}
		SaveFile.close();
	}


	void Load(std::string name)
	{
		std::ifstream f(name);
		if (!f.is_open())
			return;
		int i = 0;
		while (!f.eof())
		{
			i++;
			char line[128];
			f.getline(line, 128);
			std::strstream s;
			s << line;

			char junk;
			if (line[0] == 'm')
			{
				glm::vec2 point;
				s >> junk >> point.x >> point.y;
				midle_point = point;
			}

			if (line[0] == 'p')
			{
				glm::vec2 point;
				s >> junk >> point.x >> point.y;
				if (i < points.size())
					points[i] = point;
				else points.push_back(point);
			}


		}
		Update_Shape(false);
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