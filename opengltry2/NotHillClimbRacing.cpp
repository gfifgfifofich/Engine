#include "engine/Components/Engine.h"
#define max




const int WorldSizeX = 500;
const int WorldSizeY = 1;

float Noize1[WorldSizeX][WorldSizeY];
float Noize2[WorldSizeX][WorldSizeY];
float BufferNoize[WorldSizeX][WorldSizeY];


float mod = 1000.0f;
float modx = 100.0f;
int  Smoooothness =20;


int Stage = 1;

ParticleEmiter Sparker;



class ICE
{
public:
	class Cylinder
	{
	public:
		unsigned int sound;
		unsigned int soundsource;


		float ActiveRot = 0.0f;// 0 to 4*pi
		float ActivePeriod = pi;// 0 to 4*pi

		float offset = 0.0f;
		
		float force = 100.0f;
		float idleforce = -0.001f;

		bool idleState = false;
		void ready(unsigned int* sound)
		{
			GenSource(&soundsource);
			SetSourceSound(&soundsource, sound);
		}
		float Process(float rotation, bool fire)
		{
			if (fire) 
			{
				rotation -= offset;
				if (rotation >= ActiveRot && rotation <= ActivePeriod)
				{
					if (idleState)
					{
						idleState = false;
						PlaySource(&soundsource);
					}
					return (ActivePeriod - rotation) / ActivePeriod * force;
				}
				else
				{
					idleState = true;
					return force * idleforce;
				}
			}
			else return force* idleforce;
		}
	};
	float rotation=0.0f;
	float rotationVelocity=0.0f;
	std::vector<Cylinder> Cylinders;
	
	float ForceMult = 4000.0f;

	float frictionP = 0.001f;// in percents
	float frictionC = 1.0f;// constant

	bool ignited = false;

	int substeps = 8;

	float shaftRad = 30.0f;
	float cylinderOffset = 40.0f;

	glm::vec2 EngPos = glm::vec2(0.0f);

	glm::vec2 SoundPos = glm::vec2(0.0f);

	void AddCylinder(float offset = 0.0f)
	{
		Cylinder c;
		c.offset = offset;
		Cylinders.push_back(c);
	}

	void init(unsigned int*Sound)
	{
		for (int i = 0; i < Cylinders.size(); i++)
			Cylinders[i].ready(Sound);
	}

	void Draw()
	{
		for (int i = 0; i < Cylinders.size(); i++)
		{
			float sine = sin(rotation + Cylinders[i].offset);

			glm::vec2 point1 = EngPos + glm::vec2(cylinderOffset*i,  sine * shaftRad - 200);
			glm::vec2 point2 = EngPos + glm::vec2(cylinderOffset * i, sine * shaftRad);



			DrawLine(point1, point2, 15);
		}
	}

	void Process(float dt)
	{

		for (int i = 0; i < Cylinders.size(); i++)
			SetSourcePosition(&Cylinders[i].soundsource, glm::vec3(SoundPos,0.0f));
		dt /= substeps;
		for (int s = 0; s < substeps; s++)
		{
			rotation += rotationVelocity * dt;
			float f = 0.0f;
			for (int i = 0; i < Cylinders.size(); i++)
				f += Cylinders[i].Process(rotation, ignited)*dt;
			
			if (rotationVelocity < 0.0f)
				f *= -1.0f;

			rotationVelocity += f * dt * ForceMult;
			float constforce = frictionC * dt;
			if (rotationVelocity < 0.0f)
				constforce *= -1.0f;
			rotationVelocity -= constforce + rotationVelocity * frictionP * dt;

			if (rotation > pi * 4.0f)
				rotation = 0.0f;
			if (rotation < 0.0f)
				rotation = 0.0f;
		}


	}

};


