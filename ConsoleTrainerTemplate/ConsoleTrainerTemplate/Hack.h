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
public: //ctors
	// code patch ctor
	Hack(Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize); 

	// val freeze ctors
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, int value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, int64_t value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int64_t value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, float value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, float value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, double value);
	Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, double value);
	~Hack();

public: //Inits
	void InitTypeAndAddress(HackType ht, ValType vt, uintptr_t pAddress);
	void InitTypeAndPointer(HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count);

public: //Toggles
	void TogglePatch();
	void WriteValue();
	void Toggle();

	void AddHackToVec();
	void AddToVec(std::vector<Hack> & hack);

private:
	Memory & mem;
	HackType ht;
	ValType vt;

	bool bEnabled = false;

	//for code patch and maybe hooking hacks
	uintptr_t pAddress = NULL;
	UINT szSize = NULL;
	std::vector<byte> vOldBytes;

	//for pointer based hacks.
	uintptr_t pBase = NULL;
	UCHAR ucOffsetCount = NULL; //amount of offsets
	UINT * pOffsets = nullptr; //ptr -> offsets	

	int iValue = 0;
	int64_t i64Value = 0;
	float fValue = 0;
	double dValue = 0;
	
};

