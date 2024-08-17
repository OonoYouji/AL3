#include "ParticleSystem.h"

#include <MainCamera.h>
#include <WorldTime.h>

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
void ParticleSystem::Initialize() {}


/// ===================================================
/// 更新処理
/// ===================================================
void ParticleSystem::Update() {}


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
	std::unique_ptr<Particle> newParticle;

	/// world transformの設定
	newParticle->worldTransform.Initialize();
	newParticle->worldTransform.parent_ = &worldTransform_;
	newParticle->worldTransform.UpdateMatrix();



	particles_.push_back(std::move(newParticle));

}


void ParticleSystem::UpdateParticle(Particle* particle) {

	/// 移動計算
	Vec3 velocity = particle->direction * 100.0f;

	if(isActiveAttenuation_) {
		velocity *= WorldTime::FrameTime();
	}

	particle->worldTransform.translation_ += velocity;

	//Mat4 matRotate;

	/// 回転計算
	switch(rotateType) {
	case kForward:		/// 順回転
		
		break;
	case kBackspin:		/// 逆回転
		
		break;
	case kSideForward:	/// 横順回転
		
		break;
	case kSideBackspin:	/// 横逆回転

		break;
	}

	particle->worldTransform.UpdateMatrix();

	/// 制限時間の減少
	float subTime = WorldTime::GetDeltaTime();
	if(isActiveAttenuation_) {
		subTime = WorldTime::FrameTime();
	}

	particle->lifeTime -= subTime;

}
