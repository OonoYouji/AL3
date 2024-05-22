#include <Ground.h>



Ground::Ground() {}
Ground::~Ground() {}



void Ground::Initialize() {

	worldTransform_.Initialize();
	worldTransform_.scale_ *= 10.0f;
	worldTransform_.UpdateMatrix();

	model_.reset(Model::CreateFromOBJ("ground"));

}


void Ground::Update() {

	worldTransform_.UpdateMatrix();

}


void Ground::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
