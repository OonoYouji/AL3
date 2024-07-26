#include "Player.h"

#include <cassert>

#include <MainCamera.h>

#include <CreateName.h>
#include <Mat4Math.h>


Player::Player() {
	SetName(CreateName(this));
	SetTag("Player");
}
Player::~Player() {}



void Player::Initialize() {

	model_.reset(Model::CreateFromOBJ("axis"));

	worldTransform_.Initialize();

	octree_.SetGameObject(this);
	octree_.SetModelPtr(model_.get());

	collider_.Initialize(model_.get());

	color_.Initialize();

}



void Player::Update() {

	UpdateMatrix();

	octree_.Update();
	color_.SetColor({ 1.0f,1.0f,1.0f,0.5f });
	color_.TransferMatrix();

	collider_.SetPos(GetPosition());
	collider_.SetRotate(worldTransform_.rotation_);
	collider_.SetScale(worldTransform_.scale_);

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &color_);

	collider_.Draw();

	//octree_.Draw();

}
