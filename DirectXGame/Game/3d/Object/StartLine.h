#pragma once

#include <BaseGameObject.h>
#include <Model.h>


/// ===================================================
/// ゲームのスタートライン
/// ===================================================
class StartLine final : public BaseGameObject {
public:

	StartLine();
	~StartLine() {}

	/// ===================================================
	/// public : methods
	/// ===================================================

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 最後の更新
	/// </summary>
	void LastUpdate() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;


public:

	/// ===================================================
	/// public : not override methods
	/// ===================================================

	void SetGameManagerObject(BaseGameObject* object);


private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	Model* model_ = nullptr;

	BaseGameObject* gameManagerObject_ = nullptr;

};