#pragma once


#include <memory>

#include "BaseScene.h"

/// <summary>
/// BaseSceneクラスの管理クラス
/// </summary>
class SceneManager final {
	SceneManager() = default;
	~SceneManager() = default;
public:

	/// <summary>
	/// インスタンス確保
	/// </summary>
	/// <returns></returns>
	static SceneManager* GetInstance();

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
	/// シーンの読み込み
	/// </summary>
	void Load(BaseScene* next);

	/// <summary>
	/// シーンのゲット
	/// </summary>
	BaseScene* GetScene() const;

private:

	std::unique_ptr<BaseScene> currentScene_;
	std::unique_ptr<BaseScene> nextScene_;

private:
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;
};