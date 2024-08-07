#include "engine/Components/Redactor.h"

void fLoadTextureFromData(unsigned int* texture, int width, int height, float* Data, int chanelsAmount)
{
	if (*texture != NULL)
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (chanelsAmount == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, Data);

	if (chanelsAmount == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, width, height, 0, GL_RG, GL_FLOAT, Data);

	if (chanelsAmount == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, Data);

	if (chanelsAmount == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, Data);

	glBindTexture(GL_TEXTURE_2D, 0);

}


void PreReady()
{
	
}

Shader NNShader;
void RunNNLayerOnGPU(int inSize,int outSize,int InstanceCount,int Func,
					unsigned int* OutTexture, unsigned int packedInTexture,unsigned int packedWeightsTexture,unsigned int packedBiasesTexture)
{
	if (*OutTexture != NULL && glIsTexture(*OutTexture))
	{
		//std::cout << "DELETED " << *OutTexture << "\n";
		glDeleteTextures(1, OutTexture);
		*OutTexture = NULL;
		
	}
	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);
	unsigned int framebuffer;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, OutTexture);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, *OutTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, outSize, InstanceCount, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *OutTexture, 0);


	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ZERO, GL_ONE);
	glBlendFunc(GL_ONE,GL_ZERO);
	
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, outSize, InstanceCount);
	UseShader(NNShader.program);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0.0f,0.0f,0.0f,0.0f);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, packedBiasesTexture);
	glUniform1i(glGetUniformLocation(NNShader.program, "biases"), 0);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, packedInTexture);
	glUniform1i(glGetUniformLocation(NNShader.program, "data_in"), 2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, packedWeightsTexture);
	glUniform1i(glGetUniformLocation(NNShader.program, "weights"), 1);

	glBindVertexArray(ScreenVAO);
	glUniform1i(glGetUniformLocation(NNShader.program, "inSize"), inSize);
	glUniform1i(glGetUniformLocation(NNShader.program, "outSize"), outSize);
	glUniform1i(glGetUniformLocation(NNShader.program, "InstanceCount"), InstanceCount);
	glUniform1i(glGetUniformLocation(NNShader.program, "Func"), Func);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


	glDeleteFramebuffers(1, &framebuffer);

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}


float* readTexture(unsigned int texture, glm::ivec2 size, int channels = 1)
{

	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);


	float* buffer = new float[size.x * size.y * channels];
	for(int i =0;i<size.x * size.y * channels;i++)
		buffer[i]= 0.0f;
	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, buffer);

	return buffer;
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
	NNShader.VertexPath = "./engine/Shaders/NeuralNetworks/NN.vert";
	NNShader.FragmentPath = "./engine/Shaders/NeuralNetworks/NNRun.frag";
	NNShader.Load();

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
	
	float* buff = readTexture(Visual_T_Out,{insize,1},1);



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
	NNShader.Delete();
}