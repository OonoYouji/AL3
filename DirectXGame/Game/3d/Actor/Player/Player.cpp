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
#include <AudioManager.h>

#include <CreateName.h>
#include <Mat4Math.h>
#include <Vec3Math.h>
#include <Vector2.h>
#include <Random.h>

#include <PlayerBullet.h>
#include <GameManagerObject.h>
#include <BulletItem.h>
#include <DeadZone.h>
#include <StartLine.h>
#include <Enemy.h>
#include <GameCamera.h>
#include <ParticleSystem.h>
#include <GoalLine.h>
#include <InformationHUD.h>
#include <GameResultUI.h>



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


	//model_ = ModelManager::GetModel("player");


	worldTransform_.translation_.y = 0.5f;

	modelParts_.resize(PART_COUNT);
	for(auto& part : modelParts_) {
		part.reset(new ModelPart());
	}
	modelParts_[HEAD]->model = ModelManager::GetModel("player_head");
	modelParts_[BODY]->model = ModelManager::GetModel("player_body");
	modelParts_[L_ARM]->model = ModelManager::GetModel("player_l_arm");
	modelParts_[R_ARM]->model = ModelManager::GetModel("player_r_arm");
	modelParts_[L_LEG]->model = ModelManager::GetModel("player_l_leg");
	modelParts_[R_LEG]->model = ModelManager::GetModel("player_r_leg");

	for(auto& part : modelParts_) {
		part->transform.Initialize();
	}


	modelParts_[BODY]->transform.parent_ = &worldTransform_;
	for(int i = 0; i < PART_COUNT; ++i) {
		if(i == BODY) { continue; }
		modelParts_[i]->transform.parent_ = &modelParts_[BODY]->transform;
	}

	modelParts_[L_ARM]->transform.translation_ = { -1.04113f, 1.63164f, 0.0f };
	modelParts_[R_ARM]->transform.translation_ = { 1.04113f, 1.63164f, -0.333162f };
	modelParts_[L_LEG]->transform.translation_ = { -0.576401f,  0.705473f, 0.0f };
	modelParts_[R_LEG]->transform.translation_ = { 0.576401f,  0.705473f, 0.0f };

	color_.Initialize();
	color_.SetColor({ 1,0,0,1 });
	color_.TransferMatrix();


	move_ = {};
	speed_ = 10.0f;
	nextAttenuation_ = WorldTime::GetAttenuation();

	CreateBoxCollider(ModelManager::GetModel("playerHitBox"));

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


	/// 他クラスポインタの初期化
	infoHUD_ = dynamic_cast<InformationHUD*>(GameObjectManager::GetInstance()->GetGameObject("InformationHUD"));

}



