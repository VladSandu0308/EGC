#include "BirdSound.h"

BirdSound::BirdSound(char* filename)
{
	buffer = 0;
	HInstance = GetModuleHandle(0);

	HANDLE hResInfo;

	// Find the WAVE resource. 

	hResInfo = FindResource(HInstance, (LPCWSTR)filename, RT_PLUGPLAY);

	hRes = LoadResource(HInstance, (HRSRC)hResInfo);
}

BirdSound::~BirdSound()
{
	PlaySound(NULL, 0, 0);
	delete[] buffer;
}
void BirdSound::play()
{
	buffer = (LPCWSTR)LockResource(hRes);
	if (buffer != NULL) {
		sndPlaySound(buffer, SND_MEMORY | SND_SYNC | SND_NODEFAULT);
		UnlockResource(hRes);
	}

	FreeResource(hRes);
}