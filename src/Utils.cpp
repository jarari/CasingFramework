#include "Utils.h"

REL::Relocation<uint32_t*> Utils::ptr_invalidhandle{ REL::ID(888641) };
REL::Relocation<float*> Utils::ptr_engineTime{ REL::ID(599343) };
REL::Relocation<float*> Utils::ptr_deltaTime{ REL::ID(1013228) };

RE::TESForm* Utils::GetFormFromMod(std::string modname, uint32_t formid) {
	if (!modname.length() || !formid)
		return nullptr;
	return RE::TESDataHandler::GetSingleton()->LookupForm(formid, modname);
}

std::string Utils::SplitString(const std::string str, const std::string delimiter, std::string& remainder)
{
	std::string ret;
	size_t i = str.find(delimiter);
	if (i == std::string::npos) {
		ret = str;
		remainder = "";
		return ret;
	}

	ret = str.substr(0, i);
	remainder = str.substr(i + 1);
	return ret;
}

float Utils::BSRandomFloat(float f1, float f2)
{
	typedef float (*FnBSRandomFloat)(float, float);
	REL::Relocation<FnBSRandomFloat> func{ REL::ID(1118937) };
	return func(f1, f2);
}
