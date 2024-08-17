#pragma once

#include <BaseGameObject.h>
#include <ObjectColor.h>
#include <Vector3.h>
#include <Enemy.h>

class Player;
class GameManagerObject;

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


	void SetCenter(const Vec3& center) { center_ = center; }
	void SetMin(const Vec3& min) { min_ = min; }
	void SetMax(const Vec3& max) { max_ = max; }

	void SetRangeZ(float rangeZ) { rangeZ_ = rangeZ; }
	void SetSpawnNum(int spawnNum) { spawnNum_ = spawnNum; }
	void SetType(int type) { type_ = type; }
	void SetEnemyHP(int enemyHP) { enemyHP_ = enemyHP; }


	const Vec3& GetCenter() const { return center_; }
	const Vec3& GetMin() const { return min_; }
	const Vec3& GetMax() const { return max_; }

	float GetRangeZ() const { return rangeZ_; }
	int GetSpawnNum() const { return spawnNum_; }
	int GetType() const { return type_; }
	int GetEnemyHP() const { return enemyHP_; }

private:

	/// ===================================================
	/// private : objects
	/// ===================================================

	static int sInstanceCount_;
	int id_ = 0;

	
	
	Vec3 center_ = {};
	Vec3 max_ = {  1,  1,  1 };
	Vec3 min_ = { -1, -1, -1 };

	int spawnNum_	= 10;			/// 出現する敵の数
	float rangeZ_	= 50.0f;		/// 敵が出現する距離
	int type_		= Enemy::kDown;	/// 出現する敵の移動タイプ
	int enemyHP_	= 1;			/// 出現する敵のHP

	bool isSpawned_ = false;

	Model* model_ = nullptr;
	ObjectColor objectColor;

	Player* pPlayer_ = nullptr;

};