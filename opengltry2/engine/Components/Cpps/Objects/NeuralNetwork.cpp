#include "../../Include/Helper.h"
#include "../../Include/Drawing.h"
#include "../../Include/Objects/NeuralNetwork.h"

#include <thread>
#include <algorithm>
#include <execution>
void NeuralNetwork::Create(int* Architecture, int archsize)
{
	//layers = new Layer[archsize];
	LayersAmount = archsize;
	sizein = Architecture[0];
	sizeout = Architecture[archsize - 1];


	int NN_Size = 0;
	for (int i = 0; i < archsize; i++)
		NN_Size += Architecture[i];

	if (NN_Size == 0)
		std::cerr << "NN err1: Invalid size";

	int Weights_Size = 0;

	for (int i = 1; i < archsize; i++)
		Weights_Size += Architecture[i - 1] * Architecture[i];

	if (Weights_Size == 0)
		std::cerr << "NN err2: Invalid weights size";


	outputs = new float[sizeout];
	Nodes = new float[NN_Size];

	biases = new float[NN_Size];
	biasGradients = new float[NN_Size];


	weights = new float[Weights_Size];
	weightGradients = new float[Weights_Size];
	weightOutputs = new float[Weights_Size];


	NodesAmount = NN_Size;
	WeightsAmount = Weights_Size;

	Arch = new int[archsize];
	NodesStep = new int[archsize];
	WeightsStep = new int[archsize];
	//memcpy(Arch, Architecture, sizeof(int) * archsize);

	int sum = 0;
	for (int i = 0; i < archsize; i++)
	{
		Arch[i] = Architecture[i];
		NodesStep[i] = sum;
		sum += Architecture[i];
	}
	sum = 0;
	WeightsStep[0] = 0;
	for (int i = 1; i < archsize; i++)
	{
		WeightsStep[i] = sum;
		sum += Arch[i - 1] * Arch[i];
	}




}

void NeuralNetwork::Delete()
{
	delete[sizeout] outputs;
	delete[NodesAmount] Nodes;
	delete[NodesAmount] biases;
	delete[NodesAmount] biasGradients;


	delete[WeightsAmount] weights;
	delete[WeightsAmount] weightGradients;
	delete[WeightsAmount] weightOutputs;


	delete[LayersAmount] Arch;
	delete[LayersAmount] NodesStep;
	delete[LayersAmount] WeightsStep;
}

