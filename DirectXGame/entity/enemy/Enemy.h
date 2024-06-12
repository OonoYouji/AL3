#pragma once 

#include <memory>
#include <list>

#include <Vector3.h>

#include <Model.h>

#include <BaseCharacter.h>
#include "BaseEnemyState.h"
#include "HitEffect.h"


/// <summary>
/// 敵
/// </summary>
class Enemy
	: public BaseCharacter {
public:

	Enemy();
	~Enemy();

	void Initialize(const std::map<std::string, Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;


	/// <summary>
	/// World座標でのpositionを取得
	/// </summary>
	Vec3f GetWorldPosition() const;


	/// <summary>
	/// 衝突時に呼び出す
	/// </summary>
	void OnCollision([[maybe_unused]] Collider* other) override;

	/// <summary>
	/// オブジェクトの色のSetter
	/// </summary>
	/// <param name="color"></param>
	void SetColor(const Vector4& color);

	/// <summary>
	/// 引数分だけ移動する
	/// </summary>
	/// <param name="velocity"></param>
	void Moving(const Vec3f& velocity);

	/// <summary>
	/// RotationのSetter
	/// </summary>
	/// <param name="rotate"></param>
	void SetRotation(const Vec3f& rotate);

	/// <summary>
	/// 新しいStaeteのSetter
	/// </summary>
	/// <param name="newState"></param>
	void SetState(BaseEnemyState* newState);

	/// <summary>
	/// シリアルナンバーの取得
	/// </summary>
	/// <returns></returns>
	uint32_t GetSerialNo() const;

	/// <summary>
	/// HitEffectの追加
	/// </summary>
	/// <param name="hitEffect"></param>
	void AddHitEffect(std::unique_ptr<HitEffect> hitEffect);

	/// <summary>
	/// HitEffect用モデルの取得
	/// </summary>
	/// <returns></returns>
	Model* GetHitEffectModel() const;

private:

	/// <summary>
	/// 各パーツの初期化
	/// </summary>
	void PartsInitialize();
	
	void Animation();


private:

	static uint32_t nextSerialNo_;
	uint32_t serialNo_;

	std::map<std::string, WorldTransform> partsWorldTransforms_;
	std::unique_ptr<ObjectColor> objectColor_;
	std::unique_ptr<BaseEnemyState> state_;

	float aimationTime_;

	std::list<std::unique_ptr<HitEffect>> hitEffects_;
	std::unique_ptr<Model> hitEffectModel_;

};



inline Vec3f Enemy::GetWorldPosition() const {
	return Vec3f{
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	};
}

inline void Enemy::SetColor(const Vector4& color) {
	objectColor_->SetColor(color);
}

inline uint32_t Enemy::GetSerialNo() const {
	return serialNo_;
}

inline Model* Enemy::GetHitEffectModel() const {
	return hitEffectModel_.get();
}