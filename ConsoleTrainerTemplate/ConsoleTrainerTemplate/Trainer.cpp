#include "Trainer.h"

void FreezeThread(Memory & mem, std::vector<std::reference_wrapper<Hack>> * GHackVec)
{
	static auto tpDelay = std::chrono::steady_clock::now();
	auto tpNow = std::chrono::steady_clock::now();

	while (!mem.GetProcDeathVar())
	{
		tpNow = std::chrono::steady_clock::now();
		std::chrono::duration<float> check = tpNow - tpDelay;
		if (check.count() >= 0.01f)
		{
			if (!GHackVec->empty())
			{
				for each(Hack hack in *GHackVec)
				{
					hack.WriteValue();
				}
			}
		}
	}
}

Trainer::Trainer()
	:
	make(this->mem, this->pGVHacks)
{
}

//Trainer::Trainer(std::vector<std::reference_wrapper<Hack>> & GHackVec)
//	:
//	pGVHacks(GHackVec),
//	make(this->mem, GHackVec)
//{
//}
//
//Trainer::Trainer(TCHAR * GameName, std::vector<std::reference_wrapper<Hack>> & GHackVec)
//	:
//	pGVHacks(GHackVec),
//	make(this->mem, GHackVec)
//{
//	this->GameName = GameName;
//}

Trainer::~Trainer()
{
}

void Trainer::Init()
{
//	KeyTimer = clock();
	mem.Init(GameName);
	bInitted = true;
	bSearching = false;

	// Freeze values thread
	std::thread tr(&FreezeThread, this->mem, &this->pGVHacks);
	tr.detach();
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
	bInitted = true;
	bSearching = false;
}

bool Trainer::IsReady()
{
	return bInitted;
}

//Trainer::Make::Make(Memory & mem)
//	:
//	mem(mem)
//{
//}

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
	char * cpPattern = new char[pPattern.vPattern.size()];
	
	for (UINT i = 0; i < pPattern.vPattern.size(); i++)
		cpPattern[i] = pPattern.vPattern[i];

	Hack retHack = Hack(HackName, mem, HackType::CODEPATCH, mem.pattern.ScanProcess(cpPattern, (char*)pPattern.sMask.c_str(), false), szSize);

	delete[] cpPattern;
	return retHack;
}

Hack Trainer::Make::MakePatchHack(TCHAR * HackName, Pattern & pPattern, int iPatternOffset, UINT szSize)
{
	char * cpPattern = new char[pPattern.vPattern.size()];

	for (UINT i = 0; i < pPattern.vPattern.size(); i++)
		cpPattern[i] = pPattern.vPattern[i];

	Hack retHack = Hack(HackName, mem, HackType::CODEPATCH, (mem.pattern.ScanProcess(cpPattern, (char*)pPattern.sMask.c_str(), false) + iPatternOffset), szSize);

	delete[] cpPattern;
	return retHack;
}

Hack Trainer::Make::MakeInjectionHack(TCHAR * HackName, UINT pAddress, UINT szSize, std::vector<byte> vData)
{
	byte * pData = new byte[vData.size()];
	
	for (UINT x = 0; x < vData.size(); x++)
		pData[x] = vData[x];
	
	Hack hack = Hack(HackName, mem, HackType::HOOK, pAddress, szSize, pData, (UINT)vData.size());

	delete[] pData;
	return hack;
}

Hack Trainer::Make::MakeInjectionHack(TCHAR * HackName, Pattern & pPattern, UINT szSize, std::vector<byte> vData)
{
	byte * pData = new byte[vData.size()];
	char * cpPattern = new char[pPattern.vPattern.size()];

	for (UINT x = 0; x < vData.size(); x++)
		pData[x] = vData[x];

	for (UINT i = 0; i < pPattern.vPattern.size(); i++)
		cpPattern[i] = pPattern.vPattern[i];

	Hack retHack = Hack(HackName, mem, HackType::HOOK, mem.pattern.ScanProcess(cpPattern, (char*)pPattern.sMask.c_str(), false), szSize, pData, vData.size());
	
	delete[] pData;
	delete[] cpPattern;

	return retHack;
}

Hack Trainer::Make::MakeInjectionHack(TCHAR * HackName, Pattern & pPattern, int iPatternOffset, UINT szSize, std::vector<byte> vData)
{
	byte * pData = new byte[vData.size()];
	char * cpPattern = new char[pPattern.vPattern.size()];

	for (UINT x = 0; x < vData.size(); x++)
		pData[x] = vData[x];

	for (UINT i = 0; i < pPattern.vPattern.size(); i++)
		cpPattern[i] = pPattern.vPattern[i];

	Hack retHack = Hack(HackName, mem, HackType::HOOK, (mem.pattern.ScanProcess(cpPattern, (char*)pPattern.sMask.c_str(), false) + iPatternOffset), szSize, pData, vData.size());

	delete[] pData;
	delete[] cpPattern;

	return retHack;
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, pAddress, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I64, pAddress, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::F, pAddress, value);
}

Hack Trainer::Make::MakeFreezeHack(TCHAR * HackName, uintptr_t pAddress, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::D, pAddress, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, int64_t value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::I64, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, float value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::F, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
}

Hack Trainer::Make::MakeFreezePtrHack(TCHAR * HackName, Pointer ptr, double value)
{
	return Hack(HackName, mem, pGVHacks, HackType::VALFREEZE, ValType::D, ptr.pBase, ptr.pOffsets, ptr.ofCount, value);
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

		if (!IsRunning())
		{
			bInitted = false;
			if (!bSearching)
			{
				bSearching = true;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

std::vector<std::reference_wrapper<Hack>> & Trainer::GetOptions()
{
	return Options;
}


