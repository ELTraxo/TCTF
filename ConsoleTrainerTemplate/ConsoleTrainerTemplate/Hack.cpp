#include "includes.h"


Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, pAddress);
	this->szSize = szSize;
}

Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, int value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, pAddress);
	iValue = value;
}

Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, int64_t value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, pAddress);
	i64Value = value;
}

Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, float value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, pAddress);
	fValue = value;
}

Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, double value)
	:
	mem(mem)
{
	InitTypeAndAddress(ht, pAddress);
	dValue = value;
}

Hack::~Hack()
{
	if (pOffsets)
		delete pOffsets;
}

void Hack::InitTypeAndAddress(HackType ht, uintptr_t pAddress)
{
	this->ht = ht;
	this->pAddress = pAddress;
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

void Hack::Toggle()
{
	if (ht == HackType::CODEPATCH)
	{
		TogglePatch();
	}
}
