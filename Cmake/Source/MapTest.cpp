#include "engine/Components/Engine.h"


char MapFileNameChars[128];
//std::string MapFileName =  "Maps/MenuScene.sav";
//std::string MapFileName =  "Maps/base.sav";
//std::string MapFileName =  "Maps/Background.sav";
//std::string MapFileName =  "../../HEAT/Maps/base.sav";
std::string MapFileName =  "./ECStests.sav";

//std::string MapFileName = "Maps/Shadertest.sav";
/*


	Corner.y += UI_DrawText("Fragment path: ", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&CurrentShader->FragmentPath, Corner, &Texteditcurspos, &textedit, -1).y * -1.0f - step;
	Corner.y += UI_buttonOnlyON(&b,"Load", Corner).y * -1.0f - step;
	Corner.y += UI_CheckBox(&CurrentParticleEmiter->ShowWindow,"ShowSettings", Corner).y * -1.0f - step;


	float xsize = 0.0f;

	Corner.y += UI_Drag(&CurrentShader->uniformfloat[CurrentShader->Uniforms[i].type_id], CurrentShader->Uniforms[i].name.c_str(), Corner, 0.01f).y * -1.0f - step;
	Corner.y += UI_DragInt(&CurrentShader->uniformint[CurrentShader->Uniforms[i].type_id], CurrentShader->Uniforms[i].name.c_str(), Corner, 0.01f).y * -1.0f - step;
	
	Corner.y += UI_DrawText(CurrentShader->Uniforms[i].name.c_str(), Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&CurrentShader->uniformvec2[CurrentShader->Uniforms[i].type_id].x, "x", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&CurrentShader->uniformvec2[CurrentShader->Uniforms[i].type_id].y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_DrawText(CurrentShader->Uniforms[i].name.c_str(), Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&CurrentShader->uniformvec3[CurrentShader->Uniforms[i].type_id].x, "x", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&CurrentShader->uniformvec3[CurrentShader->Uniforms[i].type_id].y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&CurrentShader->uniformvec3[CurrentShader->Uniforms[i].type_id].z, "z", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
		
	Corner.y += UI_DrawText(CurrentShader->Uniforms[i].name.c_str(), Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].x, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].y, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].z, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].w, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
*/


Scene Map;
Texture tex;

std::string TexturePath;


glm::vec2 PrevMousePosition = { 0.0f,0.0f };
glm::vec2 Corner = { 0.0f,0.0f };

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

int NewObjectId = 0;
int NewAssetId = 1;

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

bool ShowParticles = false;
bool ShowLightSources = false;
bool ShowTextures = false;
bool ShowNormalMaps = false;
bool ShowShaders = false;
bool ShowMeshes = false;

polygonData DefaultTriangle;

Node* GrabbedNode = NULL;
int GrabbedNodeID = -1;
bool grabbed = false;

Node* SelectedNode = NULL;
int SelectedNodeID = -1;

Asset* SelectedAsset = NULL;
int SelectedAssetID = -1;
void ProcessSelectedNodeUI()
{
	float xsize = 0.0f;
	float step = 15.0f;
	float xoffset = 0.0f;
	std::vector<UI_DataPack> datapacks;
	if(SelectedNode!=NULL)
	{
		datapacks = SelectedNode->GetUIData();
		Corner.y += UI_DrawText(SelectedNode->Name, Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;	
	}
	else if (SelectedAsset !=NULL)
	{
		datapacks = SelectedAsset->GetUIData();
		Corner.y += UI_DrawText(SelectedAsset->Name, Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;	
	}
	else
		return;

	for(int i=0;i<datapacks.size();i++)
	{
		xsize = 0.0f;
		xoffset=20.0f;
		Corner.y += UI_DrawText(datapacks[i].name, Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;
		xoffset = 40.0f;
		for(int a = 0; a<datapacks[i].bdata.size();a++)
			Corner.y += UI_CheckBox(datapacks[i].bdata[a],datapacks[i].bdatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f)).y * -1.0f - step;
			
		for(int a = 0; a<datapacks[i].idata.size();a++)
			Corner.y += UI_DragInt(datapacks[i].idata[a],datapacks[i].idatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f),0.2f).y * -1.0f - step;
			

		for(int a = 0; a<datapacks[i].fdata.size();a++)
			Corner.y += UI_Drag(datapacks[i].fdata[a],datapacks[i].fdatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f),0.2f).y * -1.0f - step;
			
		for(int a = 0; a<datapacks[i].iSliderdata.size();a++)
			Corner.y += UI_SliderInt(&datapacks[i].iSliderdata[a]->x,datapacks[i].iSliderdatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f),datapacks[i].iSliderdata[a]->y,datapacks[i].iSliderdata[a]->z).y * -1.0f - step;

		for(int a = 0; a<datapacks[i].fSliderdata.size();a++)
			Corner.y += UI_Slider(&datapacks[i].fSliderdata[a]->x,datapacks[i].fSliderdatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f),datapacks[i].fSliderdata[a]->y,datapacks[i].fSliderdata[a]->z).y * -1.0f - step;

		for(int a = 0; a<datapacks[i].v2data.size();a++)
		{
			Corner.y += UI_DrawText(datapacks[i].v2datanames[a], Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&datapacks[i].v2data[a]->x, "x", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&datapacks[i].v2data[a]->y, "y", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
			xsize = 0.0f;
		}
		for(int a = 0; a<datapacks[i].v3data.size();a++)
		{
			Corner.y += UI_DrawText(datapacks[i].v3datanames[a], Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&datapacks[i].v3data[a]->x, "x", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&datapacks[i].v3data[a]->y, "y", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&datapacks[i].v3data[a]->z, "z", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
			xsize = 0.0f;
		}
		for(int a = 0; a<datapacks[i].v4data.size();a++)
		{
			Corner.y += UI_DrawText(datapacks[i].v4datanames[a], Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&datapacks[i].v4data[a]->x, "x", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&datapacks[i].v4data[a]->y, "y", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&datapacks[i].v4data[a]->z, "z", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&datapacks[i].v4data[a]->w, "w", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
			xsize = 0.0f;
		}
		for(int a = 0; a<datapacks[i].colordata.size();a++)
		{
			Corner.y += UI_DrawText(datapacks[i].colordatanames[a], Corner + glm::vec2(xoffset,0.0f), 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&datapacks[i].colordata[a]->x, "r", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&datapacks[i].colordata[a]->y, "g", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&datapacks[i].colordata[a]->z, "b", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&datapacks[i].colordata[a]->w, "a", Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
			xsize = 0.0f;
		}

		for(int a = 0; a<datapacks[i].textdata.size();a++)
		{
			xsize = UI_DrawText(datapacks[i].textdatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f),0.35f).x;
			Corner.y += UI_TextBox(datapacks[i].textdata[a], Corner+ glm::vec2(xoffset,0.0f)  + glm::vec2(xsize, 0.0f)).y * -1.0f - step;
			xsize = 0.0f;
		}

		
		for(int a = 0; a<datapacks[i].texturedata.size();a++)
		{
			xsize = UI_DrawText(datapacks[i].texturedatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f),0.35f).x;
			Corner.y += UI_TextBox(datapacks[i].texturedata[a], Corner+ glm::vec2(xoffset,0.0f)  + glm::vec2(xsize, 0.0f)).y * -1.0f - step;
			xsize = 0.0f;
		}
		for(int a = 0; a<datapacks[i].materialdata.size();a++)
		{
			xsize = UI_DrawText(datapacks[i].materialdatanames[a].c_str(), Corner + glm::vec2(xoffset,-7.5f) + glm::vec2(xsize, 0.0f),0.35f).x;
			Corner.y += UI_TextBox(datapacks[i].materialdata[a], Corner+ glm::vec2(xoffset,0.0f)  + glm::vec2(xsize, 0.0f)).y * -1.0f - step;
			xsize = 0.0f;
		}

		for(int a = 0; a<datapacks[i].ParticleAssetdata.size();a++)
		{
			xsize = UI_DrawText(datapacks[i].ParticleAssetdatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f) + glm::vec2(xsize, 0.0f),0.35f).x;
			Corner.y += UI_TextBox(datapacks[i].ParticleAssetdata[a], Corner+ glm::vec2(xoffset,0.0f)  + glm::vec2(xsize, 0.0f)).y * -1.0f - step;
			xsize = 0.0f;
		}

		
		for(int a = 0; a<datapacks[i].t_texturedata.size();a++)
		{
			
			Corner.y += UI_DrawText(datapacks[i].t_texturedatanames[a].c_str(), Corner + glm::vec2(xoffset,0.0f),0.35f).y * -1.0f - step;
			xoffset+= 20.0f;
			Corner += glm::vec2(xoffset,0.0f);
					
			int typ = datapacks[i].t_texturedata[a]->Type;

			Corner.y += UI_SliderInt(&datapacks[i].t_texturedata[a]->Type, "type", Corner, 0, 9).y * -1.0f - step;

			if (datapacks[i].t_texturedata[a]->Type == 0)
				Corner.y += UI_DrawText("LoadFromName",Corner,0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 1)
				Corner.y += UI_DrawText("Round Noize",Corner,0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 2)
				Corner.y += UI_DrawText("Squere Noize",Corner,0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 3)
				Corner.y += UI_DrawText("Smooth Squere Noize",Corner,0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 4)
				Corner.y += UI_DrawText("Gradient", Corner, 0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 5)
				Corner.y += UI_DrawText("Gradient Sphere", Corner, 0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 6)
				Corner.y += UI_DrawText("Sphere", Corner, 0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 7)
				Corner.y += UI_DrawText("Quad", Corner, 0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 8)
				Corner.y += UI_DrawText("SphereNormalMap", Corner, 0.35f).y * -1.0f - step;
			if (datapacks[i].t_texturedata[a]->Type == 9)
				Corner.y += UI_DrawText("QuadNormalMap", Corner, 0.35f).y * -1.0f - step;

			std::string filter = "Linear/blurry";
			if (datapacks[i].t_texturedata[a]->filter)
				filter = "Nearest/pixelart";
			bool filt = datapacks[i].t_texturedata[a]->filter;
			Corner.y += UI_CheckBox(&datapacks[i].t_texturedata[a]->filter,filter.c_str(), Corner,18.0f, 0.35f).y * -1.0f - step;

			if (filt != datapacks[i].t_texturedata[a]->filter)
			{

				datapacks[i].t_texturedata[a]->Delete();
				datapacks[i].t_texturedata[a]->Load();
			}


			if (typ != datapacks[i].t_texturedata[a]->Type)
			{
				datapacks[i].t_texturedata[a]->Delete();
				datapacks[i].t_texturedata[a]->Load();
			}

			if(datapacks[i].t_texturedata[a]->Type  == 0)
			{
				xsize = UI_DrawText("FileName", Corner,0.35f).x;
				Corner.y += UI_TextBox(&datapacks[i].t_texturedata[a]->FileName, Corner + glm::vec2(xsize, 0.0f)).y * -1.0f - step;
				xsize = 0.0f;
			}
			if (datapacks[i].t_texturedata[a]->Type > 0 && datapacks[i].t_texturedata[a]->Type < 4)
			{
				float Tex_Freq = datapacks[i].t_texturedata[a]->Noize_Frequency;
				Corner.y += UI_Drag(&datapacks[i].t_texturedata[a]->Noize_Frequency,"Frequency ",Corner, 0.01f).y * -1.0f - step;
				if (Tex_Freq != datapacks[i].t_texturedata[a]->Noize_Frequency)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}
				int NoizeLayers = datapacks[i].t_texturedata[a]->Noize_Layers;

				Corner.y += UI_DragInt(&datapacks[i].t_texturedata[a]->Noize_Layers, "Layers ", Corner, 0.01f).y * -1.0f - step;

				if (NoizeLayers != datapacks[i].t_texturedata[a]->Noize_Layers)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}
				float Tex_Size = datapacks[i].t_texturedata[a]->Size;
				Corner.y += UI_Drag(&datapacks[i].t_texturedata[a]->Size, "Size ", Corner, 0.1f).y * -1.0f - step;
				if (Tex_Size != datapacks[i].t_texturedata[a]->Size)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}
			}
			else if (datapacks[i].t_texturedata[a]->Type == 4)
			{
				glm::vec4 color = datapacks[i].t_texturedata[a]->Gradient_Color1;


				Corner.y += UI_DrawText("Gradient Color1", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color1.r, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color1.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color1.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color1.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

				if (color != datapacks[i].t_texturedata[a]->Gradient_Color1)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}

				color = datapacks[i].t_texturedata[a]->Gradient_Color2;

				Corner.y += UI_DrawText("Gradient Color2", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color2.r, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color2.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color2.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&datapacks[i].t_texturedata[a]->Gradient_Color2.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

				if (color != datapacks[i].t_texturedata[a]->Gradient_Color2)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}

				float Tex_Size = datapacks[i].t_texturedata[a]->Size;
				Corner.y += UI_Drag(&datapacks[i].t_texturedata[a]->Size, "Size ", Corner, 0.1f).y * -1.0f - step;

				if (Tex_Size != datapacks[i].t_texturedata[a]->Size)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}

			}
			else
			{
				
				float Tex_Size = datapacks[i].t_texturedata[a]->Size;
				Corner.y += UI_Drag(&datapacks[i].t_texturedata[a]->Size, "Size ", Corner, 0.1f).y * -1.0f - step;

				if (Tex_Size != datapacks[i].t_texturedata[a]->Size)
				{
					datapacks[i].t_texturedata[a]->Delete();
					datapacks[i].t_texturedata[a]->Load();
				}

			}

			Corner -= glm::vec2(xoffset,0.0f);
			xsize = 0.0f;
			xoffset-= 20.0f;
		}

		
	}
	if(SelectedNode!=NULL)
	{
		SelectedNode->CustomUIDraw(&Corner,xoffset,step);
		if(JustPressedkey[GLFW_KEY_DELETE])
		{
			SelectedNode->Delete = true;
			SelectedNode = NULL;
			SelectedNodeID = -1;
		}
	}
	else if (SelectedAsset !=NULL)
	{
		SelectedAsset->CustomUIDraw(&Corner,xoffset,step);
		if(JustPressedkey[GLFW_KEY_DELETE])
		{
			SelectedAsset->Delete = true;
			SelectedAsset = NULL;
			SelectedAssetID = -1;
		}
	}

}

