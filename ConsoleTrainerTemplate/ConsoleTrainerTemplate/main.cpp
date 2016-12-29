#include "Traxo.h"
#include "Menu.h"

void TrainerInitializer(Trainer * tn);

int main()
{
	//Memory mem;	
	//puts("[Testing Framework]\nSearching for game...");
	//mem.Init(L"ac_client.exe");
	//puts("Found Game!");	
	////byte bArry[2] = {0};
	////mem.read.ReadBytes((uintptr_t)0x004637E9, bArry, 2);
	////Hack InfAmmo(mem, HackType::CODEPATCH, (uintptr_t)0x004637E9, 2);
	////InfAmmo.Toggle();
	////InfAmmo.Toggle();
	////char pattern[] = { 0xFF, 0x0E, 0x57, 0x8B, 0x7C, 0x24, 0x14, 0x8D, 0x74, 0x24, 0x28, 0xE8, 0x87, 0xE3, 0xFF, 0xFF, 0x5F, 0x5E, 0xB0, 0x01, 0x5B, 0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x55 };
	////uintptr_t DecAmmo = 0;
	////if (DecAmmo = mem.pattern.Scan(0x0, 0, 0x80000000, pattern, "xxxxx??xx??x????xxx?xxxxx??xxxxxxxxxxxxx"))
	////	puts("Found pattern!");
	////else
	////	puts("Didn't find shit!");
	////while (!mem.CheckProcDeath()); // <-- While has not died
	//uintptr_t pBase = (uintptr_t)0x50F4F4;
	//UINT pOffsets[] = { 0x358, 0x48, 0x1e8, 0x8, 0xf8 };
	//Hack InfAmmo(mem, GHackVec, HackType::VALFREEZE, ValType::I, pBase, pOffsets, 5, 169);	
	//InfAmmo.Toggle();
	////InfAmmo.AddHackToVec();
	//char pattern[] = { 0xFF, 0x0E, 0x57, 0x8B, 0x7C, 0x24, 0x14, 0x8D, 0x74, 0x24, 0x28, 0xE8, 0x87, 0xE3, 0xFF, 0xFF, 0x5F, 0x5E, 0xB0, 0x01, 0x5B, 0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x55 };
	//char mask[] = "xxxxx??xx??x????xxx?xxxxx??xxxxxxxxxxxxx";
	//uintptr_t DecAmmo = 0;
	//do
	//{
	//	DecAmmo = mem.pattern.ScanProcess(pattern, mask, false);
	//} while (DecAmmo == 0);
	//puts("Found pattern.");
	//uintptr_t pCodeCave = mem.ScanForCodeCave(0, 128);
	
	 // We could do it like dis
	//puts("Searching for game...");
	//tn->Init(L"ac_client.exe");
	//puts("Found Game!");
	//	
	//std::vector<UINT> GodOFs = { 0x358, 0x48, 0x1e8, 0x8, 0xf8 };
	//UINT ofGodMode[] = { 0x358, 0x48, 0x1e8, 0x8, 0xf8 };
	//Pointer pGodMode((uintptr_t)0x50f4f4, GodOFs);
	//Pointer pGodMode((uintptr_t)0x50f4f4, ofGodMode, (sizeof(ofGodMode) / sizeof(ofGodMode[0])));
	//Hack God = tn->make.MakeFreezePtrHack(L"God", pGodMode, 125);
	//God.SetHotkey(VK_NUMPAD2);
	//tn->AddOption(God);

	//// example of an injection hack.
	//TCHAR * sInfAmmo = L"Inf Ammo";
	//uintptr_t pAddress = 0x004637E6;
	//UINT szSize = 5;
	//std::vector<byte> vCaveData = { 0x8b, 0x76, 0x14 };

	//std::vector<byte> bPattern = { 0x8b, 0x76, 0x00, 0xff, 0x0e, 0x57, 0x8b, 0x7c, 0x00, 0x00, 0x8d, 0x74, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x5e, 0xb0, 0x00, 0x5b, 0x8b, 0xe5, 0x5d, 0xc2, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x55 };
	//std::string mask = "xx?xxxxx??xx??x????xxx?xxxxx??xxxxxxxxxxxxx";
	//std::vector<byte> bPattern = { 0xff, 0x0e, 0x57, 0x8b, 0x7c, 0x00, 0x00, 0x8d, 0x74, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x5e, 0xb0, 0x00, 0x5b, 0x8b, 0xe5, 0x5d, 0xc2, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x55 };
	//std::string mask = "xxxxx??xx??x????xxx?xxxxx??xxxxxxxxxxxxx";
	//Pat p(bPattern, mask);

	//Hack InfAmmo = tn->make.MakeInjectionHack(sInfAmmo, p, -3, szSize, vCaveData);

	//InfAmmo.SetHotkey(VK_NUMPAD1);
	//tn->AddOption(InfAmmo);

	//while (true)
	//{
	//	tn->Update();
	//	if (!tn->IsRunning())
	//	{
	//		system("cls");
	//		puts("Searching for game...");
	//		tn->ReInit();
	//	}
	//}
	
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