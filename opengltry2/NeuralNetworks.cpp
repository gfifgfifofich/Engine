#include "engine/Components/Engine.h"


//
//float InputData[8] = {
//	0,0,
//	0,1,
//	1,0, 
//	1,1
//};
//float OutputData[8] = {
//	0,0,
//	1,0,
//	0,1,
//	1,1
//};
//
//int DataSize = 4;

void RenderNNToTextureSecondMethod(NeuralNetwork* nn, unsigned char* DataStorage, int width, int height)
{
	unsigned int shade;
	LoadShader(&shade, "engine/shaders/Default.vert", "engine/z1ShaderTests/NNRunT.frag");
	UseShader(shade);

	SetShader1i(&shade, "archsize", nn->LayersAmount);
	SetShader1i(&shade, "Weightsize", nn->WeightsAmount);
	SetShader1i(&shade, "Biassize", nn->NodesAmount);

	//glUniform1fv(glGetUniformLocation(shade, "weights"), nn->WeightsAmount, nn->weights);
	//glUniform1fv(glGetUniformLocation(shade, "biases"), nn->NodesAmount, nn->biases);

	//glUniform1iv(glGetUniformLocation(shade, "arch"), nn->LayersAmount, nn->Arch);
	//glUniform1iv(glGetUniformLocation(shade, "NodesStep"), nn->LayersAmount, nn->NodesStep);
	//glUniform1iv(glGetUniformLocation(shade, "WeightsStep"), nn->LayersAmount, nn->WeightsStep);


	unsigned int weightsTex;
	unsigned int biasesTex;
	unsigned int archTex;
	unsigned int NodesStepTex;
	unsigned int WeightsStepTex;





	glGenTextures(1, &weightsTex);
	glBindTexture(GL_TEXTURE_1D, weightsTex);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32F, nn->WeightsAmount, 0, GL_RED, GL_FLOAT, nn->weights);

	glGenTextures(1, &biasesTex);
	glBindTexture(GL_TEXTURE_1D, biasesTex);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32F, nn->NodesAmount, 0, GL_RED, GL_FLOAT, nn->biases);

	glGenTextures(1, &archTex);
	glBindTexture(GL_TEXTURE_1D, archTex);
	
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32I, nn->LayersAmount, 0, GL_RED, GL_INT, nn->Arch);

	glGenTextures(1, &NodesStepTex);
	glBindTexture(GL_TEXTURE_1D, NodesStepTex);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32I, nn->LayersAmount, 0, GL_RED, GL_INT, nn->NodesStep);

	glGenTextures(1, &WeightsStepTex);
	glBindTexture(GL_TEXTURE_1D, WeightsStepTex);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32I, nn->LayersAmount, 0, GL_RED, GL_INT, nn->WeightsStep);

	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D, weightsTex);
	glUniform1i(glGetUniformLocation(shade, "weights"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_1D, biasesTex);
	glUniform1i(glGetUniformLocation(shade, "biases"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D, archTex);
	glUniform1i(glGetUniformLocation(shade, "arch"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_1D, NodesStepTex);
	glUniform1i(glGetUniformLocation(shade, "NodesStep"), 3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_1D, WeightsStepTex);
	glUniform1i(glGetUniformLocation(shade, "WeightsStep"), 4);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_1D, 0);


	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
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
	glDeleteFramebuffers(1, &framebuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture2);
}



void RenderNNToTexture(NeuralNetwork* nn, unsigned char* DataStorage, int width, int height)
{
	unsigned int shade;
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture2);
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteProgram(shade);


}

void fRenderNNToTexture(NeuralNetwork* nn, float* DataStorage, int width, int height)
{
	unsigned int shade;
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
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

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, DataStorage);


	glViewport(0, 0, WIDTH, HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glDeleteFramebuffers(1, &framebuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture2);



}

int frames = 300;
float CustomCost(NeuralNetwork* nn)
{
	ball bol;
	float cst = 0;

	for (int a = 0; a < 320; a++)
	{
		//glm::vec2 trg = { sin(a / 320 * 2.0f * pi) ,cos(a / 320 * 2.0f * pi) };
		glm::vec2 trg = { rand() % 1000 - 500 ,rand() % 1000 - 500 };

		bol.position = { 0.0f ,0.0f };
		bol.velocity = { 0.0f ,0.0f };
		float lastdistance = -1.0f;
		for (int i = 0; i < frames; i++)
		{
			float inp[] = { bol.position.x - trg.x,
			bol.velocity.x };
			nn->Run(inp);
			bol.Force.x = nn->outputs[0] * 10000.0f - 5000.0f;

			float inpy[] = { bol.position.y - trg.y,
					bol.velocity.y };
			nn->Run(inpy);
			bol.Force.y = nn->outputs[0] * 10000.0f - 5000.0f;

			bol.Process(0.017f);
		}
		cst += length(trg - bol.position);

	}
	if (cst < 0.0f)
		cst = 0.0f;
	return cst;
}
float Rate = 1.0f;

