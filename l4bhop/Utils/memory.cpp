#pragma once
#include "memory.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule == NULL)
		return modinfo;

	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

BYTE StrHexToByte(const std::string& str)
{
	BYTE iOutNumber;
	std::stringstream ss;
	ss << std::hex << str;
	ss >> iOutNumber;
	return iOutNumber;
}

std::vector<BYTE> GetSignatureBytes(const std::string& str)
{
	std::vector<std::string> strs;
	std::vector<BYTE> bytes;
	boost::split(strs, str, boost::is_any_of(" "));

	for (auto& strHex : strs)
	{
		if (strHex == "??")
		{
			bytes.push_back('\?');
			continue;
		}

		bytes.push_back(StrHexToByte(strHex));

	}

	return bytes;
}

uintptr_t Memory::FindPattern(const char* moduleName, const char* signature)
{
	MODULEINFO mInfo = GetModuleInfo(moduleName);
	uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;
	uintptr_t size = (uintptr_t)mInfo.SizeOfImage;

	auto pattern = GetSignatureBytes(signature);

	for (uintptr_t i = 0; i < size - pattern.size(); i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < pattern.size(); j++)
		{
			found &= pattern[j] == '\?' || pattern[j] == *(BYTE*)(base + i + j);
			if (not found)
				break;
		}
		if (found)
			return base + i;
	}

	return NULL;
}
