#include "Menu.h"


Menu::Menu(Trainer & tn)
	:
	tn(tn)
{
	Init();
}

Menu::Menu(Trainer & tn, std::string sHeader)
	:
	tn(tn)
{
	this->sHeader = sHeader;	
	this->bHasHeader = true;
}

Menu::~Menu()
{
}

void Menu::Init()
{
	Update();
}

void Menu::ClearScreen()
{
	for(int x = 0; x < 100; x++)
		printf("\n");
}

void Menu::AddHeader(std::string sHeader)
{
	bHasHeader = true;
	this->sHeader = sHeader;
}

void Menu::GetTrainerOpts()
{
	TrainerOpts = tn.GetOptions();
}

void Menu::PrintFooter()
{
	int iLines = 24;
	if (bHasHeader ) --iLines;
	iLines -= TrainerOpts.size();
	for (int x = 0; x < iLines; x++)
		printf("\n");
}

void Menu::Update()
{
	ClearScreen();
	if (tn.IsReady())
	{
		GetTrainerOpts();
		std::cout << " " << sHeader << std::endl;
		for each (Hack hack in TrainerOpts)
			std::wcout << " " << hack.GetName() << "\t\t" << ((hack.GetStatus()) ? "On" : "Off") << std::endl;
	}
	else
	{
		std::cout << "Searching for process..." << std::endl;
	}

	PrintFooter();
}
