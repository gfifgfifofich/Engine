#pragma once
#include "../Drawing.h"
#include "line.h"
#include "../Collisions/BallToLine.h"

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

	line lines[3] = { lines[0] = line(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
					  lines[1] = line(glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
					  lines[2] = line(glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f)) };


	glm::vec2 points[3];
	glm::vec2 midlePosition = glm::vec2(0.0f);
	void Update_Shape();

	Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);


	void DrawOutline(glm::vec4 color = glm::vec4(1.0f));
	void DrawNormals();
};


// Should be defined clockwise
class polygon
{
public:
	bool lighted = false;
	int Textureid = -1;
	int NormalMapId = -1;
	int id = -1;
	int Z_Index = 0;
	// Level - on which level it is, Mask - with which level it collides
	int Collision_Level = 0; // -1 - do not collide, >=0 - collision levels
	int Collision_Mask = 0; // -1 - do not collide, >=0 - collision levels
	float roughness = 1.0f;
	std::vector <Triangle> triangles;

	std::vector <glm::vec4> colors = { {1.0f,1.0f,1.0f,1.0f} }; // one - for whole poly, two or more for random color, colors_amount=triangles_amount foreach


	//glm::vec2 position = glm::vec2(0.0f);

	std::vector <glm::vec2> points;
	std::vector <glm::vec2> TexturePoints;
	std::vector <glm::ivec3> indexes;

	glm::vec2 position = glm::vec2(0.0f);

	unsigned int Texture;

	std::vector <glm::vec4> MiscPoints;



	int state = 0;

	void Move(glm::vec2 position);



	void add_Point(glm::vec2 point, bool addindex = false);

	void Update_Shape();

	void SaveAs(std::string name);


	void Load(std::string name);



	void DrawOutline(glm::vec4 color = glm::vec4(1.0f));
	void DrawTrianglesOutlines(glm::vec4 color = glm::vec4(1.0f));

	void DrawTriangles();


};