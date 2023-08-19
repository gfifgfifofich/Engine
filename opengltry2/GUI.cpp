#include "engine/Components/Engine.h"

void On_Create()
{// called once while starting app

}
void On_Update()
{// called every frame
	float width = 200.0f;
	glm::vec2 windowScale = { width,HEIGHT * 0.5f };
	glm::vec2 windowPosition = glm::vec2(WIDTH * -0.5f + width * 1.0f, 0.0f);
	float TextScale = 0.75f;
	glm::vec2 windowBegining = windowPosition - glm::vec2(windowScale.x, -windowScale.y);

	DrawCube(windowPosition, windowScale, 0.0f,glm::vec4(0.01f,0.01f,0.01f,0.4f));
	DrawText("Example", windowBegining - glm::vec2(0.0f,40* TextScale), TextScale);


}
int main()
{
	initEngine();
	return 0;
}
