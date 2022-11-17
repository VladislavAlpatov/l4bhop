//
// Created by Vlad on 18.10.2022.
//
#pragma once
#include <Windows.h>

namespace memory
{
    DWORD FindPattern(const char* moduleName, const char* signature);

}