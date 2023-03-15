#pragma once
// openAL
#include <AL/alext.h>
#include "LoadWAV.h"

ALint state = AL_PLAYING;

std::vector <ALuint*> sources;
std::vector <ALuint*> sounds;

ALCdevice* Device = alcOpenDevice(NULL);
ALCcontext* Context;
ALCboolean contextMadeCurrent;

glm::vec3 listenerPos = { 0.0,0.0,0.0 };
glm::vec3 listenerVel = { 0.0,0.0,0.0 };
ALfloat listenerOri[] = { 0.0,0.0,1.0, 0.0,-1.0,0.0 };

void AL_init()
{

	ALfloat lpos[] = { listenerPos.x, listenerPos.y, listenerPos.y};
	ALfloat lvel[] = { listenerVel.x, listenerVel.y, listenerVel.y};

	alListenerfv(AL_POSITION, lpos);
	alListenerfv(AL_VELOCITY, lvel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	if (Device) {
		Context = alcCreateContext(Device, NULL);
		alcMakeContextCurrent(Context);
	}

	contextMadeCurrent = alcMakeContextCurrent(Context);
	if (!contextMadeCurrent)
		std::cerr << "ERROR: Could not make audio context current" << "\n";


}

void UpdateListenerPosition()
{

	listenerPos.x = CameraPosition.x / WIDTH;
	listenerPos.y = CameraPosition.y / HEIGHT;

	ALfloat lpos[] = { listenerPos.x, listenerPos.y, listenerPos.z };
	ALfloat lvel[] = { listenerVel.x, listenerVel.y, listenerVel.z };

	alListenerfv(AL_POSITION, lpos);
	alListenerfv(AL_VELOCITY, lvel);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void GenSource(unsigned int* source)
{
	alGenSources(1, source);
	alSourcef(*source, AL_GAIN, 1.0f);
	alSourcef(*source, AL_PITCH, 1.0f);
	alSource3f(*source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(*source, AL_LOOPING, AL_FALSE);

	sources.push_back(source);
}
void SetSourcePitch(unsigned int* source, float pitch)// stock = 1.0f;
{
	alSourcef(*source, AL_PITCH, pitch);
}
void SetSourceGain(unsigned int* source, float gain)// stock = 1.0f;
{
	alSourcef(*source, AL_GAIN, gain);
}
void SetSourcePosition(unsigned int* source, glm::vec3 position)// stock = 0.0f,0.0f,0.0f;
{
	glm::vec3 pos;
	pos.x = position.x / WIDTH ;
	pos.y = position.y / HEIGHT ;
	pos.z = position.z;
	alSource3f(*source, AL_POSITION, pos.x, pos.y, pos.z);
}
void SetSourceVelocity(unsigned int* source, glm::vec3 velocity)// stock = 0.0f,0.0f,0.0f;
{
	alSource3f(*source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
void SetSourceLooping(unsigned int* source, bool looping)// stock = false;
{
	alSourcei(*source, AL_LOOPING, looping);
}

void SetSourceSound(unsigned int* source, unsigned int* sound)
{
	alSourcei(*source, AL_BUFFER, *sound);
}

// helpfull when source is running on loop
void SwapSourceSound(unsigned int* source, unsigned int* sound)
{
	alSourceStop(*source);
	alSourcei(*source, AL_BUFFER, *sound);
	alSourcePlay(*source);
}
void PlaySource(unsigned int* source)
{
	alSourcePlay(*source);
}
void StopSource(unsigned int* source)
{
	alSourceStop(*source);
}

void DeleteSource(unsigned int* source)
{
	alSourceStop(*source);
	alDeleteSources(1, source);

	int i = 0;
	bool go = true;
	while (go)
	{
		if (sources[i] == source)
		{
			go = false;
			sources[i] = sources[sources.size() - 1];
			sources.pop_back();
		}
		i++;
		if (i >= sources.size())
			go = false;
	}

}


void  AL_Destroy()
{
	for (int i = 0; i < sources.size(); i++)
	{
		alSourceStop(*sources[i]);
		alDeleteSources(1, sources[i]);
	}
	alcCloseDevice(Device);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(Context);
}
