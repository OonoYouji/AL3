#pragma once

#include <WorldTransform.h>

/// <summary>
/// すべてのゲームオブジェクトの基本となるクラス
/// </summary>
class GameObjcet {
public:

	GameObjcet();
	~GameObjcet();

public:

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void UpdateMatrix();

	const Mat4& GetMatTransform() const;

private:

	WorldTransform worldTransform_;

	GameObjcet* parent_;

};