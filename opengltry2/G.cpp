#include "engine/Components/Engine.h"

ParticleEmiter Sparker;

float g = 100.0f;
cube c;

glm::vec2 prevpos = glm::vec2(0.0f);

int mouseSphere;

unsigned int noize;

int test = 0;
int amount = 0;


void On_Create()
{


	GenNoizeTexture(&noize, 100);
	// particles
	Sparker.acceleration = glm::vec2(0.0f, 0.0f);
	Sparker.InitialVelocity = glm::vec2(0.0f, 0.0f);
	Sparker.VelocityRandomness = glm::vec4(-100.0f, 100.0f, -100.0f, 100.0f);
	Sparker.InitialOrbitalVelocity = 0.0f;
	Sparker.OrbitalVelocityRandomness = 0.1f;

	Sparker.lifetime = 0.5f;
	Sparker.lifetimeRandomness = 1.0f;

	Sparker.StartSize = glm::vec2(5.0f, 2.0f);
	Sparker.EndSize = glm::vec2(0.0f);

	Sparker.StartColor = glm::vec4(10.0f, 2.0f, 0.4f, 1.0f);
	Sparker.EndColor = glm::vec4(1.0f, 0.2f, 0.04f, 1.0f);

	Sparker.InitialRotation = 1.67f;
	Sparker.RotationVelocity = 0.05f;
	Sparker.RotationRandomness = 10.0f;
	Sparker.RotationAcceleration = 0.01f;

	Sparker.influenced = true;
	Sparker.lighted = true;
	Sparker.ShowWindow = true;


	Sparker.DrawToNormalMap = true;
	Sparker.Type = "TEXTUREDLINE";
	Sparker.Z_Index = 10;

	Sparker.NormalMap = BallNormalMapTexture;
	BackgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Sparker.textures.push_back(noize);

	mouseSphere = Sparker.AddSpheresOfInfluence({ 0.0f,0.0f }, 100.0f, { 0.0f,100.0f }, true, 10.0f);
	//mouseSphere = Sparker.AddLightCube({ 0.0f,0.0f }, glm::vec2(300.0f,300.0f), glm::vec4(1.0f));
	//mouseSphere = Sparker.AddLightSphere({ 0.0f,0.0f }, 200.0f, glm::vec4(10.0f,2.0f,0.4f,1.0f));
	
}
float f = 0;
void On_Update()
{/*

			for(int i =-5;i<5;i++)
				for(int y =-5;y<5;y++)
					DrawTexturedQuad({ i*200.0f,y*200.0f }, { 100.0f,100.0f }, noize, glm::vec3(0.0f,0.0f,i*y*0.6f), glm::vec4(3.0f),0, Sparker.NormalMap);
			*/

	Sparker.Process(delta);
	ImGui::Begin("s");
	ImGui::SliderFloat("orb", &Sparker.OrbitalVelocityRandomness, -10.0f, 10.0f);
	ImGui::SliderFloat("orb2", &Sparker.InitialOrbitalVelocity, -10.0f, 10.0f);
	ImGui::SliderInt("int", &test, -100, 100);
	ImGui::SliderInt("amount", &amount, 0, 1000);
	ImGui::SliderFloat("Lifetime", &Sparker.lifetime, 0, 10);
	ImGui::Checkbox("Additive", &Sparker.Additive);

	ImGui::DragFloat("AttractionStrength", &Sparker.SpheresOfInfluence[mouseSphere].attractionStrength);
	ImGui::DragFloat("SphereRadius", &Sparker.SpheresOfInfluence[mouseSphere].r);

	float v[2] = { Sparker.SpheresOfInfluence[mouseSphere].velocity.x,Sparker.SpheresOfInfluence[mouseSphere].velocity.y };
	ImGui::DragFloat2("SphereVelocity", v);
	Sparker.SpheresOfInfluence[mouseSphere].velocity.x = v[0];
	Sparker.SpheresOfInfluence[mouseSphere].velocity.y = v[1];

	ImGui::Checkbox("DrawToNormalMap", &Sparker.DrawToNormalMap);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate);
	ImGui::Text("Particles Amount %.i",
		Sparker.Particles.size());
	Sparker.SpheresOfInfluence[mouseSphere].position = MousePosition;
	Sparker.SpheresOfInfluence[mouseSphere].velocity = (MousePosition - prevpos) * 2.3f;
	//DrawLight(glm::vec3(MousePosition, -0.35f), { 700.0f,700.0f }, glm::vec4(100.0f,10.0f,10.0f,1.0f), 0.0f);

	if (ImGui::Button("clear"))
	{
		Sparker.SpheresOfInfluence.clear();
		mouseSphere = Sparker.AddSpheresOfInfluence(MousePosition, 100.0f, (MousePosition - prevpos) * 1.3f, true, 15.2f);

	}
	if (buttons[GLFW_MOUSE_BUTTON_2])
	{
		mouseSphere = Sparker.AddSpheresOfInfluence(MousePosition, Sparker.SpheresOfInfluence[mouseSphere].r, (MousePosition - prevpos) * 1.3f, true, 15.2f);
	}
	for (int i = 0; i < amount; i++)
	{
		float dist = rand() % int(HEIGHT * 0.1f) + (HEIGHT * 0.3f);
		glm::vec2 randvec = glm::vec2(rand() % 100 - 50, rand() % 100 - 50);

		randvec = Normalize(randvec);
		if (randvec.x * dist < -randvec.y * dist && randvec.x * dist < 200 || randvec.x * dist < test)
		{
			Sparker.InitialOrbitalVelocity = 0.0f;

			//Sparker.InitialVelocity = glm::vec2(randvec.y, -randvec.x) * float(1000);
			Sparker.Spawn(randvec * dist, 3);
		}
		prevpos = MousePosition;
	}
	for (int i = 0; i < amount * 0.1f; i++)
	{
		glm::vec2 randvec = glm::vec2
		(
			rand() % int(250) - HEIGHT * 0.09f,
			rand() % int(HEIGHT * 0.1f) - 70.0f
		);
		//Sparker.InitialVelocity = glm::vec2(0.75f, -0.25f) * float(000);
		Sparker.Spawn(randvec, 3);
	}
	for (int i = 0; i < amount * 0.1f; i++)
	{
		glm::vec2 randvec = glm::vec2
		(
			rand() % int(HEIGHT * 0.1f) + HEIGHT * 0.075f,
			rand() % int(240) - 300.0f
		);
		//Sparker.InitialVelocity = glm::vec2(0.05f, -0.95f) * float(000);
		Sparker.Spawn(randvec, 3);
	}

	if (keys[GLFW_KEY_X]) CameraScale *= 1.0f - delta;
	if (keys[GLFW_KEY_Z]) CameraScale *= 1.0f + delta;
	/*
	DrawCube(glm::vec2(HEIGHT * 0.12f, -70.0f), glm::vec2(100, HEIGHT*0.05f), glm::vec3(0.0f));
	DrawCube(glm::vec2(HEIGHT * 0.175f, -170.0f), glm::vec2(HEIGHT * 0.05f, 140), glm::vec3(0.0f));

	DrawCube(glm::vec2(HEIGHT * 0.3f, HEIGHT * 0.15f -50.0f), glm::vec2(100, HEIGHT*0.1f), glm::vec3(0.0f),BackgroundColor);
	DrawCube(glm::vec2(HEIGHT * 0.32f, HEIGHT * 0.15f -50.0f), glm::vec2(100, HEIGHT*1.0f), glm::vec3(0.0f),BackgroundColor);
	DrawCube(glm::vec2(HEIGHT * 0.345f, HEIGHT * 0.25f ), glm::vec2(100, HEIGHT*0.16f), glm::vec3(0.0f,0.0f,1.0),BackgroundColor);
	DrawCircle(glm::vec2(0.0f), (HEIGHT * 0.4f));
	DrawCircle(glm::vec2(0.0f), (HEIGHT * 0.3f),BackgroundColor);*/



}
int main()
{
	std::cout << "input screen width";
	int wi = 0;
	std::cin >> wi;
	std::cout << "input screen height";
	int he = 0;
	std::cin >> he;
	bool fs = false;
	std::cout << "Full screen? (1-yes/0-no)";
	std::cin >> fs;
	initEngine("ParticleSystemTest", wi, he, fs);
	//initEngine("app");
	return 0;
}