/*
void ShowParticleObjectRedactorWindow(ParticleEmiter* PE,int type,int i)
{
	
	if(type == -1 || i == -1)
		return;
	float step = 20.0f;
	float xsize = 0.0f;

	Corner.y += UI_DrawText("Particle Object", Corner, 0.35f).y * -1.0f - step;
	if (type == 0)
	{


		Corner.y += UI_DrawText("Sphere of influence", Corner, 0.35f).y * -1.0f - step;


		Corner.y += UI_Drag(&PE->SpheresOfInfluence[i].attractionStrength, "attractionForce", Corner, 0.01f).y * -1.0f - step;
		Corner.y += UI_CheckBox(&PE->SpheresOfInfluence[i].attractive, "attractive", Corner).y * -1.0f - step;

		Corner.y += UI_Drag(&PE->SpheresOfInfluence[i].r, "Radius", Corner, 0.1f).y * -1.0f - step;


		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->SpheresOfInfluence[i].position.x, "x", Corner , 1.0f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->SpheresOfInfluence[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->SpheresOfInfluence[i].velocity.x, "x", Corner , 1.0f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->SpheresOfInfluence[i].velocity.y, "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 80.0f,15.0f }).y * -1.0f - step;

		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->SpheresOfInfluence[i] = PE->SpheresOfInfluence[PE->SpheresOfInfluence.size() - 1];
			PE->SpheresOfInfluence.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}

	}
	else if (type == 1)
	{
		Corner.y += UI_DrawText("Cube of influence", Corner, 0.35f).y * -1.0f - step;

		Corner.y += UI_Drag(&PE->CubesOfInfluence[i].attractionStrength, "attractionForce", Corner, 0.01f).y * -1.0f - step;
		Corner.y += UI_CheckBox(&PE->CubesOfInfluence[i].attractive, "attractive", Corner).y * -1.0f - step;

		Corner.y += UI_DrawText("Scale", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->CubesOfInfluence[i].scale.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->CubesOfInfluence[i].scale.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->CubesOfInfluence[i].position.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->CubesOfInfluence[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->CubesOfInfluence[i].velocity.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->CubesOfInfluence[i].velocity.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;
		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->CubesOfInfluence[i] = PE->CubesOfInfluence[PE->CubesOfInfluence.size() - 1];
			PE->CubesOfInfluence.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}
	}
	else if (type == 2)
	{
		Corner.y += UI_DrawText("Point Emiter", Corner, 0.35f).y * -1.0f - step;


		Corner.y += UI_Drag(&PE->EmitionPoints[i].tick, "Tick", Corner, 0.01f).y * -1.0f - step;
		Corner.y += UI_DragInt(&PE->EmitionPoints[i].amount, "Amount", Corner, 0.01f).y * -1.0f - step;

		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionPoints[i].position.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionPoints[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionPoints[i].velocity.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionPoints[i].velocity.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;
		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->EmitionPoints[i] = PE->EmitionPoints[PE->EmitionPoints.size() - 1];
			PE->EmitionPoints.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}
	}
	else if (type == 3)
	{
		Corner.y += UI_DrawText("Crcle Emiter", Corner, 0.35f).y * -1.0f - step;


		Corner.y += UI_Drag(&PE->EmitionCircles[i].tick, "Tick", Corner, 0.01f).y * -1.0f - step;
		Corner.y += UI_DragInt(&PE->EmitionCircles[i].amount, "Amount", Corner, 0.01f).y * -1.0f - step;

		Corner.y += UI_Drag(&PE->EmitionCircles[i].r, "Radius", Corner, 0.01f).y * -1.0f - step;


		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionCircles[i].position.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionCircles[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionCircles[i].velocity.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionCircles[i].velocity.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;
		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->EmitionCircles[i] = PE->EmitionCircles[PE->EmitionCircles.size() - 1];
			PE->EmitionCircles.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}
	}
	else if (type == 4)
	{
		Corner.y += UI_DrawText("Cube Emiter", Corner, 0.35f).y * -1.0f - step;


		Corner.y += UI_Drag(&PE->EmitionCubes[i].tick, "Tick", Corner, 0.01f).y * -1.0f - step;
		Corner.y += UI_DragInt(&PE->EmitionCubes[i].amount, "Amount", Corner, 0.01f).y * -1.0f - step;


		Corner.y += UI_DrawText("scale", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionCubes[i].scale.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionCubes[i].scale.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionCubes[i].position.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionCubes[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->EmitionCubes[i].velocity.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->EmitionCubes[i].velocity.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;
		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->EmitionCubes[i] = PE->EmitionCubes[PE->EmitionCubes.size() - 1];
			PE->EmitionCubes.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}
	}
	else if (type == 5)
	{
		Corner.y += UI_DrawText("Light sphere", Corner, 0.35f).y * -1.0f - step;


		Corner.y += UI_Drag(&PE->LightSpheres[i].r, "Radius", Corner, 0.01f).y * -1.0f - step;


		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->LightSpheres[i].position.x, "x", Corner, 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->LightSpheres[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;


		Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->LightSpheres[i].Color.x, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&PE->LightSpheres[i].Color.y, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&PE->LightSpheres[i].Color.z, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->LightSpheres[i].Color.w, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->LightSpheres[i] = PE->LightSpheres[PE->LightSpheres.size() - 1];
			PE->LightSpheres.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}
	}
	else if (type == 6)
	{
		Corner.y += UI_DrawText("Light cube", Corner, 0.35f).y * -1.0f - step;


		Corner.y += UI_DrawText("scale", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->LightCubes[i].scale.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->LightCubes[i].scale.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;

		Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->LightCubes[i].position.x, "x", Corner , 0.01f, { 80.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->LightCubes[i].position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 80.0f,15.0f }).y * -1.0f - step;


		Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&PE->LightCubes[i].Color.x, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&PE->LightCubes[i].Color.y, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&PE->LightCubes[i].Color.z, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&PE->LightCubes[i].Color.w, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
		bool b = false;
		Corner.y += UI_CheckBox(&b, "delete", Corner).y * -1.0f - step;
		if (b)
		{
			PE->LightCubes[i] = PE->LightCubes[PE->LightCubes.size() - 1];
			PE->LightCubes.pop_back();

			CurrentRedactingParticleObjectType = -1;
			CurrentRedactingParticleObject = -1;
			return;
		}
	}
	else
	{

		CurrentRedactingParticleObject = -1;
		CurrentRedactingParticleObjectType = -1;
	}
}
void ShowRedactorWindow(ParticleEmiter* ParticleEmiter)
{
	float step = 20.0f;
	float xsize = 0.0f;
	Corner.y += UI_DrawText(CurrentParticleEmiter->Name, Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_CheckBox(&CurrentParticleEmiter->ShowWindow,"ShowSettings", Corner).y * -1.0f - step;


	int tip = 0;
	if (CurrentParticleEmiter->Type == "QUAD") tip = 0;
	if (CurrentParticleEmiter->Type == "LINE") tip = 1;
	if (CurrentParticleEmiter->Type == "CIRCLE") tip = 2;
	if (CurrentParticleEmiter->Type == "TEXTURED") tip = 3;
	if (CurrentParticleEmiter->Type == "TEXTUREDLINE") tip = 4;
	Corner.y += UI_SliderInt(&tip, "Type", Corner,0,4).y * -1.0f - step;
	if (tip == 0)CurrentParticleEmiter->Type = "QUAD";
	if (tip == 1)CurrentParticleEmiter->Type = "LINE";
	if (tip == 2)CurrentParticleEmiter->Type = "CIRCLE";
	if (tip == 3)CurrentParticleEmiter->Type = "TEXTURED";
	if (tip == 4)CurrentParticleEmiter->Type = "TEXTUREDLINE";
	Corner.y += UI_DrawText(CurrentParticleEmiter->Type, Corner, 0.35f).y * -1.0f - step;

	bool r = RedactingParticlesEmiter;
	Corner.y += UI_CheckBox(&RedactingParticlesEmiter, "Redact", Corner).y * -1.0f - step;

	if (r != RedactingParticlesEmiter)
	{
		GrabSelectTool = false;
		RedactingScene = false;
		RedactingPolygon = false;
	}

	if (RedactingParticlesEmiter)
	{

		Corner.y += UI_DrawText("object Type:", Corner, 0.35f).y * -1.0f - step;
		const char* str;
		if (ParticleObject == 0)str = "InfluenceSphere";
		if (ParticleObject == 1)str = "InfluenceQuad";
		if (ParticleObject == 2)str = "EmiterPoint";
		if (ParticleObject == 3)str = "EmiterSphere";
		if (ParticleObject == 4)str = "EmiterQuad";
		if (ParticleObject == 5)str = "LightSphere";
		if (ParticleObject == 6)str = "LightQuad";
		Corner.y += UI_SliderInt(&ParticleObject,str, Corner, 0, 6).y * -1.0f - step;
		if (ParticleObject > 1 && ParticleObject < 5)
		{
			Corner.y += UI_DragInt(&amount, "Amount", Corner, 0.1f).y * -1.0f - step;
			Corner.y += UI_Drag(&tick, "tick", Corner, 0.001f).y * -1.0f - step;

			Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&vel[0], "x", Corner + glm::vec2(xsize, 0.0f), 0.01f, {40.0f,15.0f}).x * 0.5f;
			Corner.y += UI_Drag(&vel[1], "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

		}

		Corner.y += UI_CheckBox(&AddRedact, "Add / Redact", Corner).y * -1.0f - step;
		if (AddRedact)
		{
			Corner.y += UI_DrawText("Hold Shift to add 1 object/click ", Corner, 0.35f).y * -1.0f - step;

			if (ParticleObject == 0)
			{

				Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&vel[0], "x", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&vel[1], "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_Drag(&radius, "Radius", Corner, 0.1f).y * -1.0f - step;
				Corner.y += UI_Drag(&AttractionForce, "AttractionForce", Corner, 0.1f).y * -1.0f - step;

				Corner.y += UI_CheckBox(&attracticve, "attracticve", Corner).y * -1.0f - step;
				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			if (ParticleObject == 1)
			{
				Corner.y += UI_DrawText("velocity", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&vel[0], "x", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&vel[1], "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_DrawText("Size", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&size[0], "x", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&size[1], "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_Drag(&AttractionForce, "AttractionForce", Corner, 0.1f).y * -1.0f - step;

				Corner.y += UI_CheckBox(&attracticve, "attracticve", Corner).y * -1.0f - step;
				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			if (ParticleObject == 2)
			{
				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			if (ParticleObject == 3)
			{
				Corner.y += UI_Drag(&radius, "Radius", Corner, 0.1f).y * -1.0f - step;
				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			if (ParticleObject == 4)
			{
				Corner.y += UI_DrawText("Size", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&size[0], "x", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&size[1], "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			if (ParticleObject == 5)
			{
				Corner.y += UI_Drag(&radius, "Radius", Corner, 0.1f).y * -1.0f - step;

				Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&LightColor[0], "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&LightColor[1], "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&LightColor[2], "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&LightColor[3], "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			if (ParticleObject == 6)
			{
				Corner.y += UI_DrawText("Size", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&size[0], "x", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&size[1], "y", Corner + glm::vec2(xsize, 0.0f), 1.0f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
				xsize = UI_Drag(&LightColor[0], "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&LightColor[1], "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				xsize += UI_Drag(&LightColor[2], "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
				Corner.y += UI_Drag(&LightColor[3], "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

				Corner.y += UI_DrawText("if holding Shift, drag mouse to change raduis", Corner, 0.35f).y * -1.0f - step;
			}
			
		}
		else
		{
			if (ParticleObject == 0)
			{
				Corner.y += UI_DrawText("SpheresOfInfluence:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->SpheresOfInfluence.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 0;
						CurrentRedactingParticleObject = i;
					}
				}
			}
			if (ParticleObject == 1)
			{
				Corner.y += UI_DrawText("CubeOfInfluence:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->CubesOfInfluence.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 1;
						CurrentRedactingParticleObject = i;
					}
				}
			}
			if (ParticleObject == 2)
			{
				Corner.y += UI_DrawText("EmitionPoints:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->EmitionPoints.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 2;
						CurrentRedactingParticleObject = i;
					}
				}
			}
			if (ParticleObject == 3)
			{
				Corner.y += UI_DrawText("EmitionCircles:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->EmitionCircles.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 3;
						CurrentRedactingParticleObject = i;
					}
				}
			}
			if (ParticleObject == 4)
			{
				Corner.y += UI_DrawText("EmitionCubes:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->EmitionCubes.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 4;
						CurrentRedactingParticleObject = i;
					}
				}
			}
			if (ParticleObject == 5)
			{
				Corner.y += UI_DrawText("LightSpheres:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->LightSpheres.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 5;
						CurrentRedactingParticleObject = i;
					}
				}
			}
			if (ParticleObject == 6)
			{
				Corner.y += UI_DrawText("LightCubes:", Corner, 0.35f).y * -1.0f - step;
				for (int i = 0; i < CurrentParticleEmiter->LightCubes.size(); i++)
				{
					bool pressed = false;
					Corner.y += UI_buttonOnlyON(&pressed, std::to_string(i).c_str(), Corner).y * -1.0f - step;
					if (pressed)
					{
						CurrentRedactingParticleObjectType = 6;
						CurrentRedactingParticleObject = i;
					}
				}
			}
		}
		

		
	}
	else
	{

		Corner.y += UI_DragInt(&CurrentParticleEmiter->id, "id", Corner, 0.1f).y * -1.0f - step;
		Corner.y += UI_DragInt(&CurrentParticleEmiter->Z_Index, "Z_Index", Corner, 0.1f).y * -1.0f - step;
		int idbuff = CurrentParticleEmiter->Textureid;
		Corner.y += UI_SliderInt(&CurrentParticleEmiter->Textureid, "TextureId", Corner, 0, Map.Textures.size() - 1).y * -1.0f - step;

		if (selectedTexture >= 0 && selectedTexture < Map.Textures.size())
		{
			Corner.y += UI_DrawText(Map.Textures[selectedTexture].FileName.c_str(), Corner, 0.35f).y * -1.0f - step;

			if (idbuff != CurrentParticleEmiter->Textureid)
				CurrentParticleEmiter->material.Texture = Map.Textures[CurrentParticleEmiter->Textureid].texture;
		}
	}
}

void ShowRedactorWindow(polygonData* Data)
{
	float step = 20.0f;
	float xsize = 0.0f;
	Corner.y += UI_DrawText("Mesh", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&SelectedMesh->Name, Corner).y * -1.0f - step;


	Corner.y += UI_DrawText("FileName", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&SelectedMesh->FilePath, Corner).y * -1.0f - step;


	bool b = false;
	Corner.y += UI_CheckBox(&b, "Load", Corner).y * -1.0f - step;
	if (b)
	{
		SelectedMesh->Load(SelectedMesh->FilePath);
		SelectedMesh->Update();
	}
	Corner.y += UI_DrawText(std::to_string(SelectedMesh->VAO), Corner, 0.35f).y * -1.0f - step;
	b = false;
	Corner.y += UI_CheckBox(&b, "Save", Corner).y * -1.0f - step;
	if (b)
		SelectedMesh->SaveAs(SelectedMesh->FilePath);


	b = false;
	Corner.y += UI_CheckBox(&b, "Redact", Corner).y * -1.0f - step;
	if (b)
		ShowPolygonTools = !ShowPolygonTools;

	b = false;
	Corner.y += UI_CheckBox(&b, "Points", Corner).y * -1.0f - step;
	if (b)
		ShowPolygonPositions = !ShowPolygonPositions;

	b = false;
	Corner.y += UI_CheckBox(&b, "TexturePositions", Corner).y * -1.0f - step;
	if (b)
		ShowPolygonTexturePositions = !ShowPolygonTexturePositions;

	if (ShowPolygonPositions)
	{
		for (int i = 0; i < SelectedMesh->Rawpoints.size(); i++)
		{
			Corner.y += UI_DrawText(std::to_string(i), Corner, 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&SelectedMesh->Rawpoints[i].x, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&SelectedMesh->Rawpoints[i].y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;
		}
	}
	if (ShowPolygonTexturePositions)
	{
		for (int i = 0; i < SelectedMesh->TexturePoints.size(); i++)
		{
			Corner.y += UI_DrawText(std::to_string(i), Corner, 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&SelectedMesh->TexturePoints[i].x, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&SelectedMesh->TexturePoints[i].y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;
		}
	}


}
void ShowRedactorWindow(polygon* Polygon)
{
	float step = 20.0f;
	float xsize = 0.0f;
	Corner.y += UI_DrawText("Polygon", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_SliderInt(&SelectedPolygon->id, "id", Corner).y * -1.0f - step;
	Corner.y += UI_SliderInt(&SelectedPolygon->MeshID, "MeshID", Corner,0,Map.polygonMeshes.size()-1).y * -1.0f - step;
	
	if(SelectedPolygon->MeshID < Map.polygonMeshes.size())
		Corner.y += UI_DrawText(Map.polygonMeshes[SelectedPolygon->MeshID].Name.c_str(), Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedPolygon->Textureid, "Texture", Corner,-1,Map.Textures.size()-1).y * -1.0f - step;
	if (SelectedPolygon->Textureid > -1)
		Corner.y += UI_DrawText(Map.Textures[SelectedPolygon->Textureid].FileName.c_str(), Corner, 0.35f).y * -1.0f - step;
	else
		Corner.y += UI_DrawText("Clear Color", Corner, 0.35f).y * -1.0f - step;
	

	Corner.y += UI_SliderInt(&SelectedPolygon->NormalMapId, "NormalMap", Corner,-1,Map.NormalMaps.size()-1).y * -1.0f - step;
	if (SelectedPolygon->NormalMapId > -1)
		Corner.y += UI_DrawText(Map.NormalMaps[SelectedPolygon->NormalMapId].FileName.c_str(), Corner, 0.35f).y * -1.0f - step;
	else
		Corner.y += UI_DrawText("Empty", Corner, 0.35f).y * -1.0f - step;

	


	Corner.y += UI_DrawText("Scale", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&SelectedPolygon->Scale.x, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedPolygon->Scale.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&SelectedPolygon->Position.x, "x", Corner, 0.1f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedPolygon->Position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.1f, { 70.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_DragInt(&SelectedPolygon->Z_Index, "Z_Index", Corner, 0.1f).y * -1.0f - step;
	Corner.y += UI_Drag(&SelectedPolygon->Rotation, "Rotation", Corner, 0.01f).y * -1.0f - step;
	SelectedPolygon->Update_Shape();
	Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&SelectedPolygon->color.r, "r", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&SelectedPolygon->color.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&SelectedPolygon->color.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedPolygon->color.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;






	return;
}

void ShowRedactorWindow(LightSource* ls)
{

	float step = 20.0f;
	Corner.y += UI_DrawText("Light source", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_DrawText(CurrentLightSource->name.c_str(), Corner, 0.35f).y * -1.0f - step;


	Corner.y += UI_DrawText("Scale", Corner, 0.35f).y * -1.0f - step;
	float xsize = UI_Drag(&CurrentLightSource->scale.x, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&CurrentLightSource->scale.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&CurrentLightSource->position.x, "x", Corner, 0.1f, { 70.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&CurrentLightSource->position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.1f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&CurrentLightSource->position.z, "z", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&CurrentLightSource->color.r, "r", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&CurrentLightSource->color.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&CurrentLightSource->color.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&CurrentLightSource->color.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_Drag(&CurrentLightSource->volume, "Volume", Corner, 0.01f, { 70.0f,15.0f }).y * -1.0f - step;

	if (CurrentLightSource->TextureId >= 0)
		Corner.y += UI_DrawText(Map.Textures[CurrentLightSource->TextureId].FileName.c_str(), Corner, 0.35f).y * -1.0f - step;
	else
		Corner.y += UI_DrawText("Light Sphere Texture", Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_SliderInt(&CurrentLightSource->TextureId, "Texture", Corner, -1, Map.Textures.size() - 1).y * -1.0f - step;
}
void ShowRedactorWindow(ball* Ball)
{
	float step = 10.0f;
	Corner.y += UI_DrawText("Ball",Corner,0.35f).y*-1.0f-step;
	Corner.y += UI_DragInt(&SelectedBall->id,"id",Corner, 0.1f).y*-1.0f-step;
	Corner.y += UI_SliderInt(&SelectedBall->type,"type",Corner, -1,1).y*-1.0f-step;
	Corner.y += UI_DragInt(&SelectedBall->Z_Index,"Z_Index",Corner, 0.1f).y*-1.0f-step;
	Corner.y += UI_Drag(&SelectedBall->r,"Radius",Corner).y*-1.0f-step;
	Corner.y += UI_Drag(&SelectedBall->rotation,"Rotation",Corner,0.01f).y*-1.0f-step;

	Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
	float xsize = UI_Drag(&SelectedBall->position.x, "x", Corner, 0.01f, {70.0f,15.0f}).x*0.5f;
	Corner.y += UI_Drag(&SelectedBall->position.y,"y",Corner + glm::vec2(xsize,0.0f),0.01f, { 70.0f,15.0f }).y*-1.0f-step;
	

	Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&SelectedBall->color.r, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&SelectedBall->color.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&SelectedBall->color.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedBall->color.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedBall->Textureid, "Texture", Corner, -1, Map.Textures.size() - 1).y * -1.0f - step;

	if (SelectedBall->Textureid > -1 && SelectedBall->Textureid < Map.Textures.size())
		Corner.y += UI_DrawText(Map.Textures[SelectedBall->Textureid].FileName, Corner, 0.35f).y * -1.0f - step;
	else if (SelectedBall->Textureid == -1)
		Corner.y += UI_DrawText("Clear color", Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedBall->Shaderid, "Shader", Corner, -1, Map.Shaders.size() - 1).y * -1.0f - step;

	if (SelectedBall->Shaderid > -1)
		Corner.y += UI_DrawText(Map.Shaders[SelectedBall->Shaderid].Name, Corner, 0.35f).y * -1.0f - step;
	if (SelectedBall->Shaderid == -1)
		Corner.y += UI_DrawText("No shader", Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedBall->NormalMapId, "NormalMap", Corner, -1, Map.NormalMaps.size() - 1).y * -1.0f - step;


	Corner.y += UI_CheckBox(&SelectedBall->lighted, "Lighted",Corner).y * -1.0f - step;
	return;
}
void ShowRedactorWindow(cube* Cube)
{
	float step = 10.0f;
	Corner.y += UI_DrawText("Cube", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_DragInt(&SelectedCube->id, "id", Corner, 0.1f).y * -1.0f - step;
	Corner.y += UI_SliderInt(&SelectedCube->type, "type", Corner, -1, 1).y * -1.0f - step;
	Corner.y += UI_DragInt(&SelectedCube->Z_Index, "Z_Index", Corner, 0.1f).y * -1.0f - step;
	//Corner.y += UI_Drag(&SelectedCube->Width, "Scale", Corner).y * -1.0f - step;

	Corner.y += UI_DrawText("Scale", Corner, 0.35f).y * -1.0f - step;
	float xsize = UI_Drag(&SelectedCube->width, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedCube->height, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;

	//Corner.y += UI_Drag(&SelectedCube->rotation, "Rotation", Corner, 0.01f).y * -1.0f - step;

	Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&SelectedCube->position.x, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedCube->position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;


	Corner.y += UI_DrawText("Color", Corner, 0.35f).y * -1.0f - step;
	xsize = UI_Drag(&SelectedCube->color.r, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&SelectedCube->color.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	xsize += UI_Drag(&SelectedCube->color.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedCube->color.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedCube->Textureid, "Texture", Corner, -1, Map.Textures.size() - 1).y * -1.0f - step;

	if (SelectedCube->Textureid > -1 && SelectedCube->Textureid < Map.Textures.size())
		Corner.y += UI_DrawText(Map.Textures[SelectedCube->Textureid].FileName, Corner, 0.35f).y * -1.0f - step;
	else if (SelectedCube->Textureid == -1)
		Corner.y += UI_DrawText("Clear color", Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedCube->Shaderid, "Shader", Corner, -1, Map.Shaders.size() - 1).y * -1.0f - step;

	if (SelectedCube->Shaderid > -1)
		Corner.y += UI_DrawText(Map.Shaders[SelectedCube->Shaderid].Name, Corner, 0.35f).y * -1.0f - step;
	if (SelectedCube->Shaderid == -1)
		Corner.y += UI_DrawText("No shader", Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_SliderInt(&SelectedCube->NormalMapId, "NormalMap", Corner, -1, Map.NormalMaps.size() - 1).y * -1.0f - step;


	Corner.y += UI_CheckBox(&SelectedCube->lighted, "Lighted", Corner).y * -1.0f - step;
	return;

}
void ShowRedactorWindow(Node* point)
{
	float step = 10.0f;
	Corner.y += UI_DrawText("point", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_DragInt(&SelectedPoint->id, "id", Corner, 0.1f).y * -1.0f - step;

	Corner.y += UI_DrawText("Position", Corner, 0.35f).y * -1.0f - step;
	float xsize = UI_Drag(&SelectedPoint->position.x, "x", Corner, 0.01f, { 70.0f,15.0f }).x * 0.5f;
	Corner.y += UI_Drag(&SelectedPoint->position.y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 70.0f,15.0f }).y * -1.0f - step;
}

int DeletetextureCountDown = 2;
void ShowRedactorWindow(Texture* Texture)
{


	float step = 20.0f;
	Corner.y += UI_DrawText("Texture", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_DrawText(CurrentTexture->FileName.c_str(), Corner, 0.35f).y * -1.0f - step;



	Corner.y += UI_TextBox(&CurrentTexture->FileName,Corner,-1).y * -1.0f - step;



	float xsize = 0;

	std::string tmp = "Texture ID: ";
	tmp += std::to_string(CurrentTexture->texture);
	Corner.y += UI_DrawText(tmp, Corner, 0.35f).y * -1.0f - step;

	int typ = CurrentTexture->Type;

	Corner.y += UI_SliderInt(&CurrentTexture->Type, "type", Corner, 0, 7).y * -1.0f - step;

	if (CurrentTexture->Type == 0)
		Corner.y += UI_DrawText("LoadFromName",Corner,0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 1)
		Corner.y += UI_DrawText("Round Noize",Corner,0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 2)
		Corner.y += UI_DrawText("Squere Noize",Corner,0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 3)
		Corner.y += UI_DrawText("Smooth Squere Noize",Corner,0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 4)
		Corner.y += UI_DrawText("Gradient", Corner, 0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 5)
		Corner.y += UI_DrawText("Gradient Sphere", Corner, 0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 6)
		Corner.y += UI_DrawText("Sphere", Corner, 0.35f).y * -1.0f - step;
	if (CurrentTexture->Type == 7)
		Corner.y += UI_DrawText("Quad", Corner, 0.35f).y * -1.0f - step;

	std::string filter = "Linear/blurry";
	if (CurrentTexture->filter)
		filter = "Nearest/pixelart";
	bool filt = CurrentTexture->filter;
	Corner.y += UI_CheckBox(&CurrentTexture->filter,filter.c_str(), Corner,18.0f, 0.35f).y * -1.0f - step;

	if (filt != CurrentTexture->filter)
	{

		CurrentTexture->Delete();
		CurrentTexture->Load();
	}


	if (typ != CurrentTexture->Type)
	{
		CurrentTexture->Delete();
		CurrentTexture->Load();
	}


	if (CurrentTexture->Type > 0 && CurrentTexture->Type < 4)
	{
		float Tex_Freq = CurrentTexture->Noize_Frequency;
		Corner.y += UI_Drag(&CurrentTexture->Noize_Frequency,"Frequency ",Corner, 0.01f).y * -1.0f - step;
		if (Tex_Freq != CurrentTexture->Noize_Frequency)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}
		int NoizeLayers = CurrentTexture->Noize_Layers;

		Corner.y += UI_DragInt(&CurrentTexture->Noize_Layers, "Layers ", Corner, 0.01f).y * -1.0f - step;

		if (NoizeLayers != CurrentTexture->Noize_Layers)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}
		float Tex_Size = CurrentTexture->Size;
		Corner.y += UI_Drag(&CurrentTexture->Size, "Size ", Corner, 0.1f).y * -1.0f - step;
		if (Tex_Size != CurrentTexture->Size)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}
	}
	else if (CurrentTexture->Type == 4)
	{
		glm::vec4 color = CurrentTexture->Gradient_Color1;


		Corner.y += UI_DrawText("Gradient Color1", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&CurrentTexture->Gradient_Color1.r, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&CurrentTexture->Gradient_Color1.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&CurrentTexture->Gradient_Color1.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&CurrentTexture->Gradient_Color1.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

		if (color != CurrentTexture->Gradient_Color1)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}

		color = CurrentTexture->Gradient_Color2;

		Corner.y += UI_DrawText("Gradient Color2", Corner, 0.35f).y * -1.0f - step;
		xsize = UI_Drag(&CurrentTexture->Gradient_Color2.r, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&CurrentTexture->Gradient_Color2.g, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		xsize += UI_Drag(&CurrentTexture->Gradient_Color2.b, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
		Corner.y += UI_Drag(&CurrentTexture->Gradient_Color2.a, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;

		if (color != CurrentTexture->Gradient_Color2)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}

		float Tex_Size = CurrentTexture->Size;
		Corner.y += UI_Drag(&CurrentTexture->Size, "Size ", Corner, 0.1f).y * -1.0f - step;

		if (Tex_Size != CurrentTexture->Size)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}

	}
	else
	{
		
		float Tex_Size = CurrentTexture->Size;
		Corner.y += UI_Drag(&CurrentTexture->Size, "Size ", Corner, 0.1f).y * -1.0f - step;

		if (Tex_Size != CurrentTexture->Size)
		{
			CurrentTexture->Delete();
			CurrentTexture->Load();
		}

	}
	bool del = false;
	xsize = UI_buttonOnlyON(&del,"DeleteTexture", Corner).x * 0.5f;
	if(del)
		DeletetextureCountDown--;

	Corner.y += UI_DrawText(std::to_string(DeletetextureCountDown),Corner+glm::vec2(xsize,0.0f),0.35f).y*-1.0f - step;
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
		return;
	}

}
void ShowRedactorWindow(Shader* shader)
{
	float step = 20.0f;
	Corner.y += UI_DrawText("Shader", Corner, 0.35f).y * -1.0f - step;

	std::string tmp = "Program ID: ";
	tmp += std::to_string(CurrentShader->program);
	Corner.y += UI_DrawText(tmp, Corner, 0.35f).y * -1.0f - step;


	Corner.y += UI_DrawText("Name: ", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&CurrentShader->Name, Corner, -1).y * -1.0f - step;


	Corner.y += UI_DrawText("Vertex path: ", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&CurrentShader->VertexPath, Corner, -1).y * -1.0f - step;


	Corner.y += UI_DrawText("Fragment path: ", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&CurrentShader->FragmentPath, Corner, -1).y * -1.0f - step;

	bool b = false;
	Corner.y += UI_buttonOnlyON(&b,"Load", Corner).y * -1.0f - step;

	if (b)
	{
		CurrentShader->ClearUniforms();
		CurrentShader->Load();
		CurrentShader->GetUniforms();
	}
	for (int i = 0; i < CurrentShader->Uniforms.size(); i++)
	{

		float xsize = 0.0f;

		if (CurrentShader->Uniforms[i].type == 0)
			Corner.y += UI_Drag(&CurrentShader->uniformfloat[CurrentShader->Uniforms[i].type_id], CurrentShader->Uniforms[i].name.c_str(), Corner, 0.01f).y * -1.0f - step;
		if (CurrentShader->Uniforms[i].type == 1)
			Corner.y += UI_DragInt(&CurrentShader->uniformint[CurrentShader->Uniforms[i].type_id], CurrentShader->Uniforms[i].name.c_str(), Corner, 0.01f).y * -1.0f - step;
		if (CurrentShader->Uniforms[i].type == 2)
		{

			Corner.y += UI_DrawText(CurrentShader->Uniforms[i].name.c_str(), Corner, 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&CurrentShader->uniformvec2[CurrentShader->Uniforms[i].type_id].x, "x", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&CurrentShader->uniformvec2[CurrentShader->Uniforms[i].type_id].y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
		}
		if (CurrentShader->Uniforms[i].type == 3)
		{

			Corner.y += UI_DrawText(CurrentShader->Uniforms[i].name.c_str(), Corner, 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&CurrentShader->uniformvec3[CurrentShader->Uniforms[i].type_id].x, "x", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&CurrentShader->uniformvec3[CurrentShader->Uniforms[i].type_id].y, "y", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&CurrentShader->uniformvec3[CurrentShader->Uniforms[i].type_id].z, "z", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
		}
		if (CurrentShader->Uniforms[i].type == 4)
		{

			Corner.y += UI_DrawText(CurrentShader->Uniforms[i].name.c_str(), Corner, 0.35f).y * -1.0f - step;
			xsize = UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].x, "r", Corner, 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].y, "g", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			xsize += UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].z, "b", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).x * 0.5f;
			Corner.y += UI_Drag(&CurrentShader->uniformvec4[CurrentShader->Uniforms[i].type_id].w, "a", Corner + glm::vec2(xsize, 0.0f), 0.01f, { 40.0f,15.0f }).y * -1.0f - step;
		}
	}



	ImGui::End();
}

*/

