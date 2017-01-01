#include "includes.h"
#include "HexStr.h"

Memory::Memory()
	:
	read(*this),
	write(*this),
	pattern(*this)
{
}

//Blocking constructor...
Memory::Memory(TCHAR * GameName)
	:
	read(*this),
	write(*this),
	pattern(*this)
{
	this->wcsGameName = GameName;
	Init();
}

Memory::~Memory()
{
}

// Main init function
void Memory::Init()
{
	if (wcsGameName)
	{
		while (pID == NULL)
			GetProcID();

		if (!OpenProc())
		{
			std::cerr << "ERROR: Could not open process." << std::endl;
		}

		// Freeze values thread
		std::thread tr(&FreezeThread, *this);
		tr.detach();
	}
	else
	{
		std::cerr << "ERROR: Game name has not been specified." << std::endl;
	}
}

void Memory::Init(TCHAR * GameName)
{
	this->wcsGameName = GameName;
	Init();
}

void Memory::ReInit()
{
	hProcess = NULL;
	pID = NULL;
	me32 = { 0 };
	this->Init();
}

bool Memory::GetProcID()
{
	if (GetProcID(this->pID, *this->wcsGameName))
		return true;
	else
		return false;
}

bool Memory::GetProcID(DWORD & pID, const TCHAR & GameName)
{
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hSnap, &pe))
	{
		if (!wcscmp(pe.szExeFile, &GameName))
		{
			pID = pe.th32ProcessID;
		}
		else
		{
			while (Process32Next(hSnap, &pe))
			{
				if (!wcscmp(pe.szExeFile, &GameName))
				{
					pID = pe.th32ProcessID;
					return true;
				}
			}
		}
	}
	return false;
}

bool Memory::OpenProc()
{
	if (pID == NULL)
	{
		return false;
	}
	else
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
		if (!hProcess)
			return false;
	}
	return true;
}

bool Memory::CheckProcDeath()
{
	DWORD pid = 0;
	if (GetProcID(pid, *wcsGameName))
	{
		if (pid != pID)
			return true;
		else
			return false;
	}
	return true;
}

bool Memory::GetProcDeathVar()
{
	return ProcDied;
}

void Memory::ParseAddress(uintptr_t pAddress, byte * pBytesArr)
{
	std::string sAddy;

	std::string sAddress;

	std::stringstream ss(sAddress);
	ss << std::hex << pAddress;
	ss >> sAddy;

	if (sizeof(uintptr_t) == 4)
	{
		if (sAddy.length() < 7)
		{
			std::string buff = "";// = std::string(sAddy);
			for (UINT x = 0; x < (8 - sAddy.length()); x++)
			{
				buff += "0";
			}
			buff += sAddy;
			sAddy = buff;
		}
	}
	else
	{
		if (sAddy.length() < 15)
		{
			std::string buff = "";// = std::string(sAddy);
			for (UINT x = 0; x < (16 - sAddy.length()); x++)
			{
				buff += "0";
			}
			buff += sAddy;
			sAddy = buff;
		}
	}
	byte pAddyBytes[sizeof(uintptr_t)];

	
	hex2bin(sAddy.c_str(), (char*)pAddyBytes);
	//pBytesArr = new byte[4];
	memcpy(pBytesArr, pAddyBytes, sizeof(uintptr_t));
}

uintptr_t Memory::EvaluatePointer(uintptr_t pBase, UINT * offsets, UCHAR count)
{
	uintptr_t evAddress;

	if (ReadProcessMemory(hProcess, (void*)pBase, &evAddress, sizeof(uintptr_t), nullptr))
	{
		if (count > 1)
		{
			for (UCHAR x = 0; x < count - 1; x++)
			{
				if (!ReadProcessMemory(hProcess, (void*)(evAddress + offsets[x]), &evAddress, sizeof(uintptr_t), nullptr))
					return 0;
			}
		}
	}
	else
		return 0;

	return (evAddress + offsets[count - 1]);
}

Memory::Read::Read(Memory & mem)
	:
	mem(mem)
{
}

