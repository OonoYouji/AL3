#include "EnemyStateUp.h"

#include <Enemy.h>
#include <WorldTime.h>

void EnemyState::Up::Update(Enemy* enemy) {

	Vec3 position = enemy->GetPosition();
	position += move_ * speed_ * WorldTime::FrameTime();

	enemy->SetPos(position);

}
