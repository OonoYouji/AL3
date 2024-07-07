#pragma once

#include <list>
#include <memory>

#include <GameObject.h>

/// <summary>
/// GameObjectを管理するクラス
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

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	std::list<std::unique_ptr<GameObject>> objects_;

private:
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) = delete;
};