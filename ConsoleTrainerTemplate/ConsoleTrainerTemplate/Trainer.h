#pragma once
#include "includes.h"
#include <chrono>

class Menu;

class Trainer
{
public:
	Trainer(std::vector<std::reference_wrapper<Hack>> & GHackVec);
	Trainer(TCHAR * GameName, std::vector<std::reference_wrapper<Hack>> & GHackVec);
	~Trainer();
	void Init();
	void Init(TCHAR * GameName);
	void ReInit();
	bool IsReady();

public:
	class Make
	{
	public:
		Make(Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks);
		Hack MakePatchHack(TCHAR * HackName, UINT pAddress, UINT szSize);
		Hack MakePatchHack(TCHAR * HackName, Pattern & pPattern, UINT szSize);
		Hack MakePatchHack(TCHAR * HackName, Pattern & pPattern, int iPatternOffset, UINT szSize);
		Hack MakeInjectionHack(TCHAR * HackName, UINT pAddress, UINT szSize, std::vector<byte> vData);
		Hack MakeInjectionHack(TCHAR * HackName, Pattern & pPattern, UINT szSize, std::vector<byte> vData);
		Hack MakeInjectionHack(TCHAR * HackName, Pattern & pPattern, int iPatternOffset, UINT szSize, std::vector<byte> vData);
		
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
	std::vector<std::reference_wrapper<Hack>> & GetOptions();

private:
	Memory mem;
	TCHAR * GameName;
	bool bInitted = false;
	bool bSearching = false;
	std::vector<std::reference_wrapper<Hack>> Options; //All options
	std::vector<std::reference_wrapper<Hack>> & pGVHacks; //All val freeze opts
	
	//key press related
	std::chrono::steady_clock::time_point keyTimer = std::chrono::steady_clock::now();
	float keyDelay = 0.2f; // = seconds
};

