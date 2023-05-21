// MEMORY LEACK in ParticleEmiter.Particles

#pragma once

struct Particle
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	float Rotation = 0.0f;
	float RotationVelocity = 0.0f;
	float time = 0.0f;

};

// Contains and Process data for particles. Pushback ptr to ParticleEmiters array, or Process() somewhere else 
class ParticleEmiter
{
public:
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



	float lifetime = 1.0f;
	std::vector <Particle> Particles;

	std::string Type = "QUAD";// QUAD, LINE, CIRCLE ( for QUAD, Size(width,height), Line - Size(length,width), Circle - Size(r,0.0f))


	
	void Process()
	{
		for (int i = 0; i < Particles.size(); i++) 
		{

			if (i < Particles.size())
			{
				float stage = Particles[i].time / lifetime;

				glm::vec2 SizeDif = StartSize - EndSize;
				glm::vec4 ColorDif = StartColor - EndColor;

				glm::vec2 Size = EndSize + (SizeDif * stage);
				glm::vec4 color = EndColor + (ColorDif * stage);


				Particles[i].position += Particles[i].velocity * delta;
				Particles[i].velocity += acceleration * delta;
				Particles[i].velocity -= Particles[i].velocity* VelocityDamper;
				Particles[i].time -= delta;

				Particles[i].Rotation += Particles[i].RotationVelocity;
				Particles[i].RotationVelocity += RotationAcceleration;
				Particles[i].RotationVelocity -= Particles[i].RotationVelocity * RotationDamper;

				if(Type=="QUAD")DrawCube(Particles[i].position, Size,glm::vec3(0.0f,0.0f, Particles[i].Rotation), color);
				if(Type=="LINE")DrawLine(Particles[i].position, Particles[i].position - Particles[i].velocity * Size.x * delta, Size.y, color);
				if(Type=="CIRCLE")DrawCircle(Particles[i].position, Size.x, color);
			}
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
		p.position = position;
		p.Rotation = InitialRotation;
		p.RotationVelocity = RotationVelocity;
		p.velocity = InitialVelocity;
		p.time = lifetime;
		for (int i = 0; i < amount; i++) 
		{
			if (RotationRandomness != 0.0f) p.Rotation += rand() % int(RotationRandomness) - RotationRandomness * 0.5f;
			if (VelocityRandomness.y - VelocityRandomness.x != 0.0f)p.velocity.x += rand() % unsigned int(VelocityRandomness.y - VelocityRandomness.x) + VelocityRandomness.x;
			if (VelocityRandomness.w - VelocityRandomness.z != 0.0f)p.velocity.y += rand() % unsigned int(VelocityRandomness.w - VelocityRandomness.z) + VelocityRandomness.z;
			Particles.push_back(p);
		}
	}
};
