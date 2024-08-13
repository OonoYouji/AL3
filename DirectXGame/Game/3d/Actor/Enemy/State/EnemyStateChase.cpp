#include "EnemyStateChase.h"

#include <Enemy.h>
#include <WorldTime.h>
#include <GameObjectManager.h>

#include <Vec3Math.h>

void EnemyState::Chase::Update(Enemy* enemy) {

	BaseGameObject* player = GameObjectManager::GetInstance()->GetGameObject("Player");

	Vec3 position = enemy->GetPosition();

	move_ = player->GetPosition() - position;
	move_ = Normalize(move_);

	position += move_ * speed_ * WorldTime::FrameTime();

	enemy->SetPos(position);

}
