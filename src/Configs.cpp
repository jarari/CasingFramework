#include <CasingManager.h>
#include <Configs.h>
#include <Utils.h>
#include <fstream>

void Configs::LoadConfigs()
{
	namespace fs = std::filesystem;
	std::string configPath = "Data\\F4SE\\Plugins\\CasingFramework";
	fs::directory_entry configEntry{ configPath };
	if (fs::exists(configPath)) {
		for (auto& it : fs::directory_iterator(configEntry)) {
			if (it.path().extension().compare(".txt") == 0) {
				ParseConfig(it.path());
			}
		}
	}
}

void Configs::ParseConfig(const std::filesystem::path path)
{
	std::ifstream file{ path };
	if (!file.is_open()) {
		logger::error("Failed to open file: {}", path.string());
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty() || std::isspace(line.at(0)) || line.at(0) == ';')
			continue;

		std::string keywordStr = Utils::SplitString(line, ",", line);
		std::string keywordFormIDstr;
		std::string keywordPlugin = Utils::SplitString(keywordStr, "|", keywordFormIDstr);
		if (keywordFormIDstr.empty())
			continue;

		RE::TESForm* keywordForm = Utils::GetFormFromMod(keywordPlugin, std::stoi(keywordFormIDstr, 0, 16));
		if (!keywordForm || !keywordForm->As<RE::BGSKeyword>())
			continue;

		std::string modelStr = Utils::SplitString(line, ",", line);
		if (modelStr.empty())
			continue;

		std::string nodeStr = line;
		if (nodeStr.empty())
			continue;

		CasingManager::GetSingleton()->AddCasing(keywordForm->As<RE::BGSKeyword>(), modelStr, nodeStr);
		logger::info("Added {} - Target Node: {}", modelStr, nodeStr);
	}
}
