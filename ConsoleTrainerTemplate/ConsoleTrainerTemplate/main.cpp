#include "includes.h"

int main()
{
	Memory mem;
	
	puts("Testing Framework...");
	mem.Init(L"ac_client.exe");
	puts("Found Game!");
	
	byte bArry[2] = {0};
	mem.read.ReadBytes((uintptr_t)0x004637E9, bArry, 2);

	Hack InfAmmo(mem, HackType::CODEPATCH, (uintptr_t)0x004637E9, 2);
	InfAmmo.Toggle();
	InfAmmo.Toggle();

	system("pause");
	return 0;
}