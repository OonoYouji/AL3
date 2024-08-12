#pragma once

#include <list>
#include <memory>

#include <Enemy.h>

class Model;

/// ===================================================
/// 敵の管理クラス
/// ===================================================
class EnemyManager final {
	EnemyManager() {};
	~EnemyManager() {};
public:


	static EnemyManager* GetInstance() {
		static EnemyManager instance;
		return &instance;
	}


	void Initialize();


	void AddEnemy(Enemy* enemy);

	Model* GetModel()const;

private:

	///
	std::list<Enemy*> enemies_;

	std::list<Model*> models_;


private:
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator= (const EnemyManager&) = delete;
	EnemyManager& operator= (EnemyManager&&) = delete;
};