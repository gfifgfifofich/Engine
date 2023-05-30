#include "engine/Components/Engine.h"


char MapFileNameChars[128];
std::string MapFileName = "Maps/mappa.sav";

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
miscPoint* grabbedPoint;

int grabbedpoint = -1;

glm::ivec3 tmpIndex = glm::ivec3(-1);
int indexCreationState = 0;

bool ShowPolygonTools = false;


bool ShowPolygonPositions = false;
bool ShowPolygonTexturePositions = false;

bool RedactingParticlesEmiter = false;
bool RedactingScene = false;
bool GrabSelectTool = true;
bool RedactingPolygon = false;
bool AddRedact = false;

int RedactorObject = 0;
int CurrentRedactorObject = -1;


ball* SelectedBall = NULL;
cube* SelectedCube = NULL;
polygon* SelectedPolygon = NULL;
miscPoint* SelectedPoint;
ParticleEmiter* CurrentParticleEmiter = NULL;
LightSource* CurrentLightSource = NULL;

char ParticleEmitterCharName[256];
char LightSourceCharName[256];
char SelectedTextureCharName[256];
std::string ParticleEmitterName = "New ParticleEmitter";
ParticleEmiter pt;
int selectedTexture = 0;


int ParticleObject = 0;
int CurrentParticleObject = -1;
int CurrentRedactingParticleObject = -1;
int CurrentRedactingParticleObjectType = -1;

float vel[2] = { 0.0f,0.0f };
float size[2] = { 10.0f,10.0f };
float radius = 10.0f;
float tick = 0.017f;
int amount = 1;
int Id = 0;
float AttractionForce = 10.0f;
bool attracticve = false;
float LightColor[4] = { 1.0f, 1.0f,1.0f,1.0f };
bool Lighted = false;

int noizeiterator = 0;

bool ShowParticlesWindow = false;
bool ShowLightSourcesWindow = false;
bool ShowTexturesWindow = false;
bool ShowNormalMapsWindow = false;

float LightVolume = 0.005f;

