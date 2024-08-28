#pragma once

#include <list>

#include <BaseGameObject.h>
#include <Model.h>
#include <ObjectColor.h>


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
	/// 一回に作成するパーティクルの量のセット
	/// </summary>
	/// <param name="count"></param>
	void SetCreateParticleCount(int count) {
		createParticleCount_ = count;
	}

	/// <summary>
	/// このインスタンスのライフタイムのセット
	/// </summary>
	/// <param name="lifeTime"></param>
	void SetThisLifeTime(float lifeTime) {
		thisLifeTime_ = lifeTime;
	}

	/// <summary>
	/// パーティクルのライフタイムのセット
	/// </summary>
	/// <param name="lifeTime"></param>
	void SetParticleLifeTime(float lifeTime) {
		particleLifeTime_ = lifeTime;
	}

	/// <summary>
	/// パーティクルの出現頻度のセット
	/// </summary>
	/// <param name="spawnCT"></param>
	void SetSpawnCT(float spawnCT) {
		spawnCT_ = spawnCT;
	}

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="modelName"></param>
	void SetModel(const std::string& modelName);

	void SetObjectColor(const ObjectColor& objectColor);

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
	float thisLifeTime_ = 1.0f; /// パーティクルシステムのライフタイム

	std::list<std::unique_ptr<Particle>> particles_;

	float spawnCT_ = 0.1f; /// 単位は秒
	float spawnTime_ = spawnCT_;
	int createParticleCount_ = 1; /// 一回に作成するパーティクルの量

	float particleLifeTime_ = 1.0f; /// パーティクルのライフタイム

	Vec3 direction_;
	float speed_ = 10.0f;
	float angle_ = 90.0f;

	bool isActiveAttenuation_; /// WorldTimeのAttenuationを適用されるのか

	bool isRotate_; /// particleが回転するかどうか 
	int rotateType; /// particleの回転方式

	ObjectColor objectColor_;

};