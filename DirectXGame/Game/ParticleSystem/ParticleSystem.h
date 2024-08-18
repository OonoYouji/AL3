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
		Vec3 direction;
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

	//void SetUseGravity()


private:
	
	/// ===================================================
	/// private : methods
	/// ===================================================
	void CreateParticle();

	void UpdateParticle(Particle* particle);

private:
	
	/// ===================================================
	/// private : objects
	/// ===================================================
	static int sInstanceCount_;
	int id_;

	Model* model_ = nullptr;

	std::list<std::unique_ptr<Particle>> particles_;

	int maxParticleCount_;
	const float kSpawnTime_ = 0.1f;
	float spawnTime_ = kSpawnTime_;
	float lifeTime_;
	float rotateValue_ = 0.0f;

	Vec3 direction_;

	bool isActiveAttenuation_; /// WorldTimeのAttenuationを適用されるのか
	bool isRotate_; /// particleが回転するかどうか 
	int rotateType; /// particleの回転方式

};