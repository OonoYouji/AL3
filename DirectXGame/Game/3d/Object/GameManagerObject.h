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


	void SetIsGameStart(bool isGameStart);
	bool GetIsGameStart() const { return isGameStart_; }

	void SetIsGameOver(bool isGameOver);
	bool GetIsGameOver() const { return isGameOver_; }

	void SetIsGameClear(bool isGameClear) { isGameClear_ = isGameClear; }
	bool GetIsGameClear() const { return isGameClear_; }

private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	bool isGameStart_ = false;
	bool isGameOver_ = false;
	bool isGameClear_ = false;


};