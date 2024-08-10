#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include <Model.h>


class ModelManager final {
	ModelManager() = default;
	~ModelManager() = default;
public:

	static ModelManager* GetInstance() {
		static ModelManager instance;
		return &instance;
	}

	

	void Initialize();

	void Finalize();



	static Model* GetModel(const std::string& key);

	static void Load(const std::string& key, const std::string& filePath);


private:

	/// modelのコンテナクラス
	std::unordered_map<std::string, std::unique_ptr<Model>> models_;

private:
	ModelManager(const ModelManager&) = delete;
	ModelManager(ModelManager&&) = delete;
	ModelManager& operator = (const ModelManager&) = delete;
	ModelManager& operator = (ModelManager&&) = delete;
};