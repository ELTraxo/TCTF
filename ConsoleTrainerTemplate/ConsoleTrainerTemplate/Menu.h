#pragma once
#include "Trainer.h"
class Menu
{
public:
	Menu(Trainer & tn);
	Menu(Trainer & tn, std::string sHeader);
	~Menu();
	void Init();
	void ClearScreen();
	void AddHeader(std::string sHeader);
	void GetTrainerOpts();
	void PrintFooter();
	std::string ParseHotkey(int hotKey);
	void Update();

private:
	Trainer & tn;

	bool bHasHeader = false;
	std::string sHeader;
	std::vector<std::reference_wrapper<Hack>> TrainerOpts;
};
