#pragma once
#include "Configs.h"
#include <shared_mutex>

struct CasingData {
	std::string model;
	std::string targetNode;
	CasingData(std::string _model, std::string _targetNode) {
		model = _model;
		targetNode = _targetNode;
	}
};

class CasingManager {
protected:
	static CasingManager* instance;

public:
	using SharedLock = std::shared_mutex;
	using ReadLocker = std::shared_lock<SharedLock>;
	using WriteLocker = std::unique_lock<SharedLock>;
	SharedLock mapLock;
	std::unordered_map<RE::BGSKeyword*, std::vector<CasingData>> casingMap;
	CasingManager() = default;
	CasingManager(CasingManager&) = delete;
	void operator=(const CasingManager&) = delete;
	static CasingManager* GetSingleton()
	{
		if (!instance)
			instance = new CasingManager();
		return instance;
	}
	inline void ResetMap(){
		casingMap.clear();
	}
	void AddCasing(RE::BGSKeyword* a_keyword, std::string a_model, std::string a_targetNode);
	bool SpawnCasing(RE::TESObjectREFR* a_ref, RE::BGSKeyword* a_keyword);
};
