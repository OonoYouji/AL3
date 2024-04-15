#pragma once

#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "BaseEnemyState.h"
#include "EnemyBullet.h"


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

	std::unique_ptr<BaseEnemyState> state_;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	int32_t shotCT_;
	float bulletSpeed_;

private: ///- メンバ関数

	/// <summary>
	/// 弾を打つ
	/// </summary>
	void Fire();


public: ///- クラス外参照可

	void Move(const Vec3f& velocity);

	void ChangeState(std::unique_ptr<BaseEnemyState> baseEnemyState);

	const Vec3f& Position() const { return worldTransform_.translation_; }


};