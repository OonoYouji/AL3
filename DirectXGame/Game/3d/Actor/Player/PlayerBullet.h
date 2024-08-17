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


	void OnCollisionEnter(BaseGameObject* collision) override;


	void SetModel(Model* model);

	bool IsDesctory() const {
		return leftLifeTime_ <= 0.0f;
	};

private:

	static int sInstanceCount_;
	int id_ = 0;


	Vec3 move_{};
	float speed_ = 30.0f;

	Model* model_ = nullptr;

	static const float skLifeTime_;
	float leftLifeTime_ = skLifeTime_;

	ObjectColor objectColor_;

};
