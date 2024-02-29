#include "engine/Components/Engine.h";
#include "engine/Components/sounds.h";

unsigned int Sine;

const int amount = 9;

unsigned int Source[amount];

float stages[amount];
float sustain[amount];
float pitch[amount];
float vibrato[amount];
float vibratospeed[amount];
float kick[amount];

float mainKick = 2.0f;
float mainvibrato = 0.0f;
float mainvibratospeed = 2.0f;
float mainpitch = 1.0f;
float mainsustain = 2.0f;

float keysoffset =  1.0f;
float keySize =  25.0f;

float FrameTime = 0.0f;
float dt = 0.0f , lasttime = 0.0f;

	void On_Create() 
	{
		AL_init();
		Sine = LoadSound("Sounds/Sine.wav");

		for (int i = 0; i < amount; i++)
		{
			GenSource(&Source[i]);
			SetSourceSound(&Source[i], &Sine);
			SetSourceLooping(&Source[i], true);
			stages[i] = 0.0f;
			SetSourceGain(&Source[i], stages[i]);
			sustain[i] = 1.125f;
			pitch[i] = (i+4)/6.0f;
			vibrato[i] = 0.00f;
			vibratospeed[i] = 6.0f;
			kick[i] = 2.0f;


			PlaySource(&Source[i]);
		}

	}
	void On_Update() 
	{
		ImGui::Begin("stuff");

		ImGui::SliderFloat("Sustain",&mainsustain,0.1f,3.0f);
		ImGui::SliderFloat("Kick speed",&mainKick,0.0f,100.0f);
		ImGui::SliderFloat("Pitch",&mainpitch,0.01f,3.0f);
		ImGui::SliderFloat("Vibrato power",&mainvibrato,0.0f,1.0f);
		ImGui::SliderFloat("Vibrato speed",&mainvibratospeed,0.01f,100.0f);


		ImGui::End();
		while (FrameTime < 0.017f)
		{
			dt *= 0.0003f;
			for (int i = 0; i < 3000; i++)
			{

				for (int i = 0; i < amount; i++)
				{
					sustain[i] = mainsustain;
					vibrato[i] = mainvibrato;
					vibratospeed[i] = mainvibratospeed;
					kick[i] = 1 + mainKick;
				}

				for (int i = 0; i < amount; i++)
					if (i % 2 == 0)
					{//white key
						float it = i / 2.0f;
						DrawCube(glm::vec2(it * keySize * 2.1f - keysoffset, -100.0f), glm::vec2(keySize, 100.0f), glm::vec3(0.0f), glm::vec4(1.0f, 1.0f - stages[i], 1.0f - stages[i], 1.0f));
					}
				for (int i = 0; i < amount; i++)
					if (i % 2 != 0)
					{//black key
						float it = i / 2.0f;
						DrawCube(glm::vec2(it * keySize * 2.1f - keysoffset, -75.0f), glm::vec2(keySize * 0.5f, 75.0f), glm::vec3(0.0f), glm::vec4(stages[i], 0.0f, 0.0f, 1.0f));

					}


				if (keys[GLFW_KEY_1]) stages[0] += dt * kick[0];
				if (keys[GLFW_KEY_2]) stages[1] += dt * kick[1];
				if (keys[GLFW_KEY_3]) stages[2] += dt * kick[2];
				if (keys[GLFW_KEY_4]) stages[3] += dt * kick[3];
				if (keys[GLFW_KEY_5]) stages[4] += dt * kick[4];
				if (keys[GLFW_KEY_6]) stages[5] += dt * kick[5];
				if (keys[GLFW_KEY_7]) stages[6] += dt * kick[6];
				if (keys[GLFW_KEY_8]) stages[7] += dt * kick[7];
				if (keys[GLFW_KEY_9]) stages[8] += dt * kick[8];

				for (int i = 0; i < amount; i++)
				{
					if (stages[i] >= 1.0f)
					{
						stages[i] = 1.0f;
					}
					SetSourceGain(&Source[i], stages[i]);
					SetSourcePitch(&Source[i], pitch[i] * mainpitch + sin(clock() * 0.001f * vibratospeed[i]) * pitch[i] * vibrato[i]);


					stages[i] -= dt / sustain[i];
					if (stages[i] <= 0)
					{
						stages[i] = 0;
						StopSource(&Source[i]);
					}
					else if (!SourcePlaying(&Source[i]))
					{
						PlaySource(&Source[i]);
						std::cout << "playing " << i << "\n";
					}
				}
			}

			dt = (clock() - lasttime) * 0.001f;
			lasttime = clock();
			FrameTime += dt;
		}
		FrameTime = 0.0f;
	}


int main()
{
	initEngine();
	AL_Destroy();

	return 0;
}