void UpdateWorld()
{
	for (int i = 0; i < WorldSizeX; i++) BufferNoize[i][0] = Noize1[i][0];// Store last piece in buffer

	//Perlin noize
		//generate white noise
	for (int i = 1; i > 0; i--)
		for (int x = 0; x < WorldSizeX / (i); x++)
			for (int y = 0; y < WorldSizeY / (i); y++)
			{
				float noise = float(rand() % 10) / (15 + i);
				for (int px = 0; px < i; px++)
					for (int py = 0; py < i; py++)
						Noize1[(x * i) + px][(y * i) + py] = noise;
			}

	//Linearly interpolate values, for smoooooooooth
	for (int i = 0; i < Smoooothness; i++)
	{
		for (int x = 1; x < WorldSizeX - 1; x++)
			for (int y = 0; y < WorldSizeY; y++)
			{
				Noize2[x][y] = (Noize1[x - 1][y + 1] + Noize1[x][y + 1] + Noize1[x + 1][y + 1] +
					Noize1[x - 1][y] + Noize1[x][y] + Noize1[x + 1][y] +
					Noize1[x - 1][y - 1] + Noize1[x][y - 1] + Noize1[x + 1][y - 1]) / 9.0f;

			}
		for (int x = 0; x < WorldSizeX; x++)
			for (int y = 0; y < WorldSizeY; y++)
			{
				Noize1[x][y] = Noize2[x][y];
			}
	}


}

class application : public Engine
{
public:
	ball Wheel1;
	ball Wheel2;


	ball BodyPoint1;
	ball BodyPoint2;

	ICE engine;

	float springLength = 450;

	float leftWhellHeight = 200.0f;
	float rightWhellHeight = 200.0f;



	float springStiffness = 10.0f;
	float BodySpringsStiffnessa = 100.0f;
	float absorption = 0.2f;
	float BodyMass = 20.0f;
	float g = 100.0f;
	float dt = 20.0f;
	bool DrawMassPoints = false;
	bool SpeedCamera = false;
	bool Triangles = false;

	bool gearssettingswindow = false;

	float dino[100];
	glm::vec2 DinoDraingPosition = glm::vec2(-600, -500);

	float gears[5];
	int gear = 1;


	unsigned int ContainerTexture;
	unsigned int AwesomeTexture;

	unsigned int CarSoundSource;
	unsigned int CarSound;
	unsigned int CarSoundOverrunning;
	unsigned int VineBoom;

	bool EngRunning = false;

