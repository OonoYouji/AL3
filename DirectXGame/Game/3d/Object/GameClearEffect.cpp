#define NOMINMAX
#include "GameClearEffect.h"

#include <TextureManager.h>

#include <Player.h>

#include <WorldTime.h>
#include <Easing.h>
#include <Vec3Math.h>


void GameClearEffect::Initialize() {
	int texHandle = TextureManager::Load("Textures/gameClear.png");
	congratulation_.reset(Sprite::Create(texHandle, Vec2(640.0f, 100.0f), Vec4(1, 1, 1, 1), Vec2(0.5f, 0.5f)));
	defaultSize_ = congratulation_->GetSize();

	player_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));
}

void GameClearEffect::Update() {
	animationTime_ += WorldTime::GetDeltaTime();
	float easingValue = Ease::Out::Elastic(std::max(std::sin(animationTime_), 0.0f));
	congratulation_->SetSize(defaultSize_ * easingValue);

	Vec3 rgb = ConvertRGB(animationTime_, 1, 0.8f);
	congratulation_->SetColor(Vec4(rgb.x, rgb.y, rgb.z, 1.0f));

	player_->SetColor(Vec4(rgb.x, rgb.y, rgb.z, 1.0f));

}

void GameClearEffect::FrontSpriteDraw() {
	congratulation_->Draw();
}

