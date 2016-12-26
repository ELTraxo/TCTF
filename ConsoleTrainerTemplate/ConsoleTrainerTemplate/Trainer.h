#pragma once
#include "includes.h"
#include <ctime>



class Trainer
{
public:
	Trainer(std::vector<std::reference_wrapper<Hack>> & GHackVec);
	Trainer(TCHAR * GameName, std::vector<std::reference_wrapper<Hack>> & GHackVec);
	~Trainer();
	void Init();
	void Init(TCHAR * GameName);
	void AddOption(Hack & hack);
	Hack MakePatchHack(TCHAR * HackName, UINT pAddress, UINT szSize);
	Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int value);
	Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int64_t value);
	Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, float value);
	Hack MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, double value);
	void Toggle(TCHAR * HackName);
	void Update();

private:
	Memory mem;
	std::vector<std::reference_wrapper<Hack>> Options;
	std::vector<std::reference_wrapper<Hack>> & GHackVec;
	TCHAR * GameName;
	UINT KeyTimer;
};

