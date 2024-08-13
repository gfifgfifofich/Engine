#include "engine/Components/Redactor.h"

// BallGrid needs to be a proxy, not a input/output texture


// try balltoballcollision with 2 gpu_arrays - sucks, too much calls, each call much less efficient, bc 1 call to process like 2 balls


void PreReady()
{
	
}



struct GPU_PackedBallData
{
	std::vector<glm::vec4> posvel;
	std::vector<ball*> balls;
	float Radius = 1.0f;
	unsigned int texture = NULL;
	unsigned int bufferTexture = NULL;
	void add(ball* b)
	{
		posvel.push_back({b->position,b->velocity});
		balls.push_back(b);
	}
	void SetToGPU()
	{
		for(int i=0;i<posvel.size();i++)
		{
			posvel[i] = {balls[i]->position, balls[i]->velocity};
		}
		fLoadTextureFromData(&texture,posvel.size(),1,(float*)posvel.data(),4);
	}
	void GetFromGPU()
	{
		if(texture == NULL)
			return;
		freadTexture((float*)posvel.data(),texture,{posvel.size(),1},4);

		for(int i=0;i<balls.size();i++)
		{
			balls[i]->position = {posvel[i].x,posvel[i].y};
			balls[i]->velocity = {posvel[i].z,posvel[i].w};
		}
	}
	~GPU_PackedBallData()
	{
		posvel.clear();
		if(texture !=NULL)
			glDeleteTextures(1,&texture);
		if(bufferTexture !=NULL)
			glDeleteTextures(1,&bufferTexture);
	}
};
struct GPU_PackedCubeData
{
	std::vector<glm::vec4> possize;
	unsigned int texture = NULL;
	void add(cube* b);
	void add(cube b);
	void add(glm::vec4 possize);
	void SetToGPU();
	void GetFromGPU();
};



Shader ballprocessshader;
Shader ballPartitionedCollideProcessshader;
void GPU_BallProcess(GPU_PackedBallData* gpu_balldata,float dt, glm::vec2 force = {0.0f,0.0f})
{
	if (gpu_balldata->bufferTexture == NULL)
	{
		glGenTextures(1, &gpu_balldata->bufferTexture);		
	}
	else
	{
		glDeleteTextures(1,&gpu_balldata->bufferTexture);
		glGenTextures(1, &gpu_balldata->bufferTexture);	
	}
	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);
	unsigned int framebuffer;
	glBlendFunc(GL_ONE,GL_ZERO);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, gpu_balldata->posvel.size(), 1);
	UseShader(ballprocessshader.program);
	glGenFramebuffers(1, &framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, gpu_balldata->bufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, gpu_balldata->posvel.size(), 1, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gpu_balldata->bufferTexture, 0);


	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ZERO, GL_ONE);
	

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0.0f,0.0f,0.0f,0.0f);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gpu_balldata->texture);
	glUniform1i(glGetUniformLocation(ballprocessshader.program, "Balls"), 0);

	glBindVertexArray(ScreenVAO);
	glUniform1i(glGetUniformLocation(ballprocessshader.program, "BallsCount"), gpu_balldata->posvel.size());
	glUniform1f(glGetUniformLocation(ballprocessshader.program, "delta"), dt);
	glUniform2f(glGetUniformLocation(ballprocessshader.program, "force"), force.x,force.y);
	glUniform1f(glGetUniformLocation(ballprocessshader.program, "Radius"), gpu_balldata->Radius);
	glUniform1i(glGetUniformLocation(ballprocessshader.program, "SingleSpace"), true);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	

	glDeleteFramebuffers(1, &framebuffer);

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
	//swap buffer texture and current
	unsigned int bbb = gpu_balldata->bufferTexture;
	gpu_balldata->bufferTexture = gpu_balldata->texture;
	gpu_balldata->texture = bbb;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GPU_BallSelfCollide(GPU_PackedBallData* gpu_balldata);
