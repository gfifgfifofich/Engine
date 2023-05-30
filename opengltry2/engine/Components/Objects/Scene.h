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


	void SaveAs(std::string filename)
	{

		std::ofstream SaveFile(filename);
		for (int i = 0; i < balls.size(); i++)
		{
			SaveFile << "b";
			SaveFile << std::to_string(balls[i].position.x);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].position.y);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].r);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].rotation);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].Textureid);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].NormalMapId);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].Collision_Level);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].Collision_Mask);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].color.r);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].color.g);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].color.b);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].color.a);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].lighted);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].Z_Index);
			SaveFile << " ";
			SaveFile << std::to_string(balls[i].id);
			SaveFile << "\n";
		}
		for (int i = 0; i < cubes.size(); i++)
		{
			SaveFile << "c";
			SaveFile << std::to_string(cubes[i].position.x);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].position.y);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].width);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].height);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].Textureid);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].NormalMapId);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].Collision_Level);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].Collision_Mask);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].color.r);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].color.g);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].color.b);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].color.a);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].lighted);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].Z_Index);
			SaveFile << " ";
			SaveFile << std::to_string(cubes[i].id);
			SaveFile << "\n";
		}
		for (int i = 0; i < points.size(); i++)
		{
			SaveFile << "p";
			SaveFile << std::to_string(points[i].position.x);
			SaveFile << " ";
			SaveFile << std::to_string(points[i].position.y);
			SaveFile << " ";
			SaveFile << std::to_string(points[i].id);
			SaveFile << "\n";
		}
		for (int i = 0; i < Textures.size(); i++)
		{
			SaveFile << "t";
			SaveFile << std::to_string(Textures[i].id);
			SaveFile << " ";
			SaveFile << std::to_string(Textures[i].Type);
			SaveFile << " "; 
			SaveFile << Textures[i].FileName;
			SaveFile << "\n";
		}
		for (int i = 0; i < NormalMaps.size(); i++)
		{
			SaveFile << "N";
			SaveFile << std::to_string(NormalMaps[i].id);
			SaveFile << " ";
			SaveFile << std::to_string(NormalMaps[i].Type);
			SaveFile << " ";
			SaveFile << NormalMaps[i].FileName;
			SaveFile << "\n";
		}
		for (int i = 0; i < polygons.size(); i++)
		{
			SaveFile << "P";
			SaveFile << std::to_string(polygons[i].Textureid);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].NormalMapId);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].Collision_Level);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].Collision_Mask);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].colors[0].r);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].colors[0].g);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].colors[0].b);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].colors[0].a);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].lighted);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].Z_Index);
			SaveFile << " ";
			SaveFile << std::to_string(polygons[i].id);
			SaveFile << "\n";
			for (int p = 0; p < polygons[i].points.size(); p++)
			{
				SaveFile << "p";
				SaveFile << std::to_string(polygons[i].points[p].x);
				SaveFile << " ";
				SaveFile << std::to_string(polygons[i].points[p].y);
				SaveFile << "\n";
			}
			for (int p = 0; p < polygons[i].indexes.size(); p++)
			{
				SaveFile << "i";
				SaveFile << std::to_string(polygons[i].indexes[p].x);
				SaveFile << " ";
				SaveFile << std::to_string(polygons[i].indexes[p].y);
				SaveFile << " ";
				SaveFile << std::to_string(polygons[i].indexes[p].z);
				SaveFile << "\n";
			}
			for (int p = 0; p < polygons[i].TexturePoints.size(); p++)
			{
				SaveFile << "t";
				SaveFile << std::to_string(polygons[i].TexturePoints[p].x);
				SaveFile << " ";
				SaveFile << std::to_string(polygons[i].TexturePoints[p].y);
				SaveFile << "\n";
			}
			SaveFile << "E";
			SaveFile << "\n";

		}
		for (int i = 0; i < ParticleEmiters.size(); i++)
		{
			SaveFile << "e";
			SaveFile << std::to_string(ParticleEmiters[i].InitialRotation);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].RotationAcceleration);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].RotationDamper);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].RotationRandomness);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].RotationVelocity);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].VelocityDamper);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].InitialOrbitalVelocity);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].OrbitalVelocityRandomness);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].lifetime);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].lifetimeRandomness);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].lighted);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].influenced);
			SaveFile << " ";
			SaveFile << ParticleEmiters[i].Type;
			SaveFile << " ";
			SaveFile << ParticleEmiters[i].Name;
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].Z_Index);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].id);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].NormalMapid);
			SaveFile << "\n";


			SaveFile << "V";
			SaveFile << std::to_string(ParticleEmiters[i].acceleration.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].acceleration.y);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].InitialVelocity.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].InitialVelocity.y);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].VelocityRandomness.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].VelocityRandomness.y);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].VelocityRandomness.z);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].VelocityRandomness.w);
			SaveFile << "\n";

			SaveFile << "S";
			SaveFile << std::to_string(ParticleEmiters[i].StartSize.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].StartSize.y);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].EndSize.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].EndSize.y);
			SaveFile << "\n";

			SaveFile << "C";
			SaveFile << std::to_string(ParticleEmiters[i].StartColor.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].StartColor.y);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].StartColor.z);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].StartColor.w);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].EndColor.x);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].EndColor.y);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].EndColor.z);
			SaveFile << " ";
			SaveFile << std::to_string(ParticleEmiters[i].EndColor.w);
			SaveFile << "\n";
			for (int p = 0; p < ParticleEmiters[i].Textureids.size(); p++)
			{
				SaveFile << "t";
				SaveFile << std::to_string(ParticleEmiters[i].Textureids[p]);
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].SpheresOfInfluence.size(); p++)
			{
				SaveFile << "SI";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].velocity.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].velocity.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].r);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].attractive);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].SpheresOfInfluence[p].attractionStrength);
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].CubesOfInfluence.size(); p++)
			{
				SaveFile << "CI";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].velocity.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].velocity.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].scale.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].scale.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].attractive);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].CubesOfInfluence[p].attractionStrength);
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].EmitionPoints.size(); p++)
			{
				SaveFile << "EP";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionPoints[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionPoints[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionPoints[p].velocity.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionPoints[p].velocity.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionPoints[p].amount);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionPoints[p].tick);
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].EmitionCircles.size(); p++)
			{
				SaveFile << "ES";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].velocity.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].velocity.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].r);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].amount);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCircles[p].tick);
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].EmitionCubes.size(); p++)
			{
				SaveFile << "EC";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].velocity.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].velocity.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].scale.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].scale.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].amount);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].EmitionCubes[p].tick);
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].LightSpheres.size(); p++)
			{
				SaveFile << "LS";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].r);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].Color.r);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].Color.g);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].Color.b);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightSpheres[p].Color.a);
				SaveFile << " ";
				SaveFile << "\n";
			}
			for (int p = 0; p < ParticleEmiters[i].LightCubes.size(); p++)
			{
				SaveFile << "LC";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].position.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].position.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].scale.x);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].scale.y);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].Color.r);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].Color.g);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].Color.b);
				SaveFile << " ";
				SaveFile << std::to_string(ParticleEmiters[i].LightCubes[p].Color.a);
				SaveFile << " ";
				SaveFile << "\n";
			}
			SaveFile << "E";
			SaveFile << "\n";
		}
		for (int i = 0; i < LightSources.size(); i++)
		{
			SaveFile << "LS";
			SaveFile << std::to_string(LightSources[i].position.x);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].position.y);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].scale.x);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].scale.y);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].volume);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].color.x);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].color.y);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].color.z);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].color.w);
			SaveFile << " ";
			SaveFile << std::to_string(LightSources[i].TextureId);
			SaveFile << " ";
			SaveFile <<	LightSources[i].name;
			SaveFile << " ";
			SaveFile << "\n";
		}




		/*float a = 10;
		char* b = new char[sizeof(a)];
		memcpy(b, (const void*)&a, sizeof(a));


		

		SaveFile << "F2 ";
		for (int i = 0; i < sizeof(a); i++)
			SaveFile << b[i];
		for (int i = 0; i < sizeof(a); i++)
			SaveFile << b[i];
		SaveFile << "\n";*/

		SaveFile.close();
	}

	void LoadFrom(std::string filename)
	{
		DeleteTextures();
		DeleteNormalMaps();
		balls.clear();
		cubes.clear();
		Textures.clear();
		NormalMaps.clear();
		points.clear();
		polygons.clear();
		ParticleEmiters.clear();
		LightSources.clear();

		bool readingPoly = false;
		bool readingParticle = false;
		polygon pol;
		ParticleEmiter part;

		std::ifstream f(filename);
		if (!f.is_open())
		{
			std::cerr << "ERROR LOADING MAP: Unable to load " << filename;
			return;
		}
		int i = 0;
		while (!f.eof())
		{

			char junk;
			char line[256];
			f.getline(line, 256);
			std::strstream s;
			s << line;

			/*if (line[0] == 'F' && line[1] == '1')
			{
				float c;
				memcpy(&c, (const void*)&line[3], 4);
				std::cout << c << "\n";
			}
			if (line[0] == 'F' && line[1] == '2')
			{
				float c[2];
				memcpy(c, (const void*)&line[3], 8);
				
				std::cout << c[0] << "\n";
				std::cout << c[1] << "\n";
			}*/

			if (line[0] == 'b' && !readingPoly && !readingParticle)
			{
				ball b;
				s >> junk >> b.position.x >> b.position.y >> b.r >> b.rotation >> b.Textureid>> b.NormalMapId >> b.Collision_Level >> b.Collision_Mask >> b.color.r >> b.color.g >> b.color.b >> b.color.a>> b.lighted>>b.Z_Index>>b.id;
				balls.push_back(b);
			}
			else if (line[0] == 'c' && !readingPoly && !readingParticle)
			{
				cube c;
				s >> junk >> c.position.x >> c.position.y >> c.width >> c.height >> c.Textureid >> c.NormalMapId >> c.Collision_Level >> c.Collision_Mask >> c.color.r >> c.color.g >> c.color.b >> c.color.a >> c.lighted >> c.Z_Index >> c.id;
				cubes.push_back(c);
			}
			else if (line[0] == 'p' && !readingPoly && !readingParticle)
			{
				miscPoint p;
				s >> junk >> p.position.x >> p.position.y >> p.id;
				points.push_back(p);
			}
			else if (line[0] == 't' && !readingPoly && !readingParticle)
			{
				Texture tex;
				s >> junk >> tex.id >> tex.Type >> tex.FileName;
				tex.texture = NULL;
				tex.Load();
				Textures.push_back(tex);
			}
			else if (line[0] == 'N' && !readingPoly && !readingParticle)
			{
				Texture tex;
				s >> junk >> tex.id >> tex.Type >> tex.FileName;
				tex.Load();
				NormalMaps.push_back(tex);
			}
			else if (line[0] == 'L' && line[1] == 'S' && !readingPoly && !readingParticle)
			{
				LightSource ls;
				s >> junk >> junk >> ls.position.x >> ls.position.y >> ls.scale.x >> ls.scale.y >> ls.volume >> ls.color.r >> ls.color.g >> ls.color.b >> ls.color.a >> ls.TextureId >> ls.name;
				LightSources.push_back(ls);
			}

			else if (line[0] == 'P' && !readingParticle)
			{
				readingPoly = true;
				s >> junk >> pol.Textureid >> pol.NormalMapId >> pol.Collision_Level >> pol.Collision_Mask >> pol.colors[0].r >> pol.colors[0].g >> pol.colors[0].b >> pol.colors[0].a >> pol.lighted >> pol.Z_Index >> pol.id;
			}

			else if (line[0] == 'e' && !readingPoly)
			{
				readingParticle = true;
				s >> junk  >>  part.InitialRotation >> part.RotationAcceleration >> part.RotationDamper >>
					part.RotationRandomness >> part.RotationVelocity >> part.VelocityDamper >>
					part.InitialOrbitalVelocity >> part.OrbitalVelocityRandomness >> part.lifetime >> part.lifetimeRandomness >>
					part.lighted >> part.influenced >> part.Type >> part.Name >> part.Z_Index >> part.id>> part.NormalMapid;
			}



			if (readingPoly)
			{

				if (line[0] == 'p')
				{

					glm::vec2 pnt;
					s >> junk >> pnt.x >> pnt.y;
					pol.points.push_back(pnt);
				}
				else if (line[0] == 'i')
				{

					glm::ivec3 ind;
					s >> junk >> ind.x >> ind.y >> ind.z;
					pol.indexes.push_back(ind);

				}
				else if (line[0] == 't')
				{

					glm::vec2 pnt;
					s >> junk >> pnt.x >> pnt.y;
					pol.TexturePoints.push_back(pnt);
				}
				else if (line[0] == 'E')
				{
					readingPoly = false;
					pol.Update_Shape();
					polygons.push_back(pol);
					polygon pp;
					pol = pp;
				}
			}

			if (readingParticle)
			{
				if (line[0] == 'V')
				{
					s >> junk >> part.acceleration.x >> part.acceleration.y >> part.InitialVelocity.x >> part.InitialVelocity.y
						>> part.VelocityRandomness.x >> part.VelocityRandomness.y >> part.VelocityRandomness.z >> part.VelocityRandomness.w;
				}
				else if (line[0] == 'S' && line[1]!='I')
				{
					s >> junk >>  part.StartSize.x >> part.StartSize.y >> part.EndSize.x >> part.EndSize.y;
				}
				else if (line[0] == 'C' && line[1] != 'I')
				{
					s >> junk >> part.StartColor.x >> part.StartColor.y >> part.StartColor.z >> part.StartColor.w
						>> part.EndColor.x >> part.EndColor.y >> part.EndColor.z >> part.EndColor.w;
				}
				else if (line[0] == 't')
				{
					int id;
					s >> junk >> id ;
					part.Textureids.push_back(id);
				}
				else if (line[0] == 'S' && line[1] == 'I')
				{
					glm::vec2 position;
					float r;
					glm::vec2 velocity;
					bool Attractive = false;
					float AttractionStrength = 1.0f;

					s >> junk >> junk >> position.x >> position.y >> velocity.x >> velocity.y
						>> r >> Attractive >> AttractionStrength;
					part.AddSpheresOfInfluence(position, r, velocity, Attractive, AttractionStrength);
				}
				else if (line[0] == 'C' && line[1] == 'I')
				{
					glm::vec2 position;
					glm::vec2 scale;
					glm::vec2 velocity;
					bool Attractive = false;
					float AttractionStrength = 1.0f;

					s >> junk >> junk >> position.x >> position.y >> velocity.x >> velocity.y
						>> scale.x >> scale.y >> Attractive >> AttractionStrength;
					part.AddCubeOfInfluence(position, scale, velocity, Attractive, AttractionStrength);
				}
				else if (line[0] == 'E' && line[1] == 'P')
				{
					glm::vec2 position;
					glm::vec2 velocity;
					int amount;
					float tick;

					s >> junk >> junk >> position.x >> position.y >> velocity.x >> velocity.y>> amount >> tick;
					part.AddPointEmiter(position,  velocity, amount, tick);
				}
				else if (line[0] == 'E' && line[1] == 'S')
				{
					glm::vec2 position;
					glm::vec2 velocity;
					float r;
					int amount;
					float tick;

					s >> junk >> junk >> position.x >> position.y >> velocity.x >> velocity.y
						>>r>> amount >> tick;
					part.AddCircleEmiter(position, velocity,r, amount, tick);
				}
				else if (line[0] == 'E' && line[1] == 'C')
				{
					glm::vec2 position;
					glm::vec2 velocity;
					glm::vec2 scale;
					int amount;
					float tick;

					s >> junk >> junk >> position.x >> position.y >> velocity.x >> velocity.y
						>> scale.x>>scale.y >> amount >> tick;
					part.AddCubeEmiter(position, scale, velocity, amount, tick);
				}
				else if (line[0] == 'L' && line[1] == 'S')
				{
					glm::vec2 position;
					float r;
					glm::vec4 color;

					s >> junk >> junk >> position.x >> position.y >> r
						>> color.x >> color.y >> color.z >> color.w;
					part.AddLightSphere(position,r,color);
				}
				else if (line[0] == 'L' && line[1] == 'S')
				{
					glm::vec2 position;
					glm::vec2 scale;
					glm::vec4 color;

					s >> junk >> junk >> position.x >> position.y >> scale.x>> scale.y
						>> color.x >> color.y >> color.z >> color.w;
					part.AddLightCube(position, scale, color);
				}
				else if (line[0] == 'E')
				{
					readingParticle = false;

					part.textures.clear();
					for (int i = 0; i < part.Textureids.size(); i++)
						part.textures.push_back(Textures[part.Textureids[i]].texture);

					ParticleEmiters.push_back(part);
					ParticleEmiter pt;
					part = pt;
				}
			}
		}

		f.close();
	}


	void Rescale(glm::vec2 scale, int Z_Index  =0)
	{
		for (int i = 0; i < points.size(); i++)
		{
			points[i].position.x *= scale.x;
			points[i].position.y *= scale.y;
		}
		for (int i = 0; i < balls.size(); i++)
		{
			balls[i].position *= scale; 
			balls[i].r *= scale.x;
			balls[i].Z_Index += Z_Index;
		}
		for (int i = 0; i < cubes.size(); i++)
		{
			cubes[i].position *= scale;
			cubes[i].width *= scale.x;
			cubes[i].height *= scale.x;
			cubes[i].Z_Index += Z_Index;
		}
		for (int i = 0; i < polygons.size(); i++)
		{
			for (int a = 0; a < polygons[i].points.size(); a++)
				polygons[i].points[a] *= scale;
			polygons[i].Z_Index += Z_Index;

		}
		for (int i = 0; i < ParticleEmiters.size(); i++)
		{/*
			ParticleEmiters[i].StartSize *= scale;
			ParticleEmiters[i].EndSize *= scale;
			ParticleEmiters[i].InitialVelocity *= scale;
			ParticleEmiters[i].VelocityRandomness.x *= scale.x;
			ParticleEmiters[i].VelocityRandomness.y *= scale.x;
			ParticleEmiters[i].VelocityRandomness.z *= scale.y;
			ParticleEmiters[i].VelocityRandomness.w *= scale.y;*/
			ParticleEmiters[i].Z_Index += Z_Index;

			for (int a = 0; a < ParticleEmiters[i].CubesOfInfluence.size(); a++)
			{
				ParticleEmiters[i].CubesOfInfluence[a].position *= scale;
				ParticleEmiters[i].CubesOfInfluence[a].scale *= scale;
				ParticleEmiters[i].CubesOfInfluence[a].velocity *= scale;
			}
			for (int a = 0; a < ParticleEmiters[i].EmitionCircles.size(); a++)
			{
				ParticleEmiters[i].EmitionCircles[a].position *= scale;
				ParticleEmiters[i].EmitionCircles[a].r *= scale.x;
				ParticleEmiters[i].EmitionCircles[a].velocity *= scale;
			}
			for (int a = 0; a < ParticleEmiters[i].EmitionCubes.size(); a++)
			{
				ParticleEmiters[i].EmitionCubes[a].position *= scale;
				ParticleEmiters[i].EmitionCubes[a].scale *= scale;
				ParticleEmiters[i].EmitionCubes[a].velocity *= scale;
			}
			for (int a = 0; a < ParticleEmiters[i].EmitionPoints.size(); a++)
			{
				ParticleEmiters[i].EmitionPoints[a].position *= scale;
				ParticleEmiters[i].EmitionPoints[a].velocity *= scale;
			}
			for (int a = 0; a < ParticleEmiters[i].LightCubes.size(); a++)
			{
				ParticleEmiters[i].LightCubes[a].position *= scale;
				ParticleEmiters[i].LightCubes[a].scale *= scale;
			}
			for (int a = 0; a < ParticleEmiters[i].LightSpheres.size(); a++)
			{
				ParticleEmiters[i].LightSpheres[a].position *= scale;
				ParticleEmiters[i].LightSpheres[a].r *= scale.x;
			}
			for (int a = 0; a < ParticleEmiters[i].SpheresOfInfluence.size(); a++)
			{
				ParticleEmiters[i].SpheresOfInfluence[a].position *= scale;
				ParticleEmiters[i].SpheresOfInfluence[a].r *= scale.x;
				ParticleEmiters[i].SpheresOfInfluence[a].velocity *= scale;
			}
		}


		for (int i = 0; i < LightSources.size(); i++)
		{
			LightSources[i].position *= scale;
			LightSources[i].scale *= scale;

		}
	}

	void Draw()
	{


		for (int i = 0; i < balls.size(); i++)
		{
			unsigned int NM = NULL;
			if (balls[i].lighted)
			{
				if (balls[i].NormalMapId > -1 && balls[i].NormalMapId < NormalMaps.size())
					NM = NormalMaps[balls[i].NormalMapId].texture;
				else NM = BallNormalMapTexture;
			}
			if (balls[i].Textureid == -1)
				DrawCircle(balls[i], balls[i].color, balls[i].lighted, NM, balls[i].Z_Index);
			else
				DrawTexturedQuad(balls[i].position, glm::vec2(balls[i].r), Textures[balls[i].Textureid].texture, balls[i].rotation, balls[i].color, balls[i].Z_Index, NM);
		}
		for (int i = 0; i < cubes.size(); i++)
		{
			unsigned int NM = NULL;
			if (cubes[i].lighted) 
			{
				if (cubes[i].NormalMapId > -1 && cubes[i].NormalMapId < NormalMaps.size())
					NM = NormalMaps[cubes[i].NormalMapId].texture;
				else NM = CubeNormalMapTexture;
			}
			if (cubes[i].Textureid == -1)
				DrawCube(cubes[i], cubes[i].color,0.0f, cubes[i].lighted, NM, cubes[i].Z_Index);
			else
				DrawTexturedQuad(cubes[i], Textures[cubes[i].Textureid].texture, cubes[i].color,0.0f, cubes[i].Z_Index, NM);
		}
		for (int i = 0; i < polygons.size(); i++)
		{

			if (polygons[i].Textureid == -1)
			{
				polygons[i].Texture = NULL;
				polygons[i].DrawTriangles();
			}
			else
			{
				polygons[i].Texture = Textures[polygons[i].Textureid].texture;
				polygons[i].DrawTriangles();
			}
		}
		for (int i = 0; i < ParticleEmiters.size(); i++)
		{
			unsigned int NM = NULL;
			if (ParticleEmiters[i].DrawToNormalMap)
			{
				if (ParticleEmiters[i].NormalMapid > -1 && ParticleEmiters[i].NormalMapid < NormalMaps.size())
					NM = NormalMaps[ParticleEmiters[i].NormalMapid].texture;
				else NM = CubeNormalMapTexture;

				ParticleEmiters[i].NormalMap = NM;
			}

			ParticleEmiters[i].Process(delta);
		}


		for (int i = 0; i < LightSources.size(); i++)
		{
			unsigned int t = LightSphereTexture;

			if(LightSources[i].TextureId <=0)
				DrawLight(LightSources[i].position, LightSources[i].scale, LightSources[i].color, LightSources[i].volume,t);
			else if (LightSources[i].TextureId > 0)
			{
				t = Textures[LightSources[i].TextureId].texture;
				DrawLight(LightSources[i].position, LightSources[i].scale, LightSources[i].color, LightSources[i].volume, t);
			}

		}
	}
	void DeleteNormalMaps()
	{
		for (int i = 0; i < NormalMaps.size(); i++)
		{
			glDeleteTextures(1, &NormalMaps[i].texture);
			NormalMaps[i].texture = NULL;
		}
	}
	void DeleteTextures()
	{
		for (int i = 0; i < Textures.size(); i++)
		{
			glDeleteTextures(1, &Textures[i].texture);
			Textures[i].texture = NULL;
		}
	}
	void ReloadTextures()
	{
		DeleteTextures();
		for (int i = 0; i < Textures.size(); i++)
		{
			Textures[i].Load();
		}
	}
};

