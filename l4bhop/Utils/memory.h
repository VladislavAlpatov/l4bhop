#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <vector>

namespace Memory
{
	uintptr_t FindPattern(const char* moduleName, const char* signature);
}