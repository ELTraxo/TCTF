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
	size_t ofCount;
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
	void ReInit();
	bool GetProcID();
	bool GetProcID(DWORD & pID, const TCHAR & GameName);
	bool OpenProc();
	bool CheckProcDeath();
	bool GetProcDeathVar();
	void ParseAddress(uintptr_t pAddress, byte * pByteArr);
	
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
	
	class Pat
	{
	public:
		Pat(Memory & mem);
		bool CheckPattern(char * bArray, const char * pattern, const char * mask, UINT szSize, uintptr_t & patternOffset, bool bCodeCave);
		uintptr_t Scan(uintptr_t uiBegin, uintptr_t uiEnd, const char * pattern, const char * mask, bool bCodeCave);
		bool GetModule(TCHAR * pModName);
		uintptr_t GetModuleBase(TCHAR * pModName);
		uintptr_t ScanModule(TCHAR * pModName, const char * pattern, const char * mask, bool bCodeCave);
		uintptr_t ScanProcess(const char * pattern, const char * mask, bool bCodeCave);

	private:
		Memory & mem;
	}pattern;
	
	uintptr_t ScanForCodeCave(uintptr_t pStart, size_t szSize);

private:
	TCHAR * wcsGameName = nullptr;
	HANDLE hProcess = nullptr;
	DWORD pID = NULL;
	MODULEENTRY32 me32;

public:
	bool ProcDied = false;
};

//void FreezeThread(Memory & mem);

class Pattern
{
public:
	Pattern(std::vector<byte> & pattern, std::string & mask)
		:
		vPattern(pattern),
		sMask(mask)
	{
	}

	std::vector<byte> & vPattern;
	std::string  sMask;
};