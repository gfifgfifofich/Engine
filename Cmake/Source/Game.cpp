#include "engine/Components/Redactor.h"




void PreReady()
{
	
}

unsigned int T_Weights = 0;
unsigned int T_Biases = 0;
unsigned int T_Weights2 = 0;
unsigned int T_Biases2 = 0;
unsigned int T_Weights3 = 0;
unsigned int T_Biases3 = 0;
unsigned int T_In = 0;
unsigned int T_Out = 0; 
unsigned int T_Out2 = 0; 
unsigned int T_Out3 = 0; 

unsigned int Visual_T_Weights = 0;
unsigned int Visual_T_Biases = 0;
unsigned int Visual_T_In = 0;
unsigned int Visual_T_Out = 0; 

const int insize = 20000;
const int outsize = 10000;
const int outsize2 = 3000;
const int outsize3 = 50;

float Weights[insize * outsize];
float Biases[outsize];
float Weights2[outsize * outsize2];
float Biases2[outsize2];
float Weights3[outsize2 * outsize3];
float Biases3[outsize3];
float In[insize];
float Out[outsize];
float Out2[outsize2];
float Out3[outsize3];

void Ready()
{
	

	for (int i=0;i<insize * outsize;i++)
		Weights[i] = rand() %2000 * 0.001f - 1.0f;
	for (int i=0;i<outsize * outsize2;i++)
		Weights2[i] = rand() %2000 * 0.001f - 1.0f;
	for (int i=0;i<outsize2 * outsize3;i++)
		Weights3[i] = rand() %2000 * 0.001f - 1.0f;

	for (int i=0;i<insize;i++)
	{
		Biases[i] = rand() %1000 * 0.0001f;
		In[i] = rand() %1000 * 0.0001f;
	}
	for (int i=0;i<outsize;i++)
	{
		Out[i] = 0.0f;
		Biases[i] = rand() %1000 * 0.0001f;
	}
	for (int i=0;i<outsize2;i++)
	{
		Biases2[i] = rand() %1000 * 0.0001f;
		Out2[i] = 0.0f;
	}
	for (int i=0;i<outsize3;i++)
	{
		Biases3[i] = rand() %1000 * 0.0001f;
		Out3[i] = 0.0f;
	}
	
	fLoadTextureFromData(&T_Weights,insize,outsize,Weights,1);
	fLoadTextureFromData(&T_Biases,outsize,1,Biases,1);
	
	fLoadTextureFromData(&T_Weights2,outsize,outsize2,Weights2,1);
	fLoadTextureFromData(&T_Biases2,outsize2,1,Biases2,1);

	fLoadTextureFromData(&T_Weights3,outsize2,outsize3,Weights3,1);
	fLoadTextureFromData(&T_Biases3,outsize3,1,Biases3,1);

	fLoadTextureFromData(&T_In,insize,1,In,1);
	fLoadTextureFromData(&T_Out,outsize,1,Out,1);
	fLoadTextureFromData(&T_Out2,outsize2,1,Out2,1);
	fLoadTextureFromData(&T_Out3,outsize3,1,Out3,1);

	CopyTexture({insize,outsize},&Visual_T_Weights,T_Weights,4);
	CopyTexture({insize,10.0f},&Visual_T_Biases,T_Biases,4);
	CopyTexture({insize,10.0f},&Visual_T_In,T_In,4);

	RunNNLayerOnGPU(insize,outsize,1,3,&T_Out,T_In,T_Weights,T_Biases);
	RunNNLayerOnGPU(outsize,outsize2,1,3,&T_Out2,T_Out,T_Weights2,T_Biases2);
	RunNNLayerOnGPU(outsize2,outsize3,1,3,&Visual_T_Out,T_Out2,T_Weights3,T_Biases3);
	
	float* buff = freadTexture(Visual_T_Out,{insize,1},1);


	delete[] buff;
}

void Process(float dt)
{


	RunNNLayerOnGPU(insize,outsize,1,2,&T_Out,T_In,T_Weights,T_Biases);
	RunNNLayerOnGPU(outsize,outsize2,1,2,&T_Out2,T_Out,T_Weights2,T_Biases2);
	RunNNLayerOnGPU(outsize2,outsize3,1,2,&Visual_T_Out,T_Out2,T_Weights3,T_Biases3);

	DrawTexturedQuad({-200.0f,200.0f},  {100.0f,100.0f},Visual_T_Weights);
	DrawTexturedQuad({200.0f,200.0f},{100.0f,100.0f},Visual_T_Biases);
	DrawTexturedQuad({-200.0f,-200.0f},{100.0f,100.0f},Visual_T_In);
	DrawTexturedQuad({200.0f,-200.0f},{100.0f,100.0f},Visual_T_Out);

	//Draw scene 
	GameScene->Draw();
}

void Rescale(int newWindth,int newHeight)
{

}

void SubSteppedProcess(float dt, int s)
{

}

void SceneEnd()
{

}

void Destroy()
{
}