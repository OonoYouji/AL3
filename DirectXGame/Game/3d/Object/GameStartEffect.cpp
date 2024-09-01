#define NOMINMAX
#include "GameStartEffect.h"

#include <algorithm>

#include <TextureManager.h>
#include <SceneManager.h>

#include <Scene_Game.h>

#include <WorldTime.h>
#include <Vec2Math.h>


void GameStartEffect::Initialize() {
	int bgTexHandle = TextureManager::Load("white1x1.png");
	background_.reset(Sprite::Create(bgTexHandle, Vec2(0, 0), Vec4(0, 0, 0, 1)));
	background_->SetSize(Vec2(1280.0f, 720.0f));

	int titleTexHandle = TextureManager::Load("Textures/title.png");
	title_.reset(Sprite::Create(titleTexHandle, Vec2(1280, 720) / 2.0f, Vec4(1, 1, 1, 1), Vec2(0.5f, 0.5f)));

}



void GameStartEffect::Update() {
	animationTime_ += WorldTime::GetDeltaTime();

	title_->SetPosition(Lerp(
		Vec2(640.0f + 1280.0f, 360.0f),
		Vec2(640.0f, 360.0f),
		std::min(animationTime_ / 0.5f, 1.0f)
	));

	if(animationTime_ > 1.2f) {
		SceneManager::Load(new Scene_Game);
	}

}


void GameStartEffect::FrontSpriteDraw() {
	background_->Draw();
	title_->Draw();
}