int SceneWindowID;
int InspectorWindowID;
int ProjectWindowID;
int ConsoleWindowID;
int KastylID;

float SceneWindowScroll = 0.0f;
float InspectorWindowScroll = 0.0f;
float ProjectWindowScroll = 0.0f;
float ConsoleWindowScroll = 0.0f;

float SceneWindowMaxScroll = 0.0f;
float InspectorWindowMaxScroll = 0.0f;
float ProjectWindowMaxScroll = 0.0f;
float ConsoleWindowMaxScroll = 0.0f;

glm::vec4 EditorColor = { 0.025f,0.025f,0.025f,1.0f };

bool Test[10];
bool sTestb[10];
int sTesti[10];
int TestWindowID = -1;



Shader sh;






void On_Create()
{



	sh.FragmentPath = "engine/z1ShaderTests/Bald.frag";
	sh.VertexPath = "engine/z1ShaderTests/default.vert";
	sh.Load();

	//SetShader2f(&sh.program, "position",MousePosition)

	DefaultTriangle.add_Point(PrevMousePosition - glm::vec2(5, 5 * 0.5f), false);
	DefaultTriangle.add_Point(PrevMousePosition - glm::vec2(-5, 5 * 0.5f), false);
	DefaultTriangle.add_Point(PrevMousePosition + glm::vec2(0, 5), false);
	DefaultTriangle.indexes.push_back(glm::ivec3(0, 1, 2));
	DefaultTriangle.Update();
	//Map.polygonMeshes.push_back(DefaultTriangle);
	GetWindow(0)->backgroundColor = EditorColor;



	SceneWindowID = CreateWindow();
	Window* w = GetWindow(SceneWindowID);
	w->Init({ 1280,720 });
	w->Position = { 0.0f,w->ViewportSize.y * 0.2f };
	w->backgroundColor = { 0.0f,0.0f,0.0f,0.0f };

	InspectorWindowID = CreateWindow();
	Window* iw = GetWindow(InspectorWindowID);
	iw->Init({ ((WIDTH - 1280) * 0.5f),HEIGHT });
	iw->Position = { w->ViewportSize.x * 0.5f + iw->ViewportSize.x * 0.5f,0.0f };
	iw->backgroundColor = { EditorColor.r * 0.3f,EditorColor.g * 0.3f,EditorColor.b * 0.3f,1.0f };

	ProjectWindowID = CreateWindow();
	Window* pw = GetWindow(ProjectWindowID);
	pw->Init({ ((WIDTH - 1280) * 0.5f),HEIGHT });
	pw->Position = { -w->ViewportSize.x * 0.5f - pw->ViewportSize.x * 0.5f,0.0f };
	pw->backgroundColor = { EditorColor.r * 0.3f,EditorColor.g * 0.3f,EditorColor.b * 0.3f,1.0f };

	ConsoleWindowID = CreateWindow();
	Window* cw = GetWindow(ConsoleWindowID);
	cw->Init({ 1280,HEIGHT - 720 });
	cw->Position = { 0.0f,w->Position.y - w->ViewportSize.y * 0.5f };
	cw->backgroundColor = { EditorColor.r * 0.3f,EditorColor.g * 0.3f,EditorColor.b * 0.3f,1.0f };


	TestWindowID = CreateWindow();
	Window* tw = GetWindow(TestWindowID);
	tw->Init({ 300,300 });
	tw->Position = { 0.0f,w->Position.y - w->ViewportSize.y * 0.5f };
	tw->backgroundColor = { 0.0f,0.0f,0.0f,0.0f };


	
	KastylID = CreateWindow();
	Window* kw = GetWindow(KastylID);
	kw->Init({ 300,300 });
	kw->Position = MousePosition;
	kw->backgroundColor = { 0.0f,0.0f,0.0f,0.0f };
	kw->AutoDraw = false;
	kw->Autoclear = false;

	w->RecalculateSize();


	sTesti[0] = 0;

	Map.LoadFrom(MapFileName);

	


	//Map.Nodes.push_back(new Node());
	//Map.Nodes.push_back(new CollisionObject());
	//Map.Nodes.push_back(new CO_Ball());
	//Map.Nodes.push_back(new CO_Cube());
	//Map.Nodes.push_back(new LightSourceObject());
	//Map.Assets.push_back(new TextureObject());
	//Map.Assets.push_back(new MaterialObject());

}

