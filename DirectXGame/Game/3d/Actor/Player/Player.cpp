#define NOMINMAX
#include "Player.h"

#include <cassert>
#include <algorithm>
#include <numbers>

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
#include <Random.h>

#include <PlayerBullet.h>
#include <GameManagerObject.h>
#include <BulletItem.h>


Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {
	bullets_.clear();
}



void Player::Initialize() {

	//isActive = false;
	//isDrawActive = false;

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

	/// ------------------------------------------------------
	/// Bullet関係の初期化
	/// ------------------------------------------------------
	/// 0ですべて初期化
	for(auto& fireNum : fireNums_) {
		fireNum = 0;
	}

	fireNums_[ArrRefe_Normal] = 1; /// 通常弾は1固定

	for(auto& shootCT : shootCTs_) {
		shootCT = 1.0f;
	}
	shootCTs_[ArrRefe_Normal] = 0.4f;

	for(auto& shootCT : leftShootCTs_) {
		shootCT = 0.0f;
	}


	/// 弾を撃つ関数を配列化
	FireMethods_[ArrRefe_Normal] = std::bind(&Player::NormalFire, this);
	FireMethods_[ArrRefe_Twin] = std::bind(&Player::TwinFire, this);
	FireMethods_[ArrRefe_Wide] = std::bind(&Player::WideFire, this);
	FireMethods_[ArrRefe_Side] = std::bind(&Player::SideFire, this);


	/// ------------------------------------------------------
	/// Audio関係の初期化
	/// ------------------------------------------------------

	audio_ = Audio::GetInstance();
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	audio_->PlayWave(soundDataHandle_);

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
		worldTransform_.translation_.z = std::max(-50.0f, worldTransform_.translation_.z);

	}



	/// -----------------------------------------------------------------
	/// 弾を打つ処理
	/// -----------------------------------------------------------------
	if(move_ != Vec3(0, 0, 0)) {

		/// cool timeの減衰
		for(int i = 0; i < ArrRefe_Count; ++i) {

			/// 撃つ数が0なら撃たない
			if(!fireNums_[i]) { continue; }

			leftShootCTs_[i] = std::max(leftShootCTs_[i] - WorldTime::FrameTime(), 0.0f);

			if(leftShootCTs_[i] <= 0.0f) {
				FireMethods_[i]();
			}

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

		return;
	}

	BulletItem* item = dynamic_cast<BulletItem*>(collision);
	if(item) {

		GameObjectManager::GetInstance()->Destory(item);

		int arrRefe = Random::Int(2, ArrRefe_Count) - 1;
		fireNums_[arrRefe] = std::min(fireNums_[arrRefe] + 1, 5);

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


PlayerBullet* Player::Fire() {
	PlayerBullet* newBullet(new PlayerBullet);
	newBullet->Initialize();
	newBullet->SetPos(GetPosition());
	bullets_.push_back(newBullet);

	return newBullet;
}



/// ===================================================
/// 通常弾の発射
/// ===================================================
void Player::NormalFire() {
	Fire();

	leftShootCTs_[ArrRefe_Normal] = shootCTs_[ArrRefe_Normal];
}


/// ===================================================
/// 前方に二発発射
/// ===================================================
void Player::TwinFire() {

	const float kDistance = 1.0f; /// 中心からの距離

	for(int i = 0; i < 2; ++i) {
		PlayerBullet* bullet = Fire();

		Vec3 position = GetPosition();
		position.x += i ? kDistance : -kDistance;

		bullet->SetPos(position);
		bullet->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		bullet->SetSpeed(15.0f);

	}

	--currentFireNums_[ArrRefe_Twin];
	if(currentFireNums_[ArrRefe_Twin] <= 0.0f) {
		leftShootCTs_[ArrRefe_Twin] = shootCTs_[ArrRefe_Twin];
		currentFireNums_[ArrRefe_Twin] = fireNums_[ArrRefe_Twin];
	} else {
		leftShootCTs_[ArrRefe_Twin] = shootCTs_[ArrRefe_Twin] / 5.0f;
	}


}


/// ===================================================
/// 斜め前に二発発射
/// ===================================================
void Player::WideFire() {

	for(int i = 0; i < 2; ++i) {
		PlayerBullet* bullet = Fire();

		Vec3 position = GetPosition();

		bullet->SetPos(position);
		bullet->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });

		float theta = 30.0f * std::numbers::pi_v<float> / 180.0f;
		Mat4 matRotate = MakeRotateY(i ? theta : -theta);
		bullet->SetMove(Transform({ 0,0,1 }, matRotate));

		/// 向きの計算
		bullet->SetRotateY(i ? theta : -theta);

	}

	--currentFireNums_[ArrRefe_Wide];
	if(currentFireNums_[ArrRefe_Wide] <= 0.0f) {
		leftShootCTs_[ArrRefe_Wide] = shootCTs_[ArrRefe_Wide];
		currentFireNums_[ArrRefe_Wide] = fireNums_[ArrRefe_Wide];
	} else {
		leftShootCTs_[ArrRefe_Wide] = shootCTs_[ArrRefe_Wide] / 5.0f;
	}
}


/// ===================================================
/// 左右に一発ずつ発射
/// ===================================================
void Player::SideFire() {

	for(int i = 0; i < 2; ++i) {
		PlayerBullet* bullet = Fire();

		Vec3 position = GetPosition();

		bullet->SetPos(position);
		bullet->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });

		float theta = std::numbers::pi_v<float> / 2.0f;
		Mat4 matRotate = MakeRotateY(i ? theta : -theta);
		bullet->SetMove(Transform({ 0,0,1 }, matRotate));

		/// 向きの計算
		bullet->SetRotateY(i ? theta : -theta);

	}


	--currentFireNums_[ArrRefe_Side];
	if(currentFireNums_[ArrRefe_Side] <= 0.0f) {
		leftShootCTs_[ArrRefe_Side] = shootCTs_[ArrRefe_Side];
		currentFireNums_[ArrRefe_Side] = fireNums_[ArrRefe_Side];
	} else {
		leftShootCTs_[ArrRefe_Side] = shootCTs_[ArrRefe_Side] / 5.0f;
	}
}
