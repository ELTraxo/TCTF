#include "includes.h"


Hack::Hack(Memory & mem, HackType ht, uintptr_t pAddress, UINT szSize)
	:
	mem(mem)
{
	this->ht = ht;
	this->pAddress = pAddress;
	this->szSize = szSize;
}

Hack::~Hack()
{
	if (pOffsets)
		delete pOffsets;
}

void Hack::Toggle()
{
	if (ht == HackType::CODEPATCH)
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
}
