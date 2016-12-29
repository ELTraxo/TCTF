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
//	KeyTimer = clock();
	mem.Init(GameName);
}

void Trainer::Init(TCHAR * GameName)
{
	this->GameName = GameName;
	Init();
}

void Trainer::ReInit()
{
	mem.ReInit();
	for each (Hack & hack in Options)
	{
		hack.ReInit();
	}
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

Hack Trainer::Make::MakePatchHack(TCHAR * HackName, Pattern & pPattern, UINT szSize)
{
	
	return Hack(HackName, mem, HackType::CODEPATCH, mem.pattern.ScanProcess((char*)pPattern.pattern, pPattern.mask.c_str(), false), szSize);
}

Hack Trainer::Make::MakeInjectionHack(TCHAR * HackName, UINT pAddress, UINT szSize, std::vector<byte> vData)
{
	byte * pData = new byte[vData.size()];
	for (UINT x = 0; x < vData.size(); x++)
	{
		pData[x] = vData[x];
	}
	Hack hack = Hack(HackName, mem, HackType::HOOK, pAddress, szSize, pData, (UINT)vData.size());
	delete[] pData;
	return hack;
}

Hack Trainer::Make::MakeInjectionHack(TCHAR * HackName, Pattern & pPattern, UINT szSize, std::vector<byte> vData)
{
	return MakeInjectionHack(HackName, mem.pattern.ScanProcess((char*)pPattern.pattern, pPattern.mask.c_str(), false), szSize, vData);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::I64, pAddress, value);
}

Hack Trainer::Make::MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::F, pAddress, value);
}

Hack Trainer::Make::MakeWriteValHack(TCHAR * HackName, uintptr_t pAddress, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::D, pAddress, value);
}

Hack Trainer::Make::MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::I64, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::F, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeWriteValPtrHack(TCHAR * HackName, Pointer ptr, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALWRITE, ValType::D, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

void Trainer::AddOption(Hack & hack)
{
	Options.push_back(hack);
}

bool Trainer::IsRunning()
{
	return (!mem.CheckProcDeath());
}

bool Trainer::Update()
{
	using namespace std::chrono;
	steady_clock::time_point check = steady_clock::now();
	
	//duration<int, milliseconds> timeSince = steady_clock::now() - keyTimer;
	duration<float> runtime = check - keyTimer;
	for each(Hack & hack in Options)
	{
		if (runtime.count() > keyDelay)
		{
			if (GetAsyncKeyState(hack.GetHotkey()))
			{
				keyTimer = steady_clock::now();
				hack.Toggle();
				return true;
			}
		}
	}
	return false;
}


