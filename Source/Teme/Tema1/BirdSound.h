#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>

class BirdSound {

public:
	BirdSound(char* filename);
	~BirdSound();
	void play();

private:
	LPCWSTR buffer;
	HINSTANCE HInstance;
	HANDLE hRes;
};