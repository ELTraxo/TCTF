#pragma once
#include <TlHelp32.h>

class Memory
{
public:
	Memory();
	Memory(wchar_t * GameName);
	~Memory();
	void Init();
	void Init(wchar_t * GameName);
	void GetProcID();
	bool OpenProc();
	
	uintptr_t EvaluatePointer(uintptr_t pBase, UINT * offsets, UCHAR count);
	BOOL ReadInt(uintptr_t pAddress, int * pReadBuff);
	BOOL ReadInt64(uintptr_t pAddress, int64_t * pReadBuff);
	BOOL ReadFloat(uintptr_t pAddress, float * pReadBuff);
	BOOL ReadDouble(uintptr_t pAddress, double * pReadBuff);

private:
	wchar_t * wcsGameName = nullptr;
	HANDLE hProcess = nullptr;
	DWORD pID = NULL;
};

