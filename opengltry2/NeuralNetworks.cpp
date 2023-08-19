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
float NeuralNetwork::CustomCost()
{
	ball bol;
	float cst = 0;

	for (int a = 0; a < 320; a++)
	{
		//glm::vec2 trg = { sin(a / 320 * 2.0f * pi) ,cos(a / 320 * 2.0f * pi) };
		glm::vec2 trg = { rand() % 100 * 0.01f ,cos(rand() % 100 * 0.01f * 2.0f * pi) };
		trg *= 400.0f;
		bol.position = { 0.0f ,0.0f };
		bol.velocity = { 0.0f ,0.0f };
		float lastdistance = -1.0f;
		for (int i = 0; i < frames; i++)
		{
			float inp[] = { bol.position.x - trg.x,
			bol.velocity.x };
			Run(inp);
			bol.Force.x = outputs[0] * 10000.0f - 5000.0f;

			float inpy[] = { bol.position.y - trg.y,
					bol.velocity.y };
			Run(inpy);
			bol.Force.y = outputs[0] * 10000.0f - 5000.0f;

			bol.Process(0.017f);
		}
		cst += length(trg - bol.position);

	}
	if (cst < 0.0f)
		cst = 0.0f;
	return cst;
}
std::vector<NeuralNetwork*> DataStorage;

bool finitediff = false;

void NeuralNetwork::Customlearn(float Learnrate)
{
	rate = Learnrate;
	c1 = CustomCost();
	std::vector<int> iter;
	if (!finitediff) 
	{
		iter.resize(threadcount);
		for (int i = 0; i < threadcount; i++)
			iter[i] = i;

		for (int i = 0; i < DataStorage.size(); i++)
			DataStorage[i]->~NeuralNetwork();

		DataStorage.clear();
		DataStorage.resize(gyms);
	}
	else
	{
		if (threadcount >= WeightsAmount)
		{
			iter.resize(threadcount);
			for (int i = 0; i < threadcount; i++)
				iter[i] = i;
		}
		else
		{
			iter.resize(WeightsAmount);
			for (int i = 0; i < WeightsAmount; i++)
				iter[i] = i;
		}
	}if (!finitediff)
	{
		std::for_each(std::execution::par, iter.begin(), iter.end(), [this](int thr)
			{


				int amount = gyms / threadcount;
				for (int s = thr * amount; s < (thr + 1) * amount; s++)
				{
					DataStorage[s] = new NeuralNetwork;
					DataStorage[s]->Create(Arch, LayersAmount);
					for (int i = 0; i < WeightsAmount; i++)
						DataStorage[s]->weights[i] = weights[i] + h * ((rand() % 1000) / 1000.0f - 0.5f) * 2.0f;

					for (int i = 0; i < NodesAmount; i++)
						DataStorage[s]->biases[i] = biases[i] + h * ((rand() % 1000) / 1000.0f - 0.5f) * 2.0f;

					DataStorage[s]->lastCost = DataStorage[s]->CustomCost();
				}



			});
	}
	else
	{
		for (int i = 0; i < WeightsAmount; i++)
		{
			if (i < WeightsAmount)
			{
				float hh = weights[i] * h;
				weights[i] += hh;

				float c2 = CustomCost();
				weights[i] -= hh;
				float slope = (c2 - c1) / hh;

				weightGradients[i] = slope * rate;
			}
		}
		for (int i = 0; i < NodesAmount; i++)
		{
			if (i < NodesAmount)
			{
				float hh = biases[i] * h;
				biases[i] += hh;

				float c2 = CustomCost();
				biases[i] -= hh;
				float slope = (c2 - c1) / hh;

				biasGradients[i] = slope * rate;
			}
		}

	}
	if (!finitediff)
	{
		int minIndex = -1;
		float mincost = lastCost;
		for (int i = 0; i < DataStorage.size(); i++)
			if (DataStorage[i]->lastCost < mincost || (mincost < 0.0f && DataStorage[i]->lastCost >= 0.0f))
			{
				mincost = DataStorage[i]->lastCost;
				minIndex = i;
			}
		if (minIndex > -0.5f && mincost < lastCost || lastCost < 0.0f) {
			lastCost = mincost;

			for (int i = 0; i < WeightsAmount; i++)
			{
				weightGradients[i] = (weights[i] - DataStorage[minIndex]->weights[i]) * Learnrate;
				//weights[i] = DataStorage[minIndex]->weights[i];
			}
			for (int i = 0; i < NodesAmount; i++)
			{
				biasGradients[i] = (biases[i] - DataStorage[minIndex]->biases[i]) * Learnrate;
				//biases[i] = DataStorage[minIndex]->biases[i];
			}//ApplyGrad();
			float cst = CustomCost();

			float cst2 = cst;
			bool run = true;
			while (run)
			{
				run = false;
				ApplyGrad();
				cst2 = CustomCost();
				if (cst2 < cst)
				{
					run = true;
					cst = cst2;
				}
				else
					DeApplyGrad();
			}
		}
	}
	else
	{
		ApplyGrad();
		float cst = CustomCost();

		float cst2 = cst;
		bool run = true;
		while (run)
		{
			run = false;
			ApplyGrad();
			cst2 = CustomCost();
			if (cst2 < cst)
			{
				run = true;
				cst = cst2;
			}
			else
				DeApplyGrad();
		}
	}
}





