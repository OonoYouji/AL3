#pragma once

#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"



///- Enemyの状態
enum class Phase : int32_t {
	Approach,	//- 接近
	Leave,		//- 離脱
};


/// -------------------------
/// 敵
/// -------------------------
class Enemy {
public:

	Enemy();
	~Enemy();

	void Init(Model* model, const Vec3f& position, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private: ///- メンバ変数

	///- モデルと画像
	std::unique_ptr<Model> model_;
	uint32_t textureHandle_;

	///- world座標
	WorldTransform worldTransform_;

	Vec3f velocity_;
	Vec3f approachVelocity_;
	Vec3f leaveVelocity_;
	float speed_;

	///- 状態
	Phase phase_;

	static void (Enemy::* spFuncTable[])();

	///- メンバ関数
	void UpdateApproach();
	void UpdateLeave();

};