void ShowParticleObjectRedactorWindow(ParticleEmiter* PE,int type,int i)
{
	ImGui::Begin("Particle Object");
	if (type == 0)
	{
		ImGui::Text("Sphere of influence");

		ImGui::DragFloat("attractionForce",&PE->SpheresOfInfluence[i].attractionStrength);
		ImGui::Checkbox("attractive",&PE->SpheresOfInfluence[i].attractive);

		ImGui::DragFloat("Radius", &PE->SpheresOfInfluence[i].r);

		float p[2] = { PE->SpheresOfInfluence[i].position.x,PE->SpheresOfInfluence[i].position.y };
		ImGui::DragFloat2("Position",p);
		PE->SpheresOfInfluence[i].position = { p[0],p[1] };

		float v[2] = { PE->SpheresOfInfluence[i].velocity.x,PE->SpheresOfInfluence[i].velocity.y };
		ImGui::DragFloat2("velocity", v);
		PE->SpheresOfInfluence[i].velocity = { v[0],v[1] };
	}
	else if (type == 1)
	{
		ImGui::Text("Cube of influence");

		ImGui::DragFloat("attractionForce", &PE->CubesOfInfluence[i].attractionStrength);
		ImGui::Checkbox("attractive", &PE->CubesOfInfluence[i].attractive);

		float s[2] = { PE->CubesOfInfluence[i].scale.x,PE->CubesOfInfluence[i].scale.y };
		ImGui::DragFloat2("Scale", s);
		PE->CubesOfInfluence[i].scale = { s[0],s[1] };

		float p[2] = { PE->CubesOfInfluence[i].position.x,PE->CubesOfInfluence[i].position.y };
		ImGui::DragFloat2("Position", p);
		PE->CubesOfInfluence[i].position = { p[0],p[1] };

		float v[2] = { PE->CubesOfInfluence[i].velocity.x,PE->CubesOfInfluence[i].velocity.y };
		ImGui::DragFloat2("Velocity", v);
		PE->CubesOfInfluence[i].velocity = { v[0],v[1] };
	}
	else if (type == 2)
	{
		ImGui::Text("PointEmiter");

		ImGui::DragFloat("Tick", &PE->EmitionPoints[i].tick);
		ImGui::DragInt("Amount", &PE->EmitionPoints[i].amount);

		float p[2] = { PE->EmitionPoints[i].position.x,PE->EmitionPoints[i].position.y };
		ImGui::DragFloat2("Position", p);
		PE->EmitionPoints[i].position = { p[0],p[1] };

		float v[2] = { PE->EmitionPoints[i].velocity.x,PE->EmitionPoints[i].velocity.y };
		ImGui::DragFloat2("Velocity", v);
		PE->EmitionPoints[i].velocity = { v[0],v[1] };
	}
	else if (type == 3)
	{
		ImGui::Text("Crcle Emiter");

		ImGui::DragFloat("Tick", &PE->EmitionCircles[i].tick);
		ImGui::DragInt("Amount", &PE->EmitionCircles[i].amount);
		ImGui::DragFloat("Radius", &PE->EmitionCircles[i].r);

		float p[2] = { PE->EmitionCircles[i].position.x,PE->EmitionCircles[i].position.y };
		ImGui::DragFloat2("Position", p);
		PE->EmitionCircles[i].position = { p[0],p[1] };

		float v[2] = { PE->EmitionCircles[i].velocity.x,PE->EmitionCircles[i].velocity.y };
		ImGui::DragFloat2("Velocity", v);
		PE->EmitionCircles[i].velocity = { v[0],v[1] };
	}
	else if (type == 4)
	{
		ImGui::Text("Cube Emiter");

		ImGui::DragFloat("Tick", &PE->EmitionCubes[i].tick);
		ImGui::DragInt("Amount", &PE->EmitionCubes[i].amount);

		float s[2] = { PE->EmitionCubes[i].scale.x,PE->EmitionCubes[i].scale.y };
		ImGui::DragFloat2("scale", s);
		PE->EmitionCubes[i].scale = { s[0],s[1] };

		float p[2] = { PE->EmitionCubes[i].position.x,PE->EmitionCubes[i].position.y };
		ImGui::DragFloat2("Position", p);
		PE->EmitionCubes[i].position = { p[0],p[1] };

		float v[2] = { PE->EmitionCubes[i].velocity.x,PE->EmitionCubes[i].velocity.y };
		ImGui::DragFloat2("Velocity", v);
		PE->EmitionCubes[i].velocity = { v[0],v[1] };
	}
	else if (type == 5)
	{
		ImGui::Text("Light sphere");

		ImGui::DragFloat("Radius", &PE->LightSpheres[i].r);



		float p[2] = { PE->LightSpheres[i].position.x,PE->LightSpheres[i].position.y };
		ImGui::DragFloat2("Position", p);
		PE->LightSpheres[i].position = { p[0],p[1] };

		float v[4] = { PE->LightSpheres[i].Color.x,PE->LightSpheres[i].Color.y ,PE->LightSpheres[i].Color.z,PE->LightSpheres[i].Color.w };
		ImGui::ColorEdit4("Color", v);
		PE->LightSpheres[i].Color = { v[0],v[1],v[2],v[3] };
	}
	else if (type == 6)
	{
		ImGui::Text("Light cube");


		float s[2] = { PE->LightCubes[i].scale.x,PE->LightCubes[i].scale.y };
		ImGui::DragFloat2("scale", s);
		PE->LightCubes[i].scale = { s[0],s[1] };

		float p[2] = { PE->LightCubes[i].position.x,PE->LightCubes[i].position.y };
		ImGui::DragFloat2("Position", p);
		PE->LightCubes[i].position = { p[0],p[1] };

		float v[4] = { PE->LightCubes[i].Color.x,PE->LightCubes[i].Color.y ,PE->LightCubes[i].Color.z,PE->LightCubes[i].Color.w };
		ImGui::ColorEdit4("Color", v);
		PE->LightCubes[i].Color = { v[0],v[1],v[2],v[3] };
	}
	else
	{
		std::cerr << "ERROR:Incorrect type of Particle object";

		CurrentRedactingParticleObject = -1;
		CurrentRedactingParticleObjectType = -1;
	}
	ImGui::End();
}
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
		GrabSelectTool = false;
		RedactingScene = false;
		RedactingPolygon = false;
	}
	if (RedactingParticlesEmiter)
	{
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
		if (ImGui::Button("Add/Redact"))
			AddRedact = !AddRedact;
		if (AddRedact)
		{
			ImGui::Text("Hold Shift to add 1 object/click ");

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
					CurrentParticleObject = CurrentParticleEmiter->AddSpheresOfInfluence(MousePosition, radius, { vel[0],vel[1] }, attracticve, AttractionForce);

				if (ParticleObject == 1)
					CurrentParticleObject = CurrentParticleEmiter->AddCubeOfInfluence(MousePosition, { size[0],size[1] }, { vel[0],vel[1] }, attracticve, AttractionForce);

				if (ParticleObject == 2)
					CurrentParticleObject = CurrentParticleEmiter->AddPointEmiter(MousePosition, { vel[0],vel[1] }, amount, tick);

				if (ParticleObject == 3)
					CurrentParticleObject = CurrentParticleEmiter->AddCircleEmiter(MousePosition, { vel[0],vel[1] }, radius, amount, tick);

				if (ParticleObject == 4)
					CurrentParticleObject = CurrentParticleEmiter->AddCubeEmiter(MousePosition, { size[0],size[1] }, { vel[0], vel[1] }, amount, tick);

				if (ParticleObject == 5)
					CurrentParticleObject = CurrentParticleEmiter->AddLightSphere(MousePosition, radius, { LightColor[0] ,LightColor[1] ,LightColor[2] ,LightColor[3] });

				if (ParticleObject == 6)
					CurrentParticleObject = CurrentParticleEmiter->AddLightCube(MousePosition, { size[0],size[1] }, { LightColor[0] ,LightColor[1] ,LightColor[2] ,LightColor[3] });

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
					if ((MousePosition - PrevMousePosition).x != 0.0f && (MousePosition - PrevMousePosition).y != 0.0f)
						CurrentParticleEmiter->EmitionCubes[CurrentParticleObject].scale = abs((MousePosition - PrevMousePosition)) * 0.5f;

					CurrentParticleEmiter->EmitionCubes[CurrentParticleObject].position = (MousePosition + PrevMousePosition) * 0.5f;
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
		}
		else
		{
			if (ParticleObject == 0)
			{
				ImGui::Text("SpheresOfInfluence:");
				for (int i = 0; i < CurrentParticleEmiter->SpheresOfInfluence.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 0;
						CurrentRedactingParticleObject = i;
					}
			}
			if (ParticleObject == 1)
			{
				ImGui::Text("CubeOfInfluence:");
				for (int i = 0; i < CurrentParticleEmiter->CubesOfInfluence.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 1;
						CurrentRedactingParticleObject = i;
					}
			}
			if (ParticleObject == 2)
			{
				ImGui::Text("EmitionPoints:");
				for (int i = 0; i < CurrentParticleEmiter->EmitionPoints.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 2;
						CurrentRedactingParticleObject = i;
					}
			}
			if (ParticleObject == 3)
			{
				ImGui::Text("EmitionCircles:");
				for (int i = 0; i < CurrentParticleEmiter->EmitionCircles.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 3;
						CurrentRedactingParticleObject = i;
					}
			}
			if (ParticleObject == 4)
			{
				ImGui::Text("EmitionCubes:");
				for (int i = 0; i < CurrentParticleEmiter->EmitionCubes.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 4;
						CurrentRedactingParticleObject = i;
					}
			}
			if (ParticleObject == 5)
			{
				ImGui::Text("LightSpheres:");
				for (int i = 0; i < CurrentParticleEmiter->LightSpheres.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 5;
						CurrentRedactingParticleObject = i;
					}
			}
			if (ParticleObject == 6)
			{
				ImGui::Text("LightCubes:");
				for (int i = 0; i < CurrentParticleEmiter->LightCubes.size(); i++)
					if (ImGui::Button(std::to_string(i).c_str()))
					{
						CurrentRedactingParticleObjectType = 6;
						CurrentRedactingParticleObject = i;
					}
			}
			if (CurrentRedactingParticleObjectType > -1 && CurrentRedactingParticleObject > -1)
				ShowParticleObjectRedactorWindow(CurrentParticleEmiter, CurrentRedactingParticleObjectType, CurrentRedactingParticleObject);
		}
		for (int i = 0; i < CurrentParticleEmiter->SpheresOfInfluence.size(); i++)
			DrawCircle(CurrentParticleEmiter->SpheresOfInfluence[i].position, CurrentParticleEmiter->SpheresOfInfluence[i].r, glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionCircles.size(); i++)
			DrawCircle(CurrentParticleEmiter->EmitionCircles[i].position, CurrentParticleEmiter->EmitionCircles[i].r, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->LightSpheres.size(); i++)
			DrawCircle(CurrentParticleEmiter->LightSpheres[i].position, CurrentParticleEmiter->LightSpheres[i].r, glm::vec4(1.0f, 1.0f,0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->CubesOfInfluence.size(); i++)
			DrawCube(CurrentParticleEmiter->CubesOfInfluence[i].position, CurrentParticleEmiter->CubesOfInfluence[i].scale, 0.0f, glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionCubes.size(); i++)
			DrawCube(CurrentParticleEmiter->EmitionCubes[i].position, CurrentParticleEmiter->EmitionCubes[i].scale, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->LightCubes.size(); i++)
			DrawCube(CurrentParticleEmiter->LightCubes[i].position, CurrentParticleEmiter->LightCubes[i].scale, 0.0f, glm::vec4(1.0f, 1.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionPoints.size(); i++)
			DrawCircle(CurrentParticleEmiter->EmitionPoints[i].position,10, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		ImGui::End();
	}
	else
	{
		ImGui::DragInt("id", &CurrentParticleEmiter->id, 0.1f);
		ImGui::DragInt("Z_Index", &CurrentParticleEmiter->Z_Index, 0.1f);
		ImGui::SliderInt("TextureId", &selectedTexture, 0, Map.Textures.size() - 1);
		if (selectedTexture >= 0 && selectedTexture < Map.Textures.size())
			ImGui::Text(Map.Textures[selectedTexture].FileName.c_str());
		ImGui::SliderInt("NormalMap", &CurrentParticleEmiter->NormalMapid, -1, Map.NormalMaps.size() - 1);
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
void ShowRedactorWindow(LightSource* ls)
{

	ImGui::Begin(CurrentLightSource->name.c_str());
	
	if (ImGui::Button("Close window"))
	{
		CurrentLightSource = NULL;
		return;
	}
	
	float s[2] = { CurrentLightSource->scale.x ,CurrentLightSource->scale.y };
	ImGui::DragFloat2("Scale", s);
	CurrentLightSource->scale = { s[0],s[1] };


	float pos[3] = { CurrentLightSource->position.x ,CurrentLightSource->position.y,CurrentLightSource->position.z };
	ImGui::DragFloat3("Position", pos,0.001f);
	CurrentLightSource->position = { pos[0],pos[1],pos[2] };

	float col[4] = { CurrentLightSource->color.r ,CurrentLightSource->color.g,CurrentLightSource->color.b,CurrentLightSource->color.a };
	ImGui::ColorEdit4("Color", col);
	CurrentLightSource->color = { col[0],col[1],col[2],col[3] };

	ImGui::DragFloat("Volume", &CurrentLightSource->volume, 0.01f);

	if (CurrentLightSource->TextureId > 0)
		ImGui::Text(Map.Textures[CurrentLightSource->TextureId].FileName.c_str());
	else
		ImGui::Text("Light Sphere Texture");

	ImGui::DragInt("Texture", &CurrentLightSource->TextureId, 0.01f, -1, Map.Textures.size() - 1);

	ImGui::End;
}
void ShowRedactorWindow(ball* Ball)
{
	ImGui::Begin("Ball");
	if (ImGui::Button("Close window"))
	{
		SelectedBall = NULL;
		return;
	}

	ImGui::DragInt("id", &SelectedBall->id, 0.1f);
	ImGui::DragInt("Z_Index", &SelectedBall->Z_Index, 0.1f);

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
	ImGui::SliderInt("Texture", &SelectedBall->Textureid, -1, Map.Textures.size() - 1);
	ImGui::SliderInt("NormalMap", &SelectedBall->NormalMapId, -1, Map.NormalMaps.size() - 1);
	ImGui::Checkbox("Lighted", &SelectedBall->lighted);
	ImGui::DragInt("Collision_Level", &SelectedBall->Collision_Level, 0.01f);
	ImGui::DragInt("Collision_Mask", &SelectedBall->Collision_Mask, 0.01f);

	ImGui::End;
}
void ShowRedactorWindow(cube* Cube)
{
	ImGui::Begin("Cube");
	if (ImGui::Button("Close window"))
	{
		SelectedCube = NULL;
		return;
	}
	ImGui::DragInt("id", &SelectedCube->id, 0.1f);
	ImGui::DragInt("Z_Index", &SelectedCube->Z_Index, 0.1f);

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
	ImGui::SliderInt("Texture", &SelectedCube->Textureid,  -1, Map.Textures.size() - 1);
	ImGui::SliderInt("NormalMap", &SelectedCube->NormalMapId,  -1, Map.NormalMaps.size() - 1);
	ImGui::Checkbox("Lighted", &SelectedCube->lighted);
	ImGui::DragInt("Collision_Level", &SelectedCube->Collision_Level, 0.01f);
	ImGui::DragInt("Collision_Mask", &SelectedCube->Collision_Mask, 0.01f);

	ImGui::End;
}
void ShowRedactorWindow(miscPoint* point)
{
	ImGui::Begin("Point");
	if (ImGui::Button("Close window"))
	{
		SelectedPoint = NULL;
		return;
	}
	ImGui::DragInt("Id", &SelectedPoint->id,0.1f);

	float pos[2] = { SelectedPoint->position.x ,SelectedPoint->position.y };
	ImGui::DragFloat2("Position", pos);
	SelectedPoint->position = { pos[0],pos[1] };


	ImGui::End;
}
void PolygonTools(polygon* poly)
{


	ImGui::Begin("Polygon Tools");

	if (ImGui::Button("Save as polygon.pol"))
	{
		poly->SaveAs("polygon.pol");
	}
	if (ImGui::Button("load polygon.pol"))
	{
		poly->Load("polygon.pol");
		poly->Update_Shape();
	}

	if (ImGui::Button("Pushback color"))
	{
		poly->colors.push_back(glm::vec4((rand() % 100 / 50.0f), (rand() % 100 / 50.0f), (rand() % 100 / 50.0f), 1.0f));
	}
	if (ImGui::Button("Clear"))
	{
		poly->triangles.clear();
		poly->indexes.clear();
		poly->points.clear();
		poly->colors.clear();
		poly->TexturePoints.clear();
		poly->state = 0;
	}

	ImGui::Text("hold ctrl to interact with points");
	ImGui::Text("hold shift, to add new triangles between existing points");





	if (keys[GLFW_KEY_LEFT_ALT])
	{

		for (int i = 0; i < poly->points.size(); i++)
			DrawCircle(poly->points[i], 10, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));



		if (JustPressedLMB)
		{
			poly->add_Point(MousePosition, false);
		}
	}
	//creation
	if (keys[GLFW_KEY_LEFT_CONTROL] && !keys[GLFW_KEY_LEFT_SHIFT])
	{
		if (JustPressedLMB)
		{
			bool gr = false;

			for (int i = 0; i < poly->points.size(); i++)
			{
				if (!gr)
				{
					float distance = sqrlength(poly->points[i] - MousePosition);

					if (distance < 100)
					{
						grabbedpoint = i;
						gr = true;
					}
				}
			}
		}

		if (grabbedpoint >= 0 && grabbedpoint < poly->points.size())
			poly->points[grabbedpoint] = MousePosition;

		if (ReleasedLMB)grabbedpoint = -1;


		for (int i = 0; i < poly->points.size(); i++)
			DrawCircle(poly->points[i], 10, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		poly->Update_Shape();
	}
	// connection
	if (!keys[GLFW_KEY_LEFT_CONTROL] && keys[GLFW_KEY_LEFT_SHIFT] && poly->points.size() > 0)
	{

		if (JustPressedLMB)
		{
			int copycheck = indexCreationState;
			for (int i = 0; i < poly->points.size(); i++)
			{

				float distance = sqrlength(poly->points[i] - MousePosition);

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
							poly->indexes.push_back(tmpIndex);
						else std::cout << "failed to add index";
						tmpIndex.x = -1;
						tmpIndex.y = -1;
						tmpIndex.z = -1;
					}
				}
			}
		}
		for (int i = 0; i < poly->points.size(); i++)
		{

			DrawCircle(poly->points[i], 10, glm::vec4(
				i == tmpIndex.x ? 1.0f : 0.0f,
				i == tmpIndex.y ? 1.0f : 0.0f,
				i == tmpIndex.z ? 1.0f : 0.0f,
				1.0f));
		}
		poly->Update_Shape();
	}
}
void ShowRedactorWindow(polygon* Polygon)
{

	ImGui::Begin("Polygon");
	if (ImGui::Button("Close window"))
	{
		SelectedPolygon = NULL;
		return;
	}
	ImGui::DragInt("id", &SelectedPolygon->id, 0.1f);
	ImGui::DragInt("Z_Index", &SelectedPolygon->Z_Index, 0.1f);

	float col[4] = { SelectedPolygon->colors[0].r ,SelectedPolygon->colors[0].g,SelectedPolygon->colors[0].b,SelectedPolygon->colors[0].a };
	ImGui::ColorEdit4("Color", col);
	SelectedPolygon->colors[0] = { col[0],col[1],col[2],col[3] };
	if (SelectedPolygon->Textureid > -1)
		ImGui::Text(Map.Textures[SelectedPolygon->Textureid].FileName.c_str());
	else
		ImGui::Text("Clear Color");
	ImGui::SliderInt("Texture", &SelectedPolygon->Textureid, -1, Map.Textures.size() - 1);
	ImGui::SliderInt("NormalMap", &SelectedPolygon->NormalMapId,  -1, Map.NormalMaps.size() - 1);
	ImGui::Checkbox("Lighted", &SelectedPolygon->lighted);
	ImGui::DragInt("Collision_Level", &SelectedPolygon->Collision_Level, 0.01f);
	ImGui::DragInt("Collision_Mask", &SelectedPolygon->Collision_Mask, 0.01f);

	if (ImGui::Button("ShowPolygonTools"))
		ShowPolygonTools = !ShowPolygonTools;


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

	ImGui::End;

	if (ShowPolygonTools && SelectedPolygon != NULL)
		PolygonTools(SelectedPolygon);
}

int DeletetextureCountDown = 2;
void ShowRedactorWindow(Texture* Texture)
{

	ImGui::Begin("Texture");
	//ImGui::Text( CurrentTexture->FileName.c_str() );
	
	if (ImGui::Button("Close window"))
	{
		CurrentTexture = NULL;
		ImGui::End();
		return;
	}
	for (int i = 0; i < 256; i++)
	{
		if (i < CurrentTexture->FileName.size())
			SelectedTextureCharName[i] = CurrentTexture->FileName[i];
		else
			SelectedTextureCharName[i] = char();
	}

	ImGui::InputText("Texture Name:", SelectedTextureCharName, 256);

	CurrentTexture->FileName.clear();
	for (int i = 0; i < 256; i++)
		if (SelectedTextureCharName[i] != char())
			CurrentTexture->FileName += SelectedTextureCharName[i];

	ImGui::Text("Texture ID = %i", CurrentTexture->texture);

	int typ = CurrentTexture->Type;
	ImGui::SliderInt("Type ", &CurrentTexture->Type, 0, 3);

	if (CurrentTexture->Type == 0)
		ImGui::Text("LoadFromName");
	if (CurrentTexture->Type == 1)
		ImGui::Text("Round Noize");
	if (CurrentTexture->Type == 2)
		ImGui::Text("Squere Noize");
	if (CurrentTexture->Type == 3)
		ImGui::Text("Smooth Squere Noize");

	if (typ != CurrentTexture->Type)
	{
		CurrentTexture->Delete();
		CurrentTexture->Load();
	}
	if (CurrentTexture->Type != 0)
	{
		float Tex_Freq = CurrentTexture->Noize_Frequency;
		ImGui::DragFloat("Frequency ", &CurrentTexture->Noize_Frequency,0.01f);
		if (Tex_Freq != CurrentTexture->Noize_Frequency)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}
		int NoizeLayers = CurrentTexture->Noize_Layers;
		ImGui::DragInt("Layers ", &CurrentTexture->Noize_Layers);
		if (NoizeLayers != CurrentTexture->Noize_Layers)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}
		float Tex_Size = CurrentTexture->Noize_Size;
		ImGui::DragFloat("Size ", &CurrentTexture->Noize_Size);
		if (Tex_Size != CurrentTexture->Noize_Size)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}
	}

	if (ImGui::Button("DeleteTexture"))
		DeletetextureCountDown--;
	ImGui::SameLine();
	ImGui::Text("%i", DeletetextureCountDown);
	if (DeletetextureCountDown <= 0)
	{
		DeletetextureCountDown = 2;
		CurrentTexture->Delete();
		int i = 0;
		bool found = false;
		while (!found && i < Map.Textures.size())
		{
			i++;
			if (Map.Textures[i].id == CurrentTexture->id)
				found = true;
		}
		Map.Textures[i] = Map.Textures[Map.Textures.size() - 1];
		Map.Textures.pop_back();
		CurrentTexture = NULL;
		ImGui::End();
		return;
	}
	ImGui::End();
}



