#pragma once

namespace Hooks {
	void InitializeHooks();
	void HookedEjectShellCasing(RE::TESObjectREFR* a_shooter, const RE::BGSObjectInstanceT<RE::TESObjectWEAP>* a_instance, RE::BGSEquipIndex a_idx);
}
