#include "engine/Components/Engine.h";


// AL stuff
ALint state = AL_PLAYING;
ALuint source;
ALuint sound;

ALCdevice* Device = alcOpenDevice(NULL);
ALCcontext* Context;
ALCboolean contextMadeCurrent;

ALfloat listenerPos[] = { 0.0,0.0,0.0 };
ALfloat listenerVel[] = { 0.0,0.0,0.0 };
ALfloat listenerOri[] = { 0.0,0.0,1.0, 0.0,1.0,0.0 };

void AL_init()
{

	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	if (Device) {
		Context = alcCreateContext(Device, NULL);
		alcMakeContextCurrent(Context);
	}

	contextMadeCurrent = alcMakeContextCurrent(Context);
	if (!contextMadeCurrent)
		std::cerr << "ERROR: Could not make audio context current" << "\n";


	alGenSources(1, &source);
	sound = LoadSound("carenginesound.wav");
	alSourcei(source, AL_BUFFER, sound);
	alSourcef(source, AL_GAIN, 1.0f);
	alSourcef(source, AL_PITCH, 1.0f);
	alSource3f(source, AL_POSITION, 1.0f, 0.0f, 2.0f);
	alSource3f(source, AL_VELOCITY, -1.0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_TRUE);
}



int main()
{
	

	


	

	/*
	
	
// Position ...
alListenerfv(AL_POSITION,listenerPos);
if ((error = alGetError()) != AL_NO_ERROR)
{
DisplayALError("alListenerfv POSITION : ", error);
return;
}
// Velocity ...
alListenerfv(AL_VELOCITY,listenerVel);
if ((error = alGetError()) != AL_NO_ERROR)
{
DisplayALError("alListenerfv VELOCITY : ", error);
return;
}
// Orientation ...
alListenerfv(AL_ORIENTATION,listenerOri);
if ((error = alGetError()) != AL_NO_ERROR)
{
DisplayALError("alListenerfv ORIENTATION : ", error);
return;
}
	
	*/
	



	alSourcePlay(source);
	float rpm = 1.0f;
	while (state == AL_PLAYING)
	{
		alGetSourcei(sound, AL_SOURCE_STATE, &state);
		alSourcef(source, AL_PITCH, rpm);
		rpm += 0.0000001f;
	}

	alcCloseDevice(Device);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(Context);
	return 0;
}