#pragma once

glm::vec2 CameraPosition = glm::vec2(0.0f);
glm::vec2 CameraScale = glm::vec2(1.0f);

//Texture Generation

GLuint NoizeGenShader;
GLuint GradientGenShader;
GLuint AddTexturesShader;
GLuint RoundShader;
GLuint GenNormalMapShader;
GLuint GenLightSphereShader;

//Drawing
//Quad
	GLuint FillShader;
	GLuint TexturedQuadShader;


//Circle
	GLuint CircleShader;

//Lighting
	GLuint InstancedNormalMapShader;
	GLuint NormalMapDrawShader;
	GLuint LightShader;

//Triangle
	GLuint FillTriangleShader;
	GLuint TexturedTriangleShader;


//Post processing
	GLuint BlurShader;
	GLuint UpsampleBlur;
	GLuint DownsampleBlur;

	GLuint Chromatic;
	GLuint shaderBloom;
	GLuint ScrShade;

//Textures
	GLuint BallNormalMapTexture;
	GLuint CubeNormalMapTexture;
	GLuint LightSphereTexture;

//Text
	GLuint TextVAO, TextVBO;
	GLuint TextShader;

//Buffers
	GLuint FrameBuffer, ColorBuffer;
	GLuint NormalMapFBO, NormalMapColorBuffer;
	GLuint LightColorFBO, LightColorBuffer;


//VertexObjects
	GLuint quadVAO, quadVBO,
	ScreenVAO, ScreenVBO,
	CircleVAO, CircleVBO,
	TriangleVAO, TriangleVBO,
	TexturedTriangleVAO, TexturedTriangleVBO
	;


	

void PreLoadShaders()
{

	//Texture Generation
	LoadShader(&GradientGenShader, "engine/Shaders/Quad/TexturedQuad.vert", "engine/Shaders/Quad/TexturedQuad.frag");
	LoadShader(&NoizeGenShader, "engine/Shaders/NoizeGen/NoizeGen.vert", "engine/Shaders/NoizeGen/NoizeGen.frag");
	LoadShader(&RoundShader, "engine/Shaders/Round/Round.vert", "engine/Shaders/Round/Round.frag");
	LoadShader(&AddTexturesShader, "engine/Shaders/Default.vert", "engine/Shaders/Textures/AddTextures.frag");
	LoadShader(&GenNormalMapShader, "engine/Shaders/Default.vert", "engine/Shaders/NormalMap/GenNormalMap.frag");
	LoadShader(&GenLightSphereShader, "engine/Shaders/Default.vert", "engine/Shaders/Light/GenLightSphere.frag");

	//Post processing
	LoadShader(&BlurShader, "engine/Shaders/blur/blur.vert", "engine/Shaders/blur/blur.frag");
	LoadShader(&shaderBloom, "engine/Shaders/Default.vert", "engine/Shaders/Bloom/bloom.frag");
	LoadShader(&ScrShade, "engine/Shaders/Default.vert", "engine/Shaders/Screen.frag");
	LoadShader(&Chromatic, "engine/Shaders/Default.vert", "engine/Shaders/Chromatic/Chromatic.frag");
	LoadShader(&DownsampleBlur, "engine/Shaders/Default.vert", "engine/Shaders/blur/DownscaleBlur.frag");
	LoadShader(&UpsampleBlur, "engine/Shaders/Default.vert", "engine/Shaders/blur/UpsampleBlur.frag");

	//Drawing
	//Quad
	LoadShader(&FillShader, "engine/Shaders/Quad/default.vert", "engine/Shaders/Quad/Quad.frag");
	LoadShader(&TexturedQuadShader, "engine/Shaders/Quad/TexturedQuad.vert", "engine/Shaders/Quad/TexturedQuad.frag");
	
	//Circle	
	LoadShader(&CircleShader, "engine/Shaders/Circle/Circle.vert", "engine/Shaders/Circle/Circle.frag");

	//Lighting
	LoadShader(&InstancedNormalMapShader, "engine/Shaders/InstancedNormalMap/InstancedNMDraw.vert", "engine/Shaders/InstancedNormalMap/NormalMapDraw.frag");
	LoadShader(&NormalMapDrawShader, "engine/Shaders/NormalMap/NormalMapDraw.vert", "engine/Shaders/NormalMap/NormalMapDraw.frag");

	LoadShader(&LightShader, "engine/Shaders/Light/Light.vert", "engine/Shaders/Light/LightProcess.frag");

	//Triangle	
	LoadShader(&FillTriangleShader, "engine/Shaders/Triangle/Fill.vert", "engine/Shaders/Triangle/Fill.frag");
	LoadShader(&TexturedTriangleShader, "engine/Shaders/Triangle/TexturedTriangle.vert", "engine/Shaders/Triangle/TexturedTriangle.frag");

	//Text
	LoadShader(&TextShader, "engine/Shaders/Quad/TexturedQuad.vert", "engine/Shaders/Text.frag");















	





	

	

	



}

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

