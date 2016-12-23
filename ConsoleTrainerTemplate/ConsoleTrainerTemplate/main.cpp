#include "includes.h"

int main()
{
	Memory mem;
	puts("Testing Framework...");
	mem.Init(L"ac_client.exe");
	puts("Found Game!");

	byte bArray[3];

	mem.read.ReadBytes((uintptr_t)0x00429D1F, bArray, 3);

	int pHealth;
	mem.read.ReadInt((uintptr_t)0x0C3EAEAC, pHealth);

	system("pause");
	return 0;
}