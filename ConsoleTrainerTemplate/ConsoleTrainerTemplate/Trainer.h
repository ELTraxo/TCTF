#pragma once
#include "includes.h"
#include <chrono>


class Trainer
{
public:
	Trainer(std::vector<std::reference_wrapper<Hack>> & GHackVec);
	Trainer(TCHAR * GameName, std::vector<std::reference_wrapper<Hack>> & GHackVec);
	~Trainer();
	void Init();
	void Init(TCHAR * GameName);
	void ReInit();
public:
	class Make
	{
	public:
		Make(Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks);
		Hack MakePatchHack(TCHAR * HackName, UINT pAddress, UINT szSize);
		Hack MakeInjectionHack(TCHAR * HackName, UINT pAddress, UINT szSize, std::vector<byte> vData);
		
		Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int value);
		Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int64_t value);
		Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, float value);
		Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, double value);

		Hack MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int value);
		Hack MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int64_t value);
		Hack MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, float value);
		Hack MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, double value);

		Hack MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, int value);
		Hack MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, int64_t value);
		Hack MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, float value);
		Hack MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, double value);
				 
		Hack MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, int value);
		Hack MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, int64_t value);
		Hack MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, float value);
		Hack MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, double value);

	private:
		Memory & mem;
		std::vector<std::reference_wrapper<Hack>> & pGVHacks;
	}make;

public:	
	void AddOption(Hack & hack);
	bool IsRunning();
	bool Update();

private:
	Memory mem;
	std::vector<std::reference_wrapper<Hack>> Options; //All options
	std::vector<std::reference_wrapper<Hack>> & pGVHacks; //All val freeze opts
	TCHAR * GameName;
	
	std::chrono::steady_clock::time_point keyTimer = std::chrono::steady_clock::now();
	float keyDelay = 0.2f; // = seconds
};

