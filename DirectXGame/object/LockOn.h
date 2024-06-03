#pragma once

#include <memory>

#include <Sprite.h>

/// <summary>
/// ロックオン
/// </summary>
class LockOn {
public:

	LockOn();
	~LockOn();

	void Initialize();

	void Update();

	void Draw();

private:

	std::unique_ptr<Sprite> lockOnMark_;

};