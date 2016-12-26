#pragma once


enum ValType
{
	I, I64, F, D
};

class Pointer
{
public:
	Pointer(uintptr_t pBase, UINT * pOffsets, UCHAR ofCount)
	{
		this->pBase = pBase;
		this->pOffsets = pOffsets;
		this->ofCount = ofCount;
	}

	Pointer(uintptr_t pBase, std::vector<UINT> & vOffsets)
	{
		this->pBase = pBase;
		ofCount = vOffsets.size();
		pOffsets = new UINT[ofCount];

		for (SIZE_T x = 0; x < ofCount; x++)
			pOffsets[x] = vOffsets[x];		
	}

	uintptr_t pBase;
	UINT * pOffsets;
	UCHAR ofCount;
};

class Hack;

class Memory
{
public:
	Memory();
	Memory(TCHAR * GameName);
	~Memory();
	void Init();
	void Init(TCHAR * GameName);
	bool GetProcID();
	bool GetProcID(DWORD & pID, const TCHAR & GameName);
	bool OpenProc();
	bool CheckProcDeath();
	bool GetProcDeathVar();

	
	uintptr_t EvaluatePointer(uintptr_t pBase, UINT * offsets, UCHAR count);
	
	class Read
	{
	public:
		Read(Memory & mem);
		bool ReadInt(uintptr_t pAddress, int & pReadBuff);
		bool ReadInt64(uintptr_t pAddress, int64_t & pReadBuff);
		bool ReadFloat(uintptr_t pAddress, float & pReadBuff);
		bool ReadDouble(uintptr_t pAddress, double & pReadBuff);
		bool ReadBytes(uintptr_t pAddress, byte * pReadBuff, SIZE_T szSize);
	private:
		Memory & mem;
	}read;

	class Write
	{
	public:
		Write(Memory & mem);
		bool WriteInt(uintptr_t pAddress, int & pWriteBuff);
		bool WriteInt64(uintptr_t pAddress, int64_t & pWriteBuff);
		bool WriteFloat(uintptr_t pAddress, float & pWriteBuff);
		bool WriteDouble(uintptr_t pAddress, double & pWriteBuff);
		bool WriteBytes(uintptr_t pAddress, byte * pByteArray, SIZE_T szSize);
	private: 
		Memory & mem;
	}write;
	
	class Pattern
	{
	public:
		Pattern(Memory & mem);
		bool CheckPattern(char * bArray, char * pattern, char * mask, UINT szSize, UINT & patternOffset, bool bCodeCave);
		uintptr_t Scan(UINT uiBegin, UINT uiEnd, char * pattern, char * mask, bool bCodeCave);
		bool GetModule(TCHAR * pModName);
		uintptr_t ScanModule(TCHAR * pModName, char * pattern, char * mask, bool bCodeCave);
		uintptr_t ScanProcess(char * pattern, char * mask, bool bCodeCave);

	private:
		Memory & mem;
	}pattern;
	
	uintptr_t ScanForCodeCave(uintptr_t pStart, UWORD szSize);

private:
	TCHAR * wcsGameName = nullptr;
	HANDLE hProcess = nullptr;
	DWORD pID = NULL;
	MODULEENTRY32 me32;
	bool ProcDied = false;
	std::vector<Hack> Hacks;
};

void FreezeThread(Memory & mem);