void NeuralNetwork::Randomize()
{
	for (int i = 0; i < WeightsAmount; i++)
		weights[i] = ((rand() % 1000) / 1000.0f - 0.5f) * 2.0f;

	for (int i = 0; i < NodesAmount; i++)
		biases[i] = ((rand() % 1000) / 1000.0f - 0.5f) * 2.0f;
	lastCost = -1;

}
void NeuralNetwork::Run(float* inputData)
{
	inputs = inputData;

	for (int i = 0; i < sizein; i++)
		Nodes[i] = inputData[i];

	int PrevNodeStart = 0;
	for (int i = 1; i < LayersAmount; i++)
	{
		int size = Arch[i];
		int weightsPerNode = Arch[i - 1];
		int node = 0;
		for (int n = NodesStep[i]; n < NodesStep[i] + size; n++)
		{//each node of layer

			//WeightsStep[i-1]

			float sum = 0.0f;
			int start = (WeightsStep[i - 1] + node * weightsPerNode);
			int PrevLayerNode = 0;
			for (int w = start; w < start + weightsPerNode; w++)
			{
				weightOutputs[i] = weights[w] * Nodes[PrevNodeStart + PrevLayerNode];
				sum += weightOutputs[i];

				PrevLayerNode++;
			}

			Nodes[n] = sigmoidApprox(sum + biases[n]);
			node++;
		}
		PrevNodeStart = NodesStep[i];
	}
	for (int i = 0; i < sizeout; i++)
		outputs[i] = Nodes[PrevNodeStart + i];
}
void NeuralNetwork::Run(float ActFunc(float), float* inputData)
{
	inputs = inputData;

	for (int i = 0; i < sizein; i++)
		Nodes[i] = inputData[i];

	int PrevNodeStart = 0;
	for (int i = 1; i < LayersAmount; i++)
	{
		int size = Arch[i];
		int weightsPerNode = Arch[i - 1];
		int node = 0;
		for (int n = NodesStep[i]; n < NodesStep[i] + size; n++)
		{//each node of layer

			//WeightsStep[i-1]

			float sum = 0.0f;
			int start = (WeightsStep[i - 1] + node * weightsPerNode);
			int PrevLayerNode = 0;
			for (int w = start; w < start + weightsPerNode; w++)
			{
				weightOutputs[i] = weights[w] * Nodes[PrevNodeStart + PrevLayerNode];
				sum += weightOutputs[i];

				PrevLayerNode++;
			}

			Nodes[n] = ActFunc(sum + biases[n]);
			node++;
		}
		PrevNodeStart = NodesStep[i];
	}
	for (int i = 0; i < sizeout; i++)
		outputs[i] = Nodes[PrevNodeStart + i];
}
// inputs an array through a NN and calculates diviation from output 
float NeuralNetwork::Cost(float* input, float* output, int amount)
{
	float sum = 0.0f;


	for (int i = 0; i < amount; i++)
	{
		float* arr = new float[sizein];

		for (int iter = 0; iter < sizein; iter++)
			arr[iter] = input[i * sizein + iter];


		Run(arr);

		delete[sizein] arr;

		float tmp = 0.0f;
		for (int a = 0; a < sizeout; a++)
		{
			tmp = outputs[a] - output[i * sizeout + a];

			tmp = tmp * tmp;
			sum += tmp;
		}
	}

	sum /= amount;
	return sum;
}
void NeuralNetwork::ApplyGrad()
{
	for (int i = 0; i < WeightsAmount; i++)
		weights[i] -= weightGradients[i];
	for (int i = 0; i < NodesAmount; i++)
		biases[i] -= biasGradients[i];


}
void NeuralNetwork::DeApplyGrad()
{
	for (int i = 0; i < WeightsAmount; i++)
		weights[i] += weightGradients[i];
	for (int i = 0; i < NodesAmount; i++)
		biases[i] += biasGradients[i];
}
// Uses Cost() to minimize the diviation. Method - finite difirences
void NeuralNetwork::learn(float rate, float* input, float* output, int amount)
{
	float h = 0.0001f;
	float c1 = Cost(input, output, amount);


	for (int i = 0; i < WeightsAmount; i++)
	{
		weights[i] += h;

		float c2 = Cost(input, output, amount);
		weights[i] -= h;
		float slope = (c2 - c1) / h;

		weightGradients[i] = slope * rate;
	}
	for (int i = 0; i < NodesAmount; i++)
	{
		biases[i] += h;

		float c2 = Cost(input, output, amount);
		biases[i] -= h;
		float slope = (c2 - c1) / h;

		biasGradients[i] = slope * rate;
	}


	ApplyGrad();
	float cst = Cost(input, output, amount);

	float cst2 = cst;
	bool run = true;
	while (run)
	{
		run = false;
		ApplyGrad();
		cst2 = Cost(input, output, amount);
		if (cst2 < cst)
		{
			run = true;
			cst = cst2;
		}
		else
			DeApplyGrad();
	}
}
//std::string throutputs[12];


