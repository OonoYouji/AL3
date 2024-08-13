#include <EnemyManager.h>

#include <Model.h>
#include <ModelManager.h>

#include <EnemyStateDown.h>
#include <EnemyStateLeft.h>
#include <EnemyStateRight.h>
#include <EnemyStateUp.h>
#include <EnemyStateChase.h>


void EnemyManager::Initialize() {
	models_.push_back(ModelManager::GetModel("enemy"));

	moveStates_.resize(Enemy::kCount);
	moveStates_[Enemy::kDown].reset(new EnemyState::Down);
	moveStates_[Enemy::kUp].reset(new EnemyState::Up);
	moveStates_[Enemy::kLeft].reset(new EnemyState::Left);
	moveStates_[Enemy::kRight].reset(new EnemyState::Right);
	moveStates_[Enemy::kChase].reset(new EnemyState::Chase);

}


void EnemyManager::AddEnemy(Enemy* enemy) {
	enemies_.push_back(enemy);
}

Model* EnemyManager::GetModel() const {
	return models_.front();
}

void EnemyManager::MoveStateUpdate(Enemy* enemy, int moveType) {
	if(!enemy) { return; }
	if(moveType >= Enemy::kCount) { return; }

	if(moveStates_[moveType].get()) {
		moveStates_[moveType]->Update(enemy);
	}

}
