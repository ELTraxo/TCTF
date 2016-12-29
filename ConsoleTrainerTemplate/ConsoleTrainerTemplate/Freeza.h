#pragma once
std::vector<std::reference_wrapper<Hack>> GHackVec;

void FreezeThread(Memory & mem)
{
	static auto tpDelay = std::chrono::steady_clock::now();
	auto tpNow = std::chrono::steady_clock::now();

	while (!mem.GetProcDeathVar())
	{
		tpNow = std::chrono::steady_clock::now();
		std::chrono::duration<float> check = tpNow - tpDelay;
		if (check.count() >= 0.01f)
		{
			if (!GHackVec.empty())
			{
				for each(Hack hack in GHackVec)
				{
					hack.WriteValue();
				}
			}
		}
	}
}