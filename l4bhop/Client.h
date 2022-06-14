#pragma once
#include "l4d2.h"
#include "LocalPlayer.h"
#include "Utils/memory.h"


namespace SSDK
{
	LocalPlayer* GetLocalPLayer()
	{
		static auto ppLocalPlayer = *(LocalPlayer***)(Memory::FindPattern("client.dll", "B8 ? ? ? ? 39 10 74 10")+1);

		return *ppLocalPlayer;
	}
	int* GetForceJump()
	{
		static auto pForceJump = *(int**)(Memory::FindPattern("client.dll", "8B 04 B5 ? ? ? ? 8D 34 B5 ? ? ? ? A8 03 74 04 83 4D FC 02") + 3);
		return pForceJump;
	}
} 