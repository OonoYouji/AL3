#pragma once

#include <list>
#include <vector>
#include <memory>

#include <Enemy.h>
#include <EnemyEmitter.h>
#include <BaseEnemyState.h>

class Model;

/// ===================================================
/// 敵の管理クラス
/// ===================================================
class EnemyManager final {
	EnemyManager() {};
	~EnemyManager() {};
public:


	/// <summary>
	/// インスタンス確保
	/// </summary>
	/// <returns></returns>
	static inline EnemyManager* GetInstance() {
		static EnemyManager instance;
		return &instance;
	}


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// imguiを使用したデバッグ処理
	/// </summary>
	void ImGuiDebug();



	/// <summary>
	/// エネミーの追加
	/// </summary>
	/// <param name="enemy"></param>
	void AddEnemy(Enemy* enemy);
	
	/// <summary>
	/// エミッターの追加
	/// </summary>
	/// <param name="emitter"></param>
	void AddEmitter(EnemyEmitter* emitter);

	void SubEmitter(EnemyEmitter* emitter);

	void DesctoryEmitter(EnemyEmitter* emitter);

	/// <summary>
	/// Enemyのステートの更新処理
	/// </summary>
	/// <param name="enemy"></param>
	/// <param name="moveType"></param>
	void MoveStateUpdate(Enemy* enemy, int moveType);



	/// <summary>
	/// jsonファイルに保存		(エミッター限定)
	/// </summary>
	/// <param name="filePath">出力先のファイルパス</param>
	void SaveJson(const std::string& filePath);

	/// <summary>
	/// jsonファイルの読み込み	(エミッター限定)
	/// </summary>
	/// <param name="filePath"></param>
	void LoadJson(const std::string& filePath);



	/// <summary>
	/// emitterの作成
	/// </summary>
	EnemyEmitter* CreateEmitter();

private:

	///
	std::list<Enemy*> enemies_;
	std::list<EnemyEmitter*> emitters_;
	std::list<EnemyEmitter*> desctoryEmitter_;

	/// 動きの種類
	std::vector<std::unique_ptr<EnemyState::BaseState>> moveStates_;

	GameManagerObject* pGameManagerObject_ = nullptr;

private:
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator= (const EnemyManager&) = delete;
	EnemyManager& operator= (EnemyManager&&) = delete;
};