#pragma once

#include <BaseGameObject.h>
#include <ObjectColor.h>

class Model;

class PlayerBullet final : public BaseGameObject {
public:

	PlayerBullet();
	~PlayerBullet();



	void Initialize() override;

	void Update() override;

	void Draw() override;


	void SetModel(Model* model);

	bool IsDesctory() const {
		return leftLifeTime_ <= 0.0f;
	};

private:

	static int instanceCount_;
	int id_ = 0;


	Vec3 move_{};
	float speed_ = 30.0f;

	Model* model_ = nullptr;

	static const float kLifeTime_;
	float leftLifeTime_ = kLifeTime_;

	ObjectColor objectColor_;

};