int ImageW, ImageH, nrChannels;
unsigned char* Texture;

int Image2W, Image2H, nrChannels2;
unsigned char* Texture2;


int arch[4] = {
	3,30,20,1
};


float fun(float x)
{
	return  sigmoid(x);//;sin(x)*0.5f+0.5f;
}

float CustomCostTexture(NeuralNetwork* nn)
{
	float cst = 0;
	for(int y= 0;y<ImageH;y++)
		for (int x = 0; x < ImageW; x++)
		{
			float r = Texture[(x + y * ImageW)*3 + 0] / 255.0f ;
			float inp[] = { x / float(ImageW),y / float(ImageH), 0.0f};
			nn->Run(fun, inp);
			float diff = r - std::clamp(nn->outputs[0],0.0f,1.0f);
			cst +=  diff*diff;
		
			float g = Texture[(x + y * ImageW) * 3 + 1] / 255.0f;
			inp[2] = 0.333f;
			nn->Run(fun, inp);
			diff = g -std::clamp(nn->outputs[0], 0.0f, 1.0f);
			cst += diff * diff ;



			float b = Texture[(x + y * ImageW) * 3 + 2] / 255.0f;
			inp[2] = 0.666f;

			nn->Run(fun, inp);
			diff = b - std::clamp(nn->outputs[0], 0.0f, 1.0f);
			cst += diff * diff;
		}


	return cst;
}
void GenNNTexture(unsigned int* texture, NeuralNetwork* NN, unsigned int width, unsigned int height, float state)
{
	if (texture != NULL)
		glDeleteTextures(1, texture);


	unsigned char* uptexdata = new unsigned char[width * height * 3];

	//RenderNNToTexture(NN, uptexdata, width, height);
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			float inp[] = { x / float(width),y / float(height),0.0f };
			NN->Run(fun, inp);
			uptexdata[0 + (x + y * width) * 3] = NN->outputs[0]*1.0f;

			inp[2] = 0.33f;
			NN->Run(fun, inp);
			uptexdata[1 + (x + y * width) * 3] = NN->outputs[0] * 1.0f;

			inp[2] = 0.66f;
			NN->Run(fun, inp);
			uptexdata[2 + (x + y * width) * 3] = NN->outputs[0] * 1.0f;

			//uptexdata[3 + (x + y * width) * 4] = 20.0f;
		}
	LoadTextureFromData(texture, width, height, uptexdata, 3);
	delete[width * height * 3] uptexdata;

}
void GPUGenNNTexture(unsigned int* texture, NeuralNetwork* NN, unsigned int width, unsigned int height, float state)
{
	if (texture != NULL)
		glDeleteTextures(1, texture);


	unsigned char* uptexdata = new unsigned char[width * height * 3];
	//float* uptexdata = new float[width * height * 3];

	RenderNNToTexture(NN, uptexdata, width, height);
	LoadTextureFromData(texture, width, height, uptexdata, 3);
	delete[width * height * 3] uptexdata;

}
bool Autolearn = false;

bool finitediff = false;
bool autoUpscale = false;
bool autoH = false;

NeuralNetwork nn;

float state = 0.0f;

float weightscale = 0.001f;
float Neuronscale = 10.0f;
glm::vec2 scal = glm::vec2(50.0f,15.0f);
float posX = 0.0f;
Graph costgraph(0,1.0f, 0.1f,0.0f,0.0f);