	void On_Create() override
	{//initialize
		LoadTexture("container.jpg", &ContainerTexture,4);
		LoadTexture("awesomeface.png", &AwesomeTexture,4);

		CarSound = LoadSound("Sounds/carenginesound.wav");
		CarSoundOverrunning = LoadSound("Sounds/overruning.wav");
		VineBoom = LoadSound("Sounds/VineBoom.wav");

		engine.AddCylinder(0.0f);
		engine.AddCylinder(0.5f*pi);

		engine.AddCylinder(1.0f*pi);
		engine.AddCylinder(1.5f * pi);

		engine.AddCylinder(2.0f * pi);
		engine.AddCylinder(2.5f * pi);

		engine.AddCylinder(3.0f * pi);
		engine.AddCylinder(3.5f * pi);

		engine.init(&VineBoom);

		GenSource(&CarSoundSource);

		SetSourceLooping(&CarSoundSource, true);
		SetSourceSound(&CarSoundSource, &CarSound);

		PlaySource(&CarSoundSource);

		gears[0] = -0.1;
		gears[1] = 0.1f;
		gears[2] = 0.25;
		gears[3] = 0.5;
		gears[4] = 0.75;


		//Perlin noize
		//generate white noise
		for (int i = 1; i > 0; i--)
			for (int x = 0; x < WorldSizeX / (i); x++)
				for (int y = 0; y < WorldSizeY / (i); y++)
				{
					float noise = float(rand() % 10) / (15 + i);
					for (int px = 0; px < i; px++)
						for (int py = 0; py < i; py++)
							Noize1[(x * i) + px][(y * i) + py] = noise;
				}

		//Linearly interpolate values, for smoooooooooth
		for (int i = 0; i < Smoooothness; i++)
		{
			for (int x = 1; x < WorldSizeX - 1; x++)
				for (int y = 0; y < WorldSizeY; y++)
				{
					Noize2[x][y] = (Noize1[x - 1][y + 1] + Noize1[x][y + 1] + Noize1[x + 1][y + 1] +
						Noize1[x - 1][y] + Noize1[x][y] + Noize1[x + 1][y] +
						Noize1[x - 1][y - 1] + Noize1[x][y - 1] + Noize1[x + 1][y - 1]) / 9.0f;

				}
			for (int x = 0; x < WorldSizeX; x++)
				for (int y = 0; y < WorldSizeY; y++)
				{
					Noize1[x][y] = Noize2[x][y];
					BufferNoize[x][y] = Noize2[x][y];
				}
		}


		//dino initialize
		dino[0] = 1.0f;
		dino[25] = 2.0f;
		dino[75] = 9.0f;
		dino[99] = 10.0f;
		for (int i = 1; i < 100; i++)
		{
			if (i < 25)dino[i] = LinearInterpolation(dino[0], dino[25], i * 0.04f);
			else if (i >= 25 && i <= 75)dino[i] = SmoothStep(dino[25], dino[75], (i - 25) * 0.02f);
			else dino[i] = LinearInterpolation(dino[75], dino[99], (i - 75) * 0.04f);
		}

		for (int i = 0; i < 100; i++)
			dino[i] *= 0.0005f;
		// particles
		Sparker.acceleration = glm::vec2(0.0f, 0.0f);
		Sparker.InitialVelocity = glm::vec2(0.0f, 0000.0f);
		Sparker.VelocityRandomness = glm::vec4(-10.0f, 10.0f, -1.0f,400.0f);
		Sparker.InitialOrbitalVelocity = 0.0f;
		Sparker.OrbitalVelocityRandomness = 0.1f;

		Sparker.lifetime = 0.2f;
		Sparker.lifetimeRandomness = 1.0f;

		Sparker.StartSize = glm::vec2(1.0f, 3.0f);
		Sparker.EndSize = glm::vec2(0.0f);

		Sparker.StartColor = glm::vec4(2.0f, 0.2f, 0.04f, 0.1f) * 10.0f;
		Sparker.EndColor = glm::vec4(1.0f, 0.2f, 0.04f, 0.0f) ;

		Sparker.InitialRotation = 0.0f;
		Sparker.RotationVelocity = 0.0f;
		Sparker.RotationRandomness = 0.0f;
		Sparker.RotationAcceleration = 0.0f;

		Sparker.Type = "LINE";
		ParticleEmiters.push_back(&Sparker);

		//wheels
		Wheel1.position = glm::vec2(500 + 3000, 300);
		Wheel1.mass = 1.0f;
		Wheel1.r = 70;
		Wheel1.roughness = 0.0f;

		Wheel2.position = glm::vec2(1000 + 3000, 300);
		Wheel2.mass = 1.0f;
		Wheel2.r = 70;
		Wheel2.roughness = 0.0f;



		//Balls above wheels
		BodyPoint1.position = glm::vec2(500 + 3000, 500);
		BodyPoint1.mass = 1.0f;
		BodyPoint1.r = 40;

		BodyPoint2.position = glm::vec2(1000 + 3000, 500);
		BodyPoint2.mass = 1.0f;
		BodyPoint2.r = 40;




		//Drawing order, (circles, then quads -> quads above circles)
		DrawingOrder = false;
	}
	void On_Update() override
	{



		UpdateListenerPosition();

		
		if (gearssettingswindow)
		{
			ImGui::Begin("Gears");

			ImGui::SliderFloat("Revers", &gears[0], -1.0f, 0.0f);
			ImGui::SliderFloat("1", &gears[1], 0.0f, 1.0f);
			ImGui::SliderFloat("2", &gears[2], 0.0f, 1.0f);
			ImGui::SliderFloat("3", &gears[3], 0.0f, 1.0f);
			ImGui::SliderFloat("4", &gears[4], 0.0f, 1.0f);
			ImGui::End();
		}


		//UI
		ImGui::Begin("Settings");
		ImGui::Text("engine.rotationVelocity %.3f", engine.rotationVelocity);
		ImGui::SliderFloat("Stiffness of SUSpension", &springStiffness, 0.0f, 100.0f);
		ImGui::SliderFloat("Stiffness of Body SUSpension", &BodySpringsStiffnessa, 0.0f, 100.0f);
		ImGui::SliderFloat("absorption", &absorption, 0.0f, 1.0f);
		ImGui::SliderFloat("Body Mass", &BodyMass, 0.0f, 300.0f);
		ImGui::SliderFloat("Gravity", &g, 0.0f, 100.0f);
		ImGui::SliderFloat("Delta", &dt, 0.0f, 100.0f);
		ImGui::SliderInt("Gear", &gear, 0, 4);
		ImGui::Checkbox("Draw Mass Points", &DrawMassPoints);
		ImGui::Checkbox("Speed Camera(Trippy most of the time)", &SpeedCamera);
		ImGui::Checkbox("Tweak gears", &gearssettingswindow);
		ImGui::Checkbox("Show Particles Settings", &Sparker.ShowWindow);

		BodyPoint1.mass = BodyMass;
		BodyPoint2.mass = BodyMass;

		Sparker.Spawn(glm::vec2(-10000, -100000));

		if (keys[GLFW_KEY_R]) gear = 0;
		if (keys[GLFW_KEY_1]) gear = 1;
		if (keys[GLFW_KEY_2]) gear = 2;
		if (keys[GLFW_KEY_3]) gear = 3;
		if (keys[GLFW_KEY_4]) gear = 4;


		engine.SoundPos = CameraPosition;
		if (engine.rotationVelocity < 1 * pi && keys[GLFW_KEY_LEFT_SHIFT])
			engine.rotationVelocity = 1 * pi;
		engine.Process(delta);


		if (keys[GLFW_KEY_D])
			engine.ignited = true;
		else
		{
			engine.ignited = false;
		}
		if (!keys[GLFW_KEY_LEFT_CONTROL]) 
		{
			float avgrot = ((engine.rotationVelocity) * 0.01f + abs(Wheel1.rotationVelocity)) * 0.5f;
			engine.rotationVelocity = avgrot * 100.0f;
			Wheel1.rotationVelocity = -avgrot;
		}


		engine.EngPos = CameraPosition + glm::vec2(1000.0f, -700.0f);

		engine.Draw();
		//inputs
	/*	float torque = 0.001f;
		float MaxRotationSpeed = -0.1f * pi * gears[gear];*/


		//if (Wheel1.rotationVelocity < MaxRotationSpeed && gear != 0)Wheel1.rotationVelocity = MaxRotationSpeed;
		//else if (Wheel1.rotationVelocity > -MaxRotationSpeed && gear != 0)Wheel1.rotationVelocity = -MaxRotationSpeed;

		//if (Wheel1.rotationVelocity > MaxRotationSpeed && gear == 0)Wheel1.rotationVelocity = MaxRotationSpeed;
		//else if (Wheel1.rotationVelocity < -MaxRotationSpeed && gear == 0)Wheel1.rotationVelocity = -MaxRotationSpeed;


		//if (Wheel2.rotationVelocity < MaxRotationSpeed && gear != 0)Wheel2.rotationVelocity = MaxRotationSpeed;
		//else if (Wheel2.rotationVelocity > -MaxRotationSpeed && gear != 0)Wheel2.rotationVelocity = -MaxRotationSpeed;

		//if (Wheel2.rotationVelocity > MaxRotationSpeed && gear == 0)Wheel2.rotationVelocity = MaxRotationSpeed;
		//else if (Wheel2.rotationVelocity < -MaxRotationSpeed && gear == 0)Wheel2.rotationVelocity = -MaxRotationSpeed;


		/*float DinoPosition = Wheel1.rotationVelocity / MaxRotationSpeed;
		int DinoPositionInt = DinoPosition * 100;

		if ((int)DinoPositionInt <= 0)DinoPositionInt = 1;
		if ((int)DinoPositionInt >= 100)DinoPositionInt = 99;

		float w = DinoPosition * 100 - DinoPositionInt;

		torque = -0.15f * LinearInterpolation(dino[DinoPositionInt - 1], dino[DinoPositionInt], w) / gears[gear];*/

		


		//if (gear == 0 && torque < 0.0f) torque = 0.0f;
		//else if (gear != 0 && torque > 0.0f) torque = 0.0f;

		//ImGui::Text("torque %.3f", torque * 1000);
		//ImGui::Text("Wheel1.rotationVelocity %.3f", DinoPosition * 1.0f);




		//if (keys[GLFW_KEY_LEFT_SHIFT])torque *= 2.0f;

		/*if (keys[GLFW_KEY_D])
		{

			Wheel1.rotationForce = torque * Wheel1.mass * 10.0f;
			if(!EngRunning)
			{
				SwapSourceSound(&CarSoundSource, &CarSound);
				EngRunning = true; 
			}
		}
		else 
		{

			Wheel1.rotationForce = 0.0f;

			Wheel1.rotationVelocity *= 0.99f;
			if (Wheel1.rotationVelocity < 0.001f && Wheel1.rotationVelocity > -0.001f)Wheel1.rotationVelocity = 0.0f;
			if (Wheel2.rotationVelocity < 0.001f && Wheel2.rotationVelocity > -0.001f)Wheel2.rotationVelocity = 0.0f;
			

			if (EngRunning)
			{
				SwapSourceSound(&CarSoundSource, &CarSoundOverrunning);
				EngRunning = false;
			}
		}*/

		//SetSourcePitch(&CarSoundSource, max(1.0f, abs(DinoPosition * 1.0f)));
		//SetSourcePosition(&CarSoundSource, glm::vec3(CameraPosition.x, CameraPosition.y, 0.0f));
		SetSourceGain(&CarSoundSource, 0.0f);


		Wheel1.bounciness = 0.0f;
		Wheel2.bounciness = 0.0f;

		float len = length(Wheel1.velocity);


		if (len > 14.0f && SpeedCamera) CameraScale = glm::vec2((1.0f / log(len * 0.2f)));
		else CameraScale = glm::vec2(1.0f);
		CameraScale *= 0.5f;


		if (keys[GLFW_KEY_LEFT])
		{
			leftWhellHeight = 300.0f;
		}
		if (keys[GLFW_KEY_RIGHT])
		{
			rightWhellHeight = 300.0f;
		}
		int substeps = 8;


		Wheel1.GroundVector = glm::vec2(0.0f, 0.0f);
		Wheel2.GroundVector = glm::vec2(0.0f, 0.0f);

		float subdt = (dt * 0.017) / substeps;

		for (int s = 0; s < substeps; s++)
		{
			Wheel1.Force = glm::vec2(0.0f);
			Wheel2.Force = glm::vec2(0.0f);

			BodyPoint1.Force = glm::vec2(0.0f);
			BodyPoint2.Force = glm::vec2(0.0f);

			if (keys[GLFW_KEY_SPACE])
			{
				Wheel1.rotationVelocity = 0.0f;
				Wheel2.rotationVelocity = 0.0f;
			}

			//if (Wheel1.rotationVelocity < MaxRotationSpeed && gear != 0)Wheel1.rotationVelocity = MaxRotationSpeed;
			//else if (Wheel1.rotationVelocity > MaxRotationSpeed && gear == 0)Wheel1.rotationVelocity = MaxRotationSpeed;

			//springs
			SpringBetweenBalls(&Wheel1, &Wheel2, springLength * 1.5f, springStiffness * subdt, absorption);
			SpringBetweenBalls(&BodyPoint1, &BodyPoint2, springLength, springStiffness * subdt, absorption);

			FixedSpringBetweenBalls(&Wheel1, &BodyPoint1, Rotate(GetNormal(Wheel2.position - Wheel1.position), -0.785) * leftWhellHeight, BodySpringsStiffnessa * subdt, absorption );
			FixedSpringBetweenBalls(&Wheel2, &BodyPoint2, Rotate(GetNormal(Wheel2.position - Wheel1.position), 0.785) * rightWhellHeight, BodySpringsStiffnessa * subdt, absorption );


			//for (int d = 0; d < 5; d++)
			for (int x = 1; x < WorldSizeX; x++)
			{

				DrawLine(glm::vec2(((float)(x + (Stage - 1) * WorldSizeX) - 1.0f) * modx, BufferNoize[x - 1][0] * mod), glm::vec2((float)(x + (Stage - 1) * WorldSizeX) * modx, BufferNoize[x][0] * mod), 10.0f);

				line l(glm::vec2(((float)(x + (Stage - 1) * WorldSizeX) - 1.0f) * modx, BufferNoize[x - 1][0] * mod), glm::vec2((float)(x + (Stage - 1) * WorldSizeX) * modx, BufferNoize[x][0] * mod));

				DrawCube(l.P1, glm::vec2(10.0f), glm::vec3(0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				BallToGroundLineCollision(&Wheel1, l);
				BallToGroundLineCollision(&Wheel2, l);

				DrawLine(glm::vec2(((float)(x + Stage * WorldSizeX) - 1.0f) * modx, Noize1[x - 1][0] * mod), glm::vec2((float)(x + Stage * WorldSizeX) * modx, Noize1[x][0] * mod), 10.0f);

				l = line(glm::vec2(((float)(x + Stage * WorldSizeX) - 1.0f) * modx, Noize1[x - 1][0] * mod), glm::vec2((float)(x + Stage * WorldSizeX) * modx, Noize1[x][0] * mod));

				BallToGroundLineCollision(&Wheel1, l);
				BallToGroundLineCollision(&Wheel2, l);

				DrawCube(l.P1, glm::vec2(10.0f), glm::vec3(0.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

			}


			

			//////gravity, after collisions
			//Wheel1.velocity *= 0.99f;
			//Wheel2.velocity *= 0.99f;
			Wheel1.Force.y -= g * subdt * Wheel1.mass;
			Wheel2.Force.y -= g * subdt * Wheel2.mass;
			BodyPoint1.Force.y -= g * subdt * BodyPoint1.mass;
			BodyPoint2.Force.y -= g * subdt * BodyPoint2.mass;
			

			// Wheels processing
			Wheel1.Process(subdt);
			Wheel2.Process(subdt);
			BodyPoint1.Process(subdt);
			BodyPoint2.Process(subdt);
			if (keys[GLFW_KEY_A])
			{
				Wheel1.rotationVelocity *= 0.99f;
				Wheel2.rotationVelocity *= 0.99f;
				if (Wheel1.rotationVelocity < 0.001f && Wheel1.rotationVelocity > -0.001f)Wheel1.rotationVelocity = 0.0f;
				if (Wheel2.rotationVelocity < 0.001f && Wheel2.rotationVelocity > -0.001f)Wheel2.rotationVelocity = 0.0f;
			}

			if (keys[GLFW_KEY_W])
			{
				Wheel1.position.y += 10;
				Wheel1.velocity.y = 10.0;
			}

		}

		// Update world
		if (CameraPosition.x - 1000.0f > Stage * modx * WorldSizeX)
		{
			Stage++;
			UpdateWorld();
		}
		//Camera
		CameraPosition = (BodyPoint1.position + BodyPoint2.position) * 0.5f;


		//Drawing


		// body of """""car"""""
		glm::vec2 mid = (BodyPoint1.position + BodyPoint2.position) * 0.5f;
		glm::vec2 dif = (BodyPoint1.position - BodyPoint2.position);
		DrawTexturedQuad(mid + Normalize(glm::vec2(dif.y, -dif.x))*300.0f,
			glm::vec2(410, 410), ContainerTexture, glm::vec3(0.0f, 0.0f, get_angle_between_points(BodyPoint1.position, BodyPoint2.position)) , glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		ImGui::Begin("Settings");
		ImGui::Text("rotation = %.3f", get_angle_between_points(BodyPoint1.position, BodyPoint2.position));

		DrawLine(Wheel1.position, (BodyPoint1.position * 0.75f + BodyPoint2.position * 0.25f), 3.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
		DrawLine(Wheel2.position, (BodyPoint1.position * 0.25f + BodyPoint2.position * 0.75f), 3.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

		//DrawTexturedQuad(glm::vec2(1000.0f, 500), glm::vec2(1000.0f), ContainerTexture, glm::vec3(0.0f), glm::vec4(1.0f));


		DrawBall(Wheel1);
		DrawBall(Wheel2);
		if (DrawMassPoints)
		{
			DrawBall(BodyPoint1);
			DrawBall(BodyPoint2);
		}

		// Engine torque
	/*	for (int i = 1; i < 100; i++)
		{
			glm::vec2 p1 = DinoDraingPosition + CameraPosition + glm::vec2((i - 1) * 15.0f, dino[i - 1] * 50000) - glm::vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
			glm::vec2 p2 = DinoDraingPosition + CameraPosition + glm::vec2(i * 15.0f, dino[i] * 50000) - glm::vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
			DrawLine(p1, p2, 2.0f);
			if (i == DinoPositionInt)
			{
				if (w < 0.0f) w = 0.0f;
				glm::vec2 pos = glm::vec2(LinearInterpolation(p1.x, p2.x, w), LinearInterpolation(p1.y, p2.y, w));

				DrawCircle(pos, 10, glm::vec4(1000.0f, 0.0f, 0.0f, 1.0f));
			}
		}*/




	}
};
int main()
{
	

	application app;


	

	app.init("app",1920,1050,false);
	return 0;
}


