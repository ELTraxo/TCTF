#include "includes.h"

std::vector<std::reference_wrapper<Hack>> GHackVec;

void FreezeThread(Memory & mem)
{
	while (!mem.GetProcDeathVar())
	{
		if (!GHackVec.empty())
		{
			for each(Hack hack in GHackVec)
			{
				hack.WriteValue();
			}
		}
	}
}

int main()
{
	Memory mem;
	
	puts("Testing Framework...");
	mem.Init(L"ac_client.exe");
	puts("Found Game!");
	
	//byte bArry[2] = {0};
	//mem.read.ReadBytes((uintptr_t)0x004637E9, bArry, 2);

	//Hack InfAmmo(mem, HackType::CODEPATCH, (uintptr_t)0x004637E9, 2);
	//InfAmmo.Toggle();
	//InfAmmo.Toggle();
	//char pattern[] = { 0xFF, 0x0E, 0x57, 0x8B, 0x7C, 0x24, 0x14, 0x8D, 0x74, 0x24, 0x28, 0xE8, 0x87, 0xE3, 0xFF, 0xFF, 0x5F, 0x5E, 0xB0, 0x01, 0x5B, 0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x55 };
	//uintptr_t DecAmmo = 0;
	//if (DecAmmo = mem.pattern.Scan(0x0, 0, 0x80000000, pattern, "xxxxx??xx??x????xxx?xxxxx??xxxxxxxxxxxxx"))
	//	puts("Found pattern!");
	//else
	//	puts("Didn't find shit!");

	//while (!mem.CheckProcDeath()); // <-- While has not died
	uintptr_t pBase = (uintptr_t)0x50F4F4;
	UINT pOffsets[] = { 0x358, 0x48, 0x1e8, 0x8, 0xf8 };

	Hack InfAmmo(mem, GHackVec, HackType::VALFREEZE, ValType::I, pBase, pOffsets, 5, 169);
	
	InfAmmo.Toggle();
	//InfAmmo.AddHackToVec();
	while (!mem.CheckProcDeath());
	system("pause");
	return 0;
}