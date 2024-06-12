#include "EnemyStateDameged.h"

#include <algorithm>

#include "VectorMethod.h"

#include <Enemy.h>
#include "EnemyStateRoot.h"


EnemyStateDameged::EnemyStateDameged(Enemy* enemy) {
	BaseEnemyState::SetEnemy(enemy);

	red_ = 0.0f;
	color_ = { 0.0f, 0.0f, 0.0f, 1.0f };
}

EnemyStateDameged::~EnemyStateDameged() {}

void EnemyStateDameged::Update() {

	if(--actionFrame_ > 0) {
		float t = std::sin(static_cast<float>(actionFrame_ / 2.0f));
		red_ = std::lerp(0.5f, 1.0f, t);
		color_.x = red_;
		pEnemy_->SetColor(color_);
	} else {
		///- stateを基に戻す
		color_ = { 1.0f,1.0f,1.0f,1.0f };
		pEnemy_->SetColor(color_);
		pEnemy_->SetState(new EnemyStateRoot(pEnemy_));
	}

}

