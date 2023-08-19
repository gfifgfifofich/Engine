#pragma once

class NeuralNetwork
{
public:


	float* outputs;
	float* inputs;



	float* Nodes;//s

	float* biases;//s
	float* biasGradients;//s

	float* weights;//s*(s-1)
	float* weightGradients;//s*(s-1)
	float* weightOutputs;//s*(s-1)


	int* Arch;
	int* NodesStep;
	int* WeightsStep;

	int NodesAmount;
	int WeightsAmount;

	int sizein;
	int sizeout;
	int LayersAmount;

	float lastCost = -1.0f;

	float rate = 1.0f;
	float c1 = 1.0f;
	float h = 1.0f;
	int gyms = 96;// used only in a method of randomizing everything and choosing best

	void Create(int* Architecture, int archsize);
	void Randomize();
	void Run(float* inputData);
	// inputs an array through a NN and calculates diviation from output 
	float Cost(float* input, float* output, int amount);
	// Cost() but with output to GUI
	float TestCost(float* input, float* output, int amount);
	void ApplyGrad();
	void DeApplyGrad();
	// Uses Cost() to minimize the diviation. Method - finite difirences
	void learn(float rate, float* input, float* output, int amount);
	// unimplemented, use to make a custom NN learning scenario
	float CustomCost();
	// unimplemented, use to make a custom NN learning behaviour
	void Customlearn(float Learnrate);
	// Draws NN structure, all weights(lines) and biases(circles)
	void Draw(glm::vec2 position = glm::vec2(0.0f), float weigthScale = 1.0f, float NeuronScale = 1.0f, glm::vec2 scale = glm::vec2(1.0f));
	//Draws NN "During its work", weight activations(lines), Nodes values(circles)
	void Draw(float* inputdata, glm::vec2 position = glm::vec2(0.0f), float weigthScale = 1.0f, float NeuronScale = 1.0f, glm::vec2 scale = glm::vec2(1.0f));
	
	void SaveTo(std::string filename);
	void LoadFrom(std::string filename);

	void Delete();
	~NeuralNetwork()
	{
		Delete();
	}
};