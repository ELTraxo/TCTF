#include "includes.h"

// code patch ctor
Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, vt, pAddress);
	this->szSize = szSize;
}

// val freeze ctors...
Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, int value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, vt, pAddress);
	iValue = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int value)
	:
	mem(mem)
{
	InitTypeAndPointer(ht, vt, pBase, Offsets, count);
	iValue = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, int64_t value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, vt, pAddress);
	i64Value = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, int64_t value)
	:
	mem(mem)
{
	InitTypeAndPointer(ht, vt, pBase, Offsets, count);
	i64Value = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, float value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, vt, pAddress);
	fValue = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, float value)
	:
	mem(mem)
{
	InitTypeAndPointer(ht, vt, pBase, Offsets, count);
	fValue = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pAddress, double value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, vt, pAddress);
	dValue = value;
}

Hack::Hack(Memory & mem, HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count, double value)
	:
	mem(mem)
{
	InitTypeAndPointer(ht, vt, pBase, Offsets, count);
	dValue = value;
}

Hack::~Hack()
{
	if (pOffsets)
		delete pOffsets;
}

void Hack::InitTypeAndAddress(HackType ht, ValType vt, uintptr_t pAddress)
{
	this->ht = ht;
	this->vt = vt;
	this->pAddress = pAddress;
	AddHackToVec();
}

void Hack::InitTypeAndPointer(HackType ht, ValType vt, uintptr_t pBase, UINT * Offsets, UCHAR count)
{
	this->ht = ht;
	this->vt = vt;
	this->pBase;
	this->pOffsets = Offsets;
	this->ucOffsetCount = count;
	AddHackToVec();
}

void Hack::TogglePatch()
{
	bEnabled = !bEnabled;
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
	if (ht == HackType::CODEPATCH)
	{
		TogglePatch();
	}
	bEnabled = !bEnabled;
}

void Hack::AddHackToVec()
{
	mem.AddHackToVec(*this);
}

void Hack::AddToVec(std::vector<Hack>& hack)
{
	hack.push_back(*this);
}
