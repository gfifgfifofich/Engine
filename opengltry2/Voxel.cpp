#include "engine/Components/Engine.h"

class VoxelMap
{
public:
	polygon Polygon;
	
	float Maxlinelength = 350.0f;
	float Minlinelength = 50.0f;

	void UpdateShape()
	{
		bool Changing = false;/*
		while (Changing)
		{*/
			Changing = false;
			int indexesSize = Polygon.indexes.size();
			for (int i = 0; i < indexesSize; i++)
				if (i < Polygon.indexes.size())
				{
					int a = Polygon.indexes[i].x;
					int b = Polygon.indexes[i].y;
					int c = Polygon.indexes[i].z;
					if (sqrlength(Polygon.points[a] - Polygon.points[b]) > Maxlinelength * Maxlinelength)
					{
						Changing = true;

						glm::vec2 mid = (Polygon.points[a] + Polygon.points[b]) * 0.5f;

						Polygon.add_Point(mid, false);


						Polygon.indexes[i] = Polygon.indexes[Polygon.indexes.size() - 1];
						Polygon.indexes.pop_back();

						glm::ivec3 NewIndex1 = { a,c, Polygon.points.size() - 1 };
						glm::ivec3 NewIndex2 = { b,c, Polygon.points.size() - 1 };

						Polygon.indexes.push_back(NewIndex1);
						Polygon.indexes.push_back(NewIndex2);
					}
					else if (sqrlength(Polygon.points[a] - Polygon.points[c]) > Maxlinelength * Maxlinelength)
					{
						Changing = true;

						glm::vec2 mid = (Polygon.points[a] + Polygon.points[c]) * 0.5f;

						Polygon.add_Point(mid, false);

						Polygon.indexes[i] = Polygon.indexes[Polygon.indexes.size() - 1];
						Polygon.indexes.pop_back();

						glm::ivec3 NewIndex1 = { a,b, Polygon.points.size() - 1 };
						glm::ivec3 NewIndex2 = { c,b, Polygon.points.size() - 1 };

						Polygon.indexes.push_back(NewIndex1);
						Polygon.indexes.push_back(NewIndex2);
					}
					else if (sqrlength(Polygon.points[b] - Polygon.points[c]) > Maxlinelength * Maxlinelength)
					{
						Changing = true;

						glm::vec2 mid = (Polygon.points[b] + Polygon.points[c]) * 0.5f;

						Polygon.add_Point(mid, false);

						Polygon.indexes[i] = Polygon.indexes[Polygon.indexes.size() - 1];
						Polygon.indexes.pop_back();

						glm::ivec3 NewIndex1 = { b,a, Polygon.points.size() - 1 };
						glm::ivec3 NewIndex2 = { c,a, Polygon.points.size() - 1 };

						Polygon.indexes.push_back(NewIndex1);
						Polygon.indexes.push_back(NewIndex2);
					}
					else if (sqrlength(Polygon.points[a] - Polygon.points[b]) < Minlinelength * Minlinelength)
					{
						Changing = true;

						glm::vec2 mid = (Polygon.points[a] + Polygon.points[b]) * 0.5f;


						Polygon.points[b] = mid;


						Polygon.points[a] = Polygon.points[Polygon.points.size() - 1];
						Polygon.points.pop_back();

						for (int ind = 0; ind < Polygon.indexes.size(); ind++)
						{
							if (Polygon.indexes[ind].x == a)
								Polygon.indexes[ind].x = b;

							if (Polygon.indexes[ind].y == a)
								Polygon.indexes[ind].y = b;

							if (Polygon.indexes[ind].z == a)
								Polygon.indexes[ind].z = b;
						}

						Polygon.indexes[i] = Polygon.indexes[Polygon.indexes.size() - 1];
						Polygon.indexes.pop_back();
					}
					else if (sqrlength(Polygon.points[a] - Polygon.points[c]) < Minlinelength * Minlinelength)
					{
						Changing = true;

						glm::vec2 mid = (Polygon.points[a] + Polygon.points[c]) * 0.5f;


						Polygon.points[c] = mid;


						Polygon.points[a] = Polygon.points[Polygon.points.size() - 1];
						Polygon.points.pop_back();

						for (int ind = 0; ind < Polygon.indexes.size(); ind++)
						{
							if (Polygon.indexes[ind].x == a)
								Polygon.indexes[ind].x = c;

							if (Polygon.indexes[ind].y == a)
								Polygon.indexes[ind].y = c;

							if (Polygon.indexes[ind].z == a)
								Polygon.indexes[ind].z = c;
						}

						Polygon.indexes[i] = Polygon.indexes[Polygon.indexes.size() - 1];
						Polygon.indexes.pop_back();
					}
					else if (sqrlength(Polygon.points[b] - Polygon.points[c]) < Minlinelength * Minlinelength)
					{
						Changing = true;

						glm::vec2 mid = (Polygon.points[b] + Polygon.points[c]) * 0.5f;


						Polygon.points[c] = mid;


						Polygon.points[b] = Polygon.points[Polygon.points.size() - 1];
						Polygon.points.pop_back();

						for (int ind = 0; ind < Polygon.indexes.size(); ind++)
						{
							if (Polygon.indexes[ind].x == b)
								Polygon.indexes[ind].x = c;

							if (Polygon.indexes[ind].y == b)
								Polygon.indexes[ind].y = c;

							if (Polygon.indexes[ind].z == b)
								Polygon.indexes[ind].z = c;
						}

						Polygon.indexes[i] = Polygon.indexes[Polygon.indexes.size() - 1];
						Polygon.indexes.pop_back();
					}
				}
		//}

		Polygon.Update_Shape();
	}


	void DigSphere(glm::vec2 position, float r,float power = 1.0f)
	{
		for (int i = 0; i < Polygon.points.size(); i++)
			if (sqrlength(position - Polygon.points[i]) < r * r)
			{
				
				float ln = length(Polygon.points[i] - position);

				Polygon.points[i] += (Polygon.points[i] - position)/ln * (r-ln) * power;
			}

		UpdateShape();
	}

	void Draw()
	{
		Polygon.DrawTriangles();
	}




};

class application : public Engine
{
	VoxelMap VM;
	void On_Create() override
	{

		VM.Polygon.add_Point(glm::vec2( -100,-100), true);
		VM.Polygon.add_Point(glm::vec2( 100,-100), true);
		VM.Polygon.add_Point(glm::vec2( -100,100), true);
		VM.Polygon.add_Point(glm::vec2( 100,100), true);

		VM.UpdateShape();

	}
	void On_Update() override
	{
		if (buttons[GLFW_MOUSE_BUTTON_1])
			VM.DigSphere(MousePosition, 100);

		//VM.Polygon.DrawOutline();
		VM.Polygon.DrawTrianglesOutlines(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		VM.Draw();
	}
};
int main()
{
	application app;
	app.init();
	return 0;
}