void GPU_BallSelfCollideProcess(GPU_PackedBallData* gpu_balldata,float dt, glm::vec2 force = {0.0f,0.0f});
void GPU_BallToBallCollision(GPU_PackedBallData* gpu_balldata1,GPU_PackedBallData* gpu_balldata2);
void GPU_BallToCubeCollision(GPU_PackedBallData* gpu_balldata1,GPU_PackedCubeData* gpu_cubedata);


//needs rework

class BallGrid
{
public:
	unsigned int BallsPV = 0;
	unsigned int BufferBallsPV = 0;
	unsigned int PackedBallsPV = 0;
	unsigned int ArrPositions = 0;
	//pointer to all the balls
	std::vector<ball*> balls;
	float Radius = 1.0f;
	//Maxamount of balls per cell
	int cellsize = 100;
	//amount of divisions by 2 of space (1 - 4 cells 2x2, 2 - 16, 4x4 etc.)
	int SpaceDecisionPower = 5;
	//2d array of posvels, stored in 1d array for easy transfer to texture 
	std::vector<glm::vec4> posvelPacked;// goes to GPU
	std::vector<glm::vec4> posvel;// goes to GPU
	//std::vector<glm::vec4> posvel;// goes to GPU
	std::vector<glm::vec3> Texturepositions;// goes to GPU
	std::vector<std::vector<int>> celliterators;
	std::vector<int> arraypositions;// stores position of ball[i] in a posvel array/texture

	int cellYcount =0;
	int totalcellcount =0;

	glm::vec2 position = {0.0f,0.0f};
	glm::vec2 scale = {1024.0f,1024.0f};

