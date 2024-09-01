#define NOMINMAX
#include "InformationHUD.h"

#include <TextureManager.h>
#include <Player.h>

#include <Vec2Math.h>
#include <Vec3Math.h>
#include <WorldTime.h>


InformationHUD::InformationHUD() {
	SetTag("InformationHUD");
	SetName("InformationHUD");
}



void InformationHUD::Initialize() {

	int fontTexHandle = TextureManager::Load("Textures/score.png");
	scoreFont_.reset(Sprite::Create(fontTexHandle, Vec2(12.0f, 12.0f), Vec4(1, 1, 1, 1), Vec2(0, 0)));

	for(int i = 0; i < 10; ++i) {
		numberTexHandles_[i] = TextureManager::Load("Textures/number" + std::to_string(i) + ".png");
	}

	for(auto& sprite : numberSprites_) {
		sprite.reset(Sprite::Create(numberTexHandles_[0], Vec2(0, 0), Vec4(1, 1, 1, 1), Vec2(0.5f, 0.5f)));
	}

	score_ = 0;

	digitInterval_ = 20.0f;

	worldTransform_.translation_ = Vec3(37.0f, 85.0f, 0);

	/// 他クラスへのポインタの初期化
	player_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));

	CreateVariableGroup();

}



void InformationHUD::Update() {

	if(player_->GetIsAlive()) {

		scoreDigit_ = 0;
		for(int i = 0; i < 4; ++i) {

			int currentDigitNum = score_ / static_cast<int>(std::pow(10, i)) % 10;

			numberSprites_[i]->SetTextureHandle(numberTexHandles_[currentDigitNum]);

			Vec2 position = {
				worldTransform_.translation_.x,
				worldTransform_.translation_.y
			};

			numberSprites_[i]->SetPosition(position + Vec2(digitInterval_ * (3.0f - i), 0.0f));

			if(!currentDigitNum) {
				break;
			}

			++scoreDigit_;

		}

	}

}



void InformationHUD::FrontSpriteDraw() {
	for(uint8_t i = 0; i < scoreDigit_; ++i) {
		numberSprites_[i]->Draw();
	}
	scoreFont_->Draw();
}

void InformationHUD::CreateVariableGroup() {
	BaseGameObject::Group& group = CreateGroup("variables");
	group.SetPtr("digitInterval", &digitInterval_);
}
