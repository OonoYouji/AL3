#pragma once

#include <BaseGameObject.h>

/// ===================================================
/// ゲームの状態を管理するマネージャオブジェクトクラス
/// ===================================================
class GameManagerObject final : public BaseGameObject {
public:

	GameManagerObject();
	~GameManagerObject() {}

	/// ===================================================
	/// public : methods
	/// ===================================================

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;


public:

	/// ===================================================
	/// public : not override methods
	/// ===================================================

	/// <summary>
	/// 変数のグループ作成
	/// </summary>
	void CreateObjectGroup();

	
	/// <summary>
	/// ゲームのスタートフラグのセット
	/// </summary>
	/// <param name="isGameStart"></param>
	void SetIsGameStart(bool isGameStart);

private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	bool isGameStart_ = false;



};