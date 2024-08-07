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

	model_.reset(Model::CreateSphere());

	worldTransform_.Initialize();

	color_.Initialize();

}



void Player::Update() {

	UpdateMatrix();

	color_.SetColor({ 1.0f,1.0f,1.0f,0.5f });
	color_.TransferMatrix();

	UpdateMatrix();
}



void Player::Draw() {
	model_->Draw(worldTransform_, MainCamera::GetInstance()->GetViewProjection(), &color_);

}
