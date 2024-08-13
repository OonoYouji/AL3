#pragma once

#include <list>
#include <vector>
#include <memory>

#include <Enemy.h>
#include <EnemyEmitter.h>
#include <BaseEnemyState.h>

class Model;

/// ===================================================
/// 敵の管理クラス
/// ===================================================
class EnemyManager final {
	EnemyManager() {};
	~EnemyManager() {};
public:


	static inline EnemyManager* GetInstance() {
		static EnemyManager instance;
		return &instance;
	}


	void Initialize();


	void AddEnemy(Enemy* enemy);

	Model* GetModel()const;

	void MoveStateUpdate(Enemy* enemy, int moveType);

private:

	///
	std::list<Enemy*> enemies_;
	std::list<EnemyEmitter*> emitters_;

	std::list<Model*> models_;

	/// 動きの種類
	std::vector<std::unique_ptr<EnemyState::BaseState>> moveStates_;


private:
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator= (const EnemyManager&) = delete;
	EnemyManager& operator= (EnemyManager&&) = delete;
};