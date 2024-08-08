#pragma once

#include <list>
#include <memory>

#include <Enemy.h>

class Model;

/// ===================================================
/// 敵の管理クラス
/// ===================================================
class EnemyManager final {
public:

	EnemyManager() {};
	~EnemyManager() {};


	void Initialize();


private:


	using unique_ptr_Enemy = std::unique_ptr<Enemy>;
	std::list<unique_ptr_Enemy> enemies_;

	std::unique_ptr<Model> enemyModel_;

};