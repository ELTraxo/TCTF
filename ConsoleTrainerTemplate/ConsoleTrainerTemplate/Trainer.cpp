#include "includes.h"



Trainer::Trainer()
{
}

Trainer::Trainer(TCHAR * GameName)
{
	this->GameName = GameName;
}


Trainer::~Trainer()
{
}

void Trainer::Init()
{
	mem.Init(GameName);
}

void Trainer::Init(TCHAR * GameName)
{
	mem.Init(GameName);
}

void Trainer::AddOption(Hack & hack)
{
	Options.push_back(hack);
}

Hack Trainer::MakePatchHack(TCHAR * HackName, UINT pAddress, UINT szSize)
{
	return Hack(HackName, mem, HackType::CODEPATCH, (uintptr_t)pAddress, szSize);
}

void Trainer::Toggle(TCHAR * HackName)
{
	for each(Hack & hack in Options)
	{
		TCHAR * currName = hack.GetName();
		if (!_tcscmp(currName, HackName))
			hack.Toggle();
	}
}

void Trainer::Update()
{
	for each(Hack hack in Options)
	{
		if (GetAsyncKeyState(hack.GetHotkey()))
			hack.Toggle();
	}
}


