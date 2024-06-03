#include <LockOn.h>

#include <TextureManager.h>


LockOn::LockOn() {}
LockOn::~LockOn() {}


void LockOn::Initialize() {

	uint32_t textureHandle = TextureManager::GetInstance()->Load("");
	lockOnMark_.reset(Sprite::Create());

}


void LockOn::Update() {

}


void LockOn::Draw() {

}
