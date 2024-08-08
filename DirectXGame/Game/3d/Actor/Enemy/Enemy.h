#pragma once


#include <BaseGameObject.h>



/// ===================================================
/// 敵のクラス
/// ===================================================
class Enemy : public BaseGameObject {
public:

	Enemy() {}
	~Enemy() {}

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:



}; 