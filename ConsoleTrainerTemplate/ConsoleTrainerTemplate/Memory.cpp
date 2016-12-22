#include "includes.h"

Memory::Memory()
{
}

//Blocking constructor...
Memory::Memory(wchar_t * GameName)
{
	this->wcsGameName = GameName;
	Init();
}

Memory::~Memory()
{
}

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
	}
	else
	{
		std::cerr << "ERROR: Game name has not been specified." << std::endl;
	}
}

void Memory::Init(wchar_t * GameName)
{
	this->wcsGameName = GameName;
	Init();
}

void Memory::GetProcID()
{
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hSnap, &pe))
	{
		if (!wcscmp(pe.szExeFile, wcsGameName))
		{
			this->pID = pe.th32ProcessID;
		}
		else
		{
			while (Process32Next(hSnap, &pe))
			{
				if (!wcscmp(pe.szExeFile, wcsGameName))
				{
					this->pID = pe.th32ProcessID;
					break;
				}
			}
		}
	}
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

uintptr_t Memory::EvaluatePointer(uintptr_t pBase, UINT * offsets, UCHAR count)
{
	uintptr_t evAddress;

	if (ReadProcessMemory(hProcess, (void*)pBase, &evAddress, sizeof(uintptr_t), nullptr))
	{
		for (UCHAR x = 0; x < count - 1; x++)
		{
			if (!ReadProcessMemory(hProcess, (void*)(evAddress + offsets[x]), &evAddress, sizeof(uintptr_t), nullptr))
				return 0;
		}
	}
	else
		return 0;

	return (evAddress + offsets[count - 1]);
}

BOOL Memory::ReadInt(uintptr_t pAddress, int * pReadBuff)
{
	return ReadProcessMemory(hProcess, (void*)pAddress, pReadBuff, sizeof(int), nullptr);
}

BOOL Memory::ReadInt64(uintptr_t pAddress, int64_t * pReadBuff)
{
	return ReadProcessMemory(hProcess, (void*)pAddress, pReadBuff, sizeof(int64_t), nullptr);
}

BOOL Memory::ReadFloat(uintptr_t pAddress, float * pReadBuff)
{
	return ReadProcessMemory(hProcess, (void*)pAddress, pReadBuff, sizeof(float), nullptr);
}

BOOL Memory::ReadDouble(uintptr_t pAddress, double * pReadBuff)
{
	return ReadProcessMemory(hProcess, (void*)pAddress, pReadBuff, sizeof(double), nullptr);
}


