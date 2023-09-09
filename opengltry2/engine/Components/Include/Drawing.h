#pragma once

#include "Shader.h"
#include "Objects.h"

//Texture Generation
#include <map>




extern

GLuint 
NoizeGenShader,
GradientGenShader,
AddTexturesShader,
RoundShader,
GenNormalMapShader,
GenLightSphereShader,
 GenPrimitiveTextureShader,


FlatColorTexture,
FlatColorCircleTexture,
//Drawing
//Quad
FillShader,
TexturedQuadShader,


//Circle
CircleShader,

//Lighting
InstancedNormalMapShader,
NormalMapDrawShader,
LightShader,

//Triangle
FillTriangleShader,
TexturedTriangleShader,


//Post processing
BlurShader,
UpsampleBlur,
DownsampleBlur,

Chromatic,
shaderBloom,
ScrShade,

//Textures
BallNormalMapTexture,
CubeNormalMapTexture,
LightSphereTexture,


//Buffers
FrameBuffer, ColorBuffer,
NormalMapFBO, NormalMapColorBuffer,
LightColorFBO, LightColorBuffer,


//VertexObjects
quadVAO, quadVBO,
ScreenVAO, ScreenVBO,
CircleVAO, CircleVBO,
TriangleVAO, TriangleVBO,
TexturedTriangleVAO, TexturedTriangleVBO,

TextVAO, TextVBO,
TextShader;

	


enum TextureShape
{
	SQUERE = 0,
	SMOOTH_EDGE = 1,
	ROUND = 2
};



struct TexturedQuadArray
{
	GLuint Texture;
	GLuint Texture2;
	std::vector <glm::vec4> QuadPosScale;
	std::vector <float> QuadRotations;
	std::vector <glm::vec4> Quadcolors;
};

struct SceneLayer
{
	int Z_Index = 0;

	bool Additive = false;

	std::vector <glm::vec4> CirclePosScale;
	std::vector <float> CircleRotations;
	std::vector <glm::vec4> Circlecolors;

	std::vector <glm::vec4> QuadPosScale;
	std::vector <float> QuadRotations;
	std::vector <glm::vec4> Quadcolors;

	std::vector <TexturedQuadArray> TexturedQuads;

	std::vector <TexturedQuadArray> NormalMaps;

	std::vector <glm::vec4> NormalMapCirclePosScale;
	std::vector <float> NormalMapCircleRotations;

	std::vector <glm::vec4> NormalMapCubePosScale;
	std::vector <float> NormalMapCubeRotations;


};
struct LightSource
{
	float volume = 0.0f;
	glm::vec3 position = glm::vec3(0.0f, 0.0, -0.5f);
	glm::vec2 scale = glm::vec2(0.0f);
	float rotation = 0.0f;
	glm::vec4 color = glm::vec4(0.0f);
	unsigned int texture = LightSphereTexture;
	int TextureId = 0;
	std::string name = "LightSource";
};
class Texture
{
public:
	int id = 0;//meaningless number
	std::string FileName;
	int Type = 0;// 0-Texture, 1-ROUNDNOIZE, 2-SQUERENOIZE, 3-SMOOTH_EDGENOIZE;
	unsigned int texture;

	float Noize_Frequency = 10;
	int Noize_Layers = 3;

	float Size = 100.0f;

	glm::vec4 Gradient_Color1 = glm::vec4(1.0f);
	glm::vec4 Gradient_Color2 = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

	void Load();
	void Delete();
};
struct TextLine
{
	std::string text;
	GLfloat x;
	GLfloat y;
	GLfloat scale;
	glm::vec4 color = glm::vec4(1.0f);
	bool aboveEverything = false;
};


struct Character {
	GLuint     TextureID; // ID �������� �����
	glm::ivec2 Size;      // ������� �����
	glm::ivec2 Bearing;   // �������� ������� ����� ����� �����
	GLuint     Advance;   // �������������� �������� �� ������ ���������� �����
};

extern std::vector <TextLine> TextLines;
extern std::map<GLchar, Character> Characters;

extern std::vector <LightSource> LightSources;
extern std::vector <SceneLayer> SceneLayers;

void PreLoadShaders();
void SortSceneLayers();
int FindSceneLayer(int Z_Index, bool Additive);
void DrawLight(glm::vec2 position, glm::vec2 scale, glm::vec4 color, float volume = 0.0f, float rotation = 0.0f, unsigned int texture = LightSphereTexture);
void DrawLight(glm::vec3 position, glm::vec2 scale, glm::vec4 color, float volume = 0.0f, float rotation = 0.0f, unsigned int texture = LightSphereTexture);
void NormalMapDraw(glm::vec2 position, glm::vec2 scale, unsigned int NormalMap = BallNormalMapTexture, float rotation = 0.0f, int Z_Index = 0, unsigned int Texture = NULL, bool Additive = false);
void NormalMapDrawTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int NormalMap,
	glm::vec2 texcoord1 = glm::vec2(0.0f, 1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
);
void DrawCircle(glm::vec2 position, float r, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = BallNormalMapTexture, int Z_Index = 0, bool Additive = false);
void DrawCircle(ball b, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = BallNormalMapTexture, int Z_Index = 0, bool Additive = false);
void DrawCube(glm::vec2 position, glm::vec2 scale, float rotation = 0.0f, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = CubeNormalMapTexture, int Z_Index = 0, bool Additive = false);
void DrawCube(cube c, glm::vec4 color = glm::vec4(1.0f), float rotation = 0.0f, bool Lighted = false, unsigned int NormalMap = NULL, int Z_Index = 0, bool Additive = false);
void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = CubeNormalMapTexture, int Z_Index = 0);
void DrawBall(ball b, glm::vec4 Color1 = glm::vec4(1.0f), glm::vec4 Color2 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), bool Lighted = false, unsigned int NormalMap = NULL, int Z_Index = 0);
void LoadTexture(const char* filename, unsigned int* texture, int chanelsAmount = 4);
void LoadTextureFromData(unsigned int* texture, int width, int height, unsigned char* Data, int chanelsAmount = 4);
void fLoadTextureFromData(unsigned int* texture, int width, int height, float* Data, int chanelsAmount = 4);
void GenNoizeTexture(unsigned int* texture1, int Size, int Layers = 3, float freq = 10, int shape = ROUND);
void GenPrimitiveTexture(unsigned int* texture1, int Size, int shape = ROUND);
void GenNormalMapTexture(unsigned int* texture1, int Size, int shape = ROUND);
void GenLightSphereTexture(unsigned int* texture1, int Size);
void GenGradientTexture(unsigned int* texture1, glm::vec4 Color1 = glm::vec4(1.0f), glm::vec4 Color2 = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), int Size = 100);
void DrawShaderedQuad(glm::vec2 position, glm::vec2 scale, float rotation, unsigned int shaderProgram);
void DrawTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, float rotation = 0.0f, glm::vec4 color = glm::vec4(1.0f), int Z_Index = 0, unsigned int NormalMap = NULL, bool Additive = false);
void DrawTexturedQuad(cube c, unsigned int texture, glm::vec4 color = glm::vec4(1.0f), float rotation = 0.0f, int Z_Index = 0, unsigned int NormalMap = NULL, bool Additive = false);

void DrawTexturedLine(unsigned int Texture, glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f), unsigned int NormalMap = CubeNormalMapTexture, int Z_Index = 0);
void DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec4 color = glm::vec4(1.0f));
void DrawTexturedTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int texture,
	glm::vec4 color = glm::vec4(1.0f),
	glm::vec2 texcoord1 = glm::vec2(0.0f, 1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
);
