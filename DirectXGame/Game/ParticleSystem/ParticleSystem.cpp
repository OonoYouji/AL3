#define NOMINMAX
#include "ParticleSystem.h"

#include <numbers>

#include <GameObjectManager.h>
#include <MainCamera.h>
#include <WorldTime.h>
#include <Vec3Math.h>
#include <ModelManager.h>
#include <Random.h>

int ParticleSystem::sInstanceCount_ = 0;


/// ===================================================
/// コンストラクタ
/// ===================================================
ParticleSystem::ParticleSystem() {
	id_ = sInstanceCount_++;

	SetTag("ParticleSystem");
	SetName("ParticleSystem" + std::to_string(id_));

	CreateVariablesGroup();
}

/// ===================================================
/// 初期化
/// ===================================================
void ParticleSystem::Initialize() {
	model_ = ModelManager::GetModel("cube");

	direction_ = { 0,1,0 };

}


/// ===================================================
/// 更新処理
/// ===================================================
void ParticleSystem::Update() {

	float subTime = WorldTime::GetDeltaTime();
	if(isActiveAttenuation_) {
		subTime *= WorldTime::GetAttenuation();
	}

	spawnTime_ -= subTime;
	thisLifeTime_ -= subTime;

	angle_ = std::max(angle_, 0.0f);

	/// particleの生成
	if(thisLifeTime_ > 0.0f) {
		if(spawnTime_ <= 0.0f) {
			for(int i = 0; i < createParticleCount_; ++i) {
				CreateParticle();
			}
			spawnTime_ = spawnCT_;
		}
	}

	/// particleの更新処理
	for(auto& particle : particles_) {
		UpdateParticle(particle.get());
	}

	/// life timeが0以下になったものを消去
	particles_.remove_if([](const std::unique_ptr<Particle>& particle) {
		if(particle->lifeTime <= 0.0f) {
			return true;
		}
		return false;
	});


	/// Life Timeが0以下になってparticleが一個もなければ消す
	if(thisLifeTime_ <= 0.0f) {
		if(particles_.empty()) {
			GameObjectManager::GetInstance()->Destory(this);
		}
	}

}


/// ===================================================
/// 描画処理
/// ===================================================
void ParticleSystem::Draw() {

#ifdef _DEBUG
	ModelManager::GetModel("sphere")->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());
#endif // _DEBUG


	if(!model_) { return; }

	for(auto& particle : particles_) {
		model_->Draw(particle->worldTransform, MainCamera::GetInstance()->GetViewProjection());
	}

}



void ParticleSystem::CreateParticle() {

	std::unique_ptr<Particle> newParticle(new Particle());


	/// --------------------------------------------------
	/// world transformの設定
	/// --------------------------------------------------
	newParticle->worldTransform.Initialize();
	newParticle->worldTransform.translation_ = GetPosition();
	newParticle->worldTransform.UpdateMatrix();


	/// --------------------------------------------------
	/// velocityの計算
	/// --------------------------------------------------
	Vec3 cross = Cross({ 0, 1, 0 }, direction_.Norm());
	cross *= std::numbers::pi_v<float> / 2.0f;
	Mat4 matRotate = MakeRotate(cross);

	float convertDegreeToRadian = (std::numbers::pi_v<float> / 180.0f);
	float theta = Random::Float(0, 2 * std::numbers::pi_v<float>);
	float angle = Random::Float(0.0f, angle_) * convertDegreeToRadian;
	Vec3 dir = {
		std::cos(theta) * angle_ * convertDegreeToRadian,
		std::cos(angle),
		std::sin(theta) * angle_ * convertDegreeToRadian
	};

	newParticle->velocity = Transform(dir.Norm(), matRotate) * speed_;



	/// --------------------------------------------------
	/// 
	/// --------------------------------------------------
	newParticle->lifeTime = particleLifeTime_;

	particles_.push_back(std::move(newParticle));

}


void ParticleSystem::UpdateParticle(Particle* particle) {

	/// 移動計算
	Vec3 velocity = particle->velocity * WorldTime::GetDeltaTime();

	if(isActiveAttenuation_) {
		velocity *= WorldTime::GetAttenuation();
	}

	particle->worldTransform.translation_ += velocity;

	/*Vec3 cross = Cross({ 0,1,0 }, velocity) * std::numbers::pi_v<float> / 2.0f;
	particle->worldTransform.rotation_ += cross;*/

	particle->worldTransform.UpdateMatrix(YXZ);

	/// 制限時間の減少
	float subTime = WorldTime::GetDeltaTime();
	if(isActiveAttenuation_) {
		subTime = WorldTime::FrameTime();
	}

	particle->lifeTime = std::max(particle->lifeTime - subTime, 0.0f);

}

void ParticleSystem::CreateVariablesGroup() {
	BaseGameObject::Group& group = CreateGroup("variables");

	group.SetPtr("speed", &speed_);

	group.SetPtr("particleLifeTime", &particleLifeTime_);
	group.SetPtr("thisLifeTime", &thisLifeTime_);
	group.SetPtr("spawnCT", &spawnCT_);
	group.SetPtr("createCount", &createParticleCount_);

	group.SetPtr("direction", &direction_);
	group.SetPtr("angle", &angle_);

}
