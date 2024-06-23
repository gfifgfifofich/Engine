#pragma once
// openAL
#include <AL/alext.h>

inline std::vector <ALuint*> sources;
inline std::vector <ALuint*> sounds;
inline std::vector <unsigned int> soundsArray;
inline std::vector <unsigned int*> soundsArray2;
inline ALCdevice* Device = alcOpenDevice(NULL);
inline ALCcontext* Context = NULL;
inline ALCboolean contextMadeCurrent;
inline glm::vec3 listenerPos = { 0.0,0.0,0.0 };
inline glm::vec3 listenerVel = { 0.0,0.0,0.0 };
inline ALfloat listenerOri[] = { 0.0,0.0,1.0, 0.0,-1.0,0.0 };
inline glm::vec3 soundscale = { 1.0f,1.0f ,1.0f };
inline glm::vec3 soundSpeedscale = { 1.0f,1.0f ,1.0f };

unsigned int LoadSound(const char* FileName);
void DeleteSound(unsigned int* sound);

void AL_init();
void AL_Reload();
void  AL_Destroy();
void UpdateListenerPosition();
void GenSource(unsigned int* source);
void SetSourcePitch(unsigned int* source, float pitch);
void SetSourceGain(unsigned int* source, float gain);
void SetSourceRefDist(unsigned int* source, float Distance);
void SetSourceMaxDistance(unsigned int* source, float Distance);
void SetSourceRollOff(unsigned int* source, float rolloff);
void SetSourceRelative(unsigned int* source, bool relative);

void SetSourcePosition(unsigned int* source, glm::vec3 position);
void SetSourcePosition(unsigned int* source, glm::vec2 position);

void SetSourceVelocity(unsigned int* source, glm::vec3 velocity);
void SetSourceLooping(unsigned int* source, bool looping);

void SetSourceSound(unsigned int* source, unsigned int* sound);

// helpfull when source is running on loop
void SwapSourceSound(unsigned int* source, unsigned int* sound);
void PlaySource(unsigned int* source);
void StopSource(unsigned int* source);
bool SourcePlaying(unsigned int* source);
void DeleteSource(unsigned int* source);
void PlaySound(unsigned int* sound, glm::vec2 position, float pitch = 1.0f, float gain = 1.0f);
void PlaySound(unsigned int* dst, unsigned int* sound, glm::vec2 position, float pitch = 1.0f, float gain = 1.0f);
void PlaySound(unsigned int** dst, unsigned int* sound, glm::vec2 position, float pitch = 1.0f, float gain = 1.0f);
void ProcessAL();