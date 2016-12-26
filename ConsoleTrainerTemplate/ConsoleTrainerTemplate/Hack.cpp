#include "includes.h"

// code patch ctor
Hack::Hack(TCHAR * GameName, Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize)
	:
	mem(mem),
	gvHacks(std::vector<std::reference_wrapper<Hack>>()) //Don't really need a ref to the global hacks vec
{
	InitHackAndAddress(GameName, ht, vt, pAddress);
	this->szSize = szSize;
}

// val freeze ctors...
Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pAddress, int value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndAddress(GameName, ht, vt, pAddress);
	iValue = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndPointer(GameName, ht, vt, pBase, Offsets, count);
	iValue = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pAddress, int64_t value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndAddress(GameName, ht, vt, pAddress);
	i64Value = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int64_t value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndPointer(GameName, ht, vt, pBase, Offsets, count);
	i64Value = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pAddress, float value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndAddress(GameName, ht, vt, pAddress);
	fValue = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, float value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndPointer(GameName, ht, vt, pBase, Offsets, count);
	fValue = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pAddress, double value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndAddress(GameName, ht, vt, pAddress);
	dValue = value;
}

Hack::Hack(TCHAR * GameName, Memory & mem, std::vector<std::reference_wrapper<Hack>> & gvHacks, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, double value)
	:
	mem(mem),
	gvHacks(gvHacks)
{
	InitHackAndPointer(GameName, ht, vt, pBase, Offsets, count);
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
	AddHackToVec();
}

TCHAR * Hack::GetName()
{
	return HackName;
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

void Hack::Toggle()
{
	bEnabled = !bEnabled;
	if (ht == HackType::CODEPATCH)
	{
		TogglePatch();
	}
}

void Hack::AddHackToVec()
{
	gvHacks.push_back(*this);
}

void Hack::AddToVec(std::vector<Hack>& hack)
{
	hack.push_back(*this);
}
