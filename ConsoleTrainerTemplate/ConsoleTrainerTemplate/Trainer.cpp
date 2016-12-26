#include "Trainer.h"

Trainer::Trainer(std::vector<std::reference_wrapper<Hack>> & GHackVec)
	:
	pGVHacks(GHackVec),
	make(this->mem, GHackVec)
{
}

Trainer::Trainer(TCHAR * GameName, std::vector<std::reference_wrapper<Hack>> & GHackVec)
	:
	pGVHacks(GHackVec),
	make(this->mem, GHackVec)
{
	this->GameName = GameName;
}

Trainer::~Trainer()
{
}

void Trainer::Init()
{
	KeyTimer = clock();
	mem.Init(GameName);
}

void Trainer::Init(TCHAR * GameName)
{
	this->GameName = GameName;
	Init();
}

void Trainer::AddOption(Hack & hack)
{
	Options.push_back(hack);
}

Trainer::Make::Make(Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
}

Hack Trainer::Make::MakePatchHack(TCHAR * HackName, UINT pAddress, UINT szSize)
{
	return Hack(HackName, mem, HackType::CODEPATCH, (uintptr_t)pAddress, szSize);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

void Trainer::Toggle(TCHAR * HackName)
{
	for each(Hack & hack in Options)
	{
		TCHAR * currName = hack.GetName();
		if (!_tcscmp(currName, HackName))
			hack.Toggle();
	}
}

void Trainer::Update()
{
	for each(Hack & hack in Options)
	{
		if (clock() > KeyTimer + 250)
		{
			if (GetAsyncKeyState(hack.GetHotkey()))
			{
				KeyTimer = clock();
				hack.Toggle();
			}
		}
	}
}


