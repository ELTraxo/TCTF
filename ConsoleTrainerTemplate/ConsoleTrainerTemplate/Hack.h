#pragma once
#include "Memory.h"

enum HackType
{
	CODEPATCH,
	VALFREEZE,
	VALWRITE,
	HOOK
};

class Hack
{
public:
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize);
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, int value);
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, int64_t value);
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, float value);
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, double value);
	~Hack();

	void InitTypeAndAddress(HackType ht, uintptr_t pAddress);

	void TogglePatch();
	void Toggle();
	

private:
	Memory & mem;
	HackType ht;
	
	//for code patch and maybe hooking hacks
	uintptr_t pAddress = NULL;
	UINT szSize = NULL;
	std::vector<byte> vOldBytes;

	//for pointer based hacks.
	UCHAR cnOffsets = NULL; //amount of offsets
	UINT * pOffsets = nullptr; //ptr -> offsets
	bool bEnabled = false;

	int iValue = 0;
	int64_t i64Value = 0;
	float fValue = 0;
	double dValue = 0;
	
};

