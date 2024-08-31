#pragma once

#include <GameObjectManager.h>


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

private:

	/// ===================================================
	/// private : objects
	/// ===================================================



};