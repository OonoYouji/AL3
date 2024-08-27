#pragma once

#include <memory>

#include <BaseGameObject.h>
#include <Model.h>
#include <Sprite.h>
#include <Vector2.h>

/// ===================================================
/// ゲームのスタートライン
/// ===================================================
class StartLine final : public BaseGameObject {
public:

	StartLine();
	~StartLine() {}

	/// ===================================================
	/// public : methods
	/// ===================================================

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 最後の更新
	/// </summary>
	void LastUpdate() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void FrontSpriteDraw() override;

	void OnCollisionEnter(BaseGameObject* collision) override;

public:

	/// ===================================================
	/// public : not override methods
	/// ===================================================

	void SetGameManagerObject(BaseGameObject* object);


private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	Model* model_ = nullptr;

	BaseGameObject* gameManagerObject_ = nullptr;
	BaseGameObject* player_ = nullptr;

	std::unique_ptr<Sprite> startLine_sprite_;
	std::unique_ptr<Sprite> startFont_sprite_;
	Vec2 screenPos_;

	bool isStart_ = false;
	float lerpT_ = 0.0f;
	float maxTime_ = 1.0f;		/// second
	float currentTime_ = 0.0f;	/// second

};