void Player::Update() {


	/// -----------------------------------------------------------------
	/// プレイヤーが死亡したときの処理
	/// -----------------------------------------------------------------
	if(DeadEffect()) {

		return;
	}


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
	/// パーツのアニメーション処理
	/// -----------------------------------------------------------------
	PartAnimation(move_ != Vec3(0, 0, 0), WorldTime::FrameTime() * 8.0f);

	worldTransform_.rotation_.x = 0.125f;
	worldTransform_.rotation_.y = 0.0f;
	if(move_.x > 0.0f) {
		worldTransform_.rotation_.y = 1.0f / 6.0f;
	} else if(move_.x < 0.0f) {
		worldTransform_.rotation_.y = -1.0f / 6.0f;
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
				AudioManager::PlayAudio("fire", 0.1f);
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

	for(auto& part : modelParts_) {
		part->transform.UpdateMatrix();
	}

	/*if(GetPosition().z > 1000.0f) {
		GameManagerObject* object =
			dynamic_cast<GameManagerObject*>(GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));

		object->SetIsGameClear(true);

	}*/

}



void Player::Draw() {
	//model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &color_);
	for(auto& part : modelParts_) {
		part->model->Draw(part->transform, MainCamera::GetInstance()->GetViewProjection(), &color_);
	}
}

void Player::OnCollisionEnter([[maybe_unused]] BaseGameObject* collision) {

	/// スタートラインに衝突したときの処理
	StartLine* startLine = dynamic_cast<StartLine*>(collision);
	if(startLine) {

		GameManagerObject* object = dynamic_cast<GameManagerObject*>(
			GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));


		if(!object->GetIsGameStart()) {

			object->SetIsGameStart(true);
			AudioManager::PlayAudio("Start", 0.2f);

		}

		return;
	}


	GameManagerObject* gameManagerObject = dynamic_cast<GameManagerObject*>(
		GameObjectManager::GetInstance()->GetGameObject("GameManagerObject"));
	if(gameManagerObject) {
		if(!gameManagerObject->GetIsGameStart()) {
			return;
		}
	}


	/// 敵に衝突したときの処理
	Enemy* enemy = dynamic_cast<Enemy*>(collision);
	if(enemy) {

		gameManagerObject->SetIsGameOver(true);
		isAlive_ = false;


		DeadZone* deadZone = dynamic_cast<DeadZone*>(
			GameObjectManager::GetInstance()->GetGameObject("DeadZone"));
		deadZone->isActive = false;

		AudioManager::PlayAudio("playerDead", 1.0f);

		return;
	}

	/// 弾の種類を増やすアイテムと衝突したときの処理
	BulletItem* item = dynamic_cast<BulletItem*>(collision);
	if(item) {

		GameObjectManager::GetInstance()->Destory(item);

		int arrRefe = Random::Int(2, ArrRefe_Count) - 1;
		fireNums_[arrRefe] = std::min(fireNums_[arrRefe] + 1, 5);

		AudioManager::PlayAudio("ItemGet", 0.5f);

		return;
	}


	/// デッドゾーンに衝突したときの処理
	DeadZone* deadZone = dynamic_cast<DeadZone*>(collision);
	if(deadZone) {

		gameManagerObject->SetIsGameOver(true);
		isAlive_ = false;
		deadZone->isActive = false;
		AudioManager::PlayAudio("playerDead", 1.0f);

		return;
	}


	GoalLine* goalLine = dynamic_cast<GoalLine*>(collision);
	if(goalLine) {

		gameManagerObject->SetIsGameClear(true);

		return;
	}


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

bool Player::DeadEffect() {
	if(isAlive_) {
		return false;
	}


	if(deadEffect_.lerpT == 1.0f) {

		deadSinceTime_ += WorldTime::GetDeltaTime();

		if(deadSinceTime_ >= 0.2f) {
			WorldTime::SetAttenuation(0.01f);
		}

		if(!isEffectTransition_) {
			isEffectTransition_ = true;

			playerLerpStartPos_ = GetPosition();
			playerLerpEndPos_ = playerLerpStartPos_;
			playerLerpEndPos_.x += 20.0f;
			playerLerpEndPos_.z -= 20.0f;
			playerLerpEndPos_.y = 3.0f;


			/// effectをcameraのtargetに設定
			GameCamera* camera = dynamic_cast<GameCamera*>(MainCamera::GetInstance()->GetCamera());
			if(camera) {
				cameraOffset_ = camera->GetOffset();
				cameraRotate_ = camera->GetRotate();
			}

		} else {

			float t = std::min(deadSinceTime_ / 0.2f, 1.0f);
			Vec3 cameraOffset = Lerp(cameraOffset_, Vec3(0.0f, 3.0f, -17.0f), t);
			Vec3 cameraRotate = Lerp(cameraRotate_, {}, t);

			Vec3 position = Lerp(playerLerpStartPos_, playerLerpEndPos_, t);
			SetPos(position);

			GameCamera* camera = dynamic_cast<GameCamera*>(MainCamera::GetInstance()->GetCamera());
			camera->SetOffset(cameraOffset);
			camera->SetRotate(cameraRotate);

			worldTransform_.rotation_.y += 1.0f * WorldTime::GetDeltaTime();
			UpdateMatrix();
			PartAnimation(true, WorldTime::GetDeltaTime() * 8.0f);

			if(t == 1.0f) {
				isDrawActive = true;
				if(!isEffectEnded_) {
					(new GameResultUI())->Initialize();
				}
				isEffectEnded_ = true;
			}

		}


	} else {

		WorldTime::SetAttenuation(0.5f);


		deadEffect_.currentTime = std::min(deadEffect_.currentTime + WorldTime::GetDeltaTime(), deadEffect_.maxTime);
		deadEffect_.lerpT = deadEffect_.currentTime / deadEffect_.maxTime;

		float t = 0.5f * (sin(deadEffect_.lerpT * 10.0f) + 1.0f) * 0.5f + 0.5f;
		color_.SetColor(Vector4(91 / 255.0f, 110 / 255.0f, 225 / 255.0f, 1.0f) * t);
		color_.TransferMatrix();

		if(deadEffect_.lerpT == 1.0f) {
			isDrawActive = false;

			ParticleSystem* particle = new ParticleSystem();
			particle->Initialize();
			particle->SetPos(GetPosition());
			particle->UpdateMatrix();
			particle->SetThisLifeTime(1.0f);
			particle->SetCreateParticleCount(3);
			particle->SetIsActiveAttenuation(true);
			particle->SetObjectColor(color_);

			WorldTime::SetAttenuation(0.5f);
			for(int i = 0; i < 60; ++i) {
				particle->Update();
			}

			color_.SetColor(Vector4(91 / 255.0f, 110 / 255.0f, 225 / 255.0f, 1.0f));
			color_.TransferMatrix();

			deadSinceTime_ = 0.0f;
		}

	}

	return true;
}

void Player::PartAnimation(bool isAnimation, float time) {
	if(!isAnimation) { return; }

	animationTime_ += time;

	modelParts_[BODY]->transform.translation_.y = std::sin(animationTime_ * 2.0f) * 0.5f + 0.5f;

	modelParts_[L_ARM]->transform.rotation_.y = std::sin(animationTime_) * 0.5f;
	modelParts_[R_ARM]->transform.rotation_.y = std::sin(animationTime_) * 0.5f;

	modelParts_[L_LEG]->transform.rotation_.x = -std::sin(animationTime_) * 0.5f;
	modelParts_[R_LEG]->transform.rotation_.x = std::sin(animationTime_) * 0.5f;

}
