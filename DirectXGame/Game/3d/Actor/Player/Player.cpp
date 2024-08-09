#define NOMINMAX
#include "Player.h"

#include <cassert>
#include <algorithm>

#include <ImGuiManager.h>
#include <Input.h>
#include <MainCamera.h>
#include <WorldTime.h>
#include <GameObjectManager.h>

#include <CreateName.h>
#include <Mat4Math.h>
#include <Vector2.h>

#include <PlayerBullet.h>



Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {
	bullets_.clear();
}



void Player::Initialize() {

	input_ = Input::GetInstance();

	model_.reset(Model::CreateSphere());
	bulletModel_.reset(Model::Create());

	worldTransform_.Initialize();

	color_.Initialize();
	color_.SetColor({ 1,0,0,1 });
	color_.TransferMatrix();


	move_ = {};
	speed_ = 10.0f;
	nextAttenuation_ = WorldTime::GetAttenuation();

}



void Player::Update() {

	/// -----------------------------------------------------------------
	/// 移動処理
	/// -----------------------------------------------------------------


	move_ = {};
	/// 左キー
	if(input_->IsPressMouse(0)) {

		Input::MouseMove mouseMove = input_->GetMouseMove();
		Vector2 v = {
			static_cast<float>(mouseMove.lX),
			static_cast<float>(mouseMove.lY)
		};

		moveLenght_ = v.Len();
		v = -v.Norm();

		/// 上下の移動
		if(std::abs(v.x) < std::abs(v.y)) {
			move_.z = v.y;
		} else { /// 左右の移動
			move_.x = -v.x;
		}


		worldTransform_.translation_ += move_ * speed_ * WorldTime::FrameTime();

	}



	UpdateMatrix();



	/// -----------------------------------------------------------------
	/// 弾を打つ処理
	/// -----------------------------------------------------------------
	if(move_ != Vec3(0, 0, 0)) {
		leftShootCT_ = std::min(leftShootCT_ - (1.0f * WorldTime::GetAttenuation()), kShootCT_);
		if(leftShootCT_ <= 0.0f) {
			leftShootCT_ = kShootCT_;
			Fire();
		}
	}


	/// -----------------------------------------------------------------
	/// 減衰度を計算する
	/// -----------------------------------------------------------------
	if(move_ != Vec3(0, 0, 0)) {
		//nextAttenuation_ += 1.0f / 20.0f * move_.Len();
		nextAttenuation_ = moveLenght_ / 5.0f;
	} else {
		nextAttenuation_ = 0.0f;
	}

	WorldTime::SetAttenuation(nextAttenuation_);




}


void Player::LastUpdate() {
	/// -----------------------------------------------------------------
	/// 消滅した弾をリストから外す処理
	/// -----------------------------------------------------------------
	bullets_.remove_if([](PlayerBullet* bullet) {
		if(bullet->IsDesctory()) {
			GameObjectManager::GetInstance()->SubGameObject(bullet);
			return true;
		}
		return false;
	});

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &color_);


}


void Player::Fire() {
	PlayerBullet* newBullet(new PlayerBullet);
	newBullet->Initialize();
	newBullet->SetModel(bulletModel_.get());
	newBullet->SetPos(GetPosition());
	bullets_.push_back(newBullet);
}
