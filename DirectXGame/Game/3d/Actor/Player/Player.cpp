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

	model_.reset(Model::CreateFromOBJ("ICO"));

	worldTransform_.Initialize();

	octree_.SetGameObject(this);
	octree_.SetModelPtr(model_.get());

}



void Player::Update() {

	UpdateMatrix();

	octree_.Update();

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection());

	octree_.Draw();

}
