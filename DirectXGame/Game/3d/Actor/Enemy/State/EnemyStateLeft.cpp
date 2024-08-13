#include "EnemyStateLeft.h"

#include <Enemy.h>
#include <WorldTime.h>

void EnemyState::Left::Update(Enemy* enemy) {

	Vec3 position = enemy->GetPosition();
	position += move_ * speed_ * WorldTime::FrameTime();

	enemy->SetPos(position);

}
