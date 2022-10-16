#include <climits>
#include <Windows.h>
#include "LocalPlayer.h"
#include "Client.h"
#include <MinHook.h>
#include "Utils/memory.h"

LPVOID oCreateMove = nullptr;

int __stdcall hCreateMove(float a1, SSDK::CUserCmd* pUserCmd)
{

	const LocalPlayer* pLocalPlayer = SSDK::GetLocalPLayer();

    if (pLocalPlayer == nullptr)
		return false;


    if (!(pLocalPlayer->m_iFlags & 1))
        pUserCmd->m_iButtons &= ~SSDK::CUserCmd::IN_JUMP;

    if (GetAsyncKeyState(VK_SHIFT))
        pUserCmd->m_iTickCount = 1677721;
    return false;
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    MH_Initialize();

    MH_CreateHook((LPVOID)Memory::FindPattern("client.dll", "55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01"), hCreateMove, &oCreateMove);
    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);
    while (!GetAsyncKeyState(VK_END))
    {

        Sleep(50);
    }
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

// C0920

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
    return TRUE;
}