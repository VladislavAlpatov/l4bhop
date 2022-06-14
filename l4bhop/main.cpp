#include <Windows.h>
#include "l4d2.h"
#include "LocalPlayer.h"
#include "Client.h"
#include <MinHook.h>
#include "Utils/memory.h"

LPVOID oCreateMove = nullptr;

int __stdcall hCreateMove(float a1, int a2)
{
    typedef bool(__stdcall* tCreateMove)(int, int);

    LocalPlayer* localplayer = SSDK::GetLocalPLayer();
    auto pFoceJmp = SSDK::GetForceJump();
    if ( not GetAsyncKeyState(VK_SPACE) or localplayer == nullptr)
    {
        return reinterpret_cast<tCreateMove>(oCreateMove)(a1, a2);
    }
    else if ((localplayer->m_iFlags == FL_ONGROUND or localplayer->m_iFlags == FL_ONGROUND_DUCK or localplayer->m_iFlags == FL_ONGOUND_IN_WATHER or localplayer->m_iFlags == FL_ONGOUND_IN_WATHER_DUCK))
    {
        *pFoceJmp = 6;
    }
    else if (*pFoceJmp == 5)
    {
        *pFoceJmp = 4;
    }


    return reinterpret_cast<tCreateMove>(oCreateMove)(a1, a2);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    MH_Initialize();

    MH_CreateHook((LPVOID)Memory::FindPattern("client.dll", "55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01"), hCreateMove, &oCreateMove);
    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);
    while (!GetAsyncKeyState(VK_END))
    {
        Sleep(100);
    }
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

// C0920

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}