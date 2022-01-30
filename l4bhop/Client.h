#pragma once
#include "l4d2.h"
#include "LocalPlayer.h"

class Client
{
public:
	union
	{
		DEFINE_MEMBER_N(int, m_iForceJump, offsets::dwForceJump);
		DEFINE_MEMBER_N(LocalPlayer*, m_pLocalPlayer, offsets::dwLocalPlayer);
	};
};