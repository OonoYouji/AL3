#include <Hammer.h>

#include "Enemy.h"
#include "EnemyStateDameged.h"


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
		enemy->SetState(new EnemyStateDameged(enemy));
	}

}