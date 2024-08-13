#pragma once

#include <cmath>

#include <BaseGameObject.h>

class Model;

/// ===================================================
/// 敵のクラス
/// ===================================================
class Enemy : public BaseGameObject {
public:

	/// ===================================================
	/// 行動パターン
	/// ===================================================
	enum StateType {
		kNone   = 1 << 0, /// 何もしない
		kMove   = 1 << 1, /// 移動する
		kAttack = 1 << 2, /// 攻撃する
	};


	enum MoveType {
		kDown,	/// 上から下へ
		kUp,	/// 下から上へ
		kLeft,	/// 右から左へ
		kRight,	/// 左から右へ
		kChase,	/// プレイヤーを追う
		kCount, /// enumのカウント用
	};


public:

	Enemy();
	~Enemy() {}

	void Initialize() override;

	void Update() override;
	void LastUpdate() override;

	void Draw() override;

	void OnCollisionEnter(BaseGameObject* collision) override;

public:

	/// -------------------------------------------
	/// not override methods
	/// -------------------------------------------

	void Attack();

	void CreateStatusGroup();


	void SetModel(Model* model);

	void SetMoveType(int moveType) { moveType_ = moveType; }

private:

	static int instanceCount_;
	int id_;

	int stateType_; /// enum StateType を参照
	int moveType_;	/// enum MoveType  を参照

	Model* model_ = nullptr;

	/// status
	uint32_t hp_ = 10;


	/// Move
	Vec3 move_{};
	float speed_ = 4.0f;

	/// Attack

};