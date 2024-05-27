#pragma once

#include <json.hpp>

#include <variant>
#include <string>
#include <map>

#include "Vector3.h"


using json = nlohmann::json;

/// <summary>
/// 項目
/// </summary>
struct Item {
	std::variant<int32_t, float, Vec3f> value;
};

/// <summary>
/// グループ
/// </summary>
struct Group {
	std::map<std::string, Item> items;
};


/// <summary>
/// パラメーター群
/// </summary>
class GlobalVariables final {
public:

	/// <summary>
	/// インスタンス確保
	/// </summary>
	/// <returns></returns>
	static GlobalVariables* GetInstance();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// グループの生成
	/// </summary>
	/// <param name="groupName"></param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// 値のセット int32_t
	/// </summary>
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);

	/// <summary>
	/// 値のセット float
	/// </summary>
	void SetValue(const std::string& groupName, const std::string& key, float value);

	/// <summary>
	/// 値のセット Vector3
	/// </summary>
	void SetValue(const std::string& groupName, const std::string& key, const Vec3f& value);

	/// <summary>
	/// ファイルに書き出し
	/// </summary>
	void SaveFile(const std::string& groupName);

private:

	const std::string kDirectoryPath_ = "Resources/GlobalVariables/";

	std::map<std::string, Group> datas_;

	GlobalVariables() = default;
	~GlobalVariables() = default;

	GlobalVariables(const GlobalVariables&) = delete;
	GlobalVariables(GlobalVariables&&) = delete;
	GlobalVariables& operator= (const GlobalVariables&) = delete;

};