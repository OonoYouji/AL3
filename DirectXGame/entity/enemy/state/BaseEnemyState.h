#pragma once

class Enemy;


/// <summary>
/// 
/// </summary>
class BaseEnemyState {
public:

	virtual ~BaseEnemyState() = default;

	/// <summary>
	/// 更新処理の仮想関数
	/// </summary>
	virtual void Update() = 0;
	
	/// <summary>
	/// EnemyへのPointerのSetter
	/// </summary>
	/// <param name="enemy"></param>
	void SetEnemy(Enemy* enemy);

protected:

	Enemy* pEnemy_;

};


inline void BaseEnemyState::SetEnemy(Enemy* enemy) {
	pEnemy_ = enemy;
}