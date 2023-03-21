#include "engine/Components/Engine.h"

Scene Map;
Texture tex;

ball b;
polygon pol;

char TexturePath[128];

Texture* CurrentTexture = NULL;

glm::vec2 PrevMousePosition = { 0.0f,0.0f };

bool grabbed = false;
int grabbedType = -1;// 0-ball, 1-cube, 2-polygonpoint, 3-point;
ball* grabbedBall;
cube* grabbedCube;
polygon* grabbedPolygon;


bool ShowPolygonPositions = false;
bool ShowPolygonTexturePositions = false;

bool RedactingParticlesEmiter = false;
bool RedactingScene = false;
bool GrabSelectTool = true;
bool RedactingPolygon = false;

int RedactorObject = 0;
int CurrentRedactorObject = -1;


ball* SelectedBall = NULL;
cube* SelectedCube = NULL;
polygon* SelectedPolygon = NULL;
ParticleEmiter* CurrentParticleEmiter = NULL;

char ParticleEmitterCharName[256];
std::string ParticleEmitterName = "New ParticleEmitter";
ParticleEmiter pt;
int selectedTexture = 0;


int ParticleObject = 0;
int CurrentParticleObject = -1;

float vel[2] = { 0.0f,0.0f };
float size[2] = { 10.0f,10.0f };
float radius = 10.0f;
float tick = 0.017f;
int amount = 1;
float AttractionForce = 10.0f;
bool attracticve = false;
float LightColor[4] = { 1.0f, 1.0f,1.0f,1.0f };

int noizeiterator = 0;

