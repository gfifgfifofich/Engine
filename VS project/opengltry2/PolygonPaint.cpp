


#include "engine/Components/Engine.h"

polygon poly;

	

	int grabbedpoint = -1;
	bool grabbedMisc = false;

	glm::ivec3 tmpIndex = glm::ivec3(-1);
	int indexCreationState = 0;

	polygonData pd;


	void On_Create() 
	{
		poly.Data = &pd;

		LoadTexture("Screenshot_1.png", &poly.Texture);
		LoadTexture("11normal.png", &poly.NormalMap);
	}
	void On_Update() 
	{

		DrawLight(MousePosition, { 2500,2500 }, { 100.0f,10.0f,0.5f,1.0f });

		ImGui::Begin("Polygon Tools");
		if (ImGui::Button("Save as polygon.pol"))
		{
			poly.Data->SaveAs("polygon.pol");
		}
		if (ImGui::Button("load polygon.pol"))
		{
			poly.Data->Load("polygon.pol");
			poly.Update_MidlePos();
			poly.Update_Shape();
		}

		
		if (ImGui::Button("Clear"))
		{
			poly.triangles.clear();
			poly.Data->indexes.clear();
			poly.Data->Rawpoints.clear();
			poly.Data->TexturePoints.clear();
			poly.Data->state = 0;
			poly.Update_Shape();
		}

		ImGui::Text("hold ctrl to interact with points");
		ImGui::Text("hold shift, to add new triangles between existing points");


		//LMB states

		float a[2] = { poly.Position.x, poly.Position.y };
		ImGui::DragFloat2("position", a);
		poly.Position = { a[0],a[1] };
		ImGui::DragFloat("Rotation", &poly.Rotation, 0.01f);


		float ab[2] = { poly.Scale.x, poly.Scale.y };
		ImGui::DragFloat2("Scale", ab, 0.01f);
		poly.Scale = { ab[0],ab[1] };

		if (ImGui::Button("cut") || keys[GLFW_KEY_SPACE])
		{
			poly.Data->state = 0;
		}


		if (keys[GLFW_KEY_LEFT_ALT])
		{

			for (int i = 0; i < poly.Data->Rawpoints.size(); i++)
				DrawCircle(poly.Data->Rawpoints[i], 10, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));



			if (JustPressedLMB)
			{
				poly.Data->add_Point(MousePosition, true);
				poly.Update_Shape();
				for (int i = 0; i < poly.Data->indexes.size(); i++)
				{
				}
			}
		}

		if (keys[GLFW_KEY_LEFT_CONTROL] && !keys[GLFW_KEY_LEFT_SHIFT])
		{
			if (JustPressedLMB)
			{
				bool gr = false;

				for (int i = 0; i < poly.Data->Rawpoints.size(); i++)
				{
					if (!gr)
					{
						float distance = sqrlength(poly.Data->Rawpoints[i] - MousePosition);

						if (distance < 100)
						{
							grabbedpoint = i;
							grabbedMisc = false;
							gr = true;
						}
					}
				}
				
			}
			if (ReleasedLMB)grabbedpoint = -1;

			if (grabbedpoint >= 0 && grabbedpoint < poly.Data->Rawpoints.size() && !grabbedMisc)
			{
				poly.Data->Rawpoints[grabbedpoint] = MousePosition;
			
				poly.Update_Shape();
				poly.Data->Update();
			}
			

			for (int i = 0; i < poly.Data->Rawpoints.size(); i++)
				DrawCircle(poly.Data->Rawpoints[i], 10, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		}

		if (!keys[GLFW_KEY_LEFT_CONTROL] && keys[GLFW_KEY_LEFT_SHIFT] && poly.Data->Rawpoints.size() > 0)
		{

			if (JustPressedLMB)
			{
				int copycheck = indexCreationState;
				for (int i = 0; i < poly.Data->Rawpoints.size(); i++)
				{

					float distance = sqrlength(poly.Data->Rawpoints[i] - MousePosition);

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
								poly.Data->indexes.push_back(tmpIndex);
							else std::cout << "failed to add index";
							tmpIndex.x = -1;
							tmpIndex.y = -1;
							tmpIndex.z = -1;
						}
					}
				}
			}
			for (int i = 0; i < poly.Data->Rawpoints.size(); i++)
			{

				DrawCircle(poly.Data->Rawpoints[i], 10, glm::vec4(
					i == tmpIndex.x ? 1.0f : 0.0f,
					i == tmpIndex.y ? 1.0f : 0.0f,
					i == tmpIndex.z ? 1.0f : 0.0f,
					1.0f));
			}
			poly.Update_Shape();
		}

		poly.Update_Shape();

		//poly.DrawTriangles();

		DrawPolygon(poly);
	
	}

int main()
{
	initEngine();

	return 0;
}