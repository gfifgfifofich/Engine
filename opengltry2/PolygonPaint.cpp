


#include "engine/Components/Engine.h"


polygon poly;

	

	int grabbedpoint = -1;
	bool grabbedMisc = false;

	glm::ivec3 tmpIndex = glm::ivec3(-1);
	int indexCreationState = 0;



	void On_Create() 
	{

	}
	void On_Update() 
	{


		ImGui::Begin("Polygon Tools");
		if (ImGui::Button("Save as polygon.pol"))
		{
			poly.SaveAs("polygon.pol");
		}
		if (ImGui::Button("load polygon.pol"))
		{
			poly.Load("polygon.pol");
			poly.Update_Shape();
		}

		if (ImGui::Button("Pushback color"))
		{
			poly.colors.push_back(glm::vec4((rand() % 100 / 50.0f), (rand() % 100 / 50.0f), (rand() % 100 / 50.0f), 1.0f));
		}
		if (ImGui::Button("Clear"))
		{
			poly.triangles.clear();
			poly.indexes.clear();
			poly.points.clear();
			poly.colors.clear();
			poly.TexturePoints.clear();
			poly.state = 0;
		}

		ImGui::Text("hold ctrl to interact with points");
		ImGui::Text("hold shift, to add new triangles between existing points");


		//LMB states


		if (HoldingLMB && !buttons[GLFW_MOUSE_BUTTON_1]) ReleasedLMB = true;
		else ReleasedLMB = false;

		if (!HoldingLMB && buttons[GLFW_MOUSE_BUTTON_1]) JustPressedLMB = true;
		else JustPressedLMB = false;

		if (buttons[GLFW_MOUSE_BUTTON_1]) HoldingLMB = true;
		else  HoldingLMB = false;




		if (ImGui::Button("cut") || keys[GLFW_KEY_SPACE])
		{
			poly.state = 0;
		}


		if (keys[GLFW_KEY_LEFT_ALT])
		{

			for (int i = 0; i < poly.points.size(); i++)
				DrawCircle(poly.points[i], 10, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));



			if (JustPressedLMB)
			{
				poly.add_Point(MousePosition, true);
			}
		}

		if (keys[GLFW_KEY_LEFT_CONTROL] && !keys[GLFW_KEY_LEFT_SHIFT])
		{
			if (JustPressedLMB)
			{
				bool gr = false;

				for (int i = 0; i < poly.points.size(); i++)
				{
					if (!gr)
					{
						float distance = sqrlength(poly.points[i] - MousePosition);

						if (distance < 100)
						{
							grabbedpoint = i;
							grabbedMisc = false;
							gr = true;
						}
					}
				}
				for (int i = 0; i < poly.MiscPoints.size(); i++)
				{
					if (!gr)
					{
						float distance = sqrlength(glm::vec2(poly.MiscPoints[i].x, poly.MiscPoints[i].y) - MousePosition);

						if (distance < 100)
						{
							grabbedpoint = i;
							grabbedMisc = true;
							gr = true;
						}
					}
				}
			}
			if (ReleasedLMB)grabbedpoint = -1;

			if (grabbedpoint >= 0 && grabbedpoint < poly.points.size() && !grabbedMisc)
				poly.points[grabbedpoint] = MousePosition;

			if (grabbedpoint >= 0 && grabbedpoint < poly.MiscPoints.size() && grabbedMisc)
			{
				poly.MiscPoints[grabbedpoint].x = MousePosition.x;
				poly.MiscPoints[grabbedpoint].y = MousePosition.y;
			}
			for (int i = 0; i < poly.MiscPoints.size(); i++)
			{
				glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
				if ((int)poly.MiscPoints[i].z % 2 == 0)
					color.x = poly.MiscPoints[i].z * 0.25f;

				if ((int)poly.MiscPoints[i].z % 3 == 0)
					color.y = poly.MiscPoints[i].z * 0.25f;

				if ((int)poly.MiscPoints[i].z % 4 == 0)
					color.z = poly.MiscPoints[i].z * 0.25f;
				if ((int)poly.MiscPoints[i].z % 4 != 0 && (int)poly.MiscPoints[i].z % 3 != 0 && (int)poly.MiscPoints[i].z % 2 != 0)
				{
					color.x = poly.MiscPoints[i].z * 0.25f;
					color.z = poly.MiscPoints[i].z * 0.25f;
					color.y = poly.MiscPoints[i].z * 0.25f;
				}
				DrawCircle(glm::vec2(poly.MiscPoints[i].x, poly.MiscPoints[i].y), 10, color);
			}

			for (int i = 0; i < poly.points.size(); i++)
				DrawCircle(poly.points[i], 10, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
			poly.Update_Shape();
		}

		if (!keys[GLFW_KEY_LEFT_CONTROL] && keys[GLFW_KEY_LEFT_SHIFT] && poly.points.size() > 0)
		{

			if (JustPressedLMB)
			{
				int copycheck = indexCreationState;
				for (int i = 0; i < poly.points.size(); i++)
				{

					float distance = sqrlength(poly.points[i] - MousePosition);

					if (distance < 100 && indexCreationState == copycheck)
					{
						if (indexCreationState == 0)
						{
							tmpIndex.x = i;
							indexCreationState++;
						}
						else if (indexCreationState == 1)
						{
							tmpIndex.y = i;
							indexCreationState++;
						}
						else  if (indexCreationState == 2)
						{
							tmpIndex.z = i;
							indexCreationState = 0;

							if (tmpIndex.x != -1 && tmpIndex.z != -1 && tmpIndex.y != -1)
								poly.indexes.push_back(tmpIndex);
							else std::cout << "failed to add index";
							tmpIndex.x = -1;
							tmpIndex.y = -1;
							tmpIndex.z = -1;
						}
					}
				}
			}
			for (int i = 0; i < poly.points.size(); i++)
			{

				DrawCircle(poly.points[i], 10, glm::vec4(
					i == tmpIndex.x ? 1.0f : 0.0f,
					i == tmpIndex.y ? 1.0f : 0.0f,
					i == tmpIndex.z ? 1.0f : 0.0f,
					1.0f));
			}
			poly.Update_Shape();
		}



	
	}

int main()
{
	initEngine();

	return 0;
}