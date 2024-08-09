#pragma once


#include <BaseGameObject.h>

class Model;

/// ===================================================
/// 行動パターン
/// ===================================================
enum EnemyStateType {
	kNone	= 1 << 0,
	kMove	= 1 << 1,
	kAttack	= 1 << 2,
};

/// ===================================================
/// 敵のクラス
/// ===================================================
class Enemy : public BaseGameObject {
public:

	Enemy();
	~Enemy() {}

	void Initialize() override;

	void Update() override;
	void LastUpdate() override;

	void Draw() override;


	void Move();

	void Attack();


	void SetModel(Model* model);


private:

	static int instanceCount_;
	int id_;

	using StateType = EnemyStateType;
	int stateType_;


	Model* model_ = nullptr;

};