void NeuralNetwork::Customlearn(float Costfunc(NeuralNetwork*), float Learnrate, bool finitediff)
{
	rate = Learnrate;
	c1 = Costfunc(this);
	std::vector<int> iter;

	iter.resize(threadcount);
	for (int i = 0; i < threadcount; i++)
		iter[i] = i;

	for (int i = 0; i < DataStorage.size(); i++)
		DataStorage[i]->~NeuralNetwork();

	DataStorage.clear();

	if (!finitediff)
	{
		
		DataStorage.resize(gyms);
		for (int i = 0; i < DataStorage.size(); i++)
		{

			DataStorage[i] = new NeuralNetwork;
			DataStorage[i]->Create(Arch, LayersAmount);
		}
		std::for_each(std::execution::par, iter.begin(), iter.end(), [this, Costfunc](int thr)
			{
				int amount = gyms / threadcount;
				int start = (thr)*amount;
				int end = (thr + 1) * amount;
				if (thr == threadcount - 1)
					end = gyms;
				for (int s = start; s < end; s++)
				{/*
					DataStorage[s] = new NeuralNetwork;
					DataStorage[s]->Create(Arch, LayersAmount);*/
					for (int i = 0; i < WeightsAmount; i++)
						DataStorage[s]->weights[i] = weights[i] + h * ((rand() % 1000) / 1000.0f - 0.5f) * 2.0f;

					for (int i = 0; i < NodesAmount; i++)
						DataStorage[s]->biases[i] = biases[i] + h * ((rand() % 1000) / 1000.0f - 0.5f) * 2.0f;

					DataStorage[s]->lastCost = Costfunc(DataStorage[s]);
				}



			});
		float mincost = lastCost;
		NeuralNetwork* bestNN = NULL;
		for (int i = 0; i < DataStorage.size(); i++)
			if (DataStorage[i]->lastCost < mincost || (mincost < 0.0f && DataStorage[i]->lastCost >= 0.0f))
			{
				mincost = DataStorage[i]->lastCost;
				bestNN = DataStorage[i];
			}
		if (mincost == lastCost)
			bestNN = this;
		if (mincost < lastCost && bestNN != NULL || lastCost < 0.0f) {
			lastCost = mincost;

			for (int i = 0; i < WeightsAmount; i++)
			{
				weightGradients[i] = (weights[i] - bestNN->weights[i]) * Learnrate;
				//weights[i] = DataStorage[minIndex]->weights[i];
			}
			for (int i = 0; i < NodesAmount; i++)
			{
				biasGradients[i] = (biases[i] - bestNN->biases[i]) * Learnrate;
				//biases[i] = DataStorage[minIndex]->biases[i];
			}
			
		}
		else
		{
			for (int i = 0; i < WeightsAmount; i++)
			{
				weightGradients[i] = 0.0f;
				//weights[i] = DataStorage[minIndex]->weights[i];
			}
			for (int i = 0; i < NodesAmount; i++)
			{
				biasGradients[i] = 0.0f;
				//biases[i] = DataStorage[minIndex]->biases[i];
			}
		}

		/*	for (int i = 0; i < DataStorage.size(); i++)
				DataStorage[i]->~NeuralNetwork();

			DataStorage.clear();*/
	}
	else
	{


		DataStorage.resize(threadcount);
		for (int i = 0; i < DataStorage.size(); i++)
		{

			DataStorage[i] = new NeuralNetwork();
			DataStorage[i]->Create(Arch, LayersAmount);
			for (int s = 0; s < WeightsAmount; s++)
				DataStorage[i]->weights[s] = weights[s];
			for (int s = 0; s < NodesAmount; s++)
				DataStorage[i]->biases[s] = biases[s];
		}
	
		std::for_each(std::execution::par, iter.begin(), iter.end(), [this, Costfunc](int thr)
			{
				int Wamount = WeightsAmount / threadcount;
				//for (int s = thr * amount; s < (thr + 1) * amount; s++)
				int Wstart = Wamount * thr ;
				int Wend = Wamount * (thr + 1);
				if (thr == threadcount - 1)
					Wend = WeightsAmount;

				for (int i = Wstart; i < Wend; i++)
				{
					DataStorage[thr]->weights[i] += (h * 0.01f);

					float c2 = Costfunc(DataStorage[thr]);
					DataStorage[thr]->weights[i] -= (h * 0.01f);
					float slope = (c2 - c1) / (h * 0.01f);

					weightGradients[i] = slope * rate * 0.001f;

				}
				int Namount = NodesAmount / threadcount;
				int Nstart = Namount * thr;
				int Nend = Namount * (thr + 1);
				if (thr == threadcount - 1)
					Nend = NodesAmount;

				for (int i = Nstart; i < Nend; i++)
				{
					
					DataStorage[thr]->biases[i] += (h * 0.01f);

					float c2 = Costfunc(DataStorage[thr]);
					DataStorage[thr]->biases[i] -= (h * 0.01f);
					float slope = (c2 - c1) / (h * 0.01f);

					biasGradients[i] = slope * rate*0.001f;

				}


			});
		

	}


	ApplyGrad();
	float cst = Costfunc(this);

	float cst2 = cst;
	bool run = true;
	while (run)
	{
		run = false;
		ApplyGrad();
		cst2 = Costfunc(this);
		if (cst2 < cst)
		{
			run = true;
			cst = cst2;
		}
		else
			DeApplyGrad();
	}
	lastCost = cst;

	for (int i = 0; i < DataStorage.size(); i++)
		DataStorage[i]->~NeuralNetwork();

	DataStorage.clear();
}

