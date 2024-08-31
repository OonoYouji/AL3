#include "InformationHUD.h"

#include <TextureManager.h>
#include <Player.h>



InformationHUD::InformationHUD() {
	SetTag("InformationHUD");
	SetName("InformationHUD");
}



void InformationHUD::Initialize() {

	for(int i = 0; i < 10; ++i) {
		numberTexHandles_[i] = TextureManager::Load("Textures/number" + std::to_string(i) + ".png");
	}

	for(auto& sprite : numberSprites_) {
		sprite.reset(Sprite::Create(numberTexHandles_[0], Vec2()));
	}

	score_ = 123;

	digitInterval_ = 10.0f;


	/// 他クラスへのポインタの初期化
	player_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));

	CreateVariableGroup();

}



void InformationHUD::Update() {

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



void InformationHUD::FrontSpriteDraw() {
	for(uint8_t i = 0; i < scoreDigit_; ++i) {
		numberSprites_[i]->Draw();
	}
}

void InformationHUD::CreateVariableGroup() {
	BaseGameObject::Group& group = CreateGroup("variables");
	group.SetPtr("digitInterval", &digitInterval_);
}
