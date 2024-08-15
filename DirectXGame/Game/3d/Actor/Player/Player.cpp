#define NOMINMAX
#include "Player.h"

#include <cassert>
#include <algorithm>

#include <ImGuiManager.h>
#include <Input.h>
#include <MainCamera.h>
#include <WorldTime.h>
#include <GameObjectManager.h>
#include <CollisionManager.h>
#include <ModelManager.h>

#include <CreateName.h>
#include <Mat4Math.h>
#include <Vector2.h>

#include <PlayerBullet.h>
#include <GameManagerObject.h>



Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {
	bullets_.clear();
}



void Player::Initialize() {

	/*isActive = false;
	isDrawActive = false;*/

	input_ = Input::GetInstance();


	model_ = ModelManager::GetModel("player");

	worldTransform_.Initialize();

	color_.Initialize();
	color_.SetColor({ 1,0,0,1 });
	color_.TransferMatrix();


	move_ = {};
	speed_ = 10.0f;
	nextAttenuation_ = WorldTime::GetAttenuation();

	CreateBoxCollider(model_);

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

		worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -60.0f, 60.0f);

	}



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
			GameObjectManager::GetInstance()->Destory(bullet);
			return true;
		}
		return false;
	});

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &color_);


}

void Player::OnCollisionEnter([[maybe_unused]] BaseGameObject* collision) {
	color_.SetColor(Vector4(0, 0, 0, 1));
	color_.TransferMatrix();

	if(collision->GetName().find("Enemy") != std::string::npos) {

		GameManagerObject* object = dynamic_cast<GameManagerObject*>(
				GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));

		object->SetIsGameOver(true);

	}

}

void Player::OnCollisionStay([[maybe_unused]] BaseGameObject* collision) {
	color_.SetColor(Vector4(1, 0, 0, 1));
	color_.TransferMatrix();
}

void Player::OnCollisionExit([[maybe_unused]] BaseGameObject* collision) {
	color_.SetColor(Vector4(1, 1, 1, 1));
	color_.TransferMatrix();
}


void Player::Fire() {
	PlayerBullet* newBullet(new PlayerBullet);
	newBullet->Initialize();
	newBullet->SetPos(GetPosition());
	bullets_.push_back(newBullet);
}