void ShowRedactorWindow(ParticleEmiter* ParticleEmiter)
{
	ImGui::Begin(CurrentParticleEmiter->Name.c_str());
	if (ImGui::Button("ShowSettings"))
		CurrentParticleEmiter->ShowWindow = !CurrentParticleEmiter->ShowWindow;


	int tip = 0;
	if (CurrentParticleEmiter->Type == "QUAD") tip = 0;
	if (CurrentParticleEmiter->Type == "LINE") tip = 1;
	if (CurrentParticleEmiter->Type == "CIRCLE") tip = 2;
	if (CurrentParticleEmiter->Type == "TEXTURED") tip = 3;
	ImGui::SliderInt("Type", &tip, 0, 3);
	if (tip == 0)CurrentParticleEmiter->Type = "QUAD";
	if (tip == 1)CurrentParticleEmiter->Type = "LINE";
	if (tip == 2)CurrentParticleEmiter->Type = "CIRCLE";
	if (tip == 3)CurrentParticleEmiter->Type = "TEXTURED";


	
	if (ImGui::Button("Redact"))
	{
		RedactingParticlesEmiter = !RedactingParticlesEmiter;
		GrabSelectTool = !RedactingParticlesEmiter;
		RedactingScene = false;
		RedactingPolygon = false;
	}
	if (RedactingParticlesEmiter)
	{
		ImGui::Text("Hold Shift to add 1 object/click ");
		ImGui::Text("object Type:");
		const char* str;
		if (ParticleObject == 0)str = "InfluenceSphere";
		if (ParticleObject == 1)str = "InfluenceQuad";
		if (ParticleObject == 2)str = "EmiterPoint";
		if (ParticleObject == 3)str = "EmiterSphere";
		if (ParticleObject == 4)str = "EmiterQuad";
		if (ParticleObject == 5)str = "LightSphere";
		if (ParticleObject == 6)str = "LightQuad";
		ImGui::SliderInt(str, &ParticleObject, 0, 6);
		if (ParticleObject > 1 && ParticleObject < 5)
		{
			ImGui::DragInt("Amount", &amount, 0.1f);
			ImGui::DragFloat("tick", &tick, 0.001f, 0);
			ImGui::DragFloat2("velocity", vel, 1.0f);
		}


		if (ParticleObject == 0)
		{
			ImGui::DragFloat2("velocity", vel, 1.0f);
			ImGui::DragFloat("Radius", &radius, 0.1f, 0);
			ImGui::DragFloat("AttractionForce", &AttractionForce, 0.1f);
			ImGui::Checkbox("attracticve", &attracticve);
			ImGui::Text("if holding Shift, drag mouse to change raduis");
		}
		if (ParticleObject == 1)
		{
			ImGui::DragFloat2("velocity", vel, 1.0f);
			ImGui::DragFloat2("Size", size, 1.0f, 0);
			ImGui::DragFloat("AttractionForce", &AttractionForce, 0.1f);
			ImGui::Checkbox("attracticve", &attracticve);
			ImGui::Text("if holding Shift, drag mouse to change size");
		}
		if (ParticleObject == 2)
		{
			ImGui::Text("if holding Shift, drag mouse to change velocity");
		}
		if (ParticleObject == 3)
		{
			ImGui::DragFloat("Radius", &radius, 0.1f, 0);
			ImGui::Text("if holding Shift, drag mouse to change Raduis");
		}
		if (ParticleObject == 4)
		{
			ImGui::DragFloat2("Size", size, 1.0f, 0);
			ImGui::Text("if holding Shift, drag mouse to change Size");
		}
		if (ParticleObject == 5)
		{
			ImGui::DragFloat("Radius", &radius, 0.1f, 0);
			ImGui::ColorEdit4("Color", LightColor);
			ImGui::Text("if holding Shift, drag mouse to change raduis");
		}
		if (ParticleObject == 6)
		{
			ImGui::DragFloat2("Size", size, 1.0f, 0);
			ImGui::ColorEdit4("Color", LightColor);
			ImGui::Text("if holding Shift, drag mouse to change size");
		}

		if (keys[GLFW_KEY_LEFT_SHIFT] && JustPressedLMB)
		{
			PrevMousePosition = MousePosition;
			if (ParticleObject == 0)
				CurrentParticleObject = CurrentParticleEmiter->AddSpheresOfInfluence(MousePosition, radius,{ vel[0],vel[1] }, attracticve, AttractionForce);

			if (ParticleObject == 1)
				CurrentParticleObject = CurrentParticleEmiter->AddCubeOfInfluence(MousePosition, { size[0],size[1]}, {vel[0],vel[1]}, attracticve, AttractionForce);

			if (ParticleObject == 2)
				CurrentParticleObject = CurrentParticleEmiter->AddPointEmiter(MousePosition, { vel[0],vel[1] }, amount, tick);

			if (ParticleObject == 3)
				CurrentParticleObject = CurrentParticleEmiter->AddCircleEmiter(MousePosition, { vel[0],vel[1] }, radius , amount, tick);

			if (ParticleObject == 4)
				CurrentParticleObject = CurrentParticleEmiter->AddCubeEmiter(MousePosition, {size[0],size[1]}, { vel[0], vel[1] }, amount, tick);

			if (ParticleObject == 5)
				CurrentParticleObject = CurrentParticleEmiter->AddLightSphere(MousePosition,radius,{ LightColor[0] ,LightColor[1] ,LightColor[2] ,LightColor[3] });

			if (ParticleObject == 6)
				CurrentParticleObject = CurrentParticleEmiter->AddLightCube(MousePosition, {size[0],size[1]}, {LightColor[0] ,LightColor[1] ,LightColor[2] ,LightColor[3]});

		}
		if (keys[GLFW_KEY_LEFT_SHIFT] && buttons[GLFW_MOUSE_BUTTON_1] && PrevMousePosition != MousePosition)
		{

			if (ParticleObject == 0)
				CurrentParticleEmiter->SpheresOfInfluence[CurrentParticleObject].r = length(MousePosition - PrevMousePosition);

			if (ParticleObject == 1)
			{
				if ((MousePosition - PrevMousePosition).x != 0.0f && (MousePosition - PrevMousePosition).y != 0.0f)
					CurrentParticleEmiter->CubesOfInfluence[CurrentParticleObject].scale = abs((MousePosition - PrevMousePosition)) * 0.5f;
				
				CurrentParticleEmiter->CubesOfInfluence[CurrentParticleObject].position = (MousePosition + PrevMousePosition) * 0.5f;
			}
			if (ParticleObject == 2)
				CurrentParticleEmiter->EmitionPoints[CurrentParticleObject].velocity = MousePosition - PrevMousePosition;

			if (ParticleObject == 3)
				CurrentParticleEmiter->EmitionCircles[CurrentParticleObject].r = length(MousePosition - PrevMousePosition);

			if (ParticleObject == 4)
			{
				if((MousePosition - PrevMousePosition).x!=0.0f&& (MousePosition - PrevMousePosition).y != 0.0f)
					CurrentParticleEmiter->EmitionCubes[CurrentParticleObject].scale = abs((MousePosition - PrevMousePosition))*0.5f;

				CurrentParticleEmiter->EmitionCubes[CurrentParticleObject].position = (MousePosition + PrevMousePosition)*0.5f;
			}
			if (ParticleObject == 5)
				CurrentParticleEmiter->LightSpheres[CurrentParticleObject].r = length(MousePosition - PrevMousePosition);

			if (ParticleObject == 6)
			{
				if ((MousePosition - PrevMousePosition).x != 0.0f && (MousePosition - PrevMousePosition).y != 0.0f)
					CurrentParticleEmiter->LightCubes[CurrentParticleObject].scale = abs((MousePosition - PrevMousePosition)) * 0.5f;

				CurrentParticleEmiter->LightCubes[CurrentParticleObject].position = (MousePosition + PrevMousePosition) * 0.5f;

			}
		}

		for (int i = 0; i < CurrentParticleEmiter->SpheresOfInfluence.size(); i++)
			DrawCircle(CurrentParticleEmiter->SpheresOfInfluence[i].position, CurrentParticleEmiter->SpheresOfInfluence[i].r, glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionCircles.size(); i++)
			DrawCircle(CurrentParticleEmiter->EmitionCircles[i].position, CurrentParticleEmiter->EmitionCircles[i].r, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->LightSpheres.size(); i++)
			DrawCircle(CurrentParticleEmiter->LightSpheres[i].position, CurrentParticleEmiter->LightSpheres[i].r, glm::vec4(1.0f, 1.0f,0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->CubesOfInfluence.size(); i++)
			DrawCube(CurrentParticleEmiter->CubesOfInfluence[i].position, CurrentParticleEmiter->CubesOfInfluence[i].scale, glm::vec3(0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionCubes.size(); i++)
			DrawCube(CurrentParticleEmiter->EmitionCubes[i].position, CurrentParticleEmiter->EmitionCubes[i].scale, glm::vec3(0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->LightCubes.size(); i++)
			DrawCube(CurrentParticleEmiter->LightCubes[i].position, CurrentParticleEmiter->LightCubes[i].scale, glm::vec3(0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionPoints.size(); i++)
			DrawCircle(CurrentParticleEmiter->EmitionPoints[i].position,10, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


	}
	else
	{
		ImGui::SliderInt("TextureId", &selectedTexture, 0, Map.Textures.size() - 1);
		if (selectedTexture >= 0 && selectedTexture < Map.Textures.size())
			ImGui::Text(Map.Textures[selectedTexture].FileName.c_str());
		if (ImGui::Button("Add"))
		{
			CurrentParticleEmiter->Textureids.push_back(selectedTexture);

			CurrentParticleEmiter->textures.clear();
			for (int i = 0; i < CurrentParticleEmiter->Textureids.size(); i++)
				CurrentParticleEmiter->textures.push_back(Map.Textures[CurrentParticleEmiter->Textureids[i]].texture);
		}
		ImGui::Text("Textures:");
		for (int i = 0; i < CurrentParticleEmiter->textures.size(); i++)
		{
			ImGui::Text(Map.Textures[CurrentParticleEmiter->Textureids[i]].FileName.c_str());
			std::string cl = "Delete ";
			cl += std::to_string(i);
			ImGui::SameLine();
			if (ImGui::Button(cl.c_str()))
			{
				CurrentParticleEmiter->Textureids[i] = CurrentParticleEmiter->Textureids[CurrentParticleEmiter->Textureids.size() - 1];
				CurrentParticleEmiter->Textureids.pop_back();

				CurrentParticleEmiter->textures.clear();
				for (int i = 0; i < CurrentParticleEmiter->Textureids.size(); i++)
					CurrentParticleEmiter->textures.push_back(Map.Textures[CurrentParticleEmiter->Textureids[i]].texture);

			}

		}
		if (ImGui::Button("Close window"))
			CurrentParticleEmiter = NULL;
	}
	ImGui::End();
}
void ShowRedactorWindow(ball* Ball)
{
	ImGui::Begin("Ball");


	ImGui::DragFloat("Radius", &SelectedBall->r);

	ImGui::DragFloat("Rotation", &SelectedBall->rotation, 0.01f);

	float pos[2] = { SelectedBall->position.x ,SelectedBall->position.y };
	ImGui::DragFloat2("Position", pos);
	SelectedBall->position = { pos[0],pos[1] };

	float col[4] = { SelectedBall->color.r ,SelectedBall->color.g,SelectedBall->color.b,SelectedBall->color.a };
	ImGui::ColorEdit4("Color", col);
	SelectedBall->color = { col[0],col[1],col[2],col[3] };
	if(SelectedBall->Textureid>-1)
		ImGui::Text(Map.Textures[SelectedBall->Textureid].FileName.c_str());
	else 
		ImGui::Text("Clear Color");
	ImGui::DragInt("Texture", &SelectedBall->Textureid, 0.01f, -1, Map.Textures.size() - 1);
	ImGui::DragInt("Collision_Level", &SelectedBall->Collision_Level, 0.01f);
	ImGui::DragInt("Collision_Mask", &SelectedBall->Collision_Mask, 0.01f);

	if (ImGui::Button("Close window"))
		SelectedBall = NULL;
	ImGui::End;
}
void ShowRedactorWindow(cube* Cube)
{
	ImGui::Begin("Cube");

	ImGui::DragFloat("width", &SelectedCube->width);
	ImGui::DragFloat("height", &SelectedCube->height);

	float pos[2] = { SelectedCube->position.x ,SelectedCube->position.y };
	ImGui::DragFloat2("Position", pos);
	SelectedCube->position = { pos[0],pos[1] };



	float col[4] = { SelectedCube->color.r ,SelectedCube->color.g,SelectedCube->color.b,SelectedCube->color.a };
	ImGui::ColorEdit4("Color", col);
	SelectedCube->color = { col[0],col[1],col[2],col[3] };
	if (SelectedCube->Textureid > -1)
		ImGui::Text(Map.Textures[SelectedCube->Textureid].FileName.c_str());
	else
		ImGui::Text("Clear Color");
	ImGui::DragInt("Texture", &SelectedCube->Textureid, 0.01f, -1, Map.Textures.size() - 1);
	ImGui::DragInt("Collision_Level", &SelectedCube->Collision_Level, 0.01f);
	ImGui::DragInt("Collision_Mask", &SelectedCube->Collision_Mask, 0.01f);

	if (ImGui::Button("Close window"))
		SelectedCube = NULL;
	ImGui::End;
}
void ShowRedactorWindow(polygon* Polygon)
{

	ImGui::Begin("Polygon");
	float col[4] = { SelectedPolygon->colors[0].r ,SelectedPolygon->colors[0].g,SelectedPolygon->colors[0].b,SelectedPolygon->colors[0].a };
	ImGui::ColorEdit4("Color", col);
	SelectedPolygon->colors[0] = { col[0],col[1],col[2],col[3] };
	if (SelectedPolygon->Textureid > -1)
		ImGui::Text(Map.Textures[SelectedPolygon->Textureid].FileName.c_str());
	else
		ImGui::Text("Clear Color");
	ImGui::DragInt("Texture", &SelectedPolygon->Textureid, 0.01f, -1, Map.Textures.size() - 1);
	ImGui::DragInt("Collision_Level", &SelectedPolygon->Collision_Level, 0.01f);
	ImGui::DragInt("Collision_Mask", &SelectedPolygon->Collision_Mask, 0.01f);

	if (ImGui::Button("TexturePositions"))
		ShowPolygonTexturePositions = !ShowPolygonTexturePositions;
	if (ImGui::Button("Points"))
		ShowPolygonPositions = !ShowPolygonPositions;
	if (ShowPolygonTexturePositions)
	{
		for (int i = 0; i < SelectedPolygon->TexturePoints.size(); i++)
		{
			std::string  iter = std::to_string(i);

			float ar[2] = { SelectedPolygon->TexturePoints[i].x ,SelectedPolygon->TexturePoints[i].y };
			ImGui::DragFloat2(iter.c_str(), ar, 0.01f);
			SelectedPolygon->TexturePoints[i] = { ar[0],ar[1] };
		}
	}
	if (ShowPolygonPositions)
	{
		for (int i = 0; i < SelectedPolygon->points.size(); i++)
		{
			std::string iter = std::to_string(i);

			float ar[2] = { SelectedPolygon->points[i].x ,SelectedPolygon->points[i].y };
			ImGui::DragFloat2(iter.c_str(), ar);
			SelectedPolygon->points[i] = { ar[0],ar[1] };
		}
	}

	if (ImGui::Button("Close window"))
		SelectedPolygon = NULL;
	ImGui::End;
}

void ShowRedactorWindow(Texture* Texture)
{
	ImGui::Begin(CurrentTexture->FileName.c_str());

	if (ImGui::Button("Close window"))
		CurrentTexture = NULL;
	ImGui::End();
}




class application : public Engine
{
	

	void On_Create() override
	{
		Map.LoadFrom("Maps/mappa.sav");
	}
	void On_Update() override
	{

		if (keys[GLFW_KEY_W]) CameraPosition.y += delta / CameraScale.y * 600.0f;
		if (keys[GLFW_KEY_S]) CameraPosition.y -= delta / CameraScale.y * 600.0f;
		if (keys[GLFW_KEY_A]) CameraPosition.x -= delta / CameraScale.x * 600.0f;
		if (keys[GLFW_KEY_D]) CameraPosition.x += delta / CameraScale.x * 600.0f;
		if (keys[GLFW_KEY_Q]) CameraScale *= 1.01f;
		if (keys[GLFW_KEY_E]) CameraScale *= 0.99f;



		ImGui::Begin("Tools");
		if (ImGui::Button("Save"))
			Map.SaveAs("Maps/mappa.sav");
		if (ImGui::Button("Load"))
			Map.LoadFrom("Maps/mappa.sav");
	


		if (RedactingParticlesEmiter)ImGui::Text("RedactingParticlesEmiter");
		else if (RedactingPolygon)ImGui::Text("RedactingPolygon");
		else if (RedactingScene)ImGui::Text("RedactingScene");
		else if (GrabSelectTool)ImGui::Text("GrabSelectTool");

		if (!RedactingParticlesEmiter && !RedactingPolygon)
			if (ImGui::Button("Switch modes"))
			{
				RedactingScene = !RedactingScene;
				GrabSelectTool = !GrabSelectTool;
				if (RedactingScene && GrabSelectTool || !RedactingScene && !GrabSelectTool)
				{
					GrabSelectTool = true;
					RedactingScene = false;
				}
			}

		//RedactingScene Tool
		if (!RedactingParticlesEmiter && RedactingScene && !GrabSelectTool && !RedactingPolygon)
		{


			ImGui::Text("object Type:");
			const char* str;
			if (RedactorObject == 0)str = "Circle";
			if (RedactorObject == 1)str = "Quad";
			if (RedactorObject == 2)str = "Polygon";
			ImGui::SliderInt(str, &RedactorObject, 0, 2);

			if (RedactorObject == 0)
			{
				ImGui::DragFloat("Radius", &radius, 0.1f, 0);
				ImGui::Text("if holding Shift, drag mouse to change raduis");
			}
			if (RedactorObject == 1)
			{
				ImGui::DragFloat2("Size", size, 1.0f, 0);
				ImGui::Text("if holding Shift, drag mouse to change size");
			}
			if (RedactorObject == 2)
			{
				ImGui::DragFloat("Radius ish", &radius, 0.1f, 0);
			}
			

			if (JustPressedLMB && keys[GLFW_KEY_LEFT_SHIFT])
			{
				PrevMousePosition = MousePosition;
				if (RedactorObject == 0)
				{
					ball b;
					b.position = PrevMousePosition;
					b.r = radius;
					Map.balls.push_back(b);
					CurrentRedactorObject = Map.balls.size() - 1;
				}
				if (RedactorObject == 1)
				{
					cube c;
					c.width = size[0];
					c.height = size[1];
					c.position = PrevMousePosition;
					Map.cubes.push_back(c);
					CurrentRedactorObject = Map.cubes.size() - 1;
				}
				if (RedactorObject == 2)
				{
					polygon p;
					p.add_Point(PrevMousePosition - glm::vec2(radius, radius *0.5f));
					p.add_Point(PrevMousePosition - glm::vec2(-radius, radius * 0.5f));
					p.add_Point(PrevMousePosition + glm::vec2(0, radius ));
					p.indexes.push_back(glm::ivec3(0, 1, 2));
					Map.polygons.push_back(p);
					CurrentRedactorObject = Map.polygons.size() - 1;
				}
			}
			else if (buttons[GLFW_MOUSE_BUTTON_1] && keys[GLFW_KEY_LEFT_SHIFT] && PrevMousePosition != MousePosition)
			{
				if (RedactorObject == 0)
				{
					float rar = length(MousePosition - PrevMousePosition);
					Map.balls[CurrentRedactorObject].r = rar;
				}
				if (RedactorObject == 1)
				{
					if ((MousePosition - PrevMousePosition).x != 0.0f && (MousePosition - PrevMousePosition).y != 0.0f)
					{
						Map.cubes[CurrentRedactorObject].width = abs((MousePosition.x - PrevMousePosition.x)) * 0.5f;
						Map.cubes[CurrentRedactorObject].height = abs((MousePosition.y - PrevMousePosition.y)) * 0.5f;
					}
					Map.cubes[CurrentRedactorObject].position = (MousePosition + PrevMousePosition) * 0.5f;
				}
				if (RedactorObject == 2)
				{
					float rar = length(MousePosition - PrevMousePosition);
					Map.polygons[CurrentRedactorObject].points[0] = (PrevMousePosition - glm::vec2(rar, rar * 0.5f));
					Map.polygons[CurrentRedactorObject].points[1] = (PrevMousePosition - glm::vec2(-rar, rar * 0.5f));
					Map.polygons[CurrentRedactorObject].points[2] = (PrevMousePosition + glm::vec2(0, rar));
					Map.polygons[CurrentRedactorObject].Update_Shape();
				}
			}
		}


		//GrabTool
		if (!RedactingParticlesEmiter && !RedactingScene && GrabSelectTool && !RedactingPolygon)
		{
			if (JustPressedLMB)
			{
				PrevMousePosition = MousePosition;
				grabbedBall = NULL;
				grabbedCube = NULL;
				grabbedPolygon = NULL;
				grabbedType = -1;
				grabbed = false;


				for (int i = 0; i < Map.balls.size(); i++)
				{
					if (BalltoPointCollisionCheck(Map.balls[i], MousePosition) && !grabbed)
					{
						grabbedBall = &Map.balls[i];
						grabbedType = 0;
						grabbed = true;
					}
				}
				for (int i = 0; i < Map.cubes.size(); i++)
				{
					if (PointToQuadCollisionCheck(Map.cubes[i], MousePosition) && !grabbed)
					{
						grabbedCube = &Map.cubes[i];
						grabbedType = 1;
						grabbed = true;
					}
				}
				for (int i = 0; i < Map.polygons.size(); i++)
				{
					if (PointToPolygonCollisionCheck(MousePosition, Map.polygons[i]) && !grabbed)
					{
						grabbedPolygon = &Map.polygons[i];
						grabbedType = 2;
						grabbed = true;
					}
				}
			}
			if (ReleasedLMB && PrevMousePosition == MousePosition)
			{
				if (grabbedBall != NULL && grabbed && grabbedType == 0)
					SelectedBall = grabbedBall;

				if (grabbedCube != NULL && grabbed && grabbedType == 1)
					SelectedCube = grabbedCube;

				if (grabbedPolygon != NULL && grabbed && grabbedType == 2)
					SelectedPolygon = grabbedPolygon;

				grabbedBall = NULL;
				grabbedCube = NULL;
				grabbedPolygon = NULL;
				grabbedType = -1;
				grabbed = false;
			}
			else if (buttons[GLFW_MOUSE_BUTTON_1] && PrevMousePosition != MousePosition)
			{
				if (grabbedBall != NULL && grabbed && grabbedType == 0)
					grabbedBall->position = MousePosition;

				if (grabbedCube != NULL && grabbed && grabbedType == 1)
					grabbedCube->position = MousePosition;

			}
		}






		ImGui::Text("texture/path/... or RN for (Round noize), SQRN for squere noize, SMN for smooth edged noize");
		ImGui::InputText("Texture path:", TexturePath, 128);


		if (ImGui::Button("LoadTexture"))
		{
			std::string s = "";
			for (int i = 0; i < 128; i++)
			{
				if (TexturePath[i] != ' ')
					s += TexturePath[i];
			}
			if (TexturePath[0] == 'R' && TexturePath[1] == 'N')
			{
				s = "RoundNoize";
				tex.Type = 1;
				s += std::to_string(noizeiterator);
				noizeiterator++;
			}
			if (TexturePath[0] == 'S' && TexturePath[1] == 'Q' && TexturePath[2] == 'R' && TexturePath[3] == 'N')
			{
				s = "SquereNoize";
				tex.Type = 2;
				s += std::to_string(noizeiterator);
				noizeiterator++;
			}
			if (TexturePath[0] == 'S' && TexturePath[1] == 'M' && TexturePath[2] == 'N')
			{
				s = "SmoothEdgedNoize";
				tex.Type = 3;
				s += std::to_string(noizeiterator);
				noizeiterator++;
			}
			tex.FileName = s;
			tex.id = Map.Textures.size();
			tex.Load();
			if(tex.texture!=NULL)
				Map.Textures.push_back(tex);
		}

		ImGui::Text("Textures:");
		for (int i = 0; i < Map.Textures.size(); i++)
		{
			if (ImGui::Button(Map.Textures[i].FileName.c_str()))
				CurrentTexture = &Map.Textures[i];
		}
		ImGui::InputText("Particle Emitter Name:", ParticleEmitterCharName, 256);
		if (ImGui::Button("Add"))
		{
			int EndOfName = -1;
			for (int i = 255; i >= 0; i--)
				if (ParticleEmitterCharName[i] != char() && ParticleEmitterCharName[i] != ' ' && EndOfName < 0)
					EndOfName = i;


			std::string nm;
			if (EndOfName > 0)
				for (int i = 0; i >= EndOfName; i++)
					nm += ParticleEmitterCharName[i];
			else if (EndOfName == 0)
				nm += ParticleEmitterCharName[0];
			else
				std::cerr << "ERROR: WRONG NAME";
			pt.Name = nm;
			Map.ParticleEmiters.push_back(pt);
		}
		
		ImGui::Text("Particles:");
		for (int i = 0; i < Map.ParticleEmiters.size(); i++)
		{
			if (ImGui::Button(Map.ParticleEmiters[i].Name.c_str()))
				CurrentParticleEmiter = &Map.ParticleEmiters[i];
		}
		ImGui::End();


		

		if (CurrentTexture != NULL)
			ShowRedactorWindow(CurrentTexture);

		if (CurrentParticleEmiter != NULL)
			ShowRedactorWindow(CurrentParticleEmiter);

		if (SelectedBall != NULL)
			ShowRedactorWindow(SelectedBall);

		if (SelectedCube != NULL)
			ShowRedactorWindow(SelectedCube);

		if (SelectedPolygon != NULL)
			ShowRedactorWindow(SelectedPolygon);

		Map.Draw();
	}
};
int main()
{
	application app;
	app.init();
	//Map.SaveAs("Maps/mappa.sav");
	return 0;
}

