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

	void SetScore(uint32_t score) { score_ = score; }
	uint32_t GetScore() const { return score_; }

	void AddScore(uint32_t addValue) {
		score_ += addValue;
	}

private:

	/// ===================================================
	/// private : methods
	/// ===================================================

	void CreateVariableGroup();

private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	std::unique_ptr<Sprite> scoreFont_;
	std::unique_ptr<Sprite> numberSprites_[4];	/// 4桁の数字を表示する
	uint32_t numberTexHandles_[10];				/// 0~9のtexture handle

	uint32_t score_;		/// ゲーム内スコア
	uint8_t scoreDigit_;	/// スコアの桁数
	float digitInterval_;	/// 桁間の間隔

	float deadAnimationTime_ = 0.0f;

	class Player* player_ = nullptr;

};