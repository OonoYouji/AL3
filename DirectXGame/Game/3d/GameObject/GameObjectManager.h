#pragma once

#include <list>
#include <memory>

#include <BaseGameObject.h>

/// <summary>
/// BaseGameObjectを管理するクラス
/// </summary>
class GameObjectManager final {
	GameObjectManager() = default;
	~GameObjectManager() = default;
public:

	/// <summary>
	/// インスタンス確保関数
	/// </summary>
	/// <returns></returns>
	static GameObjectManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// BaseGameObjectの追加
	/// </summary>
	/// <param name="object"></param>
	void AddGameObject(BaseGameObject* object);

	/// <summary>
	/// BaseGameObjectの削除
	/// </summary>
	/// <param name="object"></param>
	void SubGameObject(BaseGameObject* object);

#pragma region ImGui
	/// <summary>
	/// imguiでデバッグ表示
	/// </summary>
	void ImGuiDebug();

	/// <summary>
	/// ImGui::Selectableでchild objectをインデントする
	/// </summary>
	/// <param name="childs"></param>
	void ImGuiSelectChilds(const std::list<BaseGameObject*>& childs);

	/// <summary>
	/// select objcetのデバッグ
	/// </summary>
	void ImGuiSelectObjectDebug();

#pragma endregion

private:

	std::list<std::unique_ptr<BaseGameObject>> objects_;
	BaseGameObject* selectObject_ = nullptr;

private:
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) = delete;
};