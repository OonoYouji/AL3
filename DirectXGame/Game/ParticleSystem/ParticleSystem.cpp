#define NOMINMAX
#include "ParticleSystem.h"

#include <MainCamera.h>
#include <WorldTime.h>
#include <Vec3Math.h>
#include <ModelManager.h>

int ParticleSystem::sInstanceCount_ = 0;


/// ===================================================
/// コンストラクタ
/// ===================================================
ParticleSystem::ParticleSystem() {
	id_ = sInstanceCount_++;

	SetTag("ParticleSystem");
	SetName("ParticleSystem" + std::to_string(id_));

}

/// ===================================================
/// 初期化
/// ===================================================
void ParticleSystem::Initialize() {
	model_ = ModelManager::GetModel("cube");

	direction_ = { 0,1,0 };
	lifeTime_ = 1.0f;

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


	if(spawnTime_ <= 0.0f) {
		CreateParticle();
		spawnTime_ = kSpawnTime_;
	}

	for(auto& particle : particles_) {
		UpdateParticle(particle.get());
	}

	particles_.remove_if([](const std::unique_ptr<Particle>& particle) {
		if(particle->lifeTime <= 0.0f) {
			return true;
		}
		return false;
	});

}


/// ===================================================
/// 描画処理
/// ===================================================
void ParticleSystem::Draw() {

	if(!model_) { return; }

	for(auto& particle : particles_) {
		model_->Draw(particle->worldTransform, MainCamera::GetInstance()->GetViewProjection());
	}

}



void ParticleSystem::CreateParticle() {
	std::unique_ptr<Particle> newParticle(new Particle());

	/// world transformの設定
	newParticle->worldTransform.Initialize();
	newParticle->worldTransform.parent_ = &worldTransform_;
	newParticle->worldTransform.UpdateMatrix();

	newParticle->direction = direction_;
	newParticle->lifeTime = lifeTime_;

	particles_.push_back(std::move(newParticle));

}


void ParticleSystem::UpdateParticle(Particle* particle) {

	/// 移動計算
	Vec3 velocity = particle->direction * 100.0f * WorldTime::GetDeltaTime();

	if(isActiveAttenuation_) {
		velocity *= WorldTime::GetAttenuation();
	}

	particle->worldTransform.translation_ += velocity;

	particle->worldTransform.UpdateMatrix();

	/// 制限時間の減少
	float subTime = WorldTime::GetDeltaTime();
	if(isActiveAttenuation_) {
		subTime = WorldTime::FrameTime();
	}

	particle->lifeTime = std::max(particle->lifeTime - subTime, 0.0f);

}
