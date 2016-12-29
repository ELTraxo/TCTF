#include "Menu.h"
#include "ConsoleColor.h"

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
	if (tn.IsReady()) { iLines -= TrainerOpts.size(); }
	for (int x = 0; x < iLines; x++)
		printf("\n");
}

void Menu::Update()
{
	ClearScreen();
	if (tn.IsReady())
	{
		GetTrainerOpts();
		std::cout << " " << (tn.IsRunning() ? green : red) << sHeader << white << std::endl;
		for each (Hack hack in TrainerOpts)
		{			
			size_t len = lstrlenW(hack.GetName()) + 1;
			char * hackName = new char[len];
		
			wcstombs(hackName, hack.GetName(), len);
			if (hack.GetStatus())
			{
				std::cout << " " << hackName << "\t\t" << red << "On" << white << std::endl;
			}
			else
			{
				std::cout << " " << hackName << "\t\t" << "Off" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Searching for process..." << std::endl;
	}

	PrintFooter();
}
