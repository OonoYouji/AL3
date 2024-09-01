#include "GameStartEffect.h"

#include <TextureManager.h>

#include <WorldTime.h>


void GameStartEffect::Initialize() {
	int texHandle = TextureManager::Load("white1x1.png");
	background_.reset(Sprite::Create(texHandle, Vec2(0, 0)));
	background_->SetSize(Vec2(1280.0f, 720.0f));

	title_.reset(Sprite::Create(texHandle, Vec2(1280, 720) / 2.0f, Vec4(1, 1, 1, 1), Vec2(0.5f, 0.5f)));

}



void GameStartEffect::Update() {
	animationTime_ += WorldTime::GetDeltaTime();

	if(animationTime_ > 5.0f) {
		GameObjectManager::GetInstance()->Destory(this);
	}

}


void GameStartEffect::FrontSpriteDraw() {
	background_->Draw();
	title_->Draw();
}