bool Memory::Read::ReadInt(uintptr_t pAddress, int & pReadBuff)
{
	if (ReadProcessMemory(mem.hProcess, (void*)pAddress, &pReadBuff, sizeof(int), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Read::ReadInt64(uintptr_t pAddress, int64_t & pReadBuff)
{
	if (ReadProcessMemory(mem.hProcess, (void*)pAddress, &pReadBuff, sizeof(int64_t), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Read::ReadFloat(uintptr_t pAddress, float & pReadBuff)
{
	if (ReadProcessMemory(mem.hProcess, (void*)pAddress, &pReadBuff, sizeof(float), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Read::ReadDouble(uintptr_t pAddress, double & pReadBuff)
{
	if (ReadProcessMemory(mem.hProcess, (void*)pAddress, &pReadBuff, sizeof(double), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Read::ReadBytes(uintptr_t pAddress, byte * pReadBuff, SIZE_T szSize)
{
	if (ReadProcessMemory(mem.hProcess, (void*)pAddress, pReadBuff, szSize, nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

Memory::Write::Write(Memory & mem)
	:
	mem(mem)
{	
}

bool Memory::Write::WriteInt(uintptr_t pAddress, int & pWriteBuff)
{
	if (WriteProcessMemory(mem.hProcess, (void*)pAddress, &pWriteBuff, sizeof(int), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}
	
bool Memory::Write::WriteInt64(uintptr_t pAddress, int64_t & pWriteBuff)
{
	if (WriteProcessMemory(mem.hProcess, (void*)pAddress, &pWriteBuff, sizeof(int64_t), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Write::WriteFloat(uintptr_t pAddress, float & pWriteBuff)
{
	if (WriteProcessMemory(mem.hProcess, (void*)pAddress, &pWriteBuff, sizeof(float), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Write::WriteDouble(uintptr_t pAddress, double & pWriteBuff)
{
	if (WriteProcessMemory(mem.hProcess, (void*)pAddress, &pWriteBuff, sizeof(double), nullptr))
		return true;
	else
	{
		mem.ProcDied = mem.CheckProcDeath();
		return false;
	}
}

bool Memory::Write::WriteBytes(uintptr_t pAddress, byte * pByteArray, SIZE_T szSize)
{
	if (pByteArray == nullptr)
	{
		byte * nops = new byte[szSize];
		for (UINT x = 0; x < szSize; x++)
			nops[x] = 0x90;

		if (WriteProcessMemory(mem.hProcess, (void*)pAddress, nops, szSize, nullptr))
		{
			delete[] nops;
			return true;
		}
		else
		{
			delete[] nops;
			mem.ProcDied = mem.CheckProcDeath();
			return false;
		}
	}
	else
	{
		if (WriteProcessMemory(mem.hProcess, (void*)pAddress, pByteArray, szSize, nullptr))
			return true;
		else
		{
			mem.ProcDied = mem.CheckProcDeath();
			return false;
		}
	}
}

Memory::Pat::Pat(Memory & mem)
	:
	mem(mem)
{
}

bool Memory::Pat::CheckPattern(char * bArray, const char * pattern, const char * mask, UINT szSize, uintptr_t & patternOffset, bool bCodeCave)
{
	SIZE_T pLen = strlen(mask);
	for (uintptr_t x = 0; x < szSize; x++)
	{
		bool bFound = true;
		for (uintptr_t y = 0; y < pLen; y++)
		{
			if (!bCodeCave) 
			{
				if (mask[y] != '?' && pattern[y] != bArray[x + y])
				{
					bFound = false;
					break;
				}
			}
			else
			{
				if (bArray[x + y] != 0x00)
				{
					bFound = false;
					break;
				}
			}
		}
		if (bFound)
		{
			patternOffset = x;
			return true;
		}
	}

	return false;
}

uintptr_t Memory::Pat::Scan(uintptr_t uiBegin, uintptr_t uiEnd, const char * pattern, const char * mask, bool bCodeCave)
{
	uintptr_t patternOffset = 0;
	char * bArray;
	bool bFound = false;
	while (uiBegin < uiEnd)
	{
		MEMORY_BASIC_INFORMATION mbi;
		if (!VirtualQueryEx(mem.hProcess, (void*)uiBegin, &mbi, sizeof(MEMORY_BASIC_INFORMATION)))
			return 0;

		bArray = new char[mbi.RegionSize];

		DWORD dwOldProtection;

		if (mbi.State == MEM_COMMIT && mbi.Protect != PAGE_NOACCESS)
		{
			VirtualProtectEx(mem.hProcess, (void*)mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
			if (!mem.read.ReadBytes((uintptr_t)mbi.BaseAddress, (byte*)bArray, mbi.RegionSize))
				std::cerr << "Failed to read memory" << std::endl;
			VirtualProtectEx(mem.hProcess, (void*)mbi.BaseAddress, mbi.RegionSize, dwOldProtection, nullptr);
			if (CheckPattern(bArray, pattern, mask, mbi.RegionSize, patternOffset, bCodeCave))
			{
				bFound = true;
				break;
			}
		}
		uiBegin += mbi.RegionSize;		
	}
	delete[] bArray;
	if (!bFound) return uintptr_t(0);
	return uintptr_t(uiBegin + patternOffset);
}

bool Memory::Pat::GetModule(TCHAR * pModName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, mem.pID);
	MODULEENTRY32 modEntry;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		modEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &modEntry))
		{
			do
			{
				if (!_tcscmp(modEntry.szModule, pModName))
				{
					mem.me32 = modEntry;
					CloseHandle(hSnapshot);
					return true;
				}
			} while (Module32Next(hSnapshot, &modEntry));
		}
		CloseHandle(hSnapshot);
	}
	return false;
}

uintptr_t Memory::Pat::GetModuleBase(TCHAR * pModName)
{
	if (GetModule(pModName))
		return uintptr_t(mem.me32.modBaseAddr);
	else
		return uintptr_t(NULL);
}

uintptr_t Memory::Pat::ScanModule(TCHAR * pModName, const char * pattern, const char * mask, bool bCodeCave)
{
	if (GetModule(pModName))
	{
		return Scan((uintptr_t)mem.me32.modBaseAddr, (uintptr_t)(mem.me32.modBaseAddr + mem.me32.modBaseSize), pattern, mask, bCodeCave);
	}
	else
		return uintptr_t(NULL);
}

uintptr_t Memory::Pat::ScanProcess(const char * pattern, const char * mask, bool bCodeCave)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, mem.pID);
	MODULEENTRY32 modEntry = { 0 };

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		modEntry.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &modEntry))
		{
			uintptr_t pAddress = this->Scan((uintptr_t)modEntry.modBaseAddr, (uintptr_t)(modEntry.modBaseAddr + modEntry.modBaseSize), pattern, mask, bCodeCave);
			if (pAddress != uintptr_t(0))
			{
				CloseHandle(hSnapshot);
				return pAddress;
			}
			else
			{
				while (Module32Next(hSnapshot, &modEntry))
				{
					pAddress = this->Scan((uintptr_t)modEntry.modBaseAddr, (uintptr_t)(modEntry.modBaseAddr + modEntry.modBaseSize), pattern, mask, bCodeCave);
					if (pAddress != uintptr_t(0))
					{
						CloseHandle(hSnapshot);
						return pAddress;
					}
				}
			}
		}
	}

	return uintptr_t(0);
}

uintptr_t Memory::ScanForCodeCave(uintptr_t pStart, UINT szSize)
{
	char * pPattern = new char[szSize];
	char * pMask = new char[szSize];

	for (WORD x = 0; x < szSize; x++)
	{
		pPattern[x] = 0x00;
		pMask[x] = 'x';
	}

	uintptr_t pCodeCave = pattern.ScanProcess(pPattern, pMask, true);

	//if (pCodeCave == uintptr_t(0))
	//{
	//	for (WORD x = 0; x < szSize; x++)
	//	{
	//		pPattern[x] = 0x05;
	//		pMask[x] = 'x';
	//	}
	//	pCodeCave = pattern.Scan(0, 0x7FFFFFFF, pPattern, pMask, true);
	//}
	//else
	//{
	//	return pCodeCave;
	//}

	delete[] pPattern;
	delete[] pMask;

	return pCodeCave;
}