// Draws NN structure, all weights(lines) and biases(circles)
void NeuralNetwork::Draw(glm::vec2 position , float weigthScale , float NeuronScale , glm::vec2 scale )
{
	int PrevNodeStart = 0;

	for (int i = 0; i < Arch[0]; i++)
		DrawCircle(position + glm::vec2(0.0f, i * scale.y - Arch[0] * scale.y * 0.5f), NeuronScale);

	for (int i = 1; i < LayersAmount; i++)
	{
		int size = Arch[i];
		int weightsPerNode = Arch[i - 1];
		int node = 0;
		for (int n = NodesStep[i]; n < NodesStep[i] + size; n++)
		{//each node of layer
			DrawCircle(position + glm::vec2(i * scale.x, node * scale.y - Arch[i] * scale.y * 0.5f), NeuronScale,
				biases[n] > 0.0f ? glm::vec4(biases[n], 0.0f, 1.0f, 1.0f) : glm::vec4(0.0f, biases[n], 1.0f, 1.0f)
			);

			//WeightsStep[i-1]

			float sum = 0.0f;
			int start = (WeightsStep[i - 1] + node * weightsPerNode);
			int PrevLayerNode = 0;
			for (int w = start; w < start + weightsPerNode; w++)
			{//each weight of node
				DrawLine(position + glm::vec2(i * scale.x, node * scale.y - Arch[i] * scale.y * 0.5f),
					position + glm::vec2((i - 1) * scale.x, PrevLayerNode * scale.y - Arch[i - 1] * scale.y * 0.5f), weights[w] * weigthScale,
					weights[w] > 0.0f ? glm::vec4(weights[w], 0.0f, 1.0f, 1.0f) : glm::vec4(0.0f, weights[w], 1.0f, 1.0f)
				);

				PrevLayerNode++;
			}
			node++;
		}
		PrevNodeStart = NodesStep[i];
	}

}
//Draws NN "During its work", weight activations(lines), Nodes values(circles)
void NeuralNetwork::Draw(float* inputdata, glm::vec2 position, float weigthScale, float NeuronScale, glm::vec2 scale)
{
	Run(inputdata);
	int PrevNodeStart = 0;

	for (int i = 0; i < Arch[0]; i++)
		DrawCircle(position + glm::vec2(0.0f, i * scale.y - Arch[0] * scale.y * 0.5f), NeuronScale);

	for (int i = 1; i < LayersAmount; i++)
	{
		int size = Arch[i];
		int weightsPerNode = Arch[i - 1];
		int node = 0;
		for (int n = NodesStep[i]; n < NodesStep[i] + size; n++)
		{//each node of layer
			DrawCircle(position + glm::vec2(i * scale.x, node * scale.y - Arch[i] * scale.y * 0.5f), NeuronScale,
				Nodes[n] > 0.0f ? glm::vec4(Nodes[n], 0.0f, 1.0f, 1.0f) : glm::vec4(0.0f, Nodes[n], 1.0f, 1.0f)
			);

			//WeightsStep[i-1]

			float sum = 0.0f;
			int start = (WeightsStep[i - 1] + node * weightsPerNode);
			int PrevLayerNode = 0;
			for (int w = start; w < start + weightsPerNode; w++)
			{//each weight of node
				DrawLine(position + glm::vec2(i * scale.x, node * scale.y - Arch[i] * scale.y * 0.5f),
					position + glm::vec2((i - 1) * scale.x, PrevLayerNode * scale.y - Arch[i - 1] * scale.y * 0.5f), weightOutputs[w] * weigthScale,
					weightOutputs[w] > 0.0f ? glm::vec4(weightOutputs[w], 0.0f, 1.0f, 1.0f) : glm::vec4(0.0f, weightOutputs[w], 1.0f, 1.0f)
				);

				PrevLayerNode++;
			}
			node++;
		}
		PrevNodeStart = NodesStep[i];
	}

}

void NeuralNetwork::SaveTo(std::string filename)
{
	std::ofstream SaveFile(filename);
	SaveFile << LayersAmount;
	SaveFile << " " << WeightsAmount;
	SaveFile << " " << NodesAmount;
	SaveFile << "\n";

	for (int i = 0; i < LayersAmount; i++)
		SaveFile << Arch[i] << "\n";
	for (int i = 0; i < WeightsAmount; i++)
		SaveFile << weights[i] << "\n";
	for (int i = 0; i < NodesAmount; i++)
		SaveFile << biases[i] << "\n";
	SaveFile.close();

}
void NeuralNetwork::LoadFrom(std::string filename)
{
	Delete();

	std::ifstream f(filename);
	if (!f.is_open())
	{
		std::cerr << "ERROR LOADING NN: Unable to open " << filename;
		return;
	}
	int i = 0;
	int state = 0;
	while (!f.eof())
	{

		char junk;
		char line[32];
		f.getline(line, 32);
		std::strstream s;
		s << line;
		if (state == 0)
		{
			s >> LayersAmount >> WeightsAmount >> NodesAmount;
			std::cout << "Layers = " << LayersAmount << "  WeightsAmount = " << WeightsAmount<<"  NodesAmount = " << NodesAmount;
			Arch = new int[LayersAmount];
			state = 1;
		}
		else if (state == 1)
		{
			s >> Arch[i];

			i++;
			if (i >= LayersAmount)
			{
				i = 0;
				state = 2;

				int* Archbuff = Arch;

				Create(Arch, LayersAmount);
				delete[LayersAmount] Archbuff;
			}
		}
		else if (state == 2)
		{
			s >> weights[i];
			i++;
			if (i >= WeightsAmount)
			{
				i = 0;
				state = 3;
			}
		}
		else if (state == 3)
		{
			s >> biases[i];

			i++;
			if (i >= NodesAmount)
			{
				i = 0;
				state = 4;
			}
		}
	}
	f.close();
}

