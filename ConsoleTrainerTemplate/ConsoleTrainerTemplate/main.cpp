#include "Traxo.h"


void TrainerInitializer(Trainer * tn);

int main()
{	
	Trainer * tn = &trainer;
	Menu menu(*tn, "Traxo's Awesome Haxo");
	menu.Init();
	TrainerInitializer(tn);
	menu.Update();
	while (true)
	{
		if (tn->Update()) //If you toggle a hack it returns true.
			menu.Update();
		if (!tn->IsRunning())
		{
			menu.Update();
			tn->ReInit();
			menu.Update();
		}
	}

	system("pause");
	return 0;
}

void TrainerInitializer(Trainer * tn)
{
	//Initialize the trainer.
	tn->Init(L"ac_client.exe");

	//Create hack, set hotkey, add it to trainer.
	static Hack InfAmmo = tn->make.MakePatchHack(L"Inf Ammo", 0x4637E9, 2);
	InfAmmo.SetHotkey(VK_NUMPAD1);
	tn->AddOption(InfAmmo);

	Pointer pHealth = Pointer(0x50f4f4, std::vector<UINT>{0x358, 0x48, 0x1e8, 0x8, 0xf8});
	static Hack InfHealth = tn->make.MakeFreezePtrHack(L"Inf Health", pHealth, 150);
	InfHealth.SetHotkey(VK_NUMPAD2);
	tn->AddOption(InfHealth);
}