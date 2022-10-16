#include "memory.h"
#include <Psapi.h>
#include <vector>

MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule == NULL)
		return modinfo;

	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}
BYTE GetBit(char chr)
{
	chr = tolower(chr);

	if ('a' <= chr and chr <= 'z')
		return chr - 'a' + 10;
	return chr - '0';

}
std::vector<BYTE> GetSignatureBytes(const char* str)
{
	std::vector<BYTE> bytes;
	const auto length = strlen(str);

	for (size_t i = 0; i < length;)
	{
		if (str[i] == ' ')
		{
			i += 1;
			continue;
		}
		if (str[i] == '?')
		{
			bytes.push_back('\?');
			(str[i + 1] == '?') ? i += 2 : i++;
			continue;
		}
		bytes.push_back( GetBit(str[i]) * 16 + GetBit(str[i + 1]) );
		i += 2;
	}

	return bytes;
}

uintptr_t Memory::FindPattern(const char* moduleName, const char* signature)
{
	MODULEINFO mInfo = GetModuleInfo(moduleName);
	const auto base = (uintptr_t)mInfo.lpBaseOfDll;
	const auto size = (uintptr_t)mInfo.SizeOfImage;

	const auto pattern = GetSignatureBytes(signature);

	for (uintptr_t i = 0; i < size - pattern.size(); i++)
	{
		bool found = true;
		for (uintptr_t j = 0; j < pattern.size(); j++)
		{
			found = pattern[j] == '\?' || pattern[j] == *(BYTE*)(base + i + j);
			if (not found)
				break;
		}
		if (found)
			return base + i;
	}

	return NULL;
}
