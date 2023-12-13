#pragma once\

namespace Globals {
	extern RE::PlayerCharacter* p;
	extern RE::PlayerCamera* pcam;
	extern REL::Relocation<uint32_t*> iSceneIsComplex;
	extern REL::Relocation<RE::NiPoint3*> PlayerAdjust;
	extern REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> fGunShellCameraDistance;
	extern REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> fGunShellRotateSpeed;
	extern REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> fGunShellEjectSpeed;
	extern REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> fGunShellLifetime;
	extern REL::Relocation<RE::SettingT<RE::GameSettingCollection>*> fGunShellDirectionRandomize;

	void InitializeGlobals();
}
