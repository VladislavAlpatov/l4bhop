#pragma once
#include <Windows.h>

#define FL_ONGROUND 129
#define FL_ONGROUND_DUCK 131

namespace signatures
{
	DWORD dwLocalPlayer = 0x71A044;
	DWORD m_Flags = 0xF0;
	DWORD dwForceJump = 0x739948;
	DWORD m_Health = 0xec;
}