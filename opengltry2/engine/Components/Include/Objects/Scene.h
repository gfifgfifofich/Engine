#pragma once



class miscPoint
{
public:
	int id = 0;
	glm::vec2 position = glm::vec2(0.0f);
};

class Scene
{
public:
	

	std::vector<polygon> polygons;
	std::vector<cube> cubes;
	std::vector<ball> balls;
	std::vector<miscPoint> points;
	std::vector<Texture> Textures;
	std::vector<Texture> NormalMaps;
	std::vector<ParticleEmiter> ParticleEmiters;
	std::vector<LightSource> LightSources;
	std::vector<Shader> Shaders;

	void SaveAs(std::string filename);
	void LoadFrom(std::string filename);
	void Rescale(glm::vec2 scale, int Z_Index = 0);
	void Draw(float dt = 0.017f);
	void DeleteNormalMaps();
	void DeleteTextures();
	void ReloadTextures();
};

