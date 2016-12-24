#pragma once
#include <TlHelp32.h>
#include <vector>

struct FreezerSp
{
	uintptr_t pAddress;
	int iValue;
	int64_t i64Value;
	float fValue;
	double dValue;
};

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
		BOOL ReadInt(uintptr_t pAddress, int & pReadBuff);
		BOOL ReadInt64(uintptr_t pAddress, int64_t & pReadBuff);
		BOOL ReadFloat(uintptr_t pAddress, float & pReadBuff);
		BOOL ReadDouble(uintptr_t pAddress, double & pReadBuff);
		BOOL ReadBytes(uintptr_t pAddress, byte * pReadBuff, SIZE_T szSize);
	private:
		Memory & mem;
	}read;

	class Write
	{
	public:
		Write(Memory & mem);
		BOOL WriteInt(uintptr_t pAddress, int & pWriteBuff);
		BOOL WriteInt64(uintptr_t pAddress, int64_t & pWriteBuff);
		BOOL WriteFloat(uintptr_t pAddress, float & pWriteBuff);
		BOOL WriteDouble(uintptr_t pAddress, double & pWriteBuff);
		BOOL WriteBytes(uintptr_t pAddress, byte * pByteArray, SIZE_T szSize);
	private: 
		Memory & mem;
	}write;
	
	class Pattern
	{
	public:
		Pattern(Memory & mem);
		bool CheckPattern(char * bArray, char * pattern, char * mask, UINT szSize, UINT & patternOffset);
		uintptr_t Scan(uintptr_t pStart, UINT uiBegin, UINT uiEnd, char * pattern, char * mask);
	private:
		Memory & mem;
	}pattern;


private:
	wchar_t * wcsGameName = nullptr;
	HANDLE hProcess = nullptr;
	DWORD pID = NULL;
};

