#pragma once

class Trainer
{
public:
	Trainer();
	Trainer(TCHAR * GameName);
	~Trainer();
	void Init();
	void Init(TCHAR * GameName);
	void AddOption(Hack & hack);
	Hack MakePatchHack(TCHAR * HackName, UINT pAddress, UINT szSize);
	void Toggle(TCHAR * HackName);
	void Update();

private:
	Memory mem;
	std::vector<std::reference_wrapper<Hack>> Options;
	TCHAR * GameName;
};