void On_Create() 
{
		Map.LoadFrom(MapFileName);

		for (int i = 0; i < MapFileName.size(); i++)
			MapFileNameChars[i] = MapFileName[i];





}
void On_Update()
{

		if (keys[GLFW_KEY_W]) CameraPosition.y += delta / CameraScale.y * 600.0f;
		if (keys[GLFW_KEY_S]) CameraPosition.y -= delta / CameraScale.y * 600.0f;
		if (keys[GLFW_KEY_A]) CameraPosition.x -= delta / CameraScale.x * 600.0f;
		if (keys[GLFW_KEY_D]) CameraPosition.x += delta / CameraScale.x * 600.0f;
		if (keys[GLFW_KEY_Q]) CameraScale *= 1.01f;
		if (keys[GLFW_KEY_E]) CameraScale *= 0.99f;


		ImGui::Begin("Tools");

		ImGui::Text("CameraPosition X = %.1f, Y = %.1f", CameraPosition.x, CameraPosition.y);
		ImGui::Text("CameraScale X = %.3f, Y = %.3f", CameraScale.x, CameraScale.y);
		if (ImGui::Button("Reset Camera"))
		{
			CameraPosition = { 0.0f,0.0f };
			CameraScale = { 1.0f,1.0f };
		}

		ImGui::InputText("Save file:", MapFileNameChars, 128);
		if (ImGui::Button("Save") || keys[GLFW_KEY_LEFT_CONTROL]&& keys[GLFW_KEY_S])
		{
			MapFileName = "";
			for (int i = 0; i < 128; i++)
			{
				if (MapFileNameChars[i] != ' ')
					MapFileName += MapFileNameChars[i];
			}
			Map.SaveAs(MapFileName);
		}if (ImGui::Button("Load"))
		{
			MapFileName = "";
			for (int i = 0; i < 128; i++)
			{
				if (MapFileNameChars[i] != ' ')
					MapFileName += MapFileNameChars[i];
			}
			Map.LoadFrom(MapFileName);
		}

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
			if (RedactorObject == 3)str = "Point";
			ImGui::SliderInt(str, &RedactorObject, 0, 3);

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
			if (RedactorObject == 3)
			{
				ImGui::DragInt("Id", &Id, 0.1f, 0);
			}
			ImGui::Checkbox("Lighted", &Lighted);


			if (JustPressedLMB && keys[GLFW_KEY_LEFT_SHIFT])
			{
				PrevMousePosition = MousePosition;
				if (RedactorObject == 0)
				{
					ball b;
					b.position = PrevMousePosition;
					b.r = radius;
					b.lighted = Lighted;
					Map.balls.push_back(b);
					CurrentRedactorObject = Map.balls.size() - 1;
				}
				if (RedactorObject == 1)
				{
					cube c;
					c.width = size[0];
					c.height = size[1];
					c.position = PrevMousePosition;
					c.lighted = Lighted;
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
					p.lighted = Lighted;
					Map.polygons.push_back(p);
					CurrentRedactorObject = Map.polygons.size() - 1;
				}
				if (RedactorObject == 3)
				{
					miscPoint p;
					p.id = Id;
					p.position = MousePosition;
					Map.points.push_back(p);
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
		

		if (ImGui::Button("ParticlesWindow"))
			ShowParticlesWindow = !ShowParticlesWindow;

		if (ImGui::Button("LightSourcesWindow"))
			ShowLightSourcesWindow = !ShowLightSourcesWindow;

		if (ImGui::Button("TexturesWindow"))
			ShowTexturesWindow = !ShowTexturesWindow;
		if (ImGui::Button("NormalMapsWindow"))
			ShowNormalMapsWindow = !ShowNormalMapsWindow;

		if (ImGui::Button("SceneSettingsWindow"))
			SettingsWindow = !SettingsWindow;

		if (ImGui::Button("Recompile Shaders"))
			PreLoadShaders();
		ImGui::End();


		if (ShowTexturesWindow)
		{
			ImGui::Begin("Textures:");
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
				tex.texture = NULL;
				tex.Load();
				if (tex.texture != NULL)
					Map.Textures.push_back(tex);
			}

			ImGui::Text("Textures:");
			for (int i = 0; i < Map.Textures.size(); i++)
			{
				if (ImGui::Button(Map.Textures[i].FileName.c_str()))
					CurrentTexture = &Map.Textures[i];
			}
			ImGui::End();
		}
		if (ShowNormalMapsWindow)
		{
			ImGui::Begin("NormalMaps:");
			ImGui::Text("texture/path/...");
			ImGui::InputText("Texture path:", TexturePath, 128);


			if (ImGui::Button("LoadTexture"))
			{
				std::string s = "";
				for (int i = 0; i < 128; i++)
				{
					if (TexturePath[i] != ' ')
						s += TexturePath[i];
				}
				tex.FileName = s;
				tex.id = Map.NormalMaps.size();
				tex.Load();
				if (tex.texture != NULL)
					Map.NormalMaps.push_back(tex);
			}

			ImGui::Text("NormalMaps:");
			for (int i = 0; i < Map.NormalMaps.size(); i++)
			{
				if (ImGui::Button(Map.NormalMaps[i].FileName.c_str()))
					CurrentTexture = &Map.NormalMaps[i];
			}
			ImGui::End();
		}
		if (ShowParticlesWindow)
		{
			ImGui::Begin("Particles:");
			ImGui::InputText("Particle Emitter Name:", ParticleEmitterCharName, 256);
			if (ImGui::Button("Add"))
			{
				int EndOfName = -1;
				for (int i = 255; i >= 0; i--)
					if (ParticleEmitterCharName[i] != char() && ParticleEmitterCharName[i] != ' ' && EndOfName < 0)
						EndOfName = i;


				std::string nm;
				if (EndOfName > 0)
					for (int i = 0; i <= EndOfName; i++)
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
		}
		if (ShowLightSourcesWindow)
		{
			ImGui::Begin("LightSources:");

			ImGui::InputText("LightSource Name:", LightSourceCharName, 256);
			if (ImGui::Button("Add"))
			{
				LightSource ls;
				int EndOfName = -1;
				for (int i = 255; i >= 0; i--)
					if (LightSourceCharName[i] != char() && LightSourceCharName[i] != ' ' && EndOfName < 0)
						EndOfName = i;


				std::string nm = "";
				if (EndOfName > 0)
					for (int i = 0; i <= EndOfName; i++)
						nm += LightSourceCharName[i];
				else if (EndOfName == 0)
					nm += LightSourceCharName[0];
				else
					nm = "LightSource" + std::to_string(Map.LightSources.size());
				ls.name = nm;
				Map.LightSources.push_back(ls);
			}


			ImGui::Text("LightSources:");
			for (int i = 0; i < Map.LightSources.size(); i++)
			{
				if (ImGui::Button(Map.LightSources[i].name.c_str()))
					CurrentLightSource = &Map.LightSources[i];
			}


			ImGui::End();
		}

		if (!RedactingScene)
		{
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

			if (SelectedPoint != NULL)
				ShowRedactorWindow(SelectedPoint);

			if (CurrentLightSource != NULL)
				ShowRedactorWindow(CurrentLightSource);
		}

		//GrabTool
		if (!RedactingParticlesEmiter && !RedactingScene && GrabSelectTool && !RedactingPolygon )
		{
			if (JustPressedLMB)
			{
				PrevMousePosition = MousePosition;
				grabbedBall = NULL;
				grabbedCube = NULL;
				grabbedPolygon = NULL;
				grabbedPoint = NULL;
				grabbedType = -1;
				grabbed = false;

				for (int i = 0; i < Map.points.size(); i++)
				{
					if (sqrlength(MousePosition - Map.points[i].position) < 25 * 25)
					{
						grabbedPoint = &Map.points[i];
						grabbedType = 3;
						grabbed = true;
					}
				}
				for (int i = 0; i < Map.balls.size(); i++)
				{
					if (BalltoPointCollisionCheck(Map.balls[i], MousePosition))
					{
						if (grabbedBall != NULL)
						{
							if (grabbedBall->Z_Index < Map.balls[i].Z_Index)
							{
								grabbedBall = &Map.balls[i];
								grabbedType = 0;
							}
						}
						else if(grabbedCube != NULL)
						{
							if (grabbedCube->Z_Index < Map.balls[i].Z_Index)
							{
								grabbedBall = &Map.balls[i];
								grabbedType = 0;
							}
						}
						else if (grabbedPolygon != NULL)
						{
							if (grabbedPolygon->Z_Index < Map.balls[i].Z_Index)
							{
								grabbedBall = &Map.balls[i];
								grabbedType = 0;
							}
						}
						else if (grabbedPoint==NULL)
						{
							grabbedBall = &Map.balls[i];
							grabbedType = 0;
						}
						grabbed = true;
					}
				}
				for (int i = 0; i < Map.cubes.size(); i++)
				{
					if (PointToQuadCollisionCheck(Map.cubes[i], MousePosition))
					{
						if (grabbedBall != NULL)
						{
							if (grabbedBall->Z_Index < Map.cubes[i].Z_Index)
							{
								grabbedCube = &Map.cubes[i];
								grabbedType = 1;
							}
						}
						else if (grabbedCube != NULL)
						{
							if (grabbedCube->Z_Index < Map.cubes[i].Z_Index)
							{
								grabbedCube = &Map.cubes[i];
								grabbedType = 1;
							}
						}
						else if (grabbedPolygon != NULL)
						{
							if (grabbedPolygon->Z_Index < Map.cubes[i].Z_Index)
							{
								grabbedCube = &Map.cubes[i];
								grabbedType = 1;
							}
						}
						else if (grabbedPoint == NULL)
						{
							grabbedCube = &Map.cubes[i];
							grabbedType = 1;
						}
						grabbed = true;
					}
				}
				for (int i = 0; i < Map.polygons.size(); i++)
				{
					if (PointToPolygonCollisionCheck(MousePosition, Map.polygons[i]))
					{
						if (grabbedBall != NULL)
						{
							if (grabbedBall->Z_Index < Map.polygons[i].Z_Index)
							{
								grabbedPolygon = &Map.polygons[i];
								grabbedType = 2;
							}
						}
						else if (grabbedCube != NULL)
						{
							if (grabbedCube->Z_Index < Map.polygons[i].Z_Index)
							{
								grabbedPolygon = &Map.polygons[i];
								grabbedType = 2;
							}
						}
						else if (grabbedPolygon != NULL)
						{
							if (grabbedPolygon->Z_Index < Map.polygons[i].Z_Index)
							{
								grabbedPolygon = &Map.polygons[i];
								grabbedType = 2;
							}
						}
						else if (grabbedPoint == NULL)
						{
							grabbedPolygon = &Map.polygons[i];
							grabbedType = 2;
						}
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

				if (grabbedPoint != NULL && grabbed && grabbedType == 3)
					SelectedPoint = grabbedPoint;

				grabbedBall = NULL;
				grabbedCube = NULL;
				grabbedPolygon = NULL;
				grabbedPoint = NULL;
				grabbedType = -1;
				grabbed = false;
			}
			else if (buttons[GLFW_MOUSE_BUTTON_1] && PrevMousePosition != MousePosition && keys[GLFW_KEY_LEFT_CONTROL])
			{
				if (grabbedBall != NULL && grabbed && grabbedType == 0)
					grabbedBall->position = MousePosition;

				if (grabbedCube != NULL && grabbed && grabbedType == 1)
					grabbedCube->position = MousePosition;

				if (grabbedPoint != NULL && grabbed && grabbedType == 3)
					grabbedPoint->position = MousePosition;
			}
		}

		Map.Draw();

		for (int i = 0; i < Map.points.size(); i++)
			DrawCircle(Map.points[i].position, 25, glm::vec4(1.0f,0.0f,0.0f,1.0f));
}

int main()
{
	initEngine();
	//app.init("Redactor",1920,1080,true);
	Map.SaveAs(MapFileName + ".back");
	return 0;
}

