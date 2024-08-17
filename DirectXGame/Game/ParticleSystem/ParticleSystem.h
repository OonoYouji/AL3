#pragma once

#include <list>

#include <BaseGameObject.h>
#include <Model.h>


/// ===================================================
/// パーティクルシステム
/// ===================================================
class ParticleSystem final : public BaseGameObject {
	
	/// ===================================================
	/// 1粒子当たりの構造
	/// ===================================================
	struct Particle {
		WorldTransform worldTransform;
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


private:
	
	/// ===================================================
	/// private : methods
	/// ===================================================
	void CreateParticle();

private:
	
	/// ===================================================
	/// private : objects
	/// ===================================================
	static int sInstanceCount_;
	int id_;

	Model* model_ = nullptr;

	std::list<std::unique_ptr<Particle>> particles_;

	int maxParticleCount_;
	int spawnTime_;
	int time;

	bool isActiveAttenuation_; /// WorldTimeのAttenuationを適用されるのか

};