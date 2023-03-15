// MEMORY LEACK in ParticleEmiter.Particles (only if initialized in class)
#pragma once
#include <execution>
// Contains and Process data for particles. Pushback ptr to ParticleEmiters array, or Process() somewhere else 
class ParticleEmiter
{
public:
	struct Particle
	{
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		float Rotation = 0.0f;
		float RotationVelocity = 0.0f;
		float time = 0.0f;
		float OrbitalVelocity = 0.0f;
		int id = 0;
	};

	struct influenceSphere
	{
		glm::vec2 position;
		float r;

		glm::vec2 velocity;
		bool attractive = false;
		float attractionStrength = 1.0f;
	};
	struct influenceCube
	{
		glm::vec2 position;
		glm::vec2 scale;

		glm::vec2 velocity;
		bool attractive = false;
		float attractionStrength = 1.0f;
	};
	struct EmitionPoint
	{
		glm::vec2 position = glm::vec2(0.0f);

		glm::vec2 velocity = glm::vec2(0.0f);
		int amount = 1;
		float tick = 0.017f;
		float t = 0.0f;
	};
	struct EmitionCircle
	{
		glm::vec2 position = glm::vec2(0.0f);
		float r;

		glm::vec2 velocity = glm::vec2(0.0f);
		int amount = 1;
		float tick = 0.017f;
		float t = 0.0f;
	};
	struct EmitionCube
	{
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 scale = glm::vec2(0.0f);

		glm::vec2 velocity = glm::vec2(0.0f);
		int amount = 1;
		float tick = 0.017f;
		float t = 0.0f;
	};
	struct LightSphere
	{
		glm::vec2 position = glm::vec2(0.0f);
		float r = 300.0f;

		glm::vec4 Color = glm::vec4(1.0f);
	};
	struct LightCube
	{
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 scale = glm::vec2(0.0f);

		glm::vec4 Color = glm::vec4(1.0f);
	};


	glm::vec2 acceleration = glm::vec2(0.0f);
	glm::vec2 InitialVelocity = glm::vec2(0.0f);
	glm::vec4 VelocityRandomness = glm::vec4(0.0f);// (-x,x,-y,y), rand from -x to x, from -y to y
	float VelocityDamper =0.0f;//"friction"

	glm::vec2 StartSize = glm::vec2(1.0f);
	glm::vec2 EndSize = glm::vec2(1.0f);

	glm::vec4 StartColor = glm::vec4(1.0f);
	glm::vec4 EndColor = glm::vec4(1.0f);
	
	// all rorations are only for QUAD's
	float InitialRotation = 0.0f;
	float RotationRandomness = 0.0f;
	float RotationVelocity = 0.0f;
	float RotationAcceleration = 0.0f;
	float RotationDamper = 0.0f;//"friction"
	
	float InitialOrbitalVelocity = 0.0f;
	float OrbitalVelocityRandomness = 0.0f;

	float lifetime = 1.0f;
	float lifetimeRandomness = 0.0f;
	std::vector <Particle> Particles;

	std::string Type = "QUAD";// QUAD, LINE, CIRCLE, TEXTURED ( for QUAD & TEXTURED - Size(width,height), Line - Size(length,width), Circle - Size(r,nothing))

	std::vector<unsigned int> textures;

	
	bool influenced = false;
	std::vector<influenceSphere> SpheresOfInfluence;
	std::vector<influenceCube> CubesOfInfluence;

	std::vector<EmitionPoint> EmitionPoints;// vec4(p.x,p.y,vel.x,vel.y);
	std::vector<EmitionCircle> EmitionCircles;
	std::vector<EmitionCube> EmitionCubes;

	bool lighted = false;
	std::vector<LightSphere> LightSpheres;
	std::vector<LightCube> LightCubes;



	
	int AddSpheresOfInfluence(glm::vec2 position, float r, glm::vec2 velocity, bool Attractive = false, float AttractionStrength = 1.0f)//returns index of created sphere
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

	int AddCubeOfInfluence(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, bool Attractive = false, float AttractionStrength = 1.0f)//returns index of created Cube
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
	int AddCubeEmiter(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, float amount, float tick)//returns index of created Cube
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
	int AddCircleEmiter(glm::vec2 position, glm::vec2 velocity, float r, float amount, float tick)//returns index of created Circle
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
	int AddPointEmiter(glm::vec2 position, glm::vec2 velocity, float amount, float tick)//returns index of created point
	{
		EmitionPoint a;

		a.position = position;
		a.velocity = velocity;
		a.amount = amount;
		a.tick = tick;
		EmitionPoints.push_back(a);
		return EmitionPoints.size() - 1;
	}

