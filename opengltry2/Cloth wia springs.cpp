#include "engine/Components/Engine.h"


const int clothSizeX = 50;
const int clothSizeY = 50;
point points[clothSizeX][clothSizeY];


	float g = 1.0f;
	float Size = 4.5f;
	float Stiffness = 0.5f;

	void On_Create() 
	{
		for (int x =0;x< clothSizeX;x++)
			for (int y = 0; y < clothSizeY; y++)
			{
				points[x][y].mass = 1.0f;
				points[x][y].position = glm::vec2(5*x,5*y + 100);

			}
	}
	void On_Update() 
	{
		ImGui::Begin("lul");
		ImGui::SliderFloat("Length", &Size,1.0f,100.0f);
		ImGui::SliderFloat("Stiffnes", &Stiffness,0.0f,1.0f);
		ImGui::SliderFloat("Gravity",&g,1.0f,100.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate);
		ImGui::End();

		for (int x = 0; x < clothSizeX; x++)
			for (int y = 0; y < clothSizeY; y++)
			{
				points[x][y].Force.y -= g * dt_of_sim;

				if (buttons[GLFW_MOUSE_BUTTON_2])
				{
					float str = sqrlength(MousePosition - points[x][y].position);
					points[x][y].Force += Normalize(MousePosition - points[x][y].position)/(str*0.001f);
				}
				if (x > 0)
				{
					DrawLine(points[x][y].position, points[x - 1][y].position);
					SpringBetweenPoints(&points[x][y], &points[x - 1][y], Size, Stiffness, 1.0f);
				}
				if (y > 0)
				{
					DrawLine(points[x][y].position, points[x][y - 1].position);
					SpringBetweenPoints(&points[x][y], &points[x][y - 1], Size, Stiffness,1.0f);
				}

				//DrawCircle(points[x][y]);
				points[x][y].Process(dt_of_sim);
				if (y == clothSizeY - 1)
				{
					points[x][y].position = glm::vec2(Size * x, 5 * y + 10);
					points[x][y].velocity = glm::vec2(0.0f);
				}

			}
	}
int main()
{
	initEngine("app", 1920, 1050, false);
	return 0;
}