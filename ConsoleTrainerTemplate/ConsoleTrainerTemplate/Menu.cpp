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

std::string Menu::ParseHotkey(int hotKey)
{
	std::string key;

	switch (hotKey)
	{
	case VK_NUMPAD0:
		key = "NUM0";
		break;
	case VK_NUMPAD1:
		key = "NUM1";
		break;
	case VK_NUMPAD2:
		key = "NUM2";
		break;
	case VK_NUMPAD3:
		key = "NUM3";
		break;
	case VK_NUMPAD4:
		key = "NUM4";
		break;
	case VK_NUMPAD5:
		key = "NUM5";
		break;
	case VK_NUMPAD6:
		key = "NUM6";
		break;
	case VK_NUMPAD7:
		key = "NUM7";
		break;
	case VK_NUMPAD8:
		key = "NUM8";
		break;
	case VK_NUMPAD9:
		key = "NUM9";
		break;
	case VK_RETURN:
		key = "ENTER";
		break;
	case VK_DELETE:
		key = "DELETE";
		break;
	case VK_END:
		key = "END";
		break;
	case VK_INSERT:
		key = "INSERT";
		break;
	case VK_HOME:
		key = "HOME";
		break;
	case VK_F1:
		key = "F1";
		break;
	case VK_F2:
		key = "F2";
		break;
	case VK_F3:
		key = "F3";
		break;
	case VK_F4:
		key = "F4";
		break;
	case VK_F5:
		key = "F5";
		break;
	case VK_F6:
		key = "F6";
		break;
	case VK_F7:
		key = "F7";
		break;
	case VK_F8:
		key = "F8";
		break;
	case VK_F9:
		key = "F9";
		break;
	case VK_F10:
		key = "F10";
		break;
	case VK_F11:
		key = "F11";
		break;
	case VK_F12:
		key = "F12";
		break;
	}
	return key;
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
			size_t numOfCharConverted;
			wcstombs_s(&numOfCharConverted, hackName, len, hack.GetName(), len);
			if (hack.GetStatus())
			{
				std::cout << " [" << ParseHotkey(hack.GetHotkey()).c_str() << "] " << hackName << "\t\t" << red << "On" << white << std::endl;
			}
			else
			{
				std::cout << " [" << ParseHotkey(hack.GetHotkey()).c_str() << "] " << hackName << "\t\t" << "Off" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Searching for process..." << std::endl;
	}

	PrintFooter();
}
