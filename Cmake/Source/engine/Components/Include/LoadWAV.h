#pragma once
#include "AL/alhelpers.h"


int ReadFrom4(std::ifstream* ifs)// reads 4 bytes from ifstring as integer
{
	char* data = new char[4];
	ifs->read(data, 4);

	unsigned int aboba = 0;
	memcpy(&aboba, data, 4);

	delete[] data;
	return aboba;
}
short ReadFrom2(std::ifstream* ifs)// reads 2 bytes from ifstring as short
{
	char* data = new char[2];
	ifs->read(data, 2);

	unsigned short aboba = 0;
	memcpy(&aboba, data, 2);
	delete[] data;
	return aboba;
}
unsigned int LoadSound(const char* FileName)
{
	std::ifstream ifs(FileName, std::ios::binary);

	ReadFrom4(&ifs);//ChunkID 
	int ChunkSize = ReadFrom4(&ifs);//ChunkSize 
	ReadFrom4(&ifs);//Format 
	ReadFrom4(&ifs);//SubChunk1ID 
	int SubChunk1Size = ReadFrom4(&ifs);//SubChunk1Size 
	short AudioFormat = ReadFrom2(&ifs);//AudioFormat 
	short NumChannels = ReadFrom2(&ifs);//NumChannels 
	int SampleRate = ReadFrom4(&ifs);//SampleRate 
	int ByteRate = ReadFrom4(&ifs);//ByteRate 
	short BlockAlign = ReadFrom2(&ifs);//BlockAlign 
	short BPS = ReadFrom2(&ifs);//BPS 
	if (SubChunk1Size > 16)
	{// skip the data that i dont understand, ez
		char* jnk = new char[SubChunk1Size - 16];
		ifs.read(jnk, SubChunk1Size - 16);
	}
	ReadFrom4(&ifs);//SubChunk2ID 
	int SubChunk2Size = ReadFrom4(&ifs);//SubChunk2Size 

	unsigned int buffer;
	alGenBuffers(1, &buffer);
	ALenum format;
	if (BPS == 16 && NumChannels == 2)
		format = AL_FORMAT_STEREO16;
	else if (BPS == 16 && NumChannels == 1)
		format = AL_FORMAT_MONO16;
	else if (BPS == 32 && NumChannels == 2)
		format = AL_FORMAT_STEREO_FLOAT32;
	else if (BPS == 32 && NumChannels == 1)
		format = AL_FORMAT_MONO_FLOAT32;

	char* membuf = new char[SubChunk2Size];
	ifs.read(membuf, SubChunk2Size);

	alBufferData(buffer, format, membuf, SubChunk2Size, SampleRate);

	delete[] membuf;
	ifs.close();
	return buffer;
}
