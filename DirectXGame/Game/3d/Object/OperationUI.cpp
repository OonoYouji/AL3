#include <OperationUI.h>

#include <TextureManager.h>
#include <WorldTime.h>
#include <GameManagerObject.h>


OperationUI::OperationUI() {
	SetTag("OperationUI");
	SetName("OperationUI");
}


void OperationUI::Initialize() {
	normalTexHandle_ = TextureManager::Load("Textures/operationUI_normal.png");
	clickTexHandle_ = TextureManager::Load("Textures/operationUI_click.png");
	sprite_.reset(Sprite::Create(normalTexHandle_, position_, { 1,1,1,1 }, { 0.5f, 0.5f }));
	sprite_->SetSize(sprite_->GetSize() * 0.25f);
}

void OperationUI::Update() {

	animationTime_ += WorldTime::GetDeltaTime() * 0.5f;
	animationTime_ = -fmod(animationTime_, 1.0f);

	/// 座標計算
	position_.x = 960.0f;

	position_.y = 460.0f + 100.0f * -0.2f;
	sprite_->SetTextureHandle(normalTexHandle_);

	if(std::abs(animationTime_) >= 0.2f) {
		position_.y = 460.0f + 100.0f * animationTime_;
		sprite_->SetTextureHandle(clickTexHandle_);
	}


	sprite_->SetPosition(position_);

	GameManagerObject* object =
		dynamic_cast<GameManagerObject*>(GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));
	if(object) {
		if(object->GetIsGameStart()) {
			GameObjectManager::GetInstance()->Destory(this);
		}
	}

}

void OperationUI::FrontSpriteDraw() {
	sprite_->Draw();
}
