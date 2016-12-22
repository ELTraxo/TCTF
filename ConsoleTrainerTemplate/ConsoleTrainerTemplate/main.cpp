#include "includes.h"

int main()
{
	Memory mem;
	puts("Testing Framework...");
	mem.Init(L"ac_client.exe");
	puts("Found Game!");

	uintptr_t pHealth = mem.EvaluatePointer((uintptr_t)0x0050FC84, new UINT[2]{ 0, 0x27C }, 2);
	int64_t health = 0;
	if (mem.ReadInt64(pHealth, &health))
	{
		printf("Health: %I64d\n", health);
	}
	else
	{
		printf("Failure...\n");
	}
	system("pause");
	return 0;
}