unsigned int texture;
unsigned int texture2;
unsigned int Genedtexture = NULL;
unsigned int Upscaletexture = NULL;
int UpscaleW = 128;
int UpscaleH = 128;
unsigned char* trueTexture ;
void On_Create()
{// called once while starting app
	nn.Create(arch, 4);
	nn.Randomize();
	SettingsWindow = false;

	
	Texture = stbi_load("minisus.png", &ImageW, &ImageH, &nrChannels, 3);
	trueTexture = new unsigned char[ImageW * ImageH * 3];
	for (int y = 0; y < ImageH; y++)
		for (int x = 0; x < ImageW; x++)
		{
				trueTexture[0 + (x + y * ImageW) * 3] = Texture[(x + y * ImageW) * 3 + 0];
				trueTexture[1 + (x + y * ImageW) * 3] = Texture[(x + y * ImageW) * 3 + 1];
				trueTexture[2 + (x + y * ImageW) * 3] = Texture[(x + y * ImageW) * 3 + 2];
			
			
		}
	
	LoadTextureFromData(&texture, ImageW, ImageH, Texture, 3);
	delete[ImageW * ImageH * 4] trueTexture;

	//Texture2 = stbi_load("the 8.png", &Image2W, &Image2H, &nrChannels2, 1);
	//trueTexture = new unsigned char[Image2W * Image2H * 4];
	//for (int y = 0; y < Image2H; y++)
	//	for (int x = 0; x < Image2W; x++)
	//	{
	//		if (Texture2[x + y * Image2W] > 30)
	//		{
	//			trueTexture[0 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//			trueTexture[1 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//			trueTexture[2 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//			trueTexture[3 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//		}
	//		else
	//		{

	//			Texture2[x + y * Image2W] = 0;
	//			trueTexture[0 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//			trueTexture[1 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//			trueTexture[2 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//			trueTexture[3 + (x + y * Image2W) * 4] = Texture2[x + y * Image2W];
	//		}
	//	}
	//LoadTextureFromData(&texture2, Image2W, Image2H, trueTexture, 4);
	//delete[Image2W * Image2H * 4] trueTexture;
}
/*
ball bol;

glm::vec2 trg = { rand() % 1000 - 500 ,rand() % 1000 - 500 };*/
int counter = 0;
glm::vec2 AqueredCameraScale = glm::vec2(1.0f);
glm::vec2 PrevMousePos = glm::vec2(0.0f);


int learniterations = 1;

int Upscalemult = 1.0f;


