#pragma once

#include <BaseGameObject.h>
#include <ObjectColor.h>
#include <Vector3.h>

/// ===================================================
/// エネミーの出現位置 クラス
/// ===================================================
class EnemyEmitter final : public BaseGameObject {
public:

	EnemyEmitter();
	~EnemyEmitter() {}


	/// ===================================================
	/// public : methods
	/// ===================================================

	void Initialize() override;

	void Update() override;

	void LastUpdate() override;

	void Draw() override;

public:

	/// ===================================================
	/// public : not override methods
	/// ===================================================

	void CreateEnemies();


	void CreateVariablesGroup();


	void SetMin(const Vec3& min) { min_ = min; }
	void SetMax(const Vec3& max) { max_ = max; }

	void SetSpawnNum(int spawnNum) { spawnNum_ = spawnNum; }

	void SetType(int type) { type_ = type; }


private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	Vec3 min_ = { -1, -1, -1 };
	Vec3 max_ = {  1,  1,  1 };

	int spawnNum_;

	float rangeZ_;

	int type_;

	Model* model_ = nullptr;
	ObjectColor objectColor;

};