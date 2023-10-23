#include "engine/Components/Engine.h"


class VoxelMap
{
public:

	glm::vec2 scale = { 10.0f,10.0f };
	glm::ivec2 size = { 5,5 };

	glm::vec2 position = { 0.0f,0.0f };

	polygon terrain;

	float** data;

	void Create(glm::ivec2 Size, glm::vec2 Scale = {10.0f,10.0f})
	{
		size = Size;
		scale = Scale;

		data = new float*[size.x];

		for (int i = 0; i < size.x; i++)
			data[i] = new float[size.y];
		for (int i = 0; i < size.x; i++)
			for (int a = 0; a < size.y; a++)
				data[i][a] = rand()%100 * 0.01f;



	}

	void UpdateShape()
	{
		terrain.indexes.clear();
		terrain.Rawpoints.clear();
		terrain.Transofromedpoints.clear();

		for (int i = 0; i < size.x; i++)
			for (int a = 0; a < size.y; a++)
			{
				if (data[i][a] > 1.0f)data[i][a] = 1.0f;
				if (data[i][a] < 0.0f)data[i][a] = 0.0f;
			}
		for (int i = 0; i < size.x; i++)
			for (int a = 0; a < size.y; a++)
			{
				glm::vec2 mid = glm::vec2(i,a);
				/*


				if (i - 1 >= 0)
					mid += glm::vec2(-1.0f, 0.0f) * (1.0f-data[i-1][a]);

				if (a + 1 < size.y)
					mid += glm::vec2(0, 1.0f) * (1.0f-data[i][a+1]);

				if (a - 1 >= 0)
					mid += glm::vec2(0, -1.0f) * (1.0f-data[i][a-1]);

				if (i + 1 < size.x)
					mid += glm::vec2(1.0f, 0.0f) * (1.0f-data[i + 1][a]);

				mid *= scale;
				*/
				/*int minx = i - 1 >= 0 ? i - 1 : 0;
				int miny = a - 1 >= 0 ? a - 1 : 0;

				int maxx = i + 1 <size.x ? i + 1 : size.x-1;
				int maxy = a + 1 <size.y ? a + 1 : size.y-1;
				for (int x = minx; x <= maxx; x++)
					for (int y = miny; y <= maxy; y++)
					{
						if(x!=i&&y!=a)
							mid += (glm::vec2(x, y)  - mid ) * data[x][y];

					}*/

				terrain.add_Point(mid * scale);
			}

		for (int x = 0; x < size.x; x++)
			for (int y = 0; y < size.y; y++)
			{
				if (data[x][y] > 0.0f) 
				{
					if (x - 1 >= 0 && y - 1 >= 0)
						if (data[x-1][y] > 0.0f && data[x][y-1] > 0.0f)
							terrain.indexes.push_back({ x * size.y + y,x * size.y + y - 1,(x - 1) * size.y + y });

					if (x - 1 >= 0 && y + 1 < size.y)
						if (data[x - 1][y] > 0.0f && data[x][y + 1] > 0.0f)
							terrain.indexes.push_back({ x * size.y + y,x * size.y + y + 1,(x - 1) * size.y + y });

					if (x + 1 < size.x && y - 1 >= 0)
						if (data[x + 1][y] > 0.0f && data[x][y - 1] > 0.0f)
							terrain.indexes.push_back({ x * size.y + y,x * size.y + y - 1,(x + 1) * size.y + y });

					if (x + 1 < size.x && y + 1 < size.y)
						if (data[x + 1][y] > 0.0f && data[x][y + 1] > 0.0f)
							terrain.indexes.push_back({ x * size.y + y,x * size.y + y + 1,(x + 1) * size.y + y });
				}
			}
		terrain.Position = position;
		terrain.Update_Shape();
	}





	void Delete()
	{


		for (int i = 0; i < size.x; i++)
			delete[] data[i];
		delete[] data;
	}

};

VoxelMap vm;

unsigned int texture;

void On_Create() 
{
	vm.Create({ 40,40}, { 25.0f,25.0f });

	LoadTexture("Albedo.jpg", &texture);
	vm.terrain.colors.clear();
	vm.terrain.Texture = texture;
	vm.terrain.colors.push_back({ 3.0f,1.0f,0.5f,1.0f });
	//vm.terrain.colors.push_back({ 1.0f,0.0f,0.0f,1.0f });
	//vm.terrain.colors.push_back({ 0.0f,1.0f,0.0f,1.0f });
	//vm.terrain.colors.push_back({ 1.0f,0.0f,1.0f,1.0f });
	//vm.terrain.colors.push_back({ 0.0f,1.0f,1.0f,1.0f });
	vm.position = { -500,-450 };
}
void On_Update() 
{
	/*for(int x=0;x<vm.size.x;x++)
		for (int y = 0; y < vm.size.y; y++)
		{
			DrawCircle(vm.position + glm::vec2(x, y) * vm.scale.x, vm.data[x][y] * vm.scale.x*0.5f,glm::vec4(1.0f,1.0f,1.0f,0.4f));
		}*/

	if (JustPressedkey[GLFW_KEY_SPACE])
	{
		vm.Create({ 40,40 }, { 25.0f,25.0f });
	}

	if (buttons[GLFW_MOUSE_BUTTON_1])
		if (MousePosition.x - vm.position.x > 0.0f && MousePosition.x - vm.position. x< vm.size.x * vm.scale.x && MousePosition.y - vm.position.y> 0.0f && MousePosition.y - vm.position. y< vm.size.y * vm.scale.y)
		{
			glm::ivec2 pos = glm::ivec2(round((MousePosition.x - vm.position.x) / vm.scale.x), round((MousePosition.y - vm.position.y) / vm.scale.y));
			if (pos.x >= vm.size.x)
				pos.x = vm.size.x - 1;
			if (pos.y >= vm.size.y)
				pos.y = vm.size.y - 1;
			vm.data[pos.x][pos.y] += delta*1000.0f;


		}
	if (buttons[GLFW_MOUSE_BUTTON_2])
		if (MousePosition.x - vm.position.x > 0.0f && MousePosition.x - vm.position.x < vm.size.x * vm.scale.x && MousePosition.y - vm.position.y> 0.0f && MousePosition.y - vm.position.y < vm.size.y * vm.scale.y)
		{
			glm::ivec2 pos = glm::ivec2(round((MousePosition.x - vm.position.x) / vm.scale.x), round((MousePosition.y - vm.position.y)/ vm.scale.y));
			if (pos.x >= vm.size.x)
				pos.x = vm.size.x - 1;
			if (pos.y >= vm.size.y)
				pos.y = vm.size.y - 1;
			vm.data[pos.x][pos.y] -= delta * 1000.0f;


		}

	vm.UpdateShape();
	vm.terrain.DrawTriangles();
}
int main()
{
	initEngine();
	vm.Delete();
	return 0;
}