bool testbool;
void On_Update()
{

	if (keys[GLFW_KEY_W]) CameraPosition.y += delta / CameraScale.y * 600.0f;
	if (keys[GLFW_KEY_S]) CameraPosition.y -= delta / CameraScale.y * 600.0f;
	if (keys[GLFW_KEY_A]) CameraPosition.x -= delta / CameraScale.x * 600.0f;
	if (keys[GLFW_KEY_D]) CameraPosition.x += delta / CameraScale.x * 600.0f;



	AqueredCameraScale *= 1.0f + scrollmovement * 0.1f;
	CameraScale += (AqueredCameraScale - CameraScale) * 0.25f * delta * 60.0f;


	glm::vec2 dif = glm::vec2(0.0f);
	if (buttons[GLFW_MOUSE_BUTTON_MIDDLE])
		dif = PrevMousePos - MousePosition;
	MousePosition -= CameraPosition;
	CameraPosition += dif; 
	MousePosition += CameraPosition;
	PrevMousePos = MousePosition;

	UI_DrawCircle(ScreenMousePosition, 100, {1.0f,1.0f,1.0f,1.0f},false, NULL, 100, false);

	UI_DrawTextOnPlate("asdasd", { 300,100 }, 1.0f, { 1.0f,1.0f,1.0f,1.0f }, {0.0f,0.0f,0.0f,0.8f},102,false);
	

	UI_CheckBox(&testbool, "asd", { 100,100 });
	
	costgraph.scale = { 500.0f,500.0f };
	costgraph.DataScale = { 1.0f,20.0f };
	costgraph.position = { -0.49f*WIDTH, -0.49f*HEIGHT};
	costgraph.Inspect(MousePosition);


	ImGui::Begin("Tools");

	if (ImGui::Button("ReloadShader"))
	{
		unsigned int shade;
		LoadShader(&shade, "engine/shaders/Quad/default.vert", "engine/z1ShaderTests/NNRunT.frag");

	}

	ImGui::SliderFloat("Rate",&Rate,0.0f,10.0f);
	ImGui::SliderFloat("h",&nn.h,0.0f,1.0f);
	ImGui::SliderFloat("UpscaleState",&state,0.0f,1.0f);
	//ImGui::SliderInt("frames",&frames,0.0f,600.0f);
	ImGui::SliderFloat("weightscale",&weightscale,0.0f,10.0f);
	ImGui::SliderFloat("Neuronscale",&Neuronscale,0.0f,25.0f);

	ImGui::SliderFloat("scalex",&scal.x,0.0f,100.0f);
	ImGui::SliderFloat("scaley",&scal.y,0.0f,100.0f);
	ImGui::SliderInt("Upscalemult",&Upscalemult,1,10);
	ImGui::SliderInt("learniterations",&learniterations,0,10);
	ImGui::DragFloat("posx",&posX);
	ImGui::Text("COstCost = %.3f", nn.lastCost);
	ImGui::Checkbox("finitediff", &finitediff);

	ImGui::Text("tex id %i", Genedtexture);
	ImGui::Text("Scene layers %i", SceneLayers.size());


	if (ImGui::Button("Randomize"))
	{
		nn.Randomize();
		GenNNTexture(&Genedtexture ,&nn, ImageW, ImageH, state);
	}

	if (ImGui::Button("genUpscale"))
		GPUGenNNTexture(&Upscaletexture ,&nn, int(UpscaleW* Upscalemult), int(UpscaleH* Upscalemult), state);


	ImGui::Checkbox("autoUpscale", &autoUpscale);
	if (autoUpscale)
		GPUGenNNTexture(&Upscaletexture ,&nn, int(UpscaleW * Upscalemult), int(UpscaleH* Upscalemult), state);

	ImGui::Checkbox("autoH", &autoH);
	if (autoH)
		nn.h = nn.lastCost * 0.015f;


	if (ImGui::Button("Learn"))
	{
		nn.Customlearn(CustomCostTexture,Rate, finitediff);
		costgraph.data.push_back(nn.lastCost);
		GenNNTexture(&Genedtexture ,&nn, ImageW, ImageH, state);
	}
	//if (ImGui::Button("Randomize Point") || counter<=0)
	//{
	//	trg = { rand() % 1000 - 500 ,rand() % 1000 - 500 };
	//	//trg = Normalize(trg) * 400.0f;
	//	bol.position = { 0.0f ,0.0f };
	//	bol.velocity = { 0.0f ,0.0f };
	//	counter = frames;
	//}
	//counter--;
	ImGui::Checkbox("Autolearn", &Autolearn);

	if (ImGui::Button("Save"))
		nn.SaveTo("2TextureNN32-16.nn");

	if (ImGui::Button("Load"))
		nn.LoadFrom("2TextureNN32-16.nn");
	if (Autolearn)
	{
		for(int i=0;i< learniterations;i++)
			nn.Customlearn(CustomCostTexture,Rate, finitediff);
		costgraph.data.push_back(nn.lastCost);
		if (costgraph.data.size() > 1000)
			costgraph.data.pop_front();

		GenNNTexture(&Genedtexture ,&nn, ImageW, ImageH, state);


	ImGui::Text("last texture index %i", Genedtexture);

	ImGui::End();
	}

	costgraph.Draw();
	DrawTexturedQuad({ -800.0f,300.0f }, { 200.0f,200.0f }, texture);
	DrawTexturedQuad({ -200.0f,-600.0f }, { 200.0f,200.0f }, texture2);
	if(Genedtexture!=NULL)
		DrawTexturedQuad({ 200.0f,-400.0f }, { 200.0f,200.0f }, Genedtexture);

	if (Upscaletexture != NULL)
		DrawTexturedQuad({ 0.0f,300.0f }, { 300.0f,300.0f }, Upscaletexture);

	nn.Draw( { posX ,400.0f }, weightscale, Neuronscale, scal);

	//nn.inputs[0] = bol.position.x;
	//nn.inputs[1] = bol.position.y;
	//nn.inputs[2] = bol.velocity.x;
	//nn.inputs[3] = bol.velocity.y;
	//nn.inputs[4] = trg.x;
	//nn.inputs[5] = trg.y;
	/*float inp[] = { bol.position.x - trg.x,
			bol.velocity.x};
	nn.Run(inp);
	bol.Force.x = nn.outputs[0] * 10000.0f - 5000.0f;

	float inpy[] = { bol.position.y - trg.y,
			bol.velocity.y };
	nn.Run(inpy);
	bol.Force.y = nn.outputs[0] * 10000.0f - 5000.0f;
	bol.Process(0.017f);
	DrawBall(bol); 
	DrawCircle(trg, 5);*/

}
int main()
{
	/*std::cout << "input screen width";
	int wi = 0;
	std::cin >> wi;
	std::cout << "input screen height";
	int he = 0;
	std::cin >> he;
	bool fs = false;
	std::cout << "Full screen? (1-yes/0-no)";
	std::cin >> fs;*/
	initEngine("NN Learn image", 1920, 1080, true);
	return 0;
}