std::vector <SceneLayer> SceneLayers;
void SortSceneLayers()
{
	if (SceneLayers.size() > 2)
	{
		int i = 1;
		int a = 2;

		while (i < SceneLayers.size())
		{
			if (SceneLayers[i - 1].Z_Index < SceneLayers[i].Z_Index)
			{
				i = a;
				a++;
			}
			else
			{
				SceneLayer tmp = SceneLayers[i - 1];
				SceneLayers[i - 1] = SceneLayers[i];
				SceneLayers[i] = tmp;
				i--;
				if (i == 0)
				{
					i = a;
					a++;
				}
			}
		}
	}
	else if (SceneLayers.size() == 2)
	{
		if (SceneLayers[0].Z_Index > SceneLayers[1].Z_Index)
		{
			SceneLayer tmp = SceneLayers[0];
			SceneLayers[0] = SceneLayers[1];
			SceneLayers[1] = tmp;
		}
	}
}


float ScaleMultiplyer = 0.043545f*0.05f;

float ScreenAspectRatio = 1.0f;

float ScreenDivisorX = 1.0;
float ScreenDivisorY = 1.0;



struct LightSource
{
	float volume = 0.0f;
	glm::vec3 position = glm::vec3(0.0f,0.0,-0.5f);
	glm::vec2 scale = glm::vec2(0.0f);
	float rotation = 0.0f;
	glm::vec4 color = glm::vec4(0.0f);
	unsigned int texture = LightSphereTexture;
	int TextureId = 0;
	std::string name = "LightSource";
};
std::vector <LightSource> LightSources;
void DrawLight(glm::vec2 position, glm::vec2 scale, glm::vec4 color, float volume = 0.0f, float rotation = 0.0f, unsigned int texture = LightSphereTexture)
{
	LightSource ls;
	ls.volume =volume;
	ls.position = glm::vec3(position,-0.5f);
	ls.scale = scale;
	ls.rotation = rotation;
	ls.color = color;
	ls.texture = texture;
	LightSources.push_back(ls);
}
void DrawLight(glm::vec3 position, glm::vec2 scale, glm::vec4 color, float volume = 0.0f, float rotation = 0.0f, unsigned int texture = LightSphereTexture)
{
	LightSource ls;
	ls.volume = volume;
	ls.position = position;
	ls.scale = scale;
	ls.rotation = rotation;
	ls.color = color;
	ls.texture = texture;
	LightSources.push_back(ls);
}
void NormalMapDraw(glm::vec2 position,glm::vec2 scale,unsigned int NormalMap= BallNormalMapTexture, float rotation = 0.0f, int Z_Index = 0, unsigned int Texture = NULL)
{
	if (NormalMap != BallNormalMapTexture && NormalMap != CubeNormalMapTexture) 
	{

		int SLI = -1;

		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
		if (SLI == -1)
		{
			SceneLayer sl;
			sl.Z_Index = Z_Index;
			SceneLayers.push_back(sl);
			SortSceneLayers();
			for (int i = 0; i < SceneLayers.size(); i++)
				if (SceneLayers[i].Z_Index == Z_Index)
					SLI = i;
		}

		float aspx = ScreenDivisorX * CameraScale.x;
		float aspy = ScreenDivisorY * CameraScale.y;

		position -= CameraPosition;
		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);

		
		int TQA = -1;

		for (int i = 0; i < SceneLayers[SLI].NormalMaps.size(); i++)
			if (SceneLayers[SLI].NormalMaps[i].Texture == NormalMap && SceneLayers[SLI].NormalMaps[i].Texture2 == Texture)
				TQA = i;

		if (TQA == -1)
		{
			TexturedQuadArray NewTQA;
			NewTQA.Texture = NormalMap;
			NewTQA.Texture2 = Texture;
			SceneLayers[SLI].NormalMaps.push_back(NewTQA);
			for (int i = 0; i < SceneLayers[SLI].NormalMaps.size(); i++)
				if (SceneLayers[SLI].NormalMaps[i].Texture == NormalMap && SceneLayers[SLI].NormalMaps[i].Texture2 == Texture)
					TQA = i;
		}

		SceneLayers[SLI].NormalMaps[TQA].QuadPosScale.push_back(glm::vec4(position, scale));
		SceneLayers[SLI].NormalMaps[TQA].QuadRotations.push_back(rotation);


	}
	else 
	{
		float aspx = ScreenDivisorX * CameraScale.x;
		float aspy = ScreenDivisorY * CameraScale.y;

		position -= CameraPosition;
		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);


		int SLI = -1;

		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
		if (SLI == -1)
		{
			SceneLayer sl;
			sl.Z_Index = Z_Index;
			SceneLayers.push_back(sl);
			SortSceneLayers();
			for (int i = 0; i < SceneLayers.size(); i++)
				if (SceneLayers[i].Z_Index == Z_Index)
					SLI = i;
		}

		if (NormalMap == BallNormalMapTexture)
		{
			SceneLayers[SLI].NormalMapCircleRotations.push_back(rotation);
			SceneLayers[SLI].NormalMapCirclePosScale.push_back(glm::vec4(position,scale));
		}
		else
		{
			SceneLayers[SLI].NormalMapCubeRotations.push_back(rotation);
			SceneLayers[SLI].NormalMapCubePosScale.push_back(glm::vec4(position, scale));
		}
	}
}

void NormalMapDrawTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int NormalMap,
	glm::vec2 texcoord1 = glm::vec2(0.0f, 1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
)
{

	glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);
	UseShader(TexturedTriangleShader);
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][4] =
	{
		{ p1.x, p1.y,texcoord1.x,texcoord1.y},
		{ p2.x, p2.y,texcoord2.x,texcoord2.y},
		{ p3.x, p3.y,texcoord3.x,texcoord3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NormalMap);
	glUniform1i(glGetUniformLocation(TexturedTriangleShader, "Texture"), 0);

	glUniform4f(glGetUniformLocation(TexturedTriangleShader, "color"), 1.0f,1.0f,1.0f,1.0f);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);


	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void DrawCircle(glm::vec2 position, float r, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = BallNormalMapTexture, int Z_Index = 0)
{
	glm::vec2 scale = glm::vec2(r, r);

	if (Lighted)
		NormalMapDraw(position, scale, NormalMap, 0.0f, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);


	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}

	SceneLayers[SLI].CirclePosScale.push_back(glm::vec4(position,scale));
	SceneLayers[SLI].CircleRotations.push_back(0.0f);
	SceneLayers[SLI].Circlecolors.push_back(color);

}
void DrawCircle(ball b, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = BallNormalMapTexture, int Z_Index = 0)
{

	glm::vec2 position = b.position;
	float r = b.r;
	glm::vec2 scale = glm::vec2(r, r);
	if (Lighted)
		NormalMapDraw(position, scale, NormalMap, 0.0f, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);
	
	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}


	SceneLayers[SLI].CirclePosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].CircleRotations.push_back(0.0f);
	SceneLayers[SLI].Circlecolors.push_back(color);
}

void DrawCube(glm::vec2 position, glm::vec2 scale, float rotation = 0.0f, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = CubeNormalMapTexture, int Z_Index = 0)
{


	if (Lighted)
		NormalMapDraw(position,scale, NormalMap, rotation, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);

	


	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}

	SceneLayers[SLI].QuadPosScale.push_back(glm::vec4(position,scale));
	SceneLayers[SLI].QuadRotations.push_back(rotation);

	SceneLayers[SLI].Quadcolors.push_back(color);


}
void DrawCube(cube c, glm::vec4 color = glm::vec4(1.0f), float rotation = 0.0f, bool Lighted = false, unsigned int NormalMap = NULL, int Z_Index = 0)
{


	if (Lighted)
		NormalMapDraw(c.position, glm::vec2(c.width, c.height), NormalMap, rotation, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	glm::vec2 position = c.position - CameraPosition;
	position *= glm::vec2(aspx, aspy);
	glm::vec2 scale = glm::vec2(c.width, c.height) *  glm::vec2(aspx, aspy);

	
	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}

	SceneLayers[SLI].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].QuadRotations.push_back(rotation);

	SceneLayers[SLI].Quadcolors.push_back(color);
}


void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f), bool Lighted = false, unsigned int NormalMap = CubeNormalMapTexture, int Z_Index = 0)
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y)*0.5f;
	DrawCube(midpos, glm::vec2(width  , length), rotation, color, Lighted, NormalMap, Z_Index);
}

void DrawBall(ball b, glm::vec4 Color1 = glm::vec4(1.0f), glm::vec4 Color2 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),bool Lighted = false, unsigned int NormalMap=NULL, int Z_Index = 0)
{

	glm::vec2 univec;
	univec.x = cos(b.rotation * 5) - sin(b.rotation * 5);
	univec.y = sin(b.rotation * 5) + cos(b.rotation * 5);
	DrawLine(b.position - univec * b.r * 0.7f, b.position + univec * b.r * 0.7f, 3.0f, Color2, Lighted,CubeNormalMapTexture, Z_Index);
	DrawLine(b.position + glm::vec2(-univec.y * b.r * 0.7f, univec.x * b.r * 0.7f), b.position + glm::vec2(univec.y * b.r * 0.7f, -univec.x * b.r * 0.7f), 3.0f, Color2, Lighted, CubeNormalMapTexture, Z_Index);
	DrawCircle(b, Color1, Lighted, NormalMap, Z_Index-1);
}



// will load texture from filename, to texture 
void LoadTexture(const char* filename,unsigned int* texture,int chanelsAmount = 4)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int ImageW, ImageH, nrChannels;
	unsigned char* Texture = stbi_load(filename, &ImageW, &ImageH, &nrChannels, chanelsAmount);

	if (Texture)
	{
		if (chanelsAmount == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R, ImageW, ImageH, 0, GL_R, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 2)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, ImageW, ImageH, 0, GL_RG, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageW, ImageH, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImageW, ImageH, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture);


		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(Texture);
	glBindTexture(GL_TEXTURE_2D, 0);

}


enum
{
	SQUERE = 0,
	SMOOTH_EDGE = 1,
	ROUND = 2
};


void GenNoizeTexture(unsigned int* texture1,int Size, int Layers =3,float freq = 10, int shape = ROUND)
{
	//std::cout << "ImputTexture ID  " << *texture1;
	if (*texture1 != NULL)
	{
		//std::cout << "DELETED " << *texture1 << "\n";
		glDeleteTextures(10, texture1);
		*texture1 = NULL;
	}
	unsigned int framebuffer[2], textures[2];

	glGenFramebuffers(2, framebuffer);
	glGenTextures(2, textures);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[0], 0);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[1], 0);

	bool even = false;
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);


	for (int i = 0; i < Layers; i++)
	{
		glm::vec2 rngoffset = glm::vec2(rand()%10000, rand() % 10000);
		//std::cout<<"texture "<< *texture1 <<"  x " << rngoffset.x << "  y " << rngoffset.y<<"\n";
		UseShader(NoizeGenShader);

		float weight = 1.0f ;
		if (i == 0) weight = 1.0f;
		else weight = 1.0f / (pow(2, i));
		// add new layer (higher freq, less wieght)
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[even]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, even ? textures[1] : textures[0]);
		glUniform1i(glGetUniformLocation(NoizeGenShader, "PrevTexture"), 0);

		glUniform1f(glGetUniformLocation(NoizeGenShader, "sizex"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShader, "sizey"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShader, "weight"), weight);

		glUniform1i(glGetUniformLocation(NoizeGenShader, "shape"), shape);

		glUniform2f(glGetUniformLocation(NoizeGenShader, "offset"), rngoffset.x, rngoffset.y );

		glBindVertexArray(ScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);


		
		even = !even;
		
	}
	//unsigned int tmp = *texture1;
	*texture1 = textures[0];
	//texture2 = tmp;
	glDeleteFramebuffers(2, framebuffer);
	glDeleteTextures(1, &textures[1]);
	//std::cout << "	ExitTexture ID  " << *texture1 << "\n\n";

	glViewport(0, 0, WIDTH, HEIGHT);



	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GenNormalMapTexture(unsigned int* texture1, int Size, int shape = ROUND)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);


	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	UseShader(GenNormalMapShader);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	int i = 0;
	if (shape == ROUND)
		i = 0;
	else if (shape == SQUERE)
		i = 1;
	else if (shape == SMOOTH_EDGE)
		i = 2;
	glUniform1i(glGetUniformLocation(GenNormalMapShader, "Type"), i);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	
	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GenLightSphereTexture(unsigned int* texture1, int Size)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);

	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	UseShader(GenLightSphereShader);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

class Texture
{
public:
	int id = 0;
	std::string FileName;
	int Type = 0;// 0-Texture, 1-ROUNDNOIZE, 2-SQUERENOIZE, 3-SMOOTH_EDGENOIZE;
	unsigned int texture;

	float Noize_Frequency = 10;
	int Noize_Layers = 3;
	float Noize_Size = 100.0f;

	void Load()
	{
		if (Type == 0)
			LoadTexture(FileName.c_str(), &texture);
		else if (Type == 1)
			GenNoizeTexture(&texture, Noize_Size, Noize_Layers, Noize_Frequency, ROUND);
		else if (Type == 2)
			GenNoizeTexture(&texture, Noize_Size, Noize_Layers, Noize_Frequency, SQUERE);
		else if(Type == 3)
			GenNoizeTexture(&texture, Noize_Size, Noize_Layers, Noize_Frequency, SMOOTH_EDGE);
		if (texture == NULL)
			std::cout << "Failed to load texture:  " << FileName.c_str() << std::endl;
	}
	void Delete()
	{
		glDeleteTextures(1, &texture);
		texture = NULL;
	}

};



void DrawTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, float rotation = 0.0f, glm::vec4 color = glm::vec4(1.0f), int Z_Index = 0,unsigned int NormalMap = NULL)
{

	if (NormalMap != NULL)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);

	
	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}

	int TQA = -1;

	for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
		if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
			TQA = i;
	if (TQA == -1)
	{
		TexturedQuadArray NewTQA;
		NewTQA.Texture = texture;
		SceneLayers[SLI].TexturedQuads.push_back(NewTQA);
		for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
			if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
				TQA = i;
	}
	SceneLayers[SLI].TexturedQuads[TQA].Quadcolors.push_back(color);
	SceneLayers[SLI].TexturedQuads[TQA].QuadPosScale.push_back(glm::vec4(position,scale));
	SceneLayers[SLI].TexturedQuads[TQA].QuadRotations.push_back(rotation);

}


void DrawTexturedQuad(cube c, unsigned int texture, glm::vec4 color = glm::vec4(1.0f), float rotation = 0.0f,int Z_Index =0,unsigned int NormalMap = NULL)
{


	glm::vec2 position = c.position;
	glm::vec2 scale = glm::vec2(c.width, c.height);

	if (NormalMap != NULL)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);


	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}

	int TQA = -1;

	for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
		if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
			TQA = i;
	if (TQA == -1)
	{
		TexturedQuadArray NewTQA;
		NewTQA.Texture = texture;
		SceneLayers[SLI].TexturedQuads.push_back(NewTQA);
		for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
			if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
				TQA = i;
	}
	SceneLayers[SLI].TexturedQuads[TQA].Quadcolors.push_back(color);
	SceneLayers[SLI].TexturedQuads[TQA].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].TexturedQuads[TQA].QuadRotations.push_back(rotation);



}


void DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec4 color = glm::vec4(1.0f))
{

	glBindVertexArray(TriangleVAO);
	UseShader(FillTriangleShader);
	float aspx = 1.0f * ScreenDivisorX * CameraScale.x;
	float aspy = 1.0f * ScreenDivisorY * CameraScale.y;
	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][2] =
	{

		{ p1.x, p1.y},
		{ p2.x, p2.y},
		{ p3.x, p3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUniform4f(glGetUniformLocation(FillTriangleShader, "Color"), color.x, color.y, color.z, color.w);

	glUniform2f(glGetUniformLocation(FillTriangleShader, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);



}
void DrawTexturedTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int texture,
	glm::vec4 color = glm::vec4(1.0f),
	glm::vec2 texcoord1 = glm::vec2(0.0f,1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
	)
{

	UseShader(TexturedTriangleShader);
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][4] =
	{
		{ p1.x, p1.y,texcoord1.x,texcoord1.y},
		{ p2.x, p2.y,texcoord2.x,texcoord2.y},
		{ p3.x, p3.y,texcoord3.x,texcoord3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(TexturedTriangleShader, "Texture"),0);
	
	glUniform4f(glGetUniformLocation(TexturedTriangleShader, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	DetachShader();


}
