#include <Windows.h>
#include <iostream>
#include "l4d2.h"

#include "LocalPlayer.h"
#include "Client.h"

DWORD WINAPI HackThread(HMODULE hModule)
{

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
 
    printf("(C) Little Software Studio\n");

    Sleep(3000);

    fclose(f);
    FreeConsole();

    DWORD moduleBase = (DWORD)GetModuleHandle(L"client.dll");
    Client* client = (Client*)(moduleBase);

    while (!GetAsyncKeyState(VK_END))
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            __try
            {
                LocalPlayer* localplayer = *(LocalPlayer**)(moduleBase + offsets::dwLocalPlayer);

                switch (localplayer->m_iFlags)
                {

                case FL_ONGROUND:
                case FL_ONGOUND_IN_WATHER:
                case FL_ONGOUND_IN_WATHER_DUCK:
                case FL_ONGROUND_DUCK:
                    client->ForceJump = 6;
                    Sleep(1);
                    break;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {

            }
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
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}