bool Autolearn = false;
float Rate = 1.0f;

int arch[2] = {
	2,1
};

NeuralNetwork nn;



float weightscale = 0.001f;
float Neuronscale = 10.0f;
glm::vec2 scal = glm::vec2(50.0f,15.0f);
float posX = 0.0f;
Graph costgraph(0,1.0f, 0.1f,0.0f,0.0f);

void On_Create()
{// called once while starting app
	nn.Create(arch, 2);
	nn.Randomize();
}
ball bol;

glm::vec2 trg = { rand() % 1000 - 500 ,rand() % 1000 - 500 };
int counter = 0;
void On_Update()
{// called every frame

	costgraph.scale = { 500.0f,500.0f };
	costgraph.DataScale = { 1.0f,500.0f };
	costgraph.position = { -0.49f*WIDTH, -0.49f*HEIGHT};
	costgraph.Inspect(MousePosition);


	ImGui::Begin("Tools");

	ImGui::SliderFloat("Rate",&Rate,0.0f,1.0f);
	ImGui::SliderFloat("h",&nn.h,0.0f,1.0f);
	ImGui::SliderInt("frames",&frames,0.0f,600.0f);
	ImGui::SliderFloat("weightscale",&weightscale,0.0f,10.0f);
	ImGui::SliderFloat("Neuronscale",&Neuronscale,0.0f,25.0f);

	ImGui::SliderFloat("scalex",&scal.x,0.0f,100.0f);
	ImGui::SliderFloat("scaley",&scal.y,0.0f,100.0f);
	ImGui::DragFloat("posx",&posX);
	nn.lastCost = nn.CustomCost();
	ImGui::Text("COstCost = %.3f", nn.lastCost);
	ImGui::Checkbox("finitediff", &finitediff);


	if (ImGui::Button("Randomize"))
		nn.Randomize();

	if (ImGui::Button("Learn"))
	{
		nn.Customlearn(Rate);
		costgraph.data.push_back(nn.lastCost);
	}
	if (ImGui::Button("Randomize Point") || counter<=0)
	{
		trg = { rand() % 1000 - 500 ,rand() % 1000 - 500 };
		trg = Normalize(trg) * 400.0f;
		bol.position = { 0.0f ,0.0f };
		bol.velocity = { 0.0f ,0.0f };
		counter = frames;
	}
	ImGui::Checkbox("Autolearn", &Autolearn);

	if (ImGui::Button("Save"))
		nn.SaveTo("BallTargeter1D.nn");

	if (ImGui::Button("Load"))
		nn.LoadFrom("BallTargeter1D.nn");
	counter--;
	if (Autolearn)
	{
		nn.Customlearn(Rate);
		costgraph.data.push_back(nn.lastCost);
		if (costgraph.data.size() > 1000)
			costgraph.data.pop_front();
	}
	costgraph.Draw();

	

	ImGui::End();

	//nn.inputs[0] = bol.position.x;
	//nn.inputs[1] = bol.position.y;
	//nn.inputs[2] = bol.velocity.x;
	//nn.inputs[3] = bol.velocity.y;
	//nn.inputs[4] = trg.x;
	//nn.inputs[5] = trg.y;
	float inp[] = { bol.position.x - trg.x,
			bol.velocity.x};
	nn.Run(inp);
	bol.Force.x = nn.outputs[0] * 10000.0f - 5000.0f;

	float inpy[] = { bol.position.y - trg.y,
			bol.velocity.y };
	nn.Run(inpy);
	bol.Force.y = nn.outputs[0] * 10000.0f - 5000.0f;
	bol.Process(0.017f);
	DrawBall(bol); 
	DrawCircle(trg, 5);

	nn.Draw(inp,{ posX ,400.0f }, weightscale, Neuronscale, scal);
}
int main()
{
	initEngine();
	return 0;
}
