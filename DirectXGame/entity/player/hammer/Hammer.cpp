#include <Hammer.h>

#include <list>
#include <memory>

#include "Enemy.h"
#include "EnemyStateDameged.h"

#include "HitEffect.h"

Hammer::Hammer() {}
Hammer::~Hammer() {}

void Hammer::Initialize(Model* model) {
	Collider::Initialize();
	Collider::SetTag("Hammer");
	pModel_ = model;

	worldTransform_.Initialize();

	SetRadius(3.0f);
}

void Hammer::Update() {
	worldTransform_.UpdateMatrix();
}

void Hammer::Draw(const ViewProjection& viewProjection) {
	pModel_->Draw(worldTransform_, viewProjection);
}

void Hammer::OnCollision([[maybe_unused]] Collider* other) {
	if(other->GetTag() == "Enemy") {
		Enemy* enemy = static_cast<Enemy*>(other);
		uint32_t serialNo = enemy->GetSerialNo();

		///- 多段ヒット防止
		if(collisionRecord_.CheckLog(serialNo)) {
			return;
		}

		collisionRecord_.AddLog(serialNo);

		std::unique_ptr<HitEffect> newHitEffect = std::make_unique<HitEffect>();
		newHitEffect->SetModelPtr(enemy->GetHitEffectModel());
		newHitEffect->Initialize(enemy->GetHitEffectModel(), enemy->GetWorldPosition());

		enemy->AddHitEffect(std::move(newHitEffect));

		enemy->SetState(new EnemyStateDameged(enemy));
	}

}

void Hammer::ClearCollisionRecord() {
	collisionRecord_.Clear();
}