#pragma once
#include <vector>
#include "Memory.h"

enum HackType
{
	CODEPATCH,
	VALFREEZE,
	HOOK
};

class Hack
{
public:
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize);
	~Hack();

	void Toggle();

private:
	Memory & mem;
	HackType ht;
	
	//for code patch and maybe hooking hacks
	uintptr_t pAddress = NULL;
	UINT szSize = NULL;
	std::vector<byte> vOldBytes;

	//for pointer based hacks.
	UCHAR cOffsets = NULL;
	UINT * pOffsets = nullptr;

	bool bEnabled = false;
};