	void add(ball* b)
	{
		balls.push_back(b);
	}
	void UpdateStructure()
	{
		int cellcount = 1;
		cellYcount = pow(2,SpaceDecisionPower);
		for(int i=1;i<=SpaceDecisionPower;i++) 
		{
			cellcount *=4;
		}
		totalcellcount = cellcount;
		// nice binds
		glm::vec4*** grid = new glm::vec4**[cellYcount];
		for(int i =0 ;i< cellYcount;i++)
			grid[i] = new glm::vec4*[cellYcount]; 
		arraypositions.resize(balls.size());
		posvelPacked.resize(cellsize * cellcount);
		celliterators.resize(cellYcount);
		posvel.resize(balls.size());
		Texturepositions.resize(balls.size());

		for(int i =0;i< cellYcount;i++)
			celliterators[i].resize(cellYcount);
		for(int i =0;i< balls.size();i++)
			arraypositions[i]=-1;

		for(int i=0;i<celliterators.size();i++)
			for(int a=0;a<celliterators[i].size();a++)
				celliterators[i][a]=0;

		for(int i=0;i<posvelPacked.size();i++)
			posvelPacked[i]={0.0f,0.0f,0.0f,0.0f};

		for(int i=0;i<Texturepositions.size();i++)
			Texturepositions[i]={0.0f,0.0f,0.0f};


		for(int i =0 ;i< cellYcount;i++)
			for(int a = 0;a<cellYcount;a++)
				grid[i][a] = &posvelPacked[i*cellsize + a*cellYcount*cellsize];
		int ballcounter =0;
		for(int a = 0; a < balls.size();a++)
		{
			int cellx = 0;
			int celly = 0;

			glm::vec2 bp = balls[a]->position;
			glm::vec2 bvel = balls[a]->velocity;// mb will grab in 1 memory access with pos?
			posvel[a] = {bp,bvel};
			glm::vec2 midpos = position;
			glm::vec2 scalemult = {1.0f,1.0f};

			float cellsizex = (scale.x *2.0f) / cellYcount;
			float cellsizey = (scale.y *2.0f) / cellYcount;

			cellx = bp.x / cellsizex;
			celly = bp.y / cellsizey;
			if (cellx < 0 || cellx >= cellYcount ||
				celly < 0 || celly >= cellYcount)
			{
				arraypositions[ballcounter] = -1;
				Texturepositions[ballcounter] = {-1, -1,-1};
				ballcounter++;
				continue;
			}
			grid[cellx][celly][celliterators[cellx][celly]] = {bp,bvel};
			arraypositions[ballcounter] = ((cellx + celly*cellYcount)*cellsize + celliterators[cellx][celly]);
			Texturepositions[ballcounter] = glm::vec3(cellx, celly, celliterators[cellx][celly]);
			ballcounter++;
			celliterators[cellx][celly]++;

			if(celliterators[cellx][celly]>cellsize)
				std::cout<<cellx << "	"<< celly<<"	"<< celliterators[cellx][celly]<<"\n";
		}
		for(int i =0 ;i< cellYcount;i++)
			delete[] grid[i]; 
		delete[] grid;
	}
	void SetToGPU()
	{
		for(int i=0;i<balls.size();i++)
		{
			if(arraypositions[i]<0)
				continue;
			posvelPacked[arraypositions[i]] = {balls[i]->position, balls[i]->velocity};
			posvel[i] = {balls[i]->position, balls[i]->velocity};
		}
		fLoadTextureFromData(&BallsPV,posvel.size(),1,(float*)posvel.data(),4);
		fLoadTextureFromData(&PackedBallsPV,cellsize,totalcellcount,(float*)posvelPacked.data(),4);
		fLoadTextureFromData(&ArrPositions,Texturepositions.size(),1,(float*)Texturepositions.data(),3);
	}
	void GetFromGPU()
	{
		if(BallsPV == NULL)
			return;
		freadTexture((float*)posvel.data(),BallsPV,{posvel.size(),1},4);
		
		for(int i=0;i<balls.size();i++)
		{
			//glm::vec3 tpos = Texturepositions[i];
			//int arrpos = (tpos.x+tpos.y*cellYcount) * cellsize + tpos.z;
			//balls[i]->position = {posvelPacked[arrpos].x,posvelPacked[arrpos].y};
			//balls[i]->velocity = {posvelPacked[arrpos].z,posvelPacked[arrpos].w};
			balls[i]->position = {posvel[i].x,posvel[i].y};
			balls[i]->velocity = {posvel[i].z,posvel[i].w};
		}

	}
	void DebugDrawGrid()
	{
		std::vector<float> invpows;
		std::vector<int> pows;
		cellYcount = pow(2,SpaceDecisionPower);

		for(int i=0;i<celliterators.size();i++)
			for(int a=0;a<celliterators[i].size();a++)
			{
				DrawCube(position  + glm::vec2(i,a)*(scale/(float)cellYcount)*2.0f,scale/(float)cellYcount,0.0f,
				{celliterators[i][a]*0.9f,celliterators[i][a]*0.9f,celliterators[i][a]*0.9f,1.0f}
				);

			}
		//DrawCube(position ,scale);
		

	}
	void DebugDraw()
	{
		cellYcount = pow(2,SpaceDecisionPower);

		for(int i=0;i<celliterators.size();i++)
			for(int a=0;a<celliterators[i].size();a++)
			{
				if(celliterators[i][a]>cellsize)
				{
					glm::vec4* begin = &posvel[(i+a*cellYcount)*cellsize];
					for(int b = 0;b< celliterators[i][a];b++)
					{
						DrawCircle({begin[b].x,begin[b].y},5.0f,{2.0f,0.0f,0.0f,1.0f});
					}
				}

			}
		//DrawCube(position ,scale);
		

	}

};
void GPU_BallCollideProcess(BallGrid* BallGrid,float dt, glm::vec2 force = {0.0f,0.0f})
{
	if (BallGrid->BufferBallsPV == NULL)
	{
		glGenTextures(1, &BallGrid->BufferBallsPV);		
	}
	else
	{
		glDeleteTextures(1,&BallGrid->BufferBallsPV);
		glGenTextures(1, &BallGrid->BufferBallsPV);	
	}
	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	glClampColor(GL_CLAMP_FRAGMENT_COLOR, GL_FALSE);
	unsigned int framebuffer;
	glBlendFunc(GL_ONE,GL_ZERO);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, BallGrid->posvel.size(), 1);
	UseShader(ballPartitionedCollideProcessshader.program);
	glGenFramebuffers(1, &framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, BallGrid->BufferBallsPV);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, BallGrid->posvel.size(), 1, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, BallGrid->BufferBallsPV, 0);


	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ZERO, GL_ONE);
	

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0.0f,0.0f,0.0f,0.0f);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BallGrid->BallsPV);
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "Balls"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, BallGrid->PackedBallsPV);
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "PackedBalls"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, BallGrid->ArrPositions);
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "TexturePositions"), 2);



	glBindVertexArray(ScreenVAO);
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "BallsCount"), BallGrid->posvel.size());
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "TexturePositionsCount"), BallGrid->Texturepositions.size());
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "Cellcount"), BallGrid->totalcellcount);
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "CellYcount"), BallGrid->cellYcount);
	glUniform1i(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "Cellsize"), BallGrid->cellsize);
	glUniform1f(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "delta"), dt);
	glUniform2f(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "force"), force.x,force.y);
	glUniform1f(glGetUniformLocation(ballPartitionedCollideProcessshader.program, "Radius"), BallGrid->Radius);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	

	glDeleteFramebuffers(1, &framebuffer);

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
	//swap buffer texture and current
	unsigned int bbb = BallGrid->BufferBallsPV;
	BallGrid->BufferBallsPV = BallGrid->BallsPV;
	BallGrid->BallsPV = bbb;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




