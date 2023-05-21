#pragma once

glm::vec2 CameraPosition = glm::vec2(0.0f);
glm::vec2 CameraScale = glm::vec2(1.0f);

//QUAD
unsigned int quadVAO, quadVBO,
ScreenVAO, ScreenVBO,
CircleVAO, CircleVBO
;
std::vector <glm::mat4> Circletranslations;
std::vector <glm::vec4> Circlecolors;

float ScaleMultiplyer = 0.043545f*0.05f;

float ScreenAspectRatio = 1.0f;

float ScreenDivisorX = 1.0;
float ScreenDivisorY = 1.0;


void DrawCircle(glm::vec2 position, float r, glm::vec4 color = glm::vec4(1.0f))
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x ) / ScreenDivisorX * CameraScale.x, (position.y ) / ScreenDivisorY *CameraScale.y, 0.0f));

	trans = glm::scale(trans, glm::vec3(r  * ScaleMultiplyer * CameraScale.x, r * ScaleMultiplyer * CameraScale.y, 0.0f));


	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
}
void DrawCircle(ball b, glm::vec4 color = glm::vec4(1.0f))
{
	glm::vec2 position = b.position;
	float r = b.r;
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) / ScreenDivisorX * CameraScale.x, (position.y) / ScreenDivisorY * CameraScale.y, 0.0f));

	trans = glm::scale(trans, glm::vec3(r * ScaleMultiplyer * CameraScale.x, r * ScaleMultiplyer * CameraScale.y, 0.0f));


	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
}

std::vector <glm::mat4> Quadtranslations;
std::vector <glm::vec4> Quadcolors;
void DrawCube(glm::vec2 position, glm::vec2 scale, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f),glm::vec3(
		(position.x) / ScreenDivisorX * CameraScale.x,
		(position.y) / ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x* CameraScale.x * ScaleMultiplyer, scale.y* CameraScale.y * ScaleMultiplyer, 0.0f));


	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);


}
void DrawCube(cube c, glm::vec4 color = glm::vec4(1.0f),glm::vec3 rotation=glm::vec3(0.0f))
{
	glm::vec2 position = c.position;
	glm::vec2 scale = glm::vec2(c.width, c.height);
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) / ScreenDivisorX * CameraScale.x,
		(position.y) / ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));


	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);
}


void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f))
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) / (0.20 * 1280);
	DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);
}

void DrawBall(ball b)
{
	glm::vec2 univec;
	univec.x = cos(b.rotation * 5) - sin(b.rotation * 5);
	univec.y = sin(b.rotation * 5) + cos(b.rotation * 5);
	DrawLine(b.position - univec * b.r * 0.7f, b.position + univec * b.r * 0.7f, 3.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	DrawLine(b.position + glm::vec2(-univec.y * b.r * 0.7f, univec.x * b.r * 0.7f), b.position + glm::vec2(univec.y * b.r * 0.7f, -univec.x * b.r * 0.7f), 3.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	DrawCircle(b);
}