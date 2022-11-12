#pragma once
//QUAD
unsigned int quadVAO, quadVBO,
ScreenVAO, ScreenVBO,
CircleVAO, CircleVBO
;
std::vector <glm::mat4> Circletranslations;
std::vector <glm::vec4> Circlecolors;
std::vector <glm::vec4> CirclePosRadEdg; //(x,y,r,edgeWidth)


void DrawCircle(glm::vec2 position, float r, float edgesmoothness = 0.0001f, glm::vec4 color = glm::vec4(1.0f))
{


	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) / (HEIGHT / 2) - 1.25f + scrpos.x * 2, (position.y) / (HEIGHT / 2) - 1.0f + scrpos.y * 2, 0.0f));

	trans = glm::scale(trans, glm::vec3((r + edgesmoothness) / (0.0225 * HEIGHT), (r + edgesmoothness) / (0.0225 * HEIGHT), 0.0f));

	glm::vec4 PosRadEdge = glm::vec4(position.x, position.y, r, edgesmoothness);

	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
	CirclePosRadEdg.push_back(PosRadEdge);
}


std::vector <glm::mat4> Quadtranslations;
std::vector <glm::vec4> Quadcolors;
void DrawCube(glm::vec2 position, glm::vec2 scale, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
{
	scale *= 0.04;
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3((position.x) / (HEIGHT / 2) - 1.25f + scrpos.x * 2, (position.y) / (HEIGHT / 2) - 1.0f + scrpos.y * 2, 0.0f));

	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x, scale.y, 0.0f));


	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);


}


void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f))
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) / (0.20 * 1280);
	DrawCube(midpos, glm::vec2(length * 5.56f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);
}