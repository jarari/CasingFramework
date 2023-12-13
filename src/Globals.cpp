#include "Globals.h"
#include "Utils.h"

RE::PlayerCharacter* Globals::p = nullptr;
RE::PlayerCamera* Globals::pcam = nullptr;
REL::Relocation<uint32_t*> Globals::iSceneIsComplex{ REL::ID(1460914) };
REL::Relocation<RE::NiPoint3*> Globals::PlayerAdjust{ REL::ID(988646) };
REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> Globals::fGunShellCameraDistance{ REL::ID(296955) };
REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> Globals::fGunShellRotateSpeed{ REL::ID(171283) };
REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> Globals::fGunShellEjectSpeed{ REL::ID(829142) };
REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> Globals::fGunShellLifetime{ REL::ID(1487562) };
REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> Globals::fGunShellDirectionRandomize{ REL::ID(563273) };

void Globals::InitializeGlobals() {
	p = RE::PlayerCharacter::GetSingleton();
	pcam = RE::PlayerCamera::GetSingleton();
}
