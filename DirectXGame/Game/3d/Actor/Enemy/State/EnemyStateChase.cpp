#include "EnemyStateChase.h"

#include <Enemy.h>
#include <WorldTime.h>
#include <GameObjectManager.h>

#include <Vec3Math.h>
#include <Mat4Math.h>


void EnemyState::Chase::Update(Enemy* enemy) {

	BaseGameObject* player = GameObjectManager::GetInstance()->GetGameObject("Player");

	Vec3 position = enemy->GetPosition();
	Vec3 playerPosition = player->GetPosition();

	move_ = {
		playerPosition.x - position.x,
		0.0f,
		playerPosition.z - position.z
	};
	move_ = Normalize(move_);

	position += move_ * speed_ * WorldTime::FrameTime();

	enemy->SetPos(position);

	enemy->SetRotateY(std::atan2(move_.x, move_.z));

}
