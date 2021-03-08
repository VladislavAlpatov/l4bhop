#pragma once
#include "l4d2.h"
#include "Vec3.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class LocalPlayer
{
public:
	union
	{
		DEFINE_MEMBER_N(int, m_iFlags, offsets::m_Flags);
		DEFINE_MEMBER_N(Vector3, m_iVel, offsets::m_iVel);
	};
};
