#pragma once
#include "l4d2.h"

class Client
{
public:
	union
	{
		DEFINE_MEMBER_N(int, ForceJump, offsets::dwForceJump);

	};
};