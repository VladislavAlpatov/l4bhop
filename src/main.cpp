#include <Windows.h>
#include "utils/memory.h"
#include "utils/xorstr.h"
#include "SDK/CLocalPlayer.h"
#include "SDK/CUserCmd.h"
#include <MinHook.h>


LPVOID oCreateMove = nullptr;

int __stdcall hCreateMove(float a1, sdk::CUserCmd* pUserCmd)
{
    const sdk::CLocalPlayer* pLocalPlayer = sdk::CLocalPlayer::Get();

    if (pLocalPlayer == nullptr)
        return false;

    if (!(pLocalPlayer->m_iFlags & FL_ONGROUND))
        pUserCmd->m_iButtons &= ~sdk::CUserCmd::IN_JUMP;

    if (GetAsyncKeyState(VK_SHIFT))
        pUserCmd->m_iTickCount = 1677721;
    return false;
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    while (!GetModuleHandleA(xorstr("client.dll")))
        Sleep(50);

    MH_Initialize();
    const auto pCreateMove = memory::FindPattern(xorstr("client.dll"), xorstr("55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01"));

    MH_CreateHook((LPVOID)pCreateMove, (void*)hCreateMove, &oCreateMove);

    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);


    while (!GetAsyncKeyState(VK_END))
        Sleep(100);

    MH_DisableHook(MH_ALL_HOOKS);
    Sleep(100);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    FreeLibraryAndExitThread(hModule, 0);
}


extern "C" BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID lpvReserved
)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hinstDLL, 0, nullptr);
    }
    return TRUE;
}
