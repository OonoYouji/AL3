#define NOMINMAX
#include "GoalLine.h"

#include <ModelManager.h>
#include <TextureManager.h>
#include <Player.h>
#include <GameManagerObject.h>

#include <WorldTime.h>
#include <Vec2Math.h>
#include <Vec3Math.h>
#include <Easing.h>


GoalLine::GoalLine() {
	SetTag("GoalLine");
	SetName("GoalLine");
}



void GoalLine::Initialize() {

	/// 座標の初期化
	worldTransform_.translation_.z = 800.0f;

	UpdateMatrix();

	/// collider 
	CreateBoxCollider(ModelManager::GetModel("startLine"));

	/// textureの初期化
	uint32_t lnieTexHandle = TextureManager::Load("Textures/line.png");
	uint32_t fontTexHandle = TextureManager::Load("Textures/end.png");
	lineSprite_.reset(Sprite::Create(lnieTexHandle, Vec2(0, 0), { 1,1,1,1 }, { 0.5f, 0.5f }));
	fontSprite_.reset(Sprite::Create(fontTexHandle, Vec2(0, 0), { 1,1,1,1 }, { -1.0f, 0.0f }));

	/// 他クラスのポインタの初期化
	player_ = dynamic_cast<Player*>(GameObjectManager::GetInstance()->GetGameObject("Player"));
	gameManagerObject_ = dynamic_cast<GameManagerObject*>(GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));

}

void GoalLine::Update() {
	/// spriteの座標計算
	Vec3 worldPos = GetPosition();
	worldPos.x += player_->GetPosition().x;
	Vec2 screenPosition = ConvertScreen(worldPos);

	lineSprite_->SetPosition(screenPosition);
	fontSprite_->SetPosition(screenPosition);

	if(gameManagerObject_->GetIsGameClear()) {

		clearAnimationTime_ += 10.0f * WorldTime::GetDeltaTime();

		clearAnimationTime_ = std::min(clearAnimationTime_ + WorldTime::GetDeltaTime(), 0.5f);
		float t = clearAnimationTime_ / 0.5f;

		Vec2 pos = Lerp(screenPosition, { screenPosition.x - 1500.0f, screenPosition.y }, Ease::In::Back(t));

		lineSprite_->SetPosition(pos);
		fontSprite_->SetPosition(pos);

		if(t == 1.0f) {
			GameObjectManager::GetInstance()->Destory(this);
		}

	}

}

void GoalLine::Draw() {

}

void GoalLine::FrontSpriteDraw() {
	if(!gameManagerObject_->GetIsGameOver()) {
		lineSprite_->Draw();
		fontSprite_->Draw();
	}
}
