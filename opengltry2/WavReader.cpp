#include "engine/Components/Engine.h"
#include "engine/Components/Include/sounds.h"


//int ReadFrom4(std::ifstream* ifs)
//{
//	char* data = new char[4];
//	ifs->read(data, 4);
//
//	unsigned int aboba = 0;
//	memcpy(&aboba, data, 4);
//	
//	delete[4] data;
//	return aboba;
//}
//short ReadFrom2(std::ifstream* ifs)
//{
//	char* data = new char[2];
//	ifs->read(data, 2);
//
//	unsigned short aboba = 0;
//		memcpy(&aboba, data, 2);
//	delete[2] data;
//	return aboba;
//}
//
//unsigned int LoadSoundTheScuffedWay(const char* FileName)
//{
//	std::ifstream ifs(FileName, std::ios::binary);
//
//	ReadFrom4(&ifs);//ChunkID 
//	int ChunkSize = ReadFrom4(&ifs);//ChunkSize 
//	ReadFrom4(&ifs);//Format 
//	ReadFrom4(&ifs);//SubChunk1ID 
//	int SubChunk1Size = ReadFrom4(&ifs);//SubChunk1Size 
//	short AudioFormat = ReadFrom2(&ifs);//AudioFormat 
//	short NumChannels = ReadFrom2(&ifs);//NumChannels 
//	int SampleRate = ReadFrom4(&ifs);//SampleRate 
//	int ByteRate = ReadFrom4(&ifs);//ByteRate 
//	short BlockAlign = ReadFrom2(&ifs);//BlockAlign 
//	short BPS = ReadFrom2(&ifs);//BPS 
//	if (NumChannels == 1) {
//		ReadFrom4(&ifs);//some
//		ReadFrom4(&ifs);//shit
//		ReadFrom4(&ifs);//that is
//		ReadFrom4(&ifs);//only
//		ReadFrom4(&ifs);//in
//		ReadFrom4(&ifs);//mono
//		// idk why and what this for, but it works this way.
//	}
//	ReadFrom4(&ifs);//SubChunk2ID 
//	int SubChunk2Size = ReadFrom4(&ifs);//SubChunk2Size 
//
//	unsigned int buffer;
//	alGenBuffers(1, &buffer);
//	ALenum format;
//	if (BPS == 16 && NumChannels == 2)
//		format = AL_FORMAT_STEREO16;
//	else if (BPS == 16 && NumChannels == 1)
//		format = AL_FORMAT_MONO16;
//	else if (BPS == 32 && NumChannels == 2)
//		format = AL_FORMAT_STEREO_FLOAT32;
//	else if (BPS == 32 && NumChannels == 1)
//		format = AL_FORMAT_MONO_FLOAT32;
//
//	char* membuf = new char[SubChunk2Size];
//	ifs.read(membuf, SubChunk2Size);
//
//	alBufferData(buffer, format, membuf, SubChunk2Size, SampleRate);
//
//	delete[SubChunk2Size] membuf;
//	ifs.close();
//	return buffer;
//}
unsigned int src;
unsigned int buffer;

void On_Create()
{
	AL_init();

	//unsigned int buffer = LoadSoundTheScuffedWay("Sounds/Untitled 2.wav");
	//unsigned int buffer = LoadSoundTheScuffedWay("Sounds/metalhit1.wav");
	/*unsigned int buffer = LoadSoundTheScuffedWay("Sounds/Untitled 2_L.wav");
*/


	
	
	alGenBuffers(1, &buffer);
	//std::cout << SourcePlaying(&src)<<'\n';
	float* membuf = new float[48000];
	//float* membuff = new float[48000];
	float avg = 1.0f / 24000.0f;
	for (int i = 0; i < 48000; i++)
	{
		float a = sin((float)i * avg * 100 * pi) * 0.25f;
		a += sin((float)i * avg * 200 * pi) * 0.125f;
		a += sin((float)i * avg * 300 * pi) * 0.0625f;
		a += sin((float)i * avg * 400 * pi) * 0.0625f;
		a += sin((float)i * avg * 240 * pi) * 0.0625f;
		a += sin((float)i * avg * 530 * pi) * 0.0625f;
		a += sin((float)i * avg * 740 * pi) * 0.0625f;
		a += sin((float)i * avg * 640 * pi) * 0.0625f;
		a += sin((float)i * avg * 412 * pi) * 0.0625f;
		a += sin((float)i * avg * 472 * pi) * 0.0625f;
		a *= sin((float)i * avg * 300 * pi) * 0.98f + (rand()% 10000/10000.0f)*0.01f;
		membuf[i] = a;
	}
	ALenum format = AL_FORMAT_MONO_FLOAT32;
	alBufferData(buffer, format, membuf, 48000 * 4, 48000);
	GenSource(&src);
	SetSourceSound(&src, &buffer);
	SetSourceLooping(&src, true);
	PlaySource(&src);
	delete[] membuf;
}
void On_Update()
{	
	
	SetSourcePitch(&src, ((MousePosition.x + WIDTH) / (WIDTH * 1.0f)));
}

int main()
{
	
	initEngine("wavreader",800,600);
	AL_Destroy();
	return 0;
}