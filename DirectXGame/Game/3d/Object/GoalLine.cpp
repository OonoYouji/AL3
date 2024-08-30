#include "GoalLine.h"

#include <ModelManager.h>
#include <TextureManager.h>
#include <Player.h>

#include <Vec3Math.h>


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

}

void GoalLine::Update() {
	/// spriteの座標計算
	Vec3 worldPos = GetPosition();
	worldPos.x += player_->GetPosition().x;
	Vec2 screenPosition = ConvertScreen(worldPos);

	lineSprite_->SetPosition(screenPosition);
	fontSprite_->SetPosition(screenPosition);

}

void GoalLine::Draw() {

}

void GoalLine::FrontSpriteDraw() {
	lineSprite_->Draw();
	fontSprite_->Draw();
}
