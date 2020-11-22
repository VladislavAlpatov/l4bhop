#include <Windows.h>
#include <iostream>


DWORD WINAPI HackThread(HMODULE hModule)
{
    std::string hash = "write here some randome stuff";
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf("   __   ________\n");
    printf("  / /  / __/ __/\n");
    printf(" / /___\\ \\_\\ \\ \n");
    printf("/____/___/___/  \n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
    printf("(C) Little Software Studio\n");

    Sleep(2000);
    fclose(f);
    FreeConsole();

    DWORD moduleBase = (DWORD)GetModuleHandle(L"client.dll");

    while (!GetAsyncKeyState(VK_END))
    {
        int on_ground = *(int*)(moduleBase + 0x7615B8);
        if (GetAsyncKeyState(VK_SPACE) and on_ground)
        {
            *(int*)(moduleBase + 0x739948) = 5;
            Sleep(1);
            *(int*)(moduleBase + 0x739948) = 4;
        }
    }

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
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

