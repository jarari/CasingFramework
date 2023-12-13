#include <CasingManager.h>
#include <Globals.h>
#include <Hooks.h>
#include <Configs.h>
#include <Utils.h>

uintptr_t EjectShellCasingOrig;

void Hooks::InitializeHooks()
{
	F4SE::Trampoline& trampoline = F4SE::GetTrampoline();
	EjectShellCasingOrig = trampoline.write_call<5>(REL::Relocation<uintptr_t>{ REL::ID(1056037), 0x8DF }.address(), &Hooks::HookedEjectShellCasing);
	trampoline.write_call<5>(REL::Relocation<uintptr_t>{ REL::ID(1311102), 0xB9 }.address(), &Hooks::HookedEjectShellCasing);
}

void Hooks::HookedEjectShellCasing(RE::TESObjectREFR* a_shooter, const RE::BGSObjectInstanceT<RE::TESObjectWEAP>* a_instance, RE::BGSEquipIndex a_idx)
{
	bool casingSpawned = false;
	for (auto& [keyword, casingData] : CasingManager::GetSingleton()->casingMap) {
		if (a_instance) {
			if ((a_instance->instanceData.get() && ((RE::TESObjectWEAP::InstanceData*)a_instance->instanceData.get())->keywords && ((RE::TESObjectWEAP::InstanceData*)a_instance->instanceData.get())->keywords->HasKeyword(keyword, a_instance->instanceData.get()))
				|| (((RE::TESObjectWEAP*)a_instance->object)->HasKeyword(keyword))) {
				bool succ = CasingManager::GetSingleton()->SpawnCasing(a_shooter, keyword);
				if (succ)
					casingSpawned = true;
			}
		}
	}

	if (!casingSpawned) {
		typedef void (*FnEjectShellCasing)(RE::TESObjectREFR*, const RE::BGSObjectInstanceT<RE::TESObjectWEAP>*, RE::BGSEquipIndex);
		FnEjectShellCasing fn = (FnEjectShellCasing)EjectShellCasingOrig;
		if (fn)
			fn(a_shooter, a_instance, a_idx);
	}
}
