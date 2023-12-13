#pragma once
#include <Windows.h>

namespace Utils
{
	struct Unk
	{
		uint32_t unk00 = 0xFFFFFFFF;
		uint32_t unk04 = 0x0;
		uint32_t unk08 = 1;
	};

	RE::TESForm* GetFormFromMod(std::string modname, uint32_t formid);

	template <class Ty>
	Ty SafeWrite64Function(uintptr_t addr, Ty data)
	{
		DWORD oldProtect;
		void* _d[2];
		memcpy(_d, &data, sizeof(data));
		size_t len = sizeof(_d[0]);

		VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
		Ty olddata;
		memset(&olddata, 0, sizeof(Ty));
		memcpy(&olddata, (void*)addr, len);
		memcpy((void*)addr, &_d[0], len);
		VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
		return olddata;
	}
	std::string SplitString(const std::string str, const std::string delimiter, std::string& remainder);
	float BSRandomFloat(float f1, float f2);

	extern REL::Relocation<uint32_t*> ptr_invalidhandle;
	extern REL::Relocation<float*> ptr_engineTime;
	extern REL::Relocation<float*> ptr_deltaTime;
}