glm::vec2 AqueredCameraScale = glm::vec2(1.0f);
glm::vec2 PrevMousePos = glm::vec2(0.0f);
bool MMBJustPressedWindow[4];

bool grebbedWindow[3];// bools for window resizing
bool grebbedAnyWindow = false;// bools for window resizing
glm::vec2 GrabStartMousePos = { 0.0f,0.0f };
bool initialsizecalc = true;
std::string sTest[10];




void On_Update()
{
	Window* w = GetWindow(SceneWindowID);
	Window* iw = GetWindow(InspectorWindowID);
	Window* pw = GetWindow(ProjectWindowID);
	Window* cw = GetWindow(ConsoleWindowID);
	Window* tw = GetWindow(TestWindowID);
	Window* kw = GetWindow(KastylID);

	/*kw->Use();
	DrawShaderedQuad({ 0.0f ,0.0f}, { 100,100 }, 0.0f, sh.program);
	kw->End();*/

	if (!grebbedAnyWindow)
		GrabStartMousePos = MousePosition;

	if (JustPressedbutton[GLFW_MOUSE_BUTTON_1])
	{
		if (MousePosition.x > WIDTH * 0.5f - iw->ViewportSize.x - 3 && MousePosition.x < WIDTH * 0.5f - iw->ViewportSize.x + 3)
		{
			grebbedWindow[1] = true;
			grebbedAnyWindow = true;
		}
		if ((MousePosition.x > pw->ViewportSize.x - 3 - WIDTH * 0.5f) && (MousePosition.x < pw->ViewportSize.x + 3 - WIDTH * 0.5f))
		{
			grebbedWindow[0] = true;
			grebbedAnyWindow = true;
		}
		if ((MousePosition.y > cw->ViewportSize.y - 3 - HEIGHT * 0.5f) && (MousePosition.y < cw->ViewportSize.y + 3 - HEIGHT * 0.5f))
		{
			grebbedWindow[2] = true;
			grebbedAnyWindow = true;
		}
		GrabStartMousePos = MousePosition;
	}

	if (grebbedWindow[0])//project window /// left
	{
		pw->Scale.x = 1.0f + (MousePosition.x - GrabStartMousePos.x) / pw->ViewportSize.x;
		if (pw->Scale.x * pw->ViewportSize.x < 25) pw->Scale.x = 25 / pw->ViewportSize.x;
		if (pw->Scale.x * pw->ViewportSize.x > WIDTH - 100 - iw->ViewportSize.x) pw->Scale.x = (WIDTH - 100 - iw->ViewportSize.x) / pw->ViewportSize.x;
	}
	if (grebbedWindow[1])//inspector window /// right
	{
		iw->Scale.x = 1.0f + (GrabStartMousePos.x - MousePosition.x) / iw->ViewportSize.x;
		if (iw->Scale.x * iw->ViewportSize.x < 25) iw->Scale.x = 25 / iw->ViewportSize.x;
		if (iw->Scale.x * iw->ViewportSize.x > WIDTH - 100 - pw->ViewportSize.x) iw->Scale.x = (WIDTH - 100 - pw->ViewportSize.x) / iw->ViewportSize.x;
	}
	if (grebbedWindow[2])//inspector window /// right
	{
		cw->Scale.y = 1.0f + (MousePosition.y - GrabStartMousePos.y) / cw->ViewportSize.y;
		if (cw->Scale.y * cw->ViewportSize.y < 25) cw->Scale.y = 25 / cw->ViewportSize.y;
		if (cw->Scale.y * cw->ViewportSize.y > HEIGHT - 100) cw->Scale.y = (HEIGHT - 100) / cw->ViewportSize.y;
	}


	float rightx = pw->ViewportSize.x * pw->Scale.x - WIDTH * 0.5f + 2.0f;
	float leftx = WIDTH * 0.5f - iw->ViewportSize.x * iw->Scale.x - 2.0f;

	float maxy = HEIGHT * 0.5f;
	float miny = cw->ViewportSize.y * cw->Scale.y - HEIGHT * 0.5f + 2.0f;
	if (grebbedAnyWindow || initialsizecalc)
	{
		cw->Scale.x = (leftx - rightx) / cw->ViewportSize.x;

		w->Scale.x = (leftx - rightx) / w->ViewportSize.x;
		w->Scale.y = (maxy - miny) / w->ViewportSize.y;
	}
	if (JustReleasedbutton[GLFW_MOUSE_BUTTON_1] && grebbedAnyWindow || initialsizecalc)
	{

		w->ViewportSize *= w->Scale;
		iw->ViewportSize *= iw->Scale;
		pw->ViewportSize *= pw->Scale;
		cw->ViewportSize *= cw->Scale;

		w->Scale = { 1.0f,1.0f };
		iw->Scale = { 1.0f,1.0f };
		pw->Scale = { 1.0f,1.0f };
		cw->Scale = { 1.0f,1.0f };


		for (int i = 0; i < 3; i++)
			grebbedWindow[i] = false;
		grebbedAnyWindow = false;




		iw->RecalculateSize();
		pw->RecalculateSize();
		cw->RecalculateSize();
		w->RecalculateSize();
		/*
		std::cout << "w" << w->ViewportSize.x << "  " << w->ViewportSize.y<<"\n";
		std::cout << "cw" << cw->ViewportSize.x << "  " << cw->ViewportSize.y<<"\n";
		std::cout << "iw" << iw->ViewportSize.x << "  " << iw->ViewportSize.y<<"\n";
		std::cout << "pw" << pw->ViewportSize.x << "  " << pw->ViewportSize.y<<"\n";*/
		initialsizecalc = false;
	}

	//CountourSize


	iw->Position = glm::vec2(WIDTH * 0.5f - iw->ViewportSize.x * iw->Scale.x * 0.5f + 2.0f, 0.0f);
	iw->Draw(1001);

	pw->Position = glm::vec2(pw->ViewportSize.x * pw->Scale.x * 0.5f - WIDTH * 0.5f - 2.0f, 0.0f);
	pw->Draw(1002);

	cw->Position = glm::vec2((rightx + leftx) * 0.5f, cw->ViewportSize.y * cw->Scale.y * 0.5f - HEIGHT * 0.5f - 2.0f);
	cw->Draw(1003);

	w->Position.x = (rightx + leftx) * 0.5f;
	w->Position.y = (maxy + miny) * 0.5f;
	w->Draw(1000);



	/*
	kw->Position = MousePosition;
	kw->Scale = {1.0f,1.0f};
	kw->Draw(10000);*/

	//tw->Position = MousePosition;
	//tw->Draw(1005);

	float step = 20.0f;

	GetWindow(ConsoleWindowID)->Use();


	ConsoleWindowScroll += scrollmovement * 50.0f;
	CameraPosition.y += (ConsoleWindowScroll - CameraPosition.y) * 0.25f;

	
	glm::vec2 dif = glm::vec2(0.0f);
	if (buttons[GLFW_MOUSE_BUTTON_MIDDLE] && !JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE] && MMBJustPressedWindow[0])
		dif = PrevMousePos - MousePosition;
	CameraPosition += dif.y;
	ConsoleWindowScroll += dif.y;
	MousePosition += dif.y;
	if(cw->active)
		if (JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE])
		{
			PrevMousePos = MousePosition;
			MMBJustPressedWindow[0]=true;
			MMBJustPressedWindow[1]=false;
			MMBJustPressedWindow[2]=false;
			MMBJustPressedWindow[3]=false;
		}

	Corner = { WIDTH * -0.5f , HEIGHT * 0.5f - CameraPosition.y };
	Corner += glm::vec2(20.0f, -25.0f);

	// if (CurrentRedactingParticleObjectType > -1 && CurrentRedactingParticleObject > -1)
	// 	ShowParticleObjectRedactorWindow(CurrentParticleEmiter, CurrentRedactingParticleObjectType, CurrentRedactingParticleObject);


	float size = 100;
	int AssetStep = 20.0f;
	int MaxAmountRow = cw->ViewportSize.x/(size + AssetStep)-1; 	
	int counterX = 0;
	float AssetstepX = 0.0f;


	AssetstepX +=UI_SliderInt(&NewAssetId,"Asset id",Corner + glm::vec2(AssetstepX,0.0f),1,3).x *0.5f + AssetStep;

	if (NewAssetId == AssetType::ASSET)AssetstepX += UI_DrawText("ASSET", Corner + glm::vec2(AssetstepX,0.0f), 0.35f).x + AssetStep;
	else if (NewAssetId == AssetType::TEXTUREOBJECT)AssetstepX += UI_DrawText("TEXTUREOBJECT", Corner + glm::vec2(AssetstepX,0.0f), 0.35f).x + AssetStep;
	else if (NewAssetId == AssetType::MATERIALOBJECT)AssetstepX+= UI_DrawText("MATERIALOBJECT", Corner + glm::vec2(AssetstepX,0.0f), 0.35f).x + AssetStep;
	else if (NewAssetId == AssetType::PARTICLEASSET)AssetstepX+= UI_DrawText("PARTICLEOBJECT", Corner + glm::vec2(AssetstepX,0.0f), 0.35f).x + AssetStep;

	bool b = false;
	Corner.y += UI_button(&b,"Create", Corner + glm::vec2(AssetstepX,0.0f)).y *-1.0f - AssetStep*2.0f;
	if(b)
	{
		Map.Assets.push_back(CreateNewAssetByClassId(NewAssetId));
	}

	AssetstepX = 0.0f;
	for(int i=0;i<Map.Assets.size();i++)
	{
		
		if(counterX>=MaxAmountRow)
		{
			AssetstepX =0.0f;
			counterX = 0;
		}
		counterX++;
		b = false;
		
		Map.Assets[i]->DrawPreview(Corner + glm::vec2(AssetstepX + size*0.5f + 10.0f,0.0f),{size*0.5f,size*0.5f});
		glm::vec2 UIObjSize = UI_button(&b, "", Corner + glm::vec2(AssetstepX,0.0f),{size+20.0f,size+20.0f},0.35f,glm::vec4(0.9f),glm::vec4(0.1f),glm::vec4(0.0f));
		UI_DrawText(Map.Assets[i]->Name.c_str(), Corner + glm::vec2(AssetstepX,UIObjSize.y*-0.5f - step*0.5f), 0.35f).x + AssetStep;
		//

		if(counterX<MaxAmountRow)
			AssetstepX += UIObjSize.x + AssetStep;
		else
			Corner.y += UIObjSize.y *-1.0f - step;
		if(b)
		{
			SelectedNode = NULL;
			SelectedNodeID = -1;
			SelectedAsset = Map.Assets[i];
			SelectedAssetID=i;
		}
		
	}
	b = false;
	


	if (HEIGHT * 0.5f < abs(Corner.y + CameraPosition.y))
	{
		if (ConsoleWindowScroll > 0.0f)
			ConsoleWindowScroll = 0.0f;
		else if (ConsoleWindowScroll < (Corner.y + CameraPosition.y))
			ConsoleWindowScroll = (Corner.y + CameraPosition.y);
	}
	else
		ConsoleWindowScroll = 0.0f;


	GetWindow(ConsoleWindowID)->End();


	GetWindow(InspectorWindowID)->Use();


	InspectorWindowScroll += scrollmovement * 50.0f;
	CameraPosition.y += (InspectorWindowScroll - CameraPosition.y) * 0.25f;

	
	dif = glm::vec2(0.0f);
	if (buttons[GLFW_MOUSE_BUTTON_MIDDLE]&& !JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE] && MMBJustPressedWindow[1])
		dif = PrevMousePos - MousePosition;
	CameraPosition += dif.y;
	InspectorWindowScroll += dif.y;
	MousePosition += dif.y;
	if(iw->active)
		if (JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE])
		{
			PrevMousePos = MousePosition;
			MMBJustPressedWindow[0]=false;
			MMBJustPressedWindow[1]=true;
			MMBJustPressedWindow[2]=false;
			MMBJustPressedWindow[3]=false;
		}
	
	Corner = { WIDTH * -0.5f, HEIGHT * 0.5f - CameraPosition.y };
	Corner += glm::vec2(20.0f, -25.0f);

	if(SelectedAsset!=NULL || SelectedNode!=NULL)
		ProcessSelectedNodeUI();

	// if (CurrentTexture != NULL)
	// 	ShowRedactorWindow(CurrentTexture);


	// if (CurrentParticleEmiter != NULL)
	// 	ShowRedactorWindow(CurrentParticleEmiter);

	// if (SelectedBall != NULL)
	// 	ShowRedactorWindow(SelectedBall);

	// if (SelectedCube != NULL)
	// 	ShowRedactorWindow(SelectedCube);


	// if (SelectedPoint != NULL)
	// 	ShowRedactorWindow(SelectedPoint);

	// if (CurrentLightSource != NULL)
	// 	ShowRedactorWindow(CurrentLightSource);

	// if (CurrentShader != NULL)
	// 	ShowRedactorWindow(CurrentShader);

	// if (SelectedPolygon != NULL)
	// 	ShowRedactorWindow(SelectedPolygon);

	// if (SelectedMesh != NULL)
	// 	ShowRedactorWindow(SelectedMesh);


	if (HEIGHT * 0.5f < abs(Corner.y + CameraPosition.y))
	{
		if (InspectorWindowScroll > 0.0f)
			InspectorWindowScroll = 0.0f;
		else if (InspectorWindowScroll < (Corner.y + CameraPosition.y))
			InspectorWindowScroll = (Corner.y + CameraPosition.y);
	}
	else
		InspectorWindowScroll = 0.0f;

	GetWindow(InspectorWindowID)->End();




	GetWindow(ProjectWindowID)->Use();




	ProjectWindowScroll += scrollmovement * 50.0f;
	CameraPosition.y += (ProjectWindowScroll - CameraPosition.y) * 0.25f;

	Corner = { WIDTH * -0.5f, HEIGHT * 0.5f - CameraPosition.y };
	Corner += glm::vec2(20.0f, -25.0f);

	
	dif = glm::vec2(0.0f);
	if (buttons[GLFW_MOUSE_BUTTON_MIDDLE]&& !JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE] && MMBJustPressedWindow[2])
		dif = PrevMousePos - MousePosition;
	CameraPosition += dif.y;
	ProjectWindowScroll += dif.y;
	MousePosition += dif.y;
	if(pw->active)
		if (JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE])
		{
			PrevMousePos = MousePosition;
			MMBJustPressedWindow[0]=false;
			MMBJustPressedWindow[1]=false;
			MMBJustPressedWindow[2]=true;
			MMBJustPressedWindow[3]=false;
		}

	//if (Test[0])
	//	DirectionalLight = 1.0f;
	//else
	//	DirectionalLight = 0.0f;



	//Corner.y += UI_Drag(&bloomLevels[0],"bloom 0", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[1],"bloom 1", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[2],"bloom 2", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[3],"bloom 3", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[4],"bloom 4", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[5],"bloom 5", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[6],"bloom 6", Corner, 0.35f).y * -1.0f - step;
	//Corner.y += UI_Drag(&bloomLevels[7],"bloom 7", Corner, 0.35f).y * -1.0f - step;


	Corner.y += UI_DrawText("Tools", Corner, 0.35f).y * -1.0f - step;

	std::string s = "CameraPosition X = ";
	s += std::to_string(w->w_CameraPosition.x);
	for (int i = 0; i < 4;i++)s.pop_back();
	s += ";  Y = ";
	s += std::to_string(w->w_CameraPosition.y);
	for (int i = 0; i < 4; i++)s.pop_back();
	Corner.y += UI_DrawText(s, Corner, 0.35f).y * -1.0f - step;

	s = "CameraScale X =";
	s += std::to_string(w->w_CameraScale.x);
	for (int i = 0; i < 4; i++)s.pop_back();
	s += ";  Y = ";
	s += std::to_string(w->w_CameraScale.y);
	for (int i = 0; i < 4; i++)s.pop_back();
	Corner.y += UI_DrawText(s, Corner, 0.35f).y * -1.0f - step;

	Corner.y += UI_DrawText(std::to_string(1.0f/delta), Corner, 0.35f).y * -1.0f - step;

	b = false;
	Corner.y += UI_button(&b, "Reset Camera", Corner).y * -1.0f - step;

	if (b)
	{
		w->w_CameraPosition = { 0.0f,0.0f };
		//w->w_CameraScale = { 1.0f,1.0f };
		AqueredCameraScale = { 1.0f,1.0f };
	}



	Corner.y += UI_DrawText("Save file:", Corner, 0.35f).y * -1.0f - step;
	Corner.y += UI_TextBox(&MapFileName, Corner,128).y * -1.0f - step;
	b = false;
	Corner.y += UI_button(&b, "Save", Corner).y * -1.0f - step;

	if (b || keys[GLFW_KEY_LEFT_CONTROL] && keys[GLFW_KEY_S])
		Map.SaveAs(MapFileName);
	
	b = false;
	Corner.y += UI_button(&b, "Load", Corner).y * -1.0f - step;
	bool cleanSelection = false;
	if (b)
	{

		Map.LoadFrom(MapFileName);
		SelectedNode = NULL;
		SelectedNodeID = -1;
		SelectedAsset =NULL;
		SelectedAssetID=-1;
		
	}

	if (RedactingParticlesEmiter)Corner.y += UI_DrawText("RedactingParticlesEmiter", Corner, 0.35f).y * -1.0f - step;
	else if (RedactingPolygon)Corner.y += UI_DrawText("RedactingPolygon", Corner, 0.35f).y * -1.0f - step;
	else if (RedactingScene)Corner.y += UI_DrawText("RedactingScene", Corner, 0.35f).y * -1.0f - step;
	else if (GrabSelectTool)Corner.y += UI_DrawText("GrabSelectTool", Corner, 0.35f).y * -1.0f - step;
	b = false;

	Corner.y += UI_CheckBox(&Map.DrawCollisions, "Draw Debug", Corner).y * -1.0f - step;
	Corner.y += UI_CheckBox(&Map.DrawRegularScene, "Draw regular ViewPort", Corner).y * -1.0f - step;

	if (b && !RedactingParticlesEmiter && !RedactingPolygon)
	{
		RedactingScene = !RedactingScene;
		GrabSelectTool = !GrabSelectTool;
		if (RedactingScene && GrabSelectTool || !RedactingScene && !GrabSelectTool)
		{
			GrabSelectTool = true;
			RedactingScene = false;
		}
	}

	//Add stuff Tool
	Corner.y += UI_SliderInt(&NewObjectId,"Spawn id",Corner,0,7).y * -1.0f - step;
	
	if (NewObjectId == NodeType::NODE)Corner.y +=  UI_DrawText("NODE", Corner, 0.35f).y * -1.0f- step;
	else if (NewObjectId == NodeType::OBJECT)Corner.y += UI_DrawText("OBJECT", Corner, 0.35f).y * -1.0f- step;
	else if (NewObjectId == NodeType::COLLISIONOBJECT)Corner.y +=  UI_DrawText("COLLISIONOBJECT", Corner, 0.35f).y* -1.0f - step;
	else if (NewObjectId == NodeType::LIGHTSOURCEOBJECT)Corner.y +=  UI_DrawText("LIGHTSOURCEOBJECT", Corner, 0.35f).y * -1.0f- step;
	else if (NewObjectId == NodeType::CO_BALL)Corner.y +=  UI_DrawText("CO_BALL", Corner, 0.35f).y * -1.0f- step;
	else if (NewObjectId == NodeType::CO_CUBE)Corner.y +=  UI_DrawText("CO_CUBE", Corner, 0.35f).y * -1.0f- step;
	else if (NewObjectId == NodeType::CO_POLYGON)Corner.y +=  UI_DrawText("CO_POLYGON", Corner, 0.35f).y * -1.0f - step;
	else if (NewObjectId == NodeType::PARTICLEOBJECT)Corner.y +=  UI_DrawText("PARTICLEOBJECT", Corner, 0.35f).y * -1.0f - step;
	b = false;
	Corner.y += UI_button(&b, "Spawn", Corner).y * -1.0f - step;
	if(b)
	{
		Node* NewSpawnedNode = CreateNewNodeByClassId(NewObjectId);
		NewSpawnedNode->position = w->w_CameraPosition;
		Map.Nodes.push_back(NewSpawnedNode);
	}

	

	


	Corner.y += UI_Slider(&w->w_AmbientLight, "Ambient light", Corner).y * -1.0f - step;
	Corner.y += UI_Slider(&w->w_DirectionalLight, "Directional light", Corner).y * -1.0f - step;

	//Nodes of Scene

	for(int i=0;i<Map.Nodes.size();i++)
	{
		b = false;
		Corner.y += UI_button(&b, Map.Nodes[i]->Name.c_str(), Corner).y * -1.0f - step;
		if(b)
		{
			SelectedNode = Map.Nodes[i];
			SelectedNodeID = i;
			SelectedAsset =NULL;
			SelectedAssetID=-1;
		}
	}


	b = false;

	

	if (HEIGHT * 0.5f < abs(Corner.y + CameraPosition.y))
	{
		if (ProjectWindowScroll > 0.0f)
			ProjectWindowScroll = 0.0f;
		else if (ProjectWindowScroll < (Corner.y + CameraPosition.y))
			ProjectWindowScroll = (Corner.y + CameraPosition.y);
	}
	else
		ProjectWindowScroll = 0.0f;

	GetWindow(ProjectWindowID)->End();


	GetWindow(SceneWindowID)->Use();

	//DrawCube(MousePosition, { 100.0f,100.0f }, 0.0f, {1.0f,1.0f,1.0f,1.0f}, true, NegativeNormalMapTexture);

	AqueredCameraScale *= 1.0f + scrollmovement * 0.1f;
	CameraScale += (AqueredCameraScale - CameraScale) * 0.25f * 0.017f * 60.0f;
	

	dif = glm::vec2(0.0f);
	if (buttons[GLFW_MOUSE_BUTTON_MIDDLE]&& !JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE] && MMBJustPressedWindow[3])
		dif = PrevMousePos - MousePosition;
	CameraPosition += dif;
	MousePosition += dif;
	
	if(w->active)
		if (JustPressedbutton[GLFW_MOUSE_BUTTON_MIDDLE])
		{
			PrevMousePos = MousePosition;
			MMBJustPressedWindow[0]=false;
			MMBJustPressedWindow[1]=false;
			MMBJustPressedWindow[2]=false;
			MMBJustPressedWindow[3]=true;
		}

	if (Holdingkey[GLFW_KEY_W]) CameraPosition.y += delta / CameraScale.y * 600.0f;
	if (Holdingkey[GLFW_KEY_S]) CameraPosition.y -= delta / CameraScale.y * 600.0f;
	if (Holdingkey[GLFW_KEY_A]) CameraPosition.x -= delta / CameraScale.x * 600.0f;
	if (Holdingkey[GLFW_KEY_D]) CameraPosition.x += delta / CameraScale.x * 600.0f;

	/*
	//Add stuff again
	if (!RedactingParticlesEmiter && RedactingScene && !GrabSelectTool && !RedactingPolygon)
	{
		if (JustPressedLMB && keys[GLFW_KEY_LEFT_SHIFT])
		{
			std::cout << "\n" << Map.points.size() << "\n";
			if (RedactorObject == 0)
			{
				ball b;
				b.position = LastJustPressedLMBMousePos;
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
				c.position = LastJustPressedLMBMousePos;
				c.lighted = Lighted;
				Map.cubes.push_back(c);
				CurrentRedactorObject = Map.cubes.size() - 1;
			}
			if (RedactorObject == 2)
			{
				polygon p;
				p.Data = &DefaultTriangle;
				p.lighted = Lighted;
				p.Position = LastJustPressedLMBMousePos;
				Map.polygons.push_back(p);
				CurrentRedactorObject = Map.polygons.size() - 1;
			}
			if (RedactorObject == 3)
			{
				Node p;
				p.id = Id;
				p.position = LastJustPressedLMBMousePos;
				Map.points.push_back(p);
				CurrentRedactorObject = Map.points.size() - 1;
			}
		}
		else if (buttons[GLFW_MOUSE_BUTTON_1] && keys[GLFW_KEY_LEFT_SHIFT] && LastJustPressedLMBMousePos != MousePosition)
		{
			if (RedactorObject == 0)
			{
				float rar = length(MousePosition - LastJustPressedLMBMousePos);
				Map.balls[CurrentRedactorObject].r = rar;
			}
			if (RedactorObject == 1)
			{
				if ((MousePosition - LastJustPressedLMBMousePos).x != 0.0f && (MousePosition - LastJustPressedLMBMousePos).y != 0.0f)
				{
					Map.cubes[CurrentRedactorObject].width = abs((MousePosition.x - LastJustPressedLMBMousePos.x)) * 0.5f;
					Map.cubes[CurrentRedactorObject].height = abs((MousePosition.y - LastJustPressedLMBMousePos.y)) * 0.5f;
				}
				Map.cubes[CurrentRedactorObject].position = (MousePosition + LastJustPressedLMBMousePos) * 0.5f;
			}
			if (RedactorObject == 2)
			{
				float rar = length(MousePosition - LastJustPressedLMBMousePos);
				Map.polygons[CurrentRedactorObject].Scale = glm::vec2(abs((MousePosition.x - LastJustPressedLMBMousePos.x)) * 0.5f, abs((MousePosition.y - LastJustPressedLMBMousePos.y)) * 0.5f);
				Map.polygons[CurrentRedactorObject].Update_Shape();
			}
		}

	}
	*/
	

	// grab/select tool
	if (!RedactingParticlesEmiter && !RedactingScene && GrabSelectTool && !RedactingPolygon)
	{
		if (JustPressedLMB)
		{
			PrevMousePosition = MousePosition;
			grabbed = false;
			
			SelectedNode = NULL;
			SelectedNodeID = -1;
			SelectedAsset =NULL;
			SelectedAssetID=-1;
			for (int i = 0; i < Map.Nodes.size(); i++)
			{
				bool mousetouched = Map.Nodes[i]->SelectionCheck(MousePosition);
				

				if (mousetouched)
				{
					if(GrabbedNode == NULL || GrabbedNode->Z_Index < Map.Nodes[i]->Z_Index)
					{
						GrabbedNode = Map.Nodes[i]; 
						GrabbedNodeID = i;
					}
					grabbed = true;
				}
			}

		}
		if (ReleasedLMB && sqrlength(PrevMousePosition - MousePosition)<2.0f)
		{
			SelectedNode = GrabbedNode;
			SelectedNodeID = GrabbedNodeID; 
			GrabbedNode= NULL;
			GrabbedNodeID = -1;
			grabbed = false;
			

		}
		else if (buttons[GLFW_MOUSE_BUTTON_1] && PrevMousePosition != MousePosition && keys[GLFW_KEY_LEFT_CONTROL])
		{
			if (GrabbedNode != NULL && grabbed )
				GrabbedNode->position = MousePosition;
		}

		if(ReleasedLMB)
		{
			GrabbedNode= NULL;
			GrabbedNodeID = -1;
			grabbed = false;
		}
	}
	else
	{
		GrabbedNode= NULL;
		GrabbedNodeID = -1;
		grabbed = false;		
	}
	/*
	if (RedactingParticlesEmiter  && CurrentParticleEmiter!=NULL )
	{
		for (int i = 0; i < CurrentParticleEmiter->SpheresOfInfluence.size(); i++)
			DrawCircle(CurrentParticleEmiter->SpheresOfInfluence[i].position, CurrentParticleEmiter->SpheresOfInfluence[i].r, glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionCircles.size(); i++)
			DrawCircle(CurrentParticleEmiter->EmitionCircles[i].position, CurrentParticleEmiter->EmitionCircles[i].r, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->LightSpheres.size(); i++)
			DrawCircle(CurrentParticleEmiter->LightSpheres[i].position, CurrentParticleEmiter->LightSpheres[i].r, glm::vec4(1.0f, 1.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->CubesOfInfluence.size(); i++)
			DrawCube(CurrentParticleEmiter->CubesOfInfluence[i].position, CurrentParticleEmiter->CubesOfInfluence[i].scale, 0.0f, glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionCubes.size(); i++)
			DrawCube(CurrentParticleEmiter->EmitionCubes[i].position, CurrentParticleEmiter->EmitionCubes[i].scale, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->LightCubes.size(); i++)
			DrawCube(CurrentParticleEmiter->LightCubes[i].position, CurrentParticleEmiter->LightCubes[i].scale, 0.0f, glm::vec4(1.0f, 1.0f, 0.0f, 0.2f));

		for (int i = 0; i < CurrentParticleEmiter->EmitionPoints.size(); i++)
			DrawCircle(CurrentParticleEmiter->EmitionPoints[i].position, 10, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		if (AddRedact  && ParticleObject != -1)
		{
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
			if (keys[GLFW_KEY_LEFT_SHIFT] && buttons[GLFW_MOUSE_BUTTON_1] && PrevMousePosition != MousePosition && CurrentParticleObject != -1)
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
	}
	*/
	Map.Draw();

	// for (int i = 0; i < Map.Shaders.size(); i++)
	// 	Map.Shaders[i].UpdateUniforms();


	GetWindow(SceneWindowID)->End();

	if(cleanSelection)
	{
		SelectedNode = NULL;
		SelectedNodeID = -1;
		SelectedAsset =NULL;
		SelectedAssetID=-1;
	}
	//for (int i = 0; i < Windows.size(); i++)
	//	std::cout<<"\ni "<<i<<" ls = "<<Windows[i].w_LightSources.size();
}

int main()
{
	//initEngine();
	initEngine("Redactor", 1920,1050,false);
	//app.init("Redactor",1920,1080,true);
	Map.SaveAs(MapFileName + ".back");
	return 0;
}
