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



int frames = 300;
float fun(float x)
{
	return  sigmoidApprox(x);//;sin(x)*0.5f+0.5f;
}
float CustomCost(NeuralNetwork* nn)
{
	ball bol;
	float cst = 0;

	for (int a = 0; a < 320; a++)
	{
		//glm::vec2 trg = { sin(a / 320 * 2.0f * pi) ,cos(a / 320 * 2.0f * pi) };
		glm::vec2 trg = { rand() % 10000 - 5000 ,rand() % 10000 - 5000 };

		bol.position = { 0.0f ,0.0f };
		bol.velocity = { 0.0f ,0.0f };
		float lastdistance = -1.0f;
		for (int i = 0; i < frames; i++)
		{
			float inp[] = { bol.position.x - trg.x,
			bol.velocity.x };
			nn->Run(sigmoid,inp);
			bol.Force.x = nn->outputs[0] * 10000.0f - 5000.0f;

			float inpy[] = { bol.position.y - trg.y,
					bol.velocity.y };
			nn->Run(sigmoid, inpy);
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


int arch[2] = {
	2,1
};



bool Autolearn = false;

bool finitediff = false;
bool autoH = false;

NeuralNetwork nn;

float state = 0.0f;

float weightscale = 0.001f;
float Neuronscale = 10.0f;
glm::vec2 scal = glm::vec2(50.0f, 15.0f);
float posX = 0.0f;
Graph costgraph(0, 1.0f, 0.1f, 0.0f, 0.0f);

void On_Create()
{// called once while starting app
	nn.Create(arch, 2);
	nn.Randomize();


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
glm::vec2 trg;
ball bol;

void Done()
{
	trg = { rand() % 1000 - 500 ,rand() % 1000 - 500 };

	trg = Normalize(trg) * 500.0f;
	bol.position = { 0.0f ,0.0f };
	bol.velocity = { rand() % 3000 - 1500 ,rand() % 3000 - 1500 };
	counter = frames;
	SettingsWindow = false;
}
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



	costgraph.scale = { 500.0f,500.0f };
	costgraph.DataScale = { 1.0f,20.0f };
	costgraph.position = { -0.49f * WIDTH, -0.49f * HEIGHT };
	costgraph.Inspect(MousePosition);


	ImGui::Begin("Tools");

	if (ImGui::Button("ReloadShader"))
	{
		unsigned int shade;
		LoadShader(&shade, "engine/shaders/Quad/default.vert", "engine/z1ShaderTests/NNRunT.frag");

	}

	ImGui::SliderFloat("Rate", &Rate, 0.0f, 10.0f);
	ImGui::SliderFloat("h", &nn.h, 0.0f, 1.0f);
	ImGui::SliderFloat("UpscaleState", &state, 0.0f, 1.0f);
	ImGui::SliderInt("frames",&frames,0.0f,600.0f);
	ImGui::SliderFloat("weightscale", &weightscale, 0.0f, 10.0f);
	ImGui::SliderFloat("Neuronscale", &Neuronscale, 0.0f, 25.0f);

	ImGui::SliderFloat("scalex", &scal.x, 0.0f, 100.0f);
	ImGui::SliderFloat("scaley", &scal.y, 0.0f, 100.0f);
	ImGui::SliderInt("Upscalemult", &Upscalemult, 1, 10);
	ImGui::SliderInt("learniterations", &learniterations, 0, 10);
	ImGui::DragFloat("posx", &posX);
	ImGui::Text("COstCost = %.3f", nn.lastCost);
	ImGui::Checkbox("finitediff", &finitediff);
	ImGui::Text("Scene layers %i", SceneLayers.size());


	if (ImGui::Button("Randomize"))
	{
		nn.Randomize();
	}



	ImGui::Checkbox("autoH", &autoH);
	if (autoH)
		nn.h = nn.lastCost * 0.015f;


	if (ImGui::Button("Learn"))
	{
		nn.Customlearn(CustomCost, Rate, finitediff);
		costgraph.data.push_back(nn.lastCost);
	}
	if (ImGui::Button("Randomize Point") || counter<=0)
	{
		Done();
	}
	counter--;
	ImGui::Checkbox("Autolearn", &Autolearn);

	if (ImGui::Button("Save"))
		nn.SaveTo("RocketNN.nn");

	if (ImGui::Button("Load"))
		nn.LoadFrom("RocketNN.nn");
	if (Autolearn)
	{
		for (int i = 0; i < learniterations; i++)
			nn.Customlearn(CustomCost, Rate, finitediff);
		costgraph.data.push_back(nn.lastCost);
		if (costgraph.data.size() > 1000)
			costgraph.data.pop_front();



		ImGui::End();
	}

	costgraph.Draw();

	nn.Draw({ posX ,400.0f }, weightscale, Neuronscale, scal);

	float inp[] = { bol.position.x - trg.x,
			bol.velocity.x };
	nn.Run(sigmoid, inp);
	bol.Force.x = nn.outputs[0] * 10000.0f - 5000.0f;

	float inpy[] = { bol.position.y - trg.y,
			bol.velocity.y };
	nn.Run(sigmoid, inpy);
	bol.Force.y = nn.outputs[0] * 10000.0f - 5000.0f;


	bol.Process(0.017f);

	//// NeuralNetwork without NeuralNetwork
	//bol.Force.x = sigmoidApprox(((bol.position.x - trg.x) * -13.2473 - bol.velocity.x * 2.18509) - 11.1678) * 10000.0f - 5000.0f;
	//bol.Force.y = sigmoidApprox(((bol.position.y - trg.y) * -13.2473 - bol.velocity.y * 2.18509) - 11.1678) * 10000.0f - 5000.0f;


	bol.Process(0.017f);
	DrawBall(bol);
	DrawCircle(trg, 5);
	if (BalltoPointCollisionCheck(bol, trg))
		Done();
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
	initEngine("NN Learn image");
	return 0;
}
