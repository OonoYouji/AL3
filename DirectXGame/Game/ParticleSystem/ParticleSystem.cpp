#include "ParticleSystem.h"

#include <MainCamera.h>

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
