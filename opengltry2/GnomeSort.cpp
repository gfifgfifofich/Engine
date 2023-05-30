#include "engine/Components/Engine.h"

	float pog[20];
	glm::vec2 offset = glm::vec2(-500,-100.0f);
	void On_Create() 
	{
		for (int i = 0; i < 20; i++)
		{
			pog[i] = rand() % 50;
		}
	}

	void On_Update() 
	{
		int Size = 20;

		int i = 1;
		int a = 2;

		while (i < Size) 
		{
			if (pog[i - 1] < pog[i])
			{
				i = a;
				a++;
			}
			else
			{
				float tmp = pog[i - 1];
				pog[i - 1] = pog[i];
				pog[i] = tmp;
				i--;
				if (i == 0)
				{
					i = a;
					a++;
				}
			}
		}



		for (int j = 0; j < 20; j++)
		{
			DrawLine(glm::vec2(j * 50, pog[j] * 10) + offset, glm::vec2(j * 50, -100) + offset, 10.0f, glm::vec4(1.0f));
		}
		Sleep(35);
			
		
		



	}

int main()
{

	initEngine();

	return 0;
}