#include "EnemyStateRight.h"

#include <Enemy.h>
#include <WorldTime.h>

void EnemyState::Right::Update(Enemy* enemy) {

	Vec3 position = enemy->GetPosition();
	position += move_ * speed_ * WorldTime::FrameTime();

	enemy->SetPos(position);

}