	int AddLightSphere(glm::vec2 position, float r, glm::vec4 Color = glm::vec4(1.0f))//returns index of created point
	{
		LightSphere a;
		a.position = position;
		a.r = r;
		a.Color = Color;
		LightSpheres.push_back(a);
		return LightSpheres.size() - 1;
	}
	int AddLightCube(glm::vec2 position, glm::vec2 scale, glm::vec4 Color = glm::vec4(1.0f))//returns index of created point
	{
		LightCube a;
		a.position = position;
		a.scale = scale;
		a.Color = Color;
		LightCubes.push_back(a);
		return LightCubes.size() - 1;
	}

	bool ShowWindow = false;

	int start = 0;
	int threadcount = std::thread::hardware_concurrency();
	float delta = 0.017f;
	void Process(float dt = 0.017f)
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

			ImGui::SliderFloat("VelocityDamper", &VelocityDamper,0,1.0f);

			vec[0] = StartSize.x;
			vec[1] = StartSize.y;
			ImGui::DragFloat2("StartSize", vec,0.1f);
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
			ImGui::SliderFloat("lifetimeRandomness", &lifetimeRandomness,0,1);

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

		if (Type == "CIRCLE")
		{
			start = Circletranslations.size();
			Circletranslations.resize(Circletranslations.size() + Particles.size());
			Circlecolors.resize(Circletranslations.size() + Particles.size());
		}
		else if (Type == "QUAD" || Type == "LINE")
		{
			start = Quadcolors.size();
			Quadcolors.resize(Quadcolors.size() + Particles.size());
			Quadtranslations.resize(Quadtranslations.size() + Particles.size());
		}
		if (Particles.size() > 30000 && Type != "TEXTURED")
		{
			std::for_each(std::execution::par, iter.begin(), iter.end(), [this](int thr)
				{
					int step = Particles.size() / threadcount;
					for (int i = thr * step; i < (thr + 1) * step; i++)
						if (i < Particles.size())
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
							Particles[i].time -= delta;

							Particles[i].Rotation += Particles[i].RotationVelocity;
							Particles[i].RotationVelocity += RotationAcceleration;
							Particles[i].RotationVelocity -= Particles[i].RotationVelocity * RotationDamper;
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
									glm::vec2 posdifference = CubesOfInfluence[s].position - Particles[i].position;

									if (posdifference.x > CubesOfInfluence[s].scale.x)
										posdifference.x = CubesOfInfluence[s].scale.x;
									else if (posdifference.x < -CubesOfInfluence[s].scale.x)
										posdifference.x = -CubesOfInfluence[s].scale.x;

									if (posdifference.y > CubesOfInfluence[s].scale.y)
										posdifference.y = CubesOfInfluence[s].scale.y;
									else if (posdifference.y < -CubesOfInfluence[s].scale.y)
										posdifference.y = -CubesOfInfluence[s].scale.y;

									if (sqrlength((CubesOfInfluence[s].position - posdifference) - Particles[i].position) < 0)
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
									if (Particles[i].position.x < LightCubes[s].position.x + LightCubes[s].scale.x * 0.5f &&
										Particles[i].position.x > LightCubes[s].position.x - LightCubes[s].scale.x * 0.5f &&
										Particles[i].position.y < LightCubes[s].position.y + LightCubes[s].scale.y * 0.5f &&
										Particles[i].position.y > LightCubes[s].position.y - LightCubes[s].scale.y * 0.5f)
									{

										float stage = (abs(Particles[i].position.x - LightCubes[s].position.x) + abs(Particles[i].position.y - LightCubes[s].position.y)) / (LightCubes[s].scale.x * 0.5f + LightCubes[s].scale.y * 0.5f);

										color.r += LightSpheres[s].Color.r * LightSpheres[s].Color.a * (0.5f - stage);
										color.g += LightSpheres[s].Color.g * LightSpheres[s].Color.a * (0.5f - stage);
										color.b += LightSpheres[s].Color.b * LightSpheres[s].Color.a * (0.5f - stage);
									}
								}
							}


							if (Type == "CIRCLE") {
								glm::vec2 position = Particles[i].position - CameraPosition;
								glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

								trans = glm::scale(trans, glm::vec3(Size.x * ScaleMultiplyer * CameraScale.x, Size.x * ScaleMultiplyer * CameraScale.y, 0.0f));
								Circletranslations[start + i] = trans;
								Circlecolors[start + i] = color;
							}
							else if (Type == "QUAD")
							{
								glm::vec2 position = Particles[i].position - CameraPosition;
								glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

								if (Particles[i].Rotation != 0)
									trans = glm::rotate(trans, Particles[i].Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
								trans = glm::scale(trans, glm::vec3(Size.x * CameraScale.x * ScaleMultiplyer, Size.y * CameraScale.y * ScaleMultiplyer, 0.0f));
								Quadtranslations[start + i] = trans;
								Quadcolors[start + i] = color;
							}
							else if (Type == "LINE")
							{

								glm::vec2 p1 = Particles[i].position;
								glm::vec2 p2 = Particles[i].position + Particles[i].velocity * Size.x * delta;
								glm::vec2 midpos = (p2 + p1) / 2.0f;
								float rotation = get_angle_between_points(p1, p2);
								glm::vec2 dif = p1 - p2;
								float length = sqrt(dif.x * dif.x + dif.y * dif.y) / (0.20 * 1280);

								glm::vec2 position = midpos - CameraPosition;
								glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

								if (rotation != 0)
									trans = glm::rotate(trans, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
								trans = glm::scale(trans, glm::vec3(length * 5.125f * 25 * CameraScale.x * ScaleMultiplyer, Size.y * CameraScale.x * ScaleMultiplyer, 0.0f));


								//DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);

								Quadtranslations[start + i] = trans;
								Quadcolors[start + i] = color;
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
				float stage = Particles[i].time / lifetime;

				glm::vec2 SizeDif = StartSize - EndSize;
				glm::vec4 ColorDif = StartColor - EndColor;

				glm::vec2 Size = EndSize + (SizeDif * stage);
				glm::vec4 color = EndColor + (ColorDif * stage);


				Particles[i].position += Particles[i].velocity * delta;
				Particles[i].velocity += acceleration * delta;
				Particles[i].velocity += glm::vec2(-Particles[i].velocity.y, Particles[i].velocity.x) * Particles[i].OrbitalVelocity * delta;
				Particles[i].velocity -= Particles[i].velocity * VelocityDamper * delta;
				Particles[i].time -= delta;

				Particles[i].Rotation += Particles[i].RotationVelocity;
				Particles[i].RotationVelocity += RotationAcceleration;
				Particles[i].RotationVelocity -= Particles[i].RotationVelocity * RotationDamper;

				if (influenced)
				{
					for (int s = 0; s < SpheresOfInfluence.size(); s++)
					{
						float dist = sqrlength(Particles[i].position - SpheresOfInfluence[s].position);
						if (dist < SpheresOfInfluence[s].r * SpheresOfInfluence[s].r)
						{
							Particles[i].velocity += SpheresOfInfluence[s].velocity * dt;
							if (SpheresOfInfluence[s].attractive)
								Particles[i].velocity +=  (SpheresOfInfluence[s].position - Particles[i].position)* SpheresOfInfluence[s].attractionStrength* dt;
						}
					}
					for (int s = 0; s < CubesOfInfluence.size(); s++)
					{
						glm::vec2 posdifference = CubesOfInfluence[s].position - Particles[i].position;

						if (posdifference.x > CubesOfInfluence[s].scale.x)
							posdifference.x = CubesOfInfluence[s].scale.x;
						else if (posdifference.x < -CubesOfInfluence[s].scale.x)
							posdifference.x = -CubesOfInfluence[s].scale.x;

						if (posdifference.y > CubesOfInfluence[s].scale.y)
							posdifference.y = CubesOfInfluence[s].scale.y;
						else if (posdifference.y < -CubesOfInfluence[s].scale.y)
							posdifference.y = -CubesOfInfluence[s].scale.y;

						if (sqrlength((CubesOfInfluence[s].position - posdifference) - Particles[i].position) < 0)
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
							color.r += LightSpheres[s].Color.r * LightSpheres[s].Color.a * (1.0f-dist) ;
							color.g += LightSpheres[s].Color.g * LightSpheres[s].Color.a * (1.0f-dist) ;
							color.b += LightSpheres[s].Color.b * LightSpheres[s].Color.a * (1.0f-dist) ;
						}
					}
					for (int s = 0; s < LightCubes.size(); s++)
					{
						if (Particles[i].position.x < LightCubes[s].position.x + LightCubes[s].scale.x * 0.5f&&
							Particles[i].position.x > LightCubes[s].position.x - LightCubes[s].scale.x * 0.5f&&
							Particles[i].position.y < LightCubes[s].position.y + LightCubes[s].scale.y * 0.5f&&
							Particles[i].position.y > LightCubes[s].position.y - LightCubes[s].scale.y * 0.5f)
						{

							float stage = (abs(Particles[i].position.x - LightCubes[s].position.x) + abs(Particles[i].position.y-LightCubes[s].position.y))/(LightCubes[s].scale.x*0.5f+ LightCubes[s].scale.y * 0.5f);

							color.r += LightSpheres[s].Color.r * LightSpheres[s].Color.a * (0.5f - stage);
							color.g += LightSpheres[s].Color.g * LightSpheres[s].Color.a * (0.5f - stage);
							color.b += LightSpheres[s].Color.b * LightSpheres[s].Color.a * (0.5f - stage);
						}
					}
				}
				if (Type == "CIRCLE") {
					glm::vec2 position = Particles[i].position - CameraPosition;
					glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

					trans = glm::scale(trans, glm::vec3(Size.x * ScaleMultiplyer * CameraScale.x, Size.x * ScaleMultiplyer * CameraScale.y, 0.0f));
					Circletranslations[start + i] = trans;
					Circlecolors[start + i] = color;
				}
				else if (Type == "QUAD")
				{
					glm::vec2 position = Particles[i].position - CameraPosition;
					glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

					if (Particles[i].Rotation != 0)
						trans = glm::rotate(trans, Particles[i].Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
					trans = glm::scale(trans, glm::vec3(Size.x * CameraScale.x * ScaleMultiplyer, Size.y * CameraScale.y * ScaleMultiplyer, 0.0f));
					Quadtranslations[start + i] = trans;
					Quadcolors[start + i] = color;
				}
				else if (Type == "LINE")
				{

					glm::vec2 p1 = Particles[i].position;
					glm::vec2 p2 = Particles[i].position + Particles[i].velocity * Size.x * delta;
					glm::vec2 midpos = (p2 + p1) / 2.0f;
					float rotation = get_angle_between_points(p1, p2);
					glm::vec2 dif = p1 - p2;
					float length = sqrt(dif.x * dif.x + dif.y * dif.y) / (0.20 * 1280);

					glm::vec2 position = midpos - CameraPosition;
					glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

					if (rotation != 0)
						trans = glm::rotate(trans, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
					trans = glm::scale(trans, glm::vec3(length * 5.125f * 25 * CameraScale.x * ScaleMultiplyer, Size.y * CameraScale.x * ScaleMultiplyer, 0.0f));


					//DrawCube(midpos, glm::vec2(length * 5.125f * 25, width), glm::vec3(0.0f, 0.0f, rotation), color);

					Quadtranslations[start + i] = trans;
					Quadcolors[start + i] = color;
				}
				else if (Type == "TEXTURED")
				{
					DrawTexturedQuad(Particles[i].position, Size, textures[Particles[i].id % textures.size()], glm::vec3(0.0f, 0.0f, Particles[i].Rotation), color);
				}
				/*if (Type == "QUAD")DrawCube(Particles[i].position, Sizes[i], glm::vec3(0.0f, 0.0f, Particles[i].Rotation), colors[i]);
				if (Type == "LINE")DrawLine(Particles[i].position, Particles[i].position - Particles[i].velocity * Sizes[i].x * delta, Sizes[i].y, colors[i]);
				if (Type == "CIRCLE")DrawCircle(Particles[i].position, Sizes[i].x, colors[i]);*/
			}
				
		for (int i = 0; i < Particles.size(); i++)
		{
			
			if (Particles[i].time <= 0.0f)
			{
				Particles[i] = Particles[Particles.size() - 1];
				Particles.pop_back();

			}
			
		}
	}
	void Spawn(glm::vec2 position,int amount = 1)
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
			if (int(OrbitalVelocityRandomness * 1000) != 0.0f) p.OrbitalVelocity += rand() % int(OrbitalVelocityRandomness*1000)/1000.0f - OrbitalVelocityRandomness * 0.5f;
			if (VelocityRandomness.y - VelocityRandomness.x != 0.0f)p.velocity.x += rand() % unsigned int(VelocityRandomness.y - VelocityRandomness.x) + VelocityRandomness.x;
			if (VelocityRandomness.w - VelocityRandomness.z != 0.0f)p.velocity.y += rand() % unsigned int(VelocityRandomness.w - VelocityRandomness.z) + VelocityRandomness.z;
			p.id = rand() % 100000;
			Particles.push_back(p);
		}
	}
	void Spawn(glm::vec2 position,glm::vec2 velocity, int amount = 1)
	{
		Particle p;
		for (int i = 0; i < amount; i++)
		{

			p.position = position;
			p.Rotation = InitialRotation;
			p.RotationVelocity = RotationVelocity;
			p.velocity = velocity;
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

};
