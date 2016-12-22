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
	
	class Read
	{
	public:
		Read(Memory & mem);
		BOOL ReadInt(uintptr_t pAddress, int * pReadBuff);
		BOOL ReadInt64(uintptr_t pAddress, int64_t * pReadBuff);
		BOOL ReadFloat(uintptr_t pAddress, float * pReadBuff);
		BOOL ReadDouble(uintptr_t pAddress, double * pReadBuff);

	private:
		Memory & mem;
	}read;

	BOOL WriteInt(uintptr_t pAddress, int * pWriteBuff);
	BOOL WriteInt64(uintptr_t pAddress, int64_t * pWriteBuff);
	BOOL WriteFloat(uintptr_t pAddress, float * pWriteBuff);
	BOOL WriteDouble(uintptr_t pAddress, double * pWriteBuff);

private:
	wchar_t * wcsGameName = nullptr;
	HANDLE hProcess = nullptr;
	DWORD pID = NULL;
};

