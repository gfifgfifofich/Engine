#include "engine/Components/Engine.h"
unsigned int TestVBO;

const unsigned int size = 1000;
float data[size];
unsigned int shade;



int arch[4] = {
	3,25,10,1
};

NeuralNetwork nn;

void RenderNNToTexture(NeuralNetwork* nn, unsigned char* DataStorage, int width, int height)
{
	LoadShader(&shade, "engine/shaders/Default.vert", "engine/z1ShaderTests/NNRun.frag");
	UseShader(shade);
	glUniform1fv(glGetUniformLocation(shade, "weights"), nn->WeightsAmount, nn->weights);
	glUniform1fv(glGetUniformLocation(shade, "biases"), nn->NodesAmount, nn->biases);
	glUniform1iv(glGetUniformLocation(shade, "arch"), nn->LayersAmount, nn->Arch);

	glUniform1iv(glGetUniformLocation(shade, "NodesStep"), nn->LayersAmount, nn->NodesStep);
	glUniform1iv(glGetUniformLocation(shade, "WeightsStep"), nn->LayersAmount, nn->WeightsStep);

	SetShader1i(&shade, "archsize", nn->LayersAmount);
	SetShader1i(&shade, "Weightsize", nn->WeightsAmount);
	SetShader1i(&shade, "Biassize", nn->NodesAmount);

	

	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);


	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);



	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, DataStorage);


	glViewport(0, 0, WIDTH, HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	//glDeleteFramebuffers(1, &framebuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDeleteTextures(1, &texture2);



}

unsigned int texture;
unsigned char* Data;

void On_Create()
{
	nn.Create(arch, 4);

	nn.LoadFrom("2TextureNN32-16.nn");
	/*nn.Randomize();
	nn.Randomize();*/
	Data = new unsigned char[100 * 100 * 3];
	RenderNNToTexture(&nn, Data, 100, 100);

	for (int i = 0; i < size; i++)
		data[i] = 100;


	/*
	

uniform int arch   [10];
uniform int NodesStep   [10];
uniform int WeightsStep   [10];
	*/
}


//// getBuffeSubData to get data from VAO
//     glGetBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), recevedData);

//// glGetTexImage to get data from texture
//     glBindTexture(GL_TEXTURE_2D, rewTextureOBJ);
//     glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, newTextureData);

// #extension GL_ARB_separate_shader_objects : enable === using layouts in fragmentSHader

bool draw = false;
void On_Update()
{
	nn.Draw({ -400.0f,0.0f }, 0.1f, 5.0f, {200.0f,20.0f});
	if (ImGui::Button("ReloadShader"))
	{
		LoadShader(&shade, "engine/shaders/Quad/default.vert", "engine/z1ShaderTests/NNRunT.frag");

	}
	ImGui::Text("tex id %i", texture);
	ImGui::Checkbox("Draw", &draw);

	if(draw)
		DrawTexturedQuad(MousePosition, { 100.0f,100.0f }, texture);




	/*glBindVertexArray(quadVAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);*/


	//glDeleteTextures(1, &texture);
	//delete[] Data;
}

int main()
{
	initEngine();
	
}

/*


	glGenBuffers(1, &TestVBO);
	glBindBuffer(GL_ARRAY_BUFFER, TestVBO);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, &data[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
	//glVertexAttribDivisor(1, 1);

	float* recevedData = new float[size];
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), recevedData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	std::cout << recevedData[999]<<"\n";



int ImageW, ImageH, nrChannels;
	unsigned char* Texture = stbi_load("the 5.png", &ImageW, &ImageH, &nrChannels, 1);
	unsigned char* trueTexture = new unsigned char[ImageW * ImageH * 4];
	for (int y = 0; y < ImageH; y++)
		for (int x = 0; x < ImageW; x++)
		{
			trueTexture[0 + (x + y * ImageW) * 4] = Texture[x + y * ImageW];
			trueTexture[1 + (x + y * ImageW) * 4] = Texture[x + y * ImageW];
			trueTexture[2 + (x + y * ImageW) * 4] = Texture[x + y * ImageW];
			trueTexture[3 + (x + y * ImageW) * 4] = Texture[x + y * ImageW];
		}

	unsigned int text;
	unsigned int tt;
	LoadTextureFromData(&text, ImageW, ImageH, trueTexture, 4);
	delete[]Texture;
	delete[]trueTexture;

	unsigned char* newTexture = new unsigned char[ImageW * ImageH * 4];

	glBindTexture(GL_TEXTURE_2D,text);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, newTexture);


	LoadTextureFromData(&tt, ImageW, ImageH, newTexture, 4);
	DrawTexturedQuad(MousePosition, { 100.0f,100.0f }, tt);









	float Vertices[] = {
		// coordinates  // UV
		-1.0f,  1.0f, 0.0f,1.0f,
		 1.0f, -1.0f, 1.0f,0.0f,
		-1.0f, -1.0f, 0.0f,0.0f,

		-1.0f,  1.0f, 0.0f,1.0f,
		 1.0f, -1.0f, 1.0f,0.0f,
		 1.0f,  1.0f, 1.0f,1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);




				glGenBuffers(1, &instanceCircleVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);
				glBindVertexArray(CircleVAO);


				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].Circlecolors.size(), &SceneLayers[i].Circlecolors[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
				glVertexAttribDivisor(1, 1);

				glGenBuffers(1, &instanceCircleVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);
				glBindVertexArray(CircleVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].CirclePosScale.size(), &SceneLayers[i].CirclePosScale[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);


				glVertexAttribDivisor(2, 1);



				glGenBuffers(1, &instanceCircleVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);
				glBindVertexArray(CircleVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].CircleRotations.size(), &SceneLayers[i].CircleRotations[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
*/