#include <Configs.h>
#include <Utils.h>
#include <Globals.h>
#include <CasingManager.h>

CasingManager* CasingManager::instance = nullptr;

void CasingManager::AddCasing(RE::BGSKeyword* a_keyword, std::string a_model, std::string a_targetNode)
{
	WriteLocker lock(mapLock);
	auto find = casingMap.find(a_keyword);
	if (find == casingMap.end())
		casingMap.insert(std::pair<RE::BGSKeyword*, std::vector<CasingData>>(a_keyword, std::vector<CasingData>()));

	casingMap[a_keyword].push_back(CasingData(a_model, a_targetNode));
}

bool CasingManager::SpawnCasing(RE::TESObjectREFR* a_ref, RE::BGSKeyword* a_keyword)
{
	if (!(*Globals::iSceneIsComplex)) {
		bool casingSpawned = false;
		ReadLocker lock(mapLock);
		for (auto& casingData : casingMap[a_keyword]) {
			RE::NiAVObject* node = a_ref->Get3D()->GetObjectByName(casingData.targetNode);
			if (node) {
				RE::NiPoint3 casingPos = node->world.translate;
				bool isPlayerFP = false;
				if (a_ref == Globals::p) {
					casingPos = casingPos + *Globals::PlayerAdjust;
					isPlayerFP = !Globals::p->Is3rdPersonVisible();
				}
				RE::NiMatrix3 casingRot = node->world.rotate;

				RE::NiCamera* worldRootCamera = RE::Main::WorldRootCamera();

				__m128 loc = _mm_set_ps(a_ref->data.location.x, a_ref->data.location.y, a_ref->data.location.z, 0.f);
				__m128 camLoc = _mm_set_ps(worldRootCamera->world.translate.x, worldRootCamera->world.translate.y, worldRootCamera->world.translate.z, 0.f);
				__m128 locDiff = _mm_sub_ps(loc, camLoc);
				__m128 squared = _mm_mul_ps(locDiff, locDiff);
				__m128 shuffle = _mm_shuffle_ps(squared, squared, 0x99);
				float distSquared = (float)(squared.m128_f32[0] + shuffle.m128_f32[0]) + _mm_shuffle_ps(shuffle, shuffle, 0x55).m128_f32[0];
				if (distSquared <= Globals::fGunShellCameraDistance->GetFloat() * Globals::fGunShellCameraDistance->GetFloat()) {
					RE::BSTempEffectDebris* casing = (RE::BSTempEffectDebris*)RE::MemoryManager::GetSingleton().Allocate(sizeof(RE::BSTempEffectDebris), 0, false);
					if (casing) {
						RE::NiPoint3 vel{ casingRot.entry[2].v.x, casingRot.entry[2].v.y, casingRot.entry[2].v.z };

						float dirRand = Globals::fGunShellDirectionRandomize->GetFloat();
						float dirRandX = Utils::BSRandomFloat(-dirRand, dirRand);
						float dirRandY = Utils::BSRandomFloat(-dirRand, dirRand);
						float dirRandZ = Utils::BSRandomFloat(-dirRand, dirRand);
						vel.x = (vel.x + dirRandX) * Globals::fGunShellEjectSpeed->GetFloat();
						vel.y = (vel.y + dirRandY) * Globals::fGunShellEjectSpeed->GetFloat();
						vel.z = (vel.z + dirRandZ) * Globals::fGunShellEjectSpeed->GetFloat();

						RE::NiPoint3 linearVel;
						a_ref->GetLinearVelocity(linearVel);
						vel = vel + linearVel;

						RE::NiPoint3 angVel{ casingRot.entry[0].v.x * Globals::fGunShellRotateSpeed->GetFloat(), casingRot.entry[0].v.y * Globals::fGunShellRotateSpeed->GetFloat(), casingRot.entry[0].v.z * Globals::fGunShellRotateSpeed->GetFloat() };

						new (casing) RE::BSTempEffectDebris(a_ref->parentCell, Globals::fGunShellLifetime->GetFloat(), casingData.model.c_str(), a_ref, casingPos, casingRot, vel, angVel, 1.0f, false, true, isPlayerFP);
						casingSpawned = true;
						//logger::info("Spawned {} at node {}", casingData.model, casingData.targetNode);
					}
				}
			}
		}
		if (casingSpawned)
			return true;
	}
	return false;
}
