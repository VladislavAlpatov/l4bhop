#include <Windows.h>
#include "utils/memory.h"
#include "utils/xorstr.h"
#include "SDK/CLocalPlayer.h"
#include "SDK/CUserCmd.h"
#include <MinHook.h>
#include "d3d9.h"
#include "d3dx9.h"


LPVOID oCreateMove = nullptr;
LPVOID oPresent    = nullptr;

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

void RenderText(ID3DXFont* pFont,int x, int y, const wchar_t* txt)
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i and j)
            {
                RECT rct = {x+i, y+j, 0, 0}; //Font
                pFont->DrawTextW(nullptr, txt, -1,&rct, DT_NOCLIP , D3DCOLOR_RGBA(0,0,0, 255));
            }
    RECT rct = {x, y, 0, 0}; //Fon
    pFont->DrawTextW(nullptr, txt, -1,&rct, DT_NOCLIP , D3DCOLOR_RGBA(255,255,255, 255));


}


int __stdcall  hkPresent(LPDIRECT3DDEVICE9 pDevice, int a2, int a3, int a4, int a5)
{
    static ID3DXFont* pFont = nullptr;
    if (!pFont)
        D3DXCreateFontA( pDevice, 13, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Verdana"), &pFont);
    RenderText(pFont, 0,0, L"L4BHOP");

    typedef int(__stdcall* Present)(LPDIRECT3DDEVICE9, int, int, int, int);
    return reinterpret_cast<Present>(oPresent)(pDevice, a2, a3, a4, a5);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    while (!GetModuleHandleA(xorstr("client.dll")))
        Sleep(50);

    MH_Initialize();
    const auto pCreateMove = memory::FindPattern(xorstr("client.dll"), xorstr("55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01"));
    const auto  pPresent = memory::FindPattern(xorstr("d3d9.dll"), xorstr("?? ?? ?? ?? ?? 83 E4 F8 51 51 56 8B 75 08 8B CE F7 D9 57 1B C9 8D 46 04 23 C8 6A ?? 51 8D 4C 24 10 E8 ?? ?? ?? ?? F7 46 ?? ?? ?? ?? ?? 74 07 BF ?? ?? ?? ?? EB 17"));

    MH_CreateHook((LPVOID)pCreateMove, (void*)hCreateMove, &oCreateMove);
    MH_CreateHook((LPVOID)pPresent, (void*)hkPresent, &oPresent);

    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);


    while (!GetAsyncKeyState(VK_END))
        Sleep(50);

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
