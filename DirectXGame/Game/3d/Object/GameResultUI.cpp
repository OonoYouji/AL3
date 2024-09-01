#include "GameResultUI.h"

#include <SceneManager.h>
#include <TextureManager.h>
#include <Input.h>

#include <Scene_Game.h>


void GameResultUI::Initialize() {

	worldTransform_.translation_ = Vec3(900, 500, 0);

	int texHandle = TextureManager::Load("Textures/nextButton.png");
	Vec2 position = {
		worldTransform_.translation_.x,
		worldTransform_.translation_.y
	};

	nextButton_.reset(Sprite::Create(texHandle, Vec2(position), Vec4(1, 1, 1, 1), Vec2(0.5f, 0.5f)));



	/// 他クラスポインタ
	input_ = Input::GetInstance();

}

void GameResultUI::Update() {

	Vec2 position = {
		worldTransform_.translation_.x,
		worldTransform_.translation_.y
	};

	nextButton_->SetPosition(position);


	Vec2 mousePosition = input_->GetMousePosition();

	Vec2 min, max;
	min = nextButton_->GetPosition() - (nextButton_->GetSize() / 2.0f);
	max = nextButton_->GetPosition() + (nextButton_->GetSize() / 2.0f);

	isOverlapping_ = false;
	if(min.x < mousePosition.x && min.y < mousePosition.y
	   && mousePosition.x < max.x && mousePosition.y < max.y) {
		isOverlapping_ = true;
	}

	if(isOverlapping_) {
		nextButton_->SetColor(Vec4(0.9f, 0.9f, 0.9f, 1));

		/// 左キー
		if(input_->IsTriggerMouse(0)) {
			SceneManager::Load(new Scene_Game);
		}

	} else {
		nextButton_->SetColor(Vec4(1, 1, 1, 1));
	}

}

void GameResultUI::FrontSpriteDraw() {
	nextButton_->Draw();
}
