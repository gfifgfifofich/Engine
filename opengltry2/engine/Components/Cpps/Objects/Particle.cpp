// MEMORY LEACK in ParticleEmiter.Particles (only if initialized in class) //// probablu fixed idk



#include "../../Include/Helper.h"
#include "../../Include/Objects/Particle.h"

// Contains and Process data for particles. Pushback ptr to ParticleEmiters array, or Process() somewhere else 

int ParticleEmiter::AddSpheresOfInfluence(glm::vec2 position, float r, glm::vec2 velocity, bool Attractive, float AttractionStrength )//returns index of created sphere
{
	influenceSphere s;
	s.position = position;
	s.r = r;
	s.velocity = velocity;
	s.attractive = Attractive;
	s.attractionStrength = AttractionStrength;
	SpheresOfInfluence.push_back(s);
	return SpheresOfInfluence.size() - 1;
}

int ParticleEmiter::AddCubeOfInfluence(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, bool Attractive, float AttractionStrength)//returns index of created Cube
{
	influenceCube a;

	a.position = position;
	a.scale = scale;
	a.velocity = velocity;
	a.attractive = Attractive;
	a.attractionStrength = AttractionStrength;
	CubesOfInfluence.push_back(a);
	return CubesOfInfluence.size() - 1;
}
int ParticleEmiter::AddCubeEmiter(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, float amount, float tick)//returns index of created Cube
{
	EmitionCube a;

	a.position = position;
	a.scale = scale;
	a.velocity = velocity;
	a.amount = amount;
	a.tick = tick;
	EmitionCubes.push_back(a);
	return EmitionCubes.size() - 1;
}
int ParticleEmiter::AddCircleEmiter(glm::vec2 position, glm::vec2 velocity, float r, float amount, float tick)//returns index of created Circle
{
		EmitionCircle a;

		a.position = position;
		a.velocity = velocity;
		a.r = r;
		a.amount = amount;
		a.tick = tick;
		EmitionCircles.push_back(a);
		return EmitionCircles.size() - 1;
	}
int ParticleEmiter::AddPointEmiter(glm::vec2 position, glm::vec2 velocity, float amount, float tick)//returns index of created point
	{
		EmitionPoint a;

		a.position = position;
		a.velocity = velocity;
		a.amount = amount;
		a.tick = tick;
		EmitionPoints.push_back(a);
		return EmitionPoints.size() - 1;
	}

int ParticleEmiter::AddLightSphere(glm::vec2 position, float r, glm::vec4 Color)//returns index of created point
	{
		LightSphere a;
		a.position = position;
		a.r = r;
		a.Color = Color;
		LightSpheres.push_back(a);
		return LightSpheres.size() - 1;
	}
int ParticleEmiter::AddLightCube(glm::vec2 position, glm::vec2 scale, glm::vec4 Color)//returns index of created point
	{
		LightCube a;
		a.position = position;
		a.scale = scale;
		a.Color = Color;
		LightCubes.push_back(a);
		return LightCubes.size() - 1;
	}

