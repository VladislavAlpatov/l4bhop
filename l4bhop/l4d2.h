#pragma once
#include <Windows.h>

#define FL_ONGROUND 129
#define FL_ONGROUND_DUCK 131
#define FL_ONGOUND_IN_WATHER 641
#define FL_ONGOUND_IN_WATHER_DUCK 643

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

namespace offsets
{
	const DWORD dwLocalPlayer = 0x7B4DEC;
	const DWORD m_Flags = 0xF0;
	const DWORD dwForceJump = 0x74AA48;
	const DWORD m_Health = 0xec;
	const DWORD m_iVel = 0x100;
}