BallGrid bg;
GPU_PackedBallData gpuballs;
std::vector<ball> cpuballs;
std::vector<ball> cpuballs2;

int count = 15000;
void Ready()
{
	ballprocessshader.VertexPath = "./engine/Shaders/GPUPhysics/Array.vert";
	ballprocessshader.FragmentPath = "./engine/Shaders/GPUPhysics/BallProcess.frag";
	ballprocessshader.Load();
	ballPartitionedCollideProcessshader.VertexPath = "./engine/Shaders/GPUPhysics/Array.vert";
	ballPartitionedCollideProcessshader.FragmentPath = "./engine/Shaders/GPUPhysics/BallCollideProcessPartitioned.frag";
	ballPartitionedCollideProcessshader.Load();
	for(int i=0;i<count;i++)
	{	
		ball b;
		int sq= 64;
		b.r = 5.0f;
		b.position.x = rand() % 2000;
		b.position.y = rand() % 2000;
		b.velocity.x = 0.0f;
		b.velocity.y = 0.0f;
		
		cpuballs.push_back(b);
	}
		
	gpuballs.Radius = 5.0f;
	bg.Radius = 5.0f;
	for(int i=0;i<count;i++)
	{
		bg.add(&cpuballs[i]);
	}
	//gpuballs.SetToGPU();
	bg.UpdateStructure();
}


void Process(float dt)
{
	bg.UpdateStructure();
	for(int s=0;s<10;s++)
	{
		bg.SetToGPU();
		GPU_BallCollideProcess(&bg,std::min(dt,0.017f) * 0.1f ,{0.0f,-10.0f});
		bg.GetFromGPU();
	}

	//for(auto b : cpuballs)
	//	DrawCircle(b.position,gpuballs.Radius);
	for(auto p : bg.posvel)
		DrawCircle(glm::vec2(p),bg.Radius);

	//for(int s=0;s<10;s++)
	//{
	//	gpuballs.posvel.clear();
	//	gpuballs.balls.clear();
	//	for(int i=0;i<cpuballs.size();i++)
	//		gpuballs.add(&cpuballs[i]);
	//	gpuballs.SetToGPU();
	//	GPU_BallProcess(&gpuballs,std::min(dt * 0.1f,0.017f* 0.1f),{0.0f,-100.0f});
	//	gpuballs.GetFromGPU();
	//}
	//
	//for(auto b : cpuballs)
	//	DrawCircle(b.position,gpuballs.Radius);
	
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