#include <Windows.h>
#include <iostream>
#include "l4d2.h"

DWORD WINAPI HackThread(HMODULE hModule)
{

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
 
    printf("(C) Little Software Studio\n");

    Sleep(2000);
    fclose(f);
    FreeConsole();
    DWORD moduleBase = (DWORD)GetModuleHandle(L"client.dll");

    while (!GetAsyncKeyState(VK_END))
    {
        DWORD localplayer = *(DWORD*)(moduleBase + signatures::dwLocalPlayer);
        int m_flags = *(int*)(localplayer + signatures::m_Flags);

        if (GetAsyncKeyState(VK_SPACE) and m_flags == FL_ONGROUND or m_flags == FL_ONGROUND_DUCK)
        {
            *(int*)(moduleBase + signatures::dwForceJump) = 5;
            Sleep(1);
            *(int*)(moduleBase + signatures::dwForceJump) = 4;
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