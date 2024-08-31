#pragma once

#include <memory>

#include <GameObjectManager.h>
#include <Sprite.h>


/// ===================================================
/// ゲーム内の情報を表示する
/// ===================================================
class InformationHUD final : public BaseGameObject {
public:


	/// ===================================================
	/// public : methods
	/// ===================================================

	InformationHUD();
	~InformationHUD() {}

	void Initialize() override;
	void Update() override;
	void Draw() override {};

	void FrontSpriteDraw() override;

	void SetScore(float score) { score_ = score; }
	float GetScore() const { return score_; }

private:

	/// ===================================================
	/// private : methods
	/// ===================================================

	void CreateVariableGroup();

private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	std::unique_ptr<Sprite> numberSprites_[4];	/// 4桁の数字を表示する
	uint32_t numberTexHandles_[10];				/// 0~9のtexture handle

	uint32_t score_;		/// ゲーム内スコア
	uint8_t scoreDigit_;	/// スコアの桁数
	float digitInterval_;	/// 桁間の間隔

	class Player* player_ = nullptr;

};