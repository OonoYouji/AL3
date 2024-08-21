#pragma once

#include <list>

#include <BaseGameObject.h>
#include <Model.h>

/// ===================================================
/// パーティクルシステム
/// ===================================================
class ParticleSystem final : public BaseGameObject {
	
	/// ===================================================
	/// private : sub class
	/// ===================================================

	struct Particle {
		WorldTransform worldTransform;
		Vec3 velocity;
		float lifeTime;
	};

public:

	/// ===================================================
	/// public : sub class  or  enum
	/// ===================================================

	enum RotateType {
		kForward,		/// 順回転
		kBackspin,		/// 逆回転
		kSideForward,	/// 横順回転
		kSideBackspin,	/// 横逆回転
	};


public:

	ParticleSystem();
	~ParticleSystem() {}
	
	/// ===================================================
	/// public : methods
	/// ===================================================
	void Initialize() override;

	void Update() override;

	void Draw() override;


	/// <summary>
	/// 時間の減衰度を使用するかどうかのフラグ
	/// </summary>
	void SetIsActiveAttenuation(bool isActiveAttenuation) {
		isActiveAttenuation_ = isActiveAttenuation;
	}

	/// <summary>
	/// 一回に作成するパーティクルの量
	/// </summary>
	/// <param name="count"></param>
	void SetCreateParticleCount(int count) {
		createParticleCount_ = count;
	}

private:
	
	/// ===================================================
	/// private : methods
	/// ===================================================
	void CreateParticle();

	void UpdateParticle(Particle* particle);

	void CreateVariablesGroup();

private:
	
	/// ===================================================
	/// private : objects
	/// ===================================================
	static int sInstanceCount_;
	int id_;

	Model* model_ = nullptr;

	std::list<std::unique_ptr<Particle>> particles_;

	float spawnCT_ = 0.1f;
	float spawnTime_ = spawnCT_;
	int createParticleCount_ = 1; /// 一回に作成するパーティクルの量

	float lifeTime_;

	float speed_ = 10.0f;

	Vec3 direction_;
	float angle_ = 90.0f;

	bool isActiveAttenuation_; /// WorldTimeのAttenuationを適用されるのか

	bool isRotate_; /// particleが回転するかどうか 
	int rotateType; /// particleの回転方式

};