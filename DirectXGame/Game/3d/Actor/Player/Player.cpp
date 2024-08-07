#define NOMINMAX
#include "Player.h"

#include <cassert>
#include <algorithm>

#include <Input.h>
#include <MainCamera.h>
#include <WorldTime.h>
#include <GameObjectManager.h>

#include <CreateName.h>
#include <Mat4Math.h>

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


	move_ = {};
	speed_ = 10.0f;
	nextAttenuation_ = WorldTime::GetAttenuation();

}



void Player::Update() {

	UpdateMatrix();



	move_ = {
		float(input_->PushKey(DIK_D) - input_->PushKey(DIK_A)),
		float(input_->PushKey(DIK_W) - input_->PushKey(DIK_S))
	};

	worldTransform_.translation_ += move_ * speed_ * WorldTime::FrameTime();


	if(move_ != Vec3(0.0f, 0.0f)) {
		leftShootCT_ = std::min(leftShootCT_ - (1.0f * WorldTime::GetAttenuation()), kShootCT_);
		if(leftShootCT_ <= 0.0f) {
			leftShootCT_ = kShootCT_;
			Fire();
		}

		nextAttenuation_ += 1.0f / 120.0f;
	} else {
		nextAttenuation_ -= 1.0f / 20.0f;
	}

	nextAttenuation_ = std::clamp(nextAttenuation_, 0.0f, 1.0f);
	WorldTime::SetAttenuation(nextAttenuation_);


	//for(auto& bullet : bullets_) {
	//	bullet->Update();
	//}

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
