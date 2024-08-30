#define NOMINMAX
#include <StartLine.h>

#include <ModelManager.h>
#include <GameObjectManager.h>
#include <AudioManager.h>
#include <TextureManager.h>

#include <MainCamera.h>
#include <GameManagerObject.h>
#include <Player.h>

#include <Easing.h>
#include <Vec2Math.h>
#include <Vec3Math.h>
#include <WorldTime.h>



/// ===================================================
/// コンストラクタ
/// ===================================================
StartLine::StartLine() {
	SetTag("StartLine");
	SetName("StartLine");
}


/// ===================================================
/// 初期化
/// ===================================================
void StartLine::Initialize() {

	//isDrawActive = false;

	SetPos({ 0,0,20 });
	UpdateMatrix();

	CreateBoxCollider(ModelManager::GetModel("startLine"));

	SetGameManagerObject(GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));
	player_ = GameObjectManager::GetInstance()->GetGameObject("Player");

	int lineHandle = TextureManager::Load("Textures/line.png");
	int fontHandle = TextureManager::Load("Textures/start.png");
	startLine_sprite_.reset(Sprite::Create(lineHandle, screenPos_, { 1,1,1,1 }, { 0.5f, 0.5f }));
	startFont_sprite_.reset(Sprite::Create(fontHandle, screenPos_, { 1,1,1,1 }, { -1.0f, 0.0f }));

}


/// ===================================================
/// 更新
/// ===================================================
void StartLine::Update() {

	/// spriteの座標計算
	Vec3 worldPos = GetPosition();
	worldPos.x += player_->GetPosition().x;
	screenPos_ = ConvertScreen(worldPos);

	startLine_sprite_->SetPosition(screenPos_);
	startFont_sprite_->SetPosition(screenPos_);

	if(isStart_) {
		currentTime_ = std::min(currentTime_ + WorldTime::GetDeltaTime(), maxTime_);
		lerpT_ = currentTime_ / maxTime_;

		Vec2 pos = Lerp(screenPos_, { screenPos_.x - 1500.0f, screenPos_.y }, Ease::In::Back(lerpT_));

		startLine_sprite_->SetPosition(pos);
		startFont_sprite_->SetPosition(pos);

		if(lerpT_ == 1.0f) {
			GameObjectManager::GetInstance()->Destory(this);
		}

	}

}



/// ===================================================
/// 最後の更新
/// ===================================================
void StartLine::LastUpdate() {
	UpdateMatrix();
}


/// ===================================================
/// 描画
/// ===================================================
void StartLine::Draw() {
	//if(model_) {
	//	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
	//}
}

void StartLine::FrontSpriteDraw() {
	startLine_sprite_->Draw();
	startFont_sprite_->Draw();
}



void StartLine::OnCollisionEnter(BaseGameObject* collision) {
	Player* player = dynamic_cast<Player*>(collision);
	if(player) {

		isStart_ = true;

		return;
	}
}


/// ===================================================
/// game manager objectのセット
/// ===================================================
void StartLine::SetGameManagerObject(BaseGameObject* object) {
	gameManagerObject_ = object;
}
