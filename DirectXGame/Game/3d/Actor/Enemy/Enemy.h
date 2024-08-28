#pragma once

#include <cmath>

#include <BaseGameObject.h>
#include <ObjectColor.h>

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

	enum ENEMY_PART {
		HEAD,
		BODY,
		TAIL,
		ENEMY_PART_COUNT
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

	void SetMoveType(int moveType) { moveType_ = moveType; }

	void SetHP(int hp) { hp_ = hp; }

	void SetHasItem(bool hasItem) {
		hasItem_ = hasItem;
	}

	void SetColor(const Vector4& color);

private:

	static int sInstanceCount_;
	int id_;

	int stateType_; /// enum StateType を参照
	int moveType_;	/// enum MoveType  を参照

	struct ModelPart {
		Model* model;
		WorldTransform transform_;
	};

	std::vector<std::unique_ptr<ModelPart>> modelParts_;
	ObjectColor objectColor_;

	/// status
	int hp_ = 1;

	bool hasItem_ = false;

};