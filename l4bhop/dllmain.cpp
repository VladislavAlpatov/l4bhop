#include <Windows.h>
#include "l4d2.h"
#include "LocalPlayer.h"
#include "Client.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    MessageBeep(MB_ICONINFORMATION);
    DWORD moduleBase = (DWORD)GetModuleHandle(L"client.dll");
    Client* client = (Client*)(moduleBase);

    while (!GetAsyncKeyState(VK_END))
    {
        LocalPlayer* localplayer = *(LocalPlayer**)(moduleBase + offsets::dwLocalPlayer);

        if (!GetAsyncKeyState(VK_SPACE))
        {
            Sleep(10);
        }
        else if ((localplayer->m_iFlags == FL_ONGROUND or localplayer->m_iFlags == FL_ONGROUND_DUCK or localplayer->m_iFlags == FL_ONGOUND_IN_WATHER or localplayer->m_iFlags == FL_ONGOUND_IN_WATHER_DUCK))
        {
            client->ForceJump = 5;
            Sleep(50);
            client->ForceJump = 4;

        }
        else if ( localplayer->m_iFlags == 130 and client->ForceJump == 5)
        {
            client->ForceJump = 4;
        }


    }
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}



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