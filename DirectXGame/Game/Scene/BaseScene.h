#pragma once

#include "Audio.h"
#include "Input.h"


/// <summary>
/// すべてのSceneの基底クラス
/// </summary>
class BaseScene {
public:

	BaseScene();
	virtual ~BaseScene() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void Draw();

	/// <summary>
	/// 背景Spriteの描画
	/// </summary>
	virtual void BackSpriteDraw() = 0;

	/// <summary>
	/// 3dObjectの描画
	/// </summary>
	virtual void Object3dDraw() = 0;

	/// <summary>
	/// 前景Spriteの描画
	/// </summary>
	virtual void FrontSpriteDraw() = 0;

protected:

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

};