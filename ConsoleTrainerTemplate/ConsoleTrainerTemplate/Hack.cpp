#include "includes.h"

// code patch ctor
Hack::Hack(TCHAR * HackName, Memory & mem, HackType ht, uintptr_t pAddress, size_t szSize)
	:
	mem(mem),
	pGVHacks(std::vector<std::reference_wrapper<Hack>>()) //Don't really need a ref to the global hacks vec
{
	InitHackAndAddress(HackName, ht, vt, pAddress);
	this->szSize = szSize;
}

// code injection ctor
Hack::Hack(TCHAR * HackName, Memory & mem, HackType ht, uintptr_t pAddress, size_t szSize, byte * pData, UINT iCaveSize)
	:
	mem(mem),
	pGVHacks(std::vector<std::reference_wrapper<Hack>>())
{
	InitHackAndAddress(HackName, ht, vt, pAddress);
	this->szSize = szSize;
	for (UINT x = 0; x < iCaveSize; x++)
	{
		vCaveData.push_back(pData[x]);
	}
}

// val freeze ctors...
Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pAddress, int value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndAddress(HackName, ht, vt, pAddress);
	iValue = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pAddress, int64_t value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndAddress(HackName, ht, vt, pAddress);
	i64Value = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pAddress, float value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndAddress(HackName, ht, vt, pAddress);
	fValue = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pAddress, double value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndAddress(HackName, ht, vt, pAddress);
	dValue = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndPointer(HackName, ht, vt, pBase, Offsets, count);
	iValue = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int64_t value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndPointer(HackName, ht, vt, pBase, Offsets, count);
	i64Value = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, float value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndPointer(HackName, ht, vt, pBase, Offsets, count);
	fValue = value;
}

Hack::Hack(TCHAR * HackName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & pGVHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, double value)
	:
	mem(mem),
	pGVHacks(pGVHacks)
{
	InitHackAndPointer(HackName, ht, vt, pBase, Offsets, count);
	dValue = value;
}

Hack::~Hack()
{
}

void Hack::InitHackAndAddress(TCHAR * HackName, HackType ht, ValType vt, uintptr_t pAddress)
{
	this->HackName = HackName;
	this->ht = ht;
	this->vt = vt;
	this->pAddress = pAddress;
	if(ht == HackType::VALFREEZE || ht == HackType::VALWRITE)
		AddHackToVec();
}

void Hack::InitHackAndPointer(TCHAR * HackName, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count)
{
	this->HackName = HackName;
	this->ht = ht;
	this->vt = vt;
	this->pBase = pBase;
	this->pOffsets = Offsets;
	this->ucOffsetCount = count;
	if (ht == HackType::VALFREEZE || ht == HackType::VALWRITE)
		AddHackToVec();
}

void Hack::ReInit()
{
	if (!vOldBytes.empty())
		vOldBytes.clear();
	
	if (pCaveAddress != NULL)
		pCaveAddress = NULL;

	bEnabled = false;
}

TCHAR * Hack::GetName()
{
	return HackName;
}

HackType Hack::GetHackType()
{
	return this->ht;
}

bool Hack::GetStatus()
{
	return bEnabled;
}

void Hack::SetHotkey(int vKey)
{
	iHotkey = vKey;
}

int Hack::GetHotkey()
{
	return iHotkey;
}

void Hack::TogglePatch()
{
	if (bEnabled)
	{
		if (vOldBytes.empty())
		{
			byte * poBytes = new byte[szSize];
			if (!mem.read.ReadBytes(pAddress, &poBytes[0], szSize))
				std::cerr << "Could not read from process..." << std::endl;

			for (UINT x = 0; x < szSize; x++)
			{
				vOldBytes.push_back(poBytes[x]);
			}
		}

		mem.write.WriteBytes(pAddress, NULL, szSize);
	}
	else
	{
		byte * poBytes = new byte[szSize];
		for (UINT x = 0; x < szSize; x++)
		{
			poBytes[x] = vOldBytes.at(x);
		}
		mem.write.WriteBytes(pAddress, poBytes, szSize);
		delete[] poBytes;
	}
}

void Hack::WriteValue()
{
	if (bEnabled)
	{
		if (vt == ValType::I)
		{
			if (pBase != NULL)
			{
				mem.write.WriteInt(mem.EvaluatePointer(pBase, pOffsets, ucOffsetCount), iValue);
			}
			else
			{
				mem.write.WriteInt(pAddress, iValue);
			}
		}
		else if (vt == ValType::I64)
		{
			if (pBase != NULL)
			{
				mem.write.WriteInt64(mem.EvaluatePointer(pBase, pOffsets, ucOffsetCount), i64Value);
			}
			else
			{
				mem.write.WriteInt64(pAddress, i64Value);
			}
		}
		else if (vt == ValType::F)
		{
			if (pBase != NULL)
			{
				mem.write.WriteFloat(mem.EvaluatePointer(pBase, pOffsets, ucOffsetCount), fValue);
			}
			else
			{
				mem.write.WriteFloat(pAddress, fValue);
			}
		}
		else if (vt == ValType::D)
		{
			if (pBase != NULL)
			{
				mem.write.WriteDouble(mem.EvaluatePointer(pBase, pOffsets, ucOffsetCount), dValue);
			}
			else
			{
				mem.write.WriteDouble(pAddress, dValue);
			}
		}

	}
}

void Hack::HookInit()
{
	pCaveAddress = mem.ScanForCodeCave(0, vCaveData.size());

	byte * pOldBytes = new byte[szSize];
	mem.read.ReadBytes(pAddress, pOldBytes, szSize);

	for (UINT x = 0; x < szSize; x++)
		vOldBytes.push_back(pOldBytes[x]);

	delete[] pOldBytes;
}

void Hack::WriteCaveData()
{
	int addySize = sizeof(uintptr_t);
	//Actual cave data
	byte * pData = new byte[vCaveData.size()];
	for (UINT x = 0; x < vCaveData.size(); x++)
	{
		pData[x] = vCaveData[x];
	}

	mem.write.WriteBytes(pCaveAddress, pData, vCaveData.size());
	delete[] pData;

	// rest of this is for the jump back.
	uintptr_t destJumpBackAddy = pAddress + (szSize - 5) - (pCaveAddress + vCaveData.size());
	byte * pAddy = new byte[addySize];
	mem.ParseAddress(destJumpBackAddy, pAddy);

	byte * destJumpBack = new byte[addySize];

	destJumpBack[0] = 0xE9;
	int y = 1;
	for (int x = addySize; x > 0; x--)
	{
		if (x == addySize)
			destJumpBack[x] = pAddy[x - x];
		else
		{
			destJumpBack[x] = pAddy[x - (x - y)];
			y++;
		}
	}
	//delete[] pAddy;
	byte dstJmpBack[5] = { 0 };
	for (int x = 0; x < 5; x++)
		dstJmpBack[x] = destJumpBack[x];
	
	mem.write.WriteBytes(pCaveAddress + vCaveData.size(), dstJmpBack, 5);
	pAddy = NULL;
}

void Hack::WriteJmp2Cave()
{
	UINT addySize = sizeof(uintptr_t);
	byte * srcJump = new byte[szSize];
	srcJump[0] = 0xE9;
	uintptr_t srcToCaveJump = (pCaveAddress - pAddress - 5);
	byte pCave[sizeof(uintptr_t)];
	mem.ParseAddress(srcToCaveJump, pCave);

	int y = 1;
	if (srcToCaveJump > (uintptr_t)(sizeof(uintptr_t) > 4) ? INT64_MAX : INT_MAX)
	{
		for (int x = addySize; x > 0; x--)
		{
			if (x == addySize)
				srcJump[x] = pCave[x - x];
			else
			{
				srcJump[x] = pCave[x - (x - y)];
				y++;
			}
		}

	}
	else
	{
		for (int x = 1; x < 5; x++)
		{
			srcJump[x] = pCave[x - 1];
		}
	}

	for (UINT x = 0; x < addySize; x++)
	{
		if (x > 4)
			srcJump[x] = 0x90;
	}

	mem.write.WriteBytes(pAddress, srcJump, szSize);
	srcJump = NULL;
}

void Hack::ToggleInjection()
{
	if (bEnabled)
	{
		if (pCaveAddress == NULL)
			HookInit();

		WriteCaveData();
		WriteJmp2Cave();
	}
	else
	{
		mem.write.WriteBytes(pAddress, (byte*)&vOldBytes[0], szSize);
	}
}

void Hack::Toggle()
{
	bEnabled = !bEnabled;
	if (ht == HackType::CODEPATCH)
	{
		TogglePatch();
	}
	else if (ht == HackType::HOOK)
	{
		ToggleInjection();
	}
	else if (ht == HackType::VALWRITE)
	{
		WriteValue();
		bEnabled = false;
	}
	// Freezing isn't toggled here.
}

void Hack::AddHackToVec()
{
	pGVHacks.push_back(*this);
}