void ParticleEmiter::Process(float dt)
	{
		delta = dt;


		if (ShowWindow)
		{

			ImGui::Begin("Particles");
			float vec[2];
			vec[0] = InitialVelocity.x;
			vec[1] = InitialVelocity.y;
			ImGui::DragFloat2("Initial velocity", vec);
			InitialVelocity.x = vec[0];
			InitialVelocity.y = vec[1];

			vec[0] = acceleration.x;
			vec[1] = acceleration.y;
			ImGui::DragFloat2("acceleration", vec);
			acceleration.x = vec[0];
			acceleration.y = vec[1];


			vec[0] = VelocityRandomness.x;
			vec[1] = VelocityRandomness.y;
			ImGui::DragFloat2("VelocityRandomness X", vec);
			VelocityRandomness.x = vec[0];
			VelocityRandomness.y = vec[1];

			vec[0] = VelocityRandomness.z;
			vec[1] = VelocityRandomness.w;
			ImGui::DragFloat2("VelocityRandomness Y", vec);
			VelocityRandomness.z = vec[0];
			VelocityRandomness.w = vec[1];

			ImGui::SliderFloat("VelocityDamper", &VelocityDamper, 0, 1.0f);

			vec[0] = StartSize.x;
			vec[1] = StartSize.y;
			ImGui::DragFloat2("StartSize", vec, 0.1f);
			StartSize.x = vec[0];
			StartSize.y = vec[1];

			vec[0] = EndSize.x;
			vec[1] = EndSize.y;
			ImGui::DragFloat2("EndSize", vec, 0.1f);
			EndSize.x = vec[0];
			EndSize.y = vec[1];

			float color[4];
			color[0] = StartColor.x;
			color[1] = StartColor.y;
			color[2] = StartColor.z;
			color[3] = StartColor.w;
			ImGui::ColorEdit4("StartColor", color);
			StartColor.x = color[0];
			StartColor.y = color[1];
			StartColor.z = color[2];
			StartColor.w = color[3];

			color[0] = EndColor.x;
			color[1] = EndColor.y;
			color[2] = EndColor.z;
			color[3] = EndColor.w;
			ImGui::ColorEdit4("EndColor", color);
			EndColor.x = color[0];
			EndColor.y = color[1];
			EndColor.z = color[2];
			EndColor.w = color[3];

			ImGui::DragFloat("InitialRotation", &InitialRotation, 0.01f);
			ImGui::DragFloat("RotationRandomness", &RotationRandomness, 0.01f);
			ImGui::DragFloat("RotationVelocity", &RotationVelocity, 0.01f);
			ImGui::DragFloat("RotationAcceleration", &RotationAcceleration, 0.01f);
			ImGui::DragFloat("RotationDamper", &RotationDamper, 0.01f);

			ImGui::DragFloat("InitialOrbitalVelocity", &InitialOrbitalVelocity, 0.01f);
			ImGui::DragFloat("OrbitalVelocityRandomness", &OrbitalVelocityRandomness, 0.01f);

			ImGui::DragFloat("lifetime", &lifetime, 0.1f);
			ImGui::SliderFloat("lifetimeRandomness", &lifetimeRandomness, 0, 1);
			ImGui::Checkbox("Influenced", &influenced);
			ImGui::Checkbox("Lighted", &lighted);
			ImGui::Checkbox("DrawToNormalMap", &DrawToNormalMap);
			ImGui::Checkbox("Additive", &Additive);


			ImGui::End();
		}
		for (int i = 0; i < EmitionPoints.size(); i++)
		{
			EmitionPoints[i].t += dt;
			if (EmitionPoints[i].t > EmitionPoints[i].tick)
			{
				EmitionPoints[i].t = 0.0f;
				Spawn(EmitionPoints[i].position, EmitionPoints[i].velocity, EmitionPoints[i].amount);
			}
		}
		for (int i = 0; i < EmitionCubes.size(); i++)
		{
			EmitionCubes[i].t += dt;
			if (EmitionCubes[i].t > EmitionCubes[i].tick)
			{
				EmitionCubes[i].t = 0.0f;
				for (int a = 0; a < EmitionCubes[i].amount; a++)
				{
					glm::vec2 pos = EmitionCubes[i].position;
					pos.x += rand() % (int)EmitionCubes[i].scale.x * 2.0f - EmitionCubes[i].scale.x;
					pos.y += rand() % (int)EmitionCubes[i].scale.y * 2.0f - EmitionCubes[i].scale.y;
					Spawn(pos, EmitionCubes[i].velocity);
				}
			}
		}
		for (int i = 0; i < EmitionCircles.size(); i++)
		{
			EmitionCircles[i].t += dt;
			if (EmitionCircles[i].t > EmitionCircles[i].tick)
			{
				EmitionCircles[i].t = 0.0f;
				for (int a = 0; a < EmitionCircles[i].amount; a++)
				{
					glm::vec2 pos = EmitionCircles[i].position;

					float Radius = rand() % (int)EmitionCircles[i].r;
					float angle = rand();
					pos += glm::vec2((cos(angle) - sin(angle)) * Radius, (cos(angle) + sin(angle)) * Radius);


					Spawn(pos, EmitionCircles[i].velocity);
				}
			}
		}

		std::vector <int> iter;
		iter.resize(threadcount);

		for (int i = 0; i < threadcount; i++)
			iter[i] = i;



		int SLI = FindSceneLayer(Z_Index, Additive);
		SceneLayerIndex = SLI;

		//std::cout << "Particle SLI = " << SLI << " Z_Index = " << SceneLayers[SLI].Z_Index<<" Name = "<<Name<<"\n";

		if (Type == "CIRCLE")
		{
			start = SceneLayers[SceneLayerIndex].CirclePosScale.size();
			SceneLayers[SceneLayerIndex].CirclePosScale.resize(SceneLayers[SceneLayerIndex].CirclePosScale.size() + Particles.size());
			SceneLayers[SceneLayerIndex].Circlecolors.resize(SceneLayers[SceneLayerIndex].Circlecolors.size() + Particles.size());
			SceneLayers[SceneLayerIndex].CircleRotations.resize(SceneLayers[SceneLayerIndex].CircleRotations.size() + Particles.size());
			if (DrawToNormalMap)
			{
				Normastart = SceneLayers[SceneLayerIndex].NormalMapCirclePosScale.size();
				SceneLayers[SceneLayerIndex].NormalMapCirclePosScale.resize(SceneLayers[SceneLayerIndex].NormalMapCirclePosScale.size() + Particles.size());
				SceneLayers[SceneLayerIndex].NormalMapCircleRotations.resize(SceneLayers[SceneLayerIndex].NormalMapCircleRotations.size() + Particles.size());
			}
		}
		else if (Type == "QUAD" || Type == "LINE")
		{
			start = SceneLayers[SceneLayerIndex].Quadcolors.size();
			SceneLayers[SceneLayerIndex].Quadcolors.resize(SceneLayers[SceneLayerIndex].Quadcolors.size() + Particles.size());
			SceneLayers[SceneLayerIndex].QuadPosScale.resize(SceneLayers[SceneLayerIndex].QuadPosScale.size() + Particles.size());
			SceneLayers[SceneLayerIndex].QuadRotations.resize(SceneLayers[SceneLayerIndex].QuadRotations.size() + Particles.size());
			if (DrawToNormalMap)
			{
				Normastart = SceneLayers[SceneLayerIndex].NormalMapCubePosScale.size();
				SceneLayers[SceneLayerIndex].NormalMapCubePosScale.resize(SceneLayers[SceneLayerIndex].NormalMapCubePosScale.size() + Particles.size());
				SceneLayers[SceneLayerIndex].NormalMapCubeRotations.resize(SceneLayers[SceneLayerIndex].NormalMapCubeRotations.size() + Particles.size());
			}
		}
		else if ((Type == "TEXTURED" || Type == "TEXTUREDLINE") && textures.size() > 0)
		{
			TextureStarts.resize(textures.size());
			for (int i = 0; i < textures.size(); i++)
			{
				int TQA = -1;
				unsigned int texture = textures[i];

				for (int i = 0; i < SceneLayers[SceneLayerIndex].TexturedQuads.size(); i++)
					if (SceneLayers[SceneLayerIndex].TexturedQuads[i].Texture == texture)
						TQA = i;
				if (TQA == -1)
				{
					TexturedQuadArray NewTQA;
					NewTQA.Texture = texture;
					SceneLayers[SceneLayerIndex].TexturedQuads.push_back(NewTQA);
					for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
						if (SceneLayers[SceneLayerIndex].TexturedQuads[i].Texture == texture)
							TQA = i;
				}
				TextureIndex = TQA;
				TextureStarts[i] = SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors.size();
				SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors.resize(SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors.size() + Particles.size());
				SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadPosScale.resize(SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadPosScale.size() + Particles.size());
				SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadRotations.resize(SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadRotations.size() + Particles.size());
			}

		}
		if (DrawToNormalMap)
		{
			if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
			{
				int TQA = -1;

				for (int i = 0; i < SceneLayers[SceneLayerIndex].NormalMaps.size(); i++)
					if (SceneLayers[SceneLayerIndex].NormalMaps[i].Texture == NormalMap)
						TQA = i;
				if (TQA == -1)
				{
					TexturedQuadArray NewTQA;
					NewTQA.Texture = NormalMap;
					SceneLayers[SceneLayerIndex].NormalMaps.push_back(NewTQA);
					for (int i = 0; i < SceneLayers[SceneLayerIndex].NormalMaps.size(); i++)
						if (SceneLayers[SceneLayerIndex].NormalMaps[i].Texture == NormalMap)
							TQA = i;
				}
				NormalMapIndex = TQA;

				Normastart = SceneLayers[SceneLayerIndex].NormalMaps[TQA].QuadPosScale.size();
				SceneLayers[SceneLayerIndex].NormalMaps[TQA].QuadPosScale.resize(SceneLayers[SceneLayerIndex].NormalMaps[TQA].QuadPosScale.size() + Particles.size());
				SceneLayers[SceneLayerIndex].NormalMaps[TQA].QuadRotations.resize(SceneLayers[SceneLayerIndex].NormalMaps[TQA].QuadPosScale.size() + Particles.size());
			}
			else if (NormalMap == CubeNormalMapTexture)
			{
				Normastart = SceneLayers[SceneLayerIndex].NormalMapCubePosScale.size();
				SceneLayers[SceneLayerIndex].NormalMapCubePosScale.resize(SceneLayers[SceneLayerIndex].NormalMapCubePosScale.size() + Particles.size());
				SceneLayers[SceneLayerIndex].NormalMapCubeRotations.resize(SceneLayers[SceneLayerIndex].NormalMapCubeRotations.size() + Particles.size());
			}
			else
			{
				Normastart = SceneLayers[SceneLayerIndex].NormalMapCirclePosScale.size();
				SceneLayers[SceneLayerIndex].NormalMapCirclePosScale.resize(SceneLayers[SceneLayerIndex].NormalMapCirclePosScale.size() + Particles.size());
				SceneLayers[SceneLayerIndex].NormalMapCircleRotations.resize(SceneLayers[SceneLayerIndex].NormalMapCircleRotations.size() + Particles.size());
			}

		}
		if (Particles.size() > 5000)
		{
			std::for_each(std::execution::par, iter.begin(), iter.end(), [this](int thr)
				{
					int step = Particles.size() / threadcount;
					for (int i = thr * step; i < (thr + 1) * step; i++)
						if (i < Particles.size())
						{
							Particles[i].time -= delta;
							if (Particles[i].time > 0.0f)
							{
								float stage = Particles[i].time / lifetime;

								glm::vec2 SizeDif = StartSize - EndSize;
								glm::vec4 ColorDif = StartColor - EndColor;

								glm::vec2 Size = EndSize + (SizeDif * stage);
								glm::vec4 color = EndColor + (ColorDif * stage);

								Particles[i].position += Particles[i].velocity * delta;
								Particles[i].velocity += acceleration * delta;
								Particles[i].velocity += glm::vec2(-Particles[i].velocity.y, Particles[i].velocity.x) * Particles[i].OrbitalVelocity * delta;
								Particles[i].velocity -= Particles[i].velocity * VelocityDamper * delta;

								Particles[i].Rotation += Particles[i].RotationVelocity * delta;
								Particles[i].RotationVelocity += RotationAcceleration * delta;
								Particles[i].RotationVelocity -= Particles[i].RotationVelocity * RotationDamper * delta;
								if (influenced)
								{
									for (int s = 0; s < SpheresOfInfluence.size(); s++)
									{
										float dist = sqrlength(Particles[i].position - SpheresOfInfluence[s].position);
										if (dist < SpheresOfInfluence[s].r * SpheresOfInfluence[s].r)
										{
											Particles[i].velocity += SpheresOfInfluence[s].velocity * delta;
											if (SpheresOfInfluence[s].attractive)
												Particles[i].velocity += (SpheresOfInfluence[s].position - Particles[i].position) * SpheresOfInfluence[s].attractionStrength * delta;
										}
									}
									for (int s = 0; s < CubesOfInfluence.size(); s++)
									{
										if (CubesOfInfluence[s].position.x + CubesOfInfluence[s].scale.x >= Particles[i].position.x &&
											CubesOfInfluence[s].position.x - CubesOfInfluence[s].scale.x <= Particles[i].position.x &&
											CubesOfInfluence[s].position.y + CubesOfInfluence[s].scale.y >= Particles[i].position.y &&
											CubesOfInfluence[s].position.y - CubesOfInfluence[s].scale.y <= Particles[i].position.y)
										{

											Particles[i].velocity += CubesOfInfluence[s].velocity * delta;
											if (CubesOfInfluence[s].attractive)
												Particles[i].velocity += (CubesOfInfluence[s].position - Particles[i].position) * CubesOfInfluence[s].attractionStrength * delta;
										}
									}
								}

								if (lighted)
								{
									for (int s = 0; s < LightSpheres.size(); s++)
									{
										float dist = sqrlength(Particles[i].position - LightSpheres[s].position);
										float rr = LightSpheres[s].r * LightSpheres[s].r;
										if (dist < rr)
										{
											dist /= rr;
											color.r += LightSpheres[s].Color.r * LightSpheres[s].Color.a * (1.0f - dist);
											color.g += LightSpheres[s].Color.g * LightSpheres[s].Color.a * (1.0f - dist);
											color.b += LightSpheres[s].Color.b * LightSpheres[s].Color.a * (1.0f - dist);
										}
									}
									for (int s = 0; s < LightCubes.size(); s++)
									{
										if (Particles[i].position.x < LightCubes[s].position.x + LightCubes[s].scale.x &&
											Particles[i].position.x > LightCubes[s].position.x - LightCubes[s].scale.x &&
											Particles[i].position.y < LightCubes[s].position.y + LightCubes[s].scale.y &&
											Particles[i].position.y > LightCubes[s].position.y - LightCubes[s].scale.y)
										{

											float stage = (abs(Particles[i].position.x - LightCubes[s].position.x) + abs(Particles[i].position.y - LightCubes[s].position.y)) / (LightCubes[s].scale.x * 0.5f + LightCubes[s].scale.y * 0.5f);
											if (stage > 1.0f)
												stage = 1.0f;
											color.r += LightCubes[s].Color.r * LightCubes[s].Color.a * (1.0f - stage);
											color.g += LightCubes[s].Color.g * LightCubes[s].Color.a * (1.0f - stage);
											color.b += LightCubes[s].Color.b * LightCubes[s].Color.a * (1.0f - stage);
										}
									}
								}


								if (Type == "CIRCLE") {

									float aspx = ScreenDivisorX * CameraScale.x;
									float aspy = ScreenDivisorY * CameraScale.y;

									glm::vec2 position = Particles[i].position - CameraPosition;
									position *= glm::vec2(aspx, aspy);


									SceneLayers[SceneLayerIndex].CirclePosScale[start + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
									SceneLayers[SceneLayerIndex].Circlecolors[start + i] = color;
									if (DrawToNormalMap)
									{
										if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = Particles[i].Rotation;
										}
										else if (NormalMap == CubeNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = Particles[i].Rotation;
										}
										else
										{
											SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = Particles[i].Rotation;
										}
									}
								}
								else if (Type == "QUAD")
								{
									float aspx = ScreenDivisorX * CameraScale.x;
									float aspy = ScreenDivisorY * CameraScale.y;

									glm::vec2 position = Particles[i].position - CameraPosition;
									position *= glm::vec2(aspx, aspy);




									SceneLayers[SceneLayerIndex].QuadPosScale[start + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
									SceneLayers[SceneLayerIndex].QuadRotations[start + i] = Particles[i].Rotation;
									SceneLayers[SceneLayerIndex].Quadcolors[start + i] = color;
									if (DrawToNormalMap)
									{
										if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = Particles[i].Rotation;
										}
										else if (NormalMap == CubeNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = Particles[i].Rotation;
										}
										else
										{
											SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = Particles[i].Rotation;
										}
									}

								}
								else if (Type == "LINE")
								{

									glm::vec2 p1 = Particles[i].position;
									glm::vec2 p2 = Particles[i].position + Particles[i].velocity * Size.y * delta;
									glm::vec2 midpos = (p2 + p1) / 2.0f;
									float rotation = get_angle_between_points(p1, p2);
									glm::vec2 dif = p1 - p2;
									float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;

									float aspx = ScreenDivisorX * CameraScale.x;
									float aspy = ScreenDivisorY * CameraScale.y;

									glm::vec2 position = midpos - CameraPosition;
									position *= glm::vec2(aspx, aspy);


									//DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);

									SceneLayers[SceneLayerIndex].QuadPosScale[start + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
									SceneLayers[SceneLayerIndex].QuadRotations[start + i] = rotation;
									SceneLayers[SceneLayerIndex].Quadcolors[start + i] = color;
									if (DrawToNormalMap)
									{
										if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = rotation;
										}
										else if (NormalMap == CubeNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = rotation;
										}
										else
										{
											SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = rotation;
										}
									}
								}
								else if (Type == "TEXTURED" && textures.size() > 0)
								{
									float aspx = ScreenDivisorX * CameraScale.x;
									float aspy = ScreenDivisorY * CameraScale.y;

									glm::vec2 position = Particles[i].position - CameraPosition;
									position *= glm::vec2(aspx, aspy);



									int SLI = -1;

									for (int i = 0; i < SceneLayers.size(); i++)
										if (SceneLayers[i].Z_Index == Z_Index)
											SLI = i;
									if (SLI == -1)
									{
										SceneLayer sl;
										sl.Z_Index = Z_Index;
										SceneLayers.push_back(sl);
										SortSceneLayers();
										for (int i = 0; i < SceneLayers.size(); i++)
											if (SceneLayers[i].Z_Index == Z_Index)
												SLI = i;
									}

									int TQA = -1;

									int TexIter = Particles[i].id % textures.size();
									unsigned int texture = textures[TexIter];

									for (int i = 0; i < SceneLayers[SceneLayerIndex].TexturedQuads.size(); i++)
										if (SceneLayers[SceneLayerIndex].TexturedQuads[i].Texture == texture)
											TQA = i;
									SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors[TextureStarts[TexIter] + i] = color;
									SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadPosScale[TextureStarts[TexIter] + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
									SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadRotations[TextureStarts[TexIter] + i] = Particles[i].Rotation;

									if (DrawToNormalMap)
									{
										if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = Particles[i].Rotation;
										}
										else if (NormalMap == CubeNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = Particles[i].Rotation;
										}
										else
										{
											SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = Particles[i].Rotation;
										}
									}
								}
								else if (Type == "TEXTUREDLINE" && textures.size() > 0)
								{

									glm::vec2 p1 = Particles[i].position;
									glm::vec2 p2 = Particles[i].position + Particles[i].velocity * Size.y * delta;
									glm::vec2 midpos = (p2 + p1) / 2.0f;
									float rotation = get_angle_between_points(p1, p2);
									glm::vec2 dif = p1 - p2;
									float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;


									float aspx = ScreenDivisorX * CameraScale.x;
									float aspy = ScreenDivisorY * CameraScale.y;
									glm::vec2 position = midpos - CameraPosition;
									position *= glm::vec2(aspx, aspy);
									//DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);


									int TQA = -1;
									int TexIter = Particles[i].id % textures.size();
									unsigned int texture = textures[TexIter];

									for (int i = 0; i < SceneLayers[SceneLayerIndex].TexturedQuads.size(); i++)
										if (SceneLayers[SceneLayerIndex].TexturedQuads[i].Texture == texture)
											TQA = i;

									SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors[TextureStarts[TexIter] + i] = color;
									SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadPosScale[TextureStarts[TexIter] + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
									SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadRotations[TextureStarts[TexIter] + i] = rotation;

									if (DrawToNormalMap)
									{
										if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = rotation;
										}
										else if (NormalMap == CubeNormalMapTexture)
										{
											SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = rotation;
										}
										else
										{
											SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
											SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = rotation;
										}
									}

								}
							}
							/*if (Type == "QUAD")DrawCube(Particles[i].position, Sizes[i], glm::vec3(0.0f, 0.0f, Particles[i].Rotation), colors[i]);
							if (Type == "LINE")DrawLine(Particles[i].position, Particles[i].position - Particles[i].velocity * Sizes[i].x * delta, Sizes[i].y, colors[i]);
							if (Type == "CIRCLE")DrawCircle(Particles[i].position, Sizes[i].x, colors[i]);*/
						}
				});
		}
		else
			for (int i = 0; i < Particles.size(); i++)
			{
				Particles[i].time -= delta;
				if (Particles[i].time > 0.0f)
				{
					float stage = Particles[i].time / lifetime;

					glm::vec2 SizeDif = StartSize - EndSize;
					glm::vec4 ColorDif = StartColor - EndColor;

					glm::vec2 Size = EndSize + (SizeDif * stage);
					glm::vec4 color = EndColor + (ColorDif * stage);



					Particles[i].position += Particles[i].velocity * delta;
					Particles[i].velocity += acceleration * delta;
					Particles[i].velocity += glm::vec2(-Particles[i].velocity.y, Particles[i].velocity.x) * Particles[i].OrbitalVelocity * delta;
					Particles[i].velocity -= Particles[i].velocity * VelocityDamper * delta;

					Particles[i].Rotation += Particles[i].RotationVelocity * delta;
					Particles[i].RotationVelocity += RotationAcceleration * delta;
					Particles[i].RotationVelocity -= Particles[i].RotationVelocity * RotationDamper * delta;

					if (influenced)
					{
						for (int s = 0; s < SpheresOfInfluence.size(); s++)
						{
							float dist = sqrlength(Particles[i].position - SpheresOfInfluence[s].position);
							if (dist < SpheresOfInfluence[s].r * SpheresOfInfluence[s].r)
							{
								Particles[i].velocity += SpheresOfInfluence[s].velocity * dt;
								if (SpheresOfInfluence[s].attractive)
									Particles[i].velocity += (SpheresOfInfluence[s].position - Particles[i].position) * SpheresOfInfluence[s].attractionStrength * dt;
							}
						}
						for (int s = 0; s < CubesOfInfluence.size(); s++)
						{


							if (CubesOfInfluence[s].position.x + CubesOfInfluence[s].scale.x >= Particles[i].position.x &&
								CubesOfInfluence[s].position.x - CubesOfInfluence[s].scale.x <= Particles[i].position.x &&
								CubesOfInfluence[s].position.y + CubesOfInfluence[s].scale.y >= Particles[i].position.y &&
								CubesOfInfluence[s].position.y - CubesOfInfluence[s].scale.y <= Particles[i].position.y)
							{

								Particles[i].velocity += CubesOfInfluence[s].velocity * dt;
								if (CubesOfInfluence[s].attractive)
									Particles[i].velocity += (CubesOfInfluence[s].position - Particles[i].position) * CubesOfInfluence[s].attractionStrength * dt;
							}
						}
					}
					if (lighted)
					{
						for (int s = 0; s < LightSpheres.size(); s++)
						{
							float dist = sqrlength(Particles[i].position - LightSpheres[s].position);
							float rr = LightSpheres[s].r * LightSpheres[s].r;
							if (dist < rr)
							{
								dist /= rr;
								color.r += LightSpheres[s].Color.r * LightSpheres[s].Color.a * (1.0f - dist);
								color.g += LightSpheres[s].Color.g * LightSpheres[s].Color.a * (1.0f - dist);
								color.b += LightSpheres[s].Color.b * LightSpheres[s].Color.a * (1.0f - dist);
							}
						}
						for (int s = 0; s < LightCubes.size(); s++)
						{
							if (Particles[i].position.x < LightCubes[s].position.x + LightCubes[s].scale.x &&
								Particles[i].position.x > LightCubes[s].position.x - LightCubes[s].scale.x &&
								Particles[i].position.y < LightCubes[s].position.y + LightCubes[s].scale.y &&
								Particles[i].position.y > LightCubes[s].position.y - LightCubes[s].scale.y)
							{

								float stage = (abs(Particles[i].position.x - LightCubes[s].position.x) + abs(Particles[i].position.y - LightCubes[s].position.y)) / (LightCubes[s].scale.x * 0.5f + LightCubes[s].scale.y * 0.5f);
								if (stage > 1.0f)
									stage = 1.0f;
								color.r += LightCubes[s].Color.r * LightCubes[s].Color.a * (1.0f - stage);
								color.g += LightCubes[s].Color.g * LightCubes[s].Color.a * (1.0f - stage);
								color.b += LightCubes[s].Color.b * LightCubes[s].Color.a * (1.0f - stage);
							}
						}
					}
					if (Type == "CIRCLE") {
						float aspx = ScreenDivisorX * CameraScale.x;
						float aspy = ScreenDivisorY * CameraScale.y;

						glm::vec2 position = Particles[i].position - CameraPosition;
						position *= glm::vec2(aspx, aspy);
						SceneLayers[SceneLayerIndex].CirclePosScale[start + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
						SceneLayers[SceneLayerIndex].Circlecolors[start + i] = color;
						if (DrawToNormalMap)
						{
							if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = Particles[i].Rotation;
							}
							else if (NormalMap == CubeNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = Particles[i].Rotation;
							}
							else
							{
								SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = Particles[i].Rotation;
							}
						}
					}
					else if (Type == "QUAD")
					{

						float aspx = ScreenDivisorX * CameraScale.x;
						float aspy = ScreenDivisorY * CameraScale.y;

						glm::vec2 position = Particles[i].position - CameraPosition;
						position *= glm::vec2(aspx, aspy);



						SceneLayers[SceneLayerIndex].QuadPosScale[start + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
						SceneLayers[SceneLayerIndex].QuadRotations[start + i] = Particles[i].Rotation;

						SceneLayers[SceneLayerIndex].Quadcolors[start + i] = color;
						if (DrawToNormalMap)
						{
							if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = Particles[i].Rotation;
							}
							else if (NormalMap == CubeNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = Particles[i].Rotation;
							}
							else
							{
								SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = Particles[i].Rotation;
							}
						}

					}
					else if (Type == "LINE")
					{

						glm::vec2 p1 = Particles[i].position;
						glm::vec2 p2 = Particles[i].position + Particles[i].velocity * Size.y * delta;
						glm::vec2 midpos = (p2 + p1) / 2.0f;
						float rotation = get_angle_between_points(p1, p2);
						glm::vec2 dif = p1 - p2;
						float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;


						float aspx = ScreenDivisorX * CameraScale.x;
						float aspy = ScreenDivisorY * CameraScale.y;
						glm::vec2 position = midpos - CameraPosition;
						position *= glm::vec2(aspx, aspy);
						//DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);

						SceneLayers[SceneLayerIndex].QuadPosScale[start + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
						SceneLayers[SceneLayerIndex].QuadRotations[start + i] = rotation;
						SceneLayers[SceneLayerIndex].Quadcolors[start + i] = color;
						if (DrawToNormalMap)
						{
							if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = rotation;
							}
							else if (NormalMap == CubeNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = rotation;
							}
							else
							{
								SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = rotation;
							}
						}
					}
					else if (Type == "TEXTURED" && textures.size() > 0)
					{
						float aspx = ScreenDivisorX * CameraScale.x;
						float aspy = ScreenDivisorY * CameraScale.y;

						glm::vec2 position = Particles[i].position - CameraPosition;
						position *= glm::vec2(aspx, aspy);
						int TQA = -1;
						int TexIter = Particles[i].id % textures.size();
						unsigned int texture = textures[TexIter];

						for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
							if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
								TQA = i;

						SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors[TextureStarts[TexIter] + i] = color;
						SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadPosScale[TextureStarts[TexIter] + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
						SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadRotations[TextureStarts[TexIter] + i] = Particles[i].Rotation;

						if (DrawToNormalMap)
						{
							if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = Particles[i].Rotation;
							}
							else if (NormalMap == CubeNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = Particles[i].Rotation;
							}
							else
							{
								SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, Size * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = Particles[i].Rotation;
							}
						}

					}
					else if (Type == "TEXTUREDLINE" && textures.size() > 0)
					{

						glm::vec2 p1 = Particles[i].position;
						glm::vec2 p2 = Particles[i].position + Particles[i].velocity * Size.y * delta;
						glm::vec2 midpos = (p2 + p1) / 2.0f;
						float rotation = get_angle_between_points(p1, p2);
						glm::vec2 dif = p1 - p2;
						float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;


						float aspx = ScreenDivisorX * CameraScale.x;
						float aspy = ScreenDivisorY * CameraScale.y;
						glm::vec2 position = midpos - CameraPosition;
						position *= glm::vec2(aspx, aspy);
						//DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);


						int TQA = -1;
						int TexIter = Particles[i].id % textures.size();
						unsigned int texture = textures[TexIter];

						for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
							if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
								TQA = i;

						SceneLayers[SceneLayerIndex].TexturedQuads[TQA].Quadcolors[TextureStarts[TexIter] + i] = color;
						SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadPosScale[TextureStarts[TexIter] + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
						SceneLayers[SceneLayerIndex].TexturedQuads[TQA].QuadRotations[TextureStarts[TexIter] + i] = rotation;

						if (DrawToNormalMap)
						{
							if (NormalMap != CubeNormalMapTexture && NormalMap != BallNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadPosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMaps[NormalMapIndex].QuadRotations[Normastart + i] = rotation;
							}
							else if (NormalMap == CubeNormalMapTexture)
							{
								SceneLayers[SceneLayerIndex].NormalMapCubePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCubeRotations[Normastart + i] = rotation;
							}
							else
							{
								SceneLayers[SceneLayerIndex].NormalMapCirclePosScale[Normastart + i] = glm::vec4(position, glm::vec2(Size.x, Size.y * length) * glm::vec2(aspx, aspy));
								SceneLayers[SceneLayerIndex].NormalMapCircleRotations[Normastart + i] = rotation;
							}
						}

					}
				}
				/*if (Type == "QUAD")DrawCube(Particles[i].position, Sizes[i], glm::vec3(0.0f, 0.0f, Particles[i].Rotation), colors[i]);
				if (Type == "LINE")DrawLine(Particles[i].position, Particles[i].position - Particles[i].velocity * Sizes[i].x * delta, Sizes[i].y, colors[i]);
				if (Type == "CIRCLE")DrawCircle(Particles[i].position, Sizes[i].x, colors[i]);*/
			}


		if (Particles.size() > 100000)
			for (int i = 0; i < Particles.size(); i++)
			{
				if (i < Particles.size() && Particles[i].time <= 0.0f)
				{
					Particles[i] = Particles[Particles.size() - 1];
					Particles.pop_back();
				}
			}
		else if (Particles.size() > 1)
		{
			int counter = 0;
			int i = Particles.size() - 1;
			int LastNonZero = Particles.size() - 1;

			while (i >= 0)
			{
				if (Particles[i].time <= 0.0f)
				{
					counter++;

					Particles[i] = Particles[LastNonZero];

					LastNonZero--;
				}
				i--;
			}
			if (counter == Particles.size())
				Particles.clear();
			else
				for (int i = 0; i < counter; i++)
					if (Particles.size() > 0)
						Particles.pop_back();
		}
		else if (Particles.size() == 1)
		{
			if (Particles[0].time <= 0.0f) Particles.clear();
		}
	}

void ParticleEmiter::Spawn(glm::vec2 position, int amount)
	{
		Particle p;
		for (int i = 0; i < amount; i++)
		{

			p.position = position;
			p.Rotation = InitialRotation;
			p.RotationVelocity = RotationVelocity;
			p.velocity = InitialVelocity;
			p.time = lifetime;
			p.OrbitalVelocity = InitialOrbitalVelocity;

			p.time += (lifetime * (rand() % int(1000) / 1000.0f) - lifetime * 1.0f) * lifetimeRandomness;
			if (int(RotationRandomness) != 0.0f) p.Rotation += rand() % int(RotationRandomness) - RotationRandomness * 0.5f;
			if (int(OrbitalVelocityRandomness * 1000) != 0.0f) p.OrbitalVelocity += rand() % int(OrbitalVelocityRandomness * 1000) / 1000.0f - OrbitalVelocityRandomness * 0.5f;
			if (VelocityRandomness.y - VelocityRandomness.x != 0.0f)p.velocity.x += rand() % unsigned int(VelocityRandomness.y - VelocityRandomness.x) + VelocityRandomness.x;
			if (VelocityRandomness.w - VelocityRandomness.z != 0.0f)p.velocity.y += rand() % unsigned int(VelocityRandomness.w - VelocityRandomness.z) + VelocityRandomness.z;
			p.id = rand() % 100000;
			Particles.push_back(p);
		}
	}
void ParticleEmiter::Spawn(glm::vec2 position, glm::vec2 velocity, int amount, float LifeTime)
	{
		Particle p;
		for (int i = 0; i < amount; i++)
		{

			p.position = position;
			p.Rotation = InitialRotation;
			p.RotationVelocity = RotationVelocity;
			p.velocity = velocity;
			if (LifeTime < 0.0f)
				p.time = lifetime;
			else
				p.time = LifeTime;
			p.OrbitalVelocity = InitialOrbitalVelocity;

			p.time += (lifetime * (rand() % int(1000) / 1000.0f) - lifetime * 1.0f) * lifetimeRandomness;
			if (int(RotationRandomness) != 0.0f) p.Rotation += rand() % int(RotationRandomness) - RotationRandomness * 0.5f;
			if (int(OrbitalVelocityRandomness * 1000) != 0.0f) p.OrbitalVelocity += rand() % int(OrbitalVelocityRandomness * 1000) / 1000.0f - OrbitalVelocityRandomness * 0.5f;
			if (VelocityRandomness.y - VelocityRandomness.x != 0.0f)p.velocity.x += rand() % unsigned int(VelocityRandomness.y - VelocityRandomness.x) + VelocityRandomness.x;
			if (VelocityRandomness.w - VelocityRandomness.z != 0.0f)p.velocity.y += rand() % unsigned int(VelocityRandomness.w - VelocityRandomness.z) + VelocityRandomness.z;
			p.id = rand() % 100000;
			Particles.push_back(p);
		}
	}
void ParticleEmiter::SpawnInCube(glm::vec2 position, glm::vec2 scale, int amount)
	{
		for (int a = 0; a < amount; a++)
		{
			glm::vec2 pos = position;
			if ((int)scale.x != 0)
				pos.x += rand() % (int)scale.x * 2.0f - scale.x;
			else
				pos.x = scale.x;
			if((int)scale.y!=0)
				pos.y += rand() % (int)scale.y * 2.0f - scale.y;
			else
				pos.y = scale.y;
			Spawn(pos, 1);
		}
	}
void ParticleEmiter::SpawnInCircle(glm::vec2 position, float r, int amount)
	{
		for (int a = 0; a < amount; a++)
		{
			glm::vec2 pos = position;

			float Radius = 1;
			if ((int)r != 0)
				Radius = rand() % (int)r * 0.5f;
			else
				Radius = rand() % 1 * 0.5f;

			float angle = rand();
			pos += glm::vec2((cos(angle) - sin(angle)) * Radius, (cos(angle) + sin(angle)) * Radius);

			Spawn(pos, 1);
		}

	}
void ParticleEmiter::SpawnInCircle(glm::vec2 position, float r, int amount, glm::vec2 velocity)
{
	for (int a = 0; a < amount; a++)
	{
		glm::vec2 pos = position;

		float Radius = 1;
		if ((int)r != 0)
			Radius = rand() % (int)r * 0.5f;
		else
			Radius = rand() % 1 * 0.5f;

		float angle = rand();
		pos += glm::vec2((cos(angle) - sin(angle)) * Radius, (cos(angle) + sin(angle)) * Radius);

		Spawn(pos, velocity, 1);
	}

}
