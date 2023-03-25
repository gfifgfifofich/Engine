#include "engine/Components/Engine.h"
polygon poly;






class application : public Engine
{
public:
	bool Just_ctrl_z = false;
	
	float step = 10.0f;
	float distance = 0.0f;

	RigidBody b;

	bool holdingLMB = false;
	bool releasedLMB = false;
	bool justpressedLMB = false;

	int grabbedpoint = -1;
	bool grabbedMisc = false;

	glm::ivec3 tmpIndex = glm::ivec3(-1);
	int indexCreationState = 0;

	int MiscPointID = 0;
	float additionalFloat = 0.0f;
	bool outlines = false;

	unsigned int Container;


	void On_Create() override
	{

	

		
		LoadTexture("container.jpg", &Container);
		b.init(glm::vec2(500, 500), 50);
		b.body.roughness = 0.0f;
		poly.Texture = Container;
	}
	void On_Update() override
	{
		//poly.Texture = NULL;

		b.Process(delta);
		float velocity = 10.0f;
		if (keys[GLFW_KEY_LEFT_SHIFT]) velocity = 100.0f;
		if (keys[GLFW_KEY_W]) b.body.velocity.y += velocity;
		if (keys[GLFW_KEY_S]) b.body.velocity.y -= velocity;
		if (keys[GLFW_KEY_D]) b.body.velocity.x += velocity;
		if (keys[GLFW_KEY_A]) b.body.velocity.x -= velocity;
		if (keys[GLFW_KEY_Q]) CameraScale *= 0.99f;
		if (keys[GLFW_KEY_W]) CameraScale *= 1.01f;

		for (int i = 0; i < poly.triangles.size(); i++)
			BallToTriangleCollision(&b.body, poly.triangles[i]);

		ImGui::Begin("tools");
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
			poly.colors.push_back(glm::vec4((rand() % 100 / 50.0f), (rand() % 100 / 50.0f), (rand() % 100 / 50.0f),1.0f));
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
		if (ImGui::Button("Outlines/Fill")) outlines = !outlines;

		ImGui::DragInt("MiscPointID", &MiscPointID, 0.1);
		ImGui::DragFloat("additionalFloat", &additionalFloat, 0.1);


		ImGui::Text("hold ctrl to interact with points");
		ImGui::Text("space to cut or use button cut, and create a separate poly");
		ImGui::Text("hold shift, to add new triangles between existing points");
		ImGui::Text("ctrl+z, undo last (works funky)");
		ImGui::Text("ctrl+s,ctrl+l, quick save/load");


		//LMB states
		

		if (holdingLMB && !buttons[GLFW_MOUSE_BUTTON_1]) releasedLMB = true;
		else releasedLMB = false;

		if (!holdingLMB && buttons[GLFW_MOUSE_BUTTON_1]) justpressedLMB = true;
		else justpressedLMB = false;
		
		if (buttons[GLFW_MOUSE_BUTTON_1]) holdingLMB = true;
		else  holdingLMB = false;




		if (ImGui::Button("cut") || keys[GLFW_KEY_SPACE])
		{
			poly.state = 0;
		}

		
		if (keys[GLFW_KEY_LEFT_ALT])
		{

			for (int i = 0; i < poly.points.size(); i++)
				DrawCircle(poly.points[i], 10, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

			

			if (justpressedLMB) 
			{
				poly.add_Point(MousePosition,true);
				Just_ctrl_z = false;
			}
		}
		if (keys[GLFW_KEY_C])
		{

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
			if (justpressedLMB)
				poly.MiscPoints.push_back(glm::vec4(MousePosition,MiscPointID,additionalFloat));
		}


		
		if (keys[GLFW_KEY_LEFT_CONTROL] && keys[GLFW_KEY_Z] && poly.points.size() > 0 && !Just_ctrl_z)
		{
			poly.points.pop_back();
			poly.indexes[poly.indexes.size()-1].z = poly.points.size()-1;
			poly.Update_Shape();
			Just_ctrl_z = true;
		}
		if (keys[GLFW_KEY_LEFT_CONTROL]  && !keys[GLFW_KEY_LEFT_SHIFT])
		{
			if (justpressedLMB)
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
			if (releasedLMB)grabbedpoint = -1;

			if(grabbedpoint>=0 && grabbedpoint< poly.points.size() && !grabbedMisc)
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

			if (justpressedLMB)
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
		

		//DrawCube(MousePosition, glm::vec2(10.0f), glm::vec3(0.0f),glm::vec4(1.0f));
		//poly.DrawOutline();
		if(!outlines)poly.DrawTriangles();
		else for (int i = 0; i < poly.triangles.size(); i++)
		{
			poly.triangles[i].DrawOutline();
		}

	
		//DrawTexturedQuad(MousePosition, { 100.0f,100.0f }, 139, { 0.0f,0.0f,0.0f });

	/*	DrawTexturedTriangle(glm::vec2(MousePosition.x, MousePosition.y),
			glm::vec2(WIDTH * -1.0f, HEIGHT*-1.0f),
			glm::vec2(WIDTH, HEIGHT),
			Container,
			glm::vec4(1.0f),
			MousePosition/(float)WIDTH
		);*/
	}
};

int main()
{
	application app;
	app.init();
	return 0;
}