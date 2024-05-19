#pragma once

class Scene
{
	bool firstframe = true;
public:
	bool DrawCollisions = true;
	bool DrawRegularScene = true;
	

	std::vector<polygon*> Collision_polygons;
	std::vector<cube*> Collision_cubes;
	std::vector<ball*> Collision_balls;

	std::vector<Node*> Nodes;
	std::vector<Asset*> Assets;


	void SaveAs(std::string filename);
	void LoadFrom(std::string filename);
	void Rescale(glm::vec2 scale, int Z_Index = 0);

	void Update();
	void Process(float dt = 0.017f);
	void Draw(float dt = 0.017f);
	
	void DeleteNormalMaps();
	void DeleteTextures();
	void ReloadTextures();
};

inline Scene* SceneInProcess = NULL;