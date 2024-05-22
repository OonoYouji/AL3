#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

#include "VectorMethod.h"

GameScene::GameScene() {}
GameScene::~GameScene() {

}

void GameScene::Initialize() {

	///// ↓ GET INSTANCE
	///// -----------------------------------------
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	///// -----------------------------------------


	///// ↓ KAMATA ENGINE 
	///// -----------------------------------------
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	PrimitiveDrawer::GetInstance()->Initialize();
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	///// -----------------------------------------


	///// ↓ TEXTURE
	///// -----------------------------------------
	playerTexture_ = TextureManager::Load("uvChecker.png");
	player3dReticleTexture_ = TextureManager::Load("Images/3dReticle.png");
	enemyTexture_ = TextureManager::Load("sample.png");
	///// -----------------------------------------


	///// ↓ CAMERA
	///// -----------------------------------------
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	viewProjection_.Initialize();

	///- RailCamera Initialize
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Init(Vec3f(0.0f, 0.0f, -30.0f), Vec3f(0.0f, 0.0f, 0.0f));
	///// -----------------------------------------


	///// ↓ PLAYER
	///// -----------------------------------------
	player_ = std::make_unique<Player>();
	Vec3f playerPosition = Vec3f(0.0f, 0.0f, 10.0f);
	player_->Init(Model::Create(), playerTexture_, playerPosition, player3dReticleTexture_);
	player_->SetParent(&railCamera_->GetWorldTransform());
	///// ----------------------------------------- 


	///// ↓ ENEMY
	///// -----------------------------------------
	enemies_.clear();
	enemyBullets_.clear();
	LoadEnemyPopData();
	///// -----------------------------------------


	///// ↓ SKYDOME
	///// -----------------------------------------
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();
	///// -----------------------------------------


	///// ↓ COLLISION MANAGER
	///// -----------------------------------------
	collisionManager_ = std::make_unique<CollisionManager>();
	collisionManager_->Init();
	///// -----------------------------------------


}

void GameScene::Update() {
#ifdef _DEBUG

	///// ↓ IMGUI DEBUG
	///// -----------------------------------------
	ImGui::Begin("GameScene");

	if(ImGui::Button("Reset Scene")) {
		Initialize();
	}

	ImGui::Checkbox("debugCamera isActive", &isDebugCameraActive_);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Checkbox("pause", &isPause_);
	isUpdateOneFrame_ = false;
	if(ImGui::Button("UpdateOneFrame")) {
		isUpdateOneFrame_ = true;
	}

	ImGui::End();
	///// -----------------------------------------


	///// ↓ DEBUG CAMERA 
	///// -----------------------------------------
	railCamera_->DebugDraw();
	if(isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		///- 行列の転送
		viewProjection_.TransferMatrix();
	}
	///// -----------------------------------------

#endif // _DEBUG

	/// ------------------------------
	/// ↓ 以降がゲームの更新処理
	/// ------------------------------


	///- trueのときは更新が止まる
	if(isPause_ && !isUpdateOneFrame_) { return; }


	///// ↓ 3DRAIL CAMERA
	///// -----------------------------------------
	///- カメラをレールカメラに切り替える
	//railCamera_->Update();
	if(!isDebugCameraActive_) {
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		///- 行列の転送
		viewProjection_.TransferMatrix();
	}
	///// ----------------------------------------- 



	///// ↓ PLAYER
	///// -----------------------------------------
	player_->Update(viewProjection_);
	MultiLockOn();
	///// -----------------------------------------


	///// ↓ ENEMY
	///// -----------------------------------------
	if(!enemies_.empty()) {
		for(auto& enemy : enemies_) {
			enemy->Update(viewProjection_);
		}
	}
	//- 消滅フラグが立った敵から消す
	for(auto& enemy : enemies_) {
		if(enemy->IsDead()) {
			player_->EraseEnemy(enemy.get());
		}
	}
	enemies_.remove_if([](auto& enemy) {
		if(enemy->IsDead()) {
			return true;
		} else {
			return false;
		}
	});

	///- 敵の出現
	UpdateEnemyPopCommands();
	///// -----------------------------------------


	///// ↓ ENEMY BULLET
	///// -----------------------------------------
	for(auto& bullet : enemyBullets_) {
		bullet->Update();
	}
	///- 消滅フラグが立った弾から消す
	enemyBullets_.remove_if([](auto& bullet) {
		if(bullet->IsDead()) {
			return true;
		} else {
			return false;
		}
	});
	///// -----------------------------------------


	///// ↓ SKYDOME
	///// -----------------------------------------
	skydome_->Update();
	///// -----------------------------------------


	///// ↓ COLLISION
	///// -----------------------------------------
	CheckAllCollision();
	///// -----------------------------------------

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>



	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>


	///// ↓ PLAYER
	///// -----------------------------------------
	player_->Draw(viewProjection_);
	///// -----------------------------------------


	///// ↓ ENEMY 
	///// -----------------------------------------
	if(!enemies_.empty()) {
		for(auto& enemy : enemies_) {
			enemy->Draw(viewProjection_);
		}
	}

	if(!enemyBullets_.empty()) {
		for(auto& bullet : enemyBullets_) {
			bullet->Draw(viewProjection_);
		}
	}
	///// -----------------------------------------


	///// ↓ SKYDOME
	///// -----------------------------------------
	skydome_->Draw(viewProjection_);
	///// -----------------------------------------


	///// ↓ 3DRAIL CAMERA
	///// -----------------------------------------
	railCamera_->Draw(viewProjection_);
	///// -----------------------------------------



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	///// ↓ PLAYER UI
	///// -----------------------------------------
	player_->DrawUI();
	///// -----------------------------------------



	///// ↓ ENEMY UI
	///// -----------------------------------------
	for(auto& enemy : enemies_) {
		enemy->DrawUI();
	}
	///// -----------------------------------------



	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}




void GameScene::CheckAllCollision() {

	SetColliderAll();
	collisionManager_->CheckCollisionAll();

}

void GameScene::SetColliderAll() {

	collisionManager_->ListClear();

	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemyBullets_;

	collisionManager_->PushBackCollider(player_.get());

	for(auto& enemy : enemies_) {
		collisionManager_->PushBackCollider(enemy.get());
	}

	for(auto& playerBullet : playerBullets) {
		collisionManager_->PushBackCollider(playerBullet.get());
	}

	for(auto& enemyBullet : enemyBullets) {
		collisionManager_->PushBackCollider(enemyBullet.get());
	}


}



void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {

	std::unique_ptr<EnemyBullet> newBullet;
	newBullet.reset(enemyBullet);
	enemyBullets_.push_back(std::move(newBullet));

}



void GameScene::EnemySpawn() {
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->SetPlayer(player_.get());
	newEnemy->SetGameScene(this);
	newEnemy->Init(Model::Create(), Vec3f(0.0f, 0.0f, 30.0f), enemyTexture_, player3dReticleTexture_);
	enemies_.push_back(std::move(newEnemy));
}


void GameScene::EnemySpawnAndReset() {
	EnemySpawn();
	enemySpawnTimedCall_.push_back(std::make_unique<TimedCall>(std::bind(&GameScene::EnemySpawnAndReset, this), 60));

}

void GameScene::EnemySpawn(const Vec3f& position) {
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->SetPlayer(player_.get());
	newEnemy->SetGameScene(this);
	newEnemy->Init(Model::Create(), position, enemyTexture_, player3dReticleTexture_);
	enemies_.push_back(std::move(newEnemy));
}

void GameScene::LoadEnemyPopData() {

	///- ファイルを開く
	std::ifstream file;
	file.open("./Resources/Scripts/ememyPopData.csv");
	assert(file.is_open());

	enemyPopCommands_ << file.rdbuf();

	file.close();

}


void GameScene::UpdateEnemyPopCommands() {

	///- 待機処理
	if(isWaitEnemySpawn_) {
		--waitTime_;
		if(waitTime_ <= 0.0f) {
			isWaitEnemySpawn_ = false;
		}
		return;
	}

	std::string line;
	while(getline(enemyPopCommands_, line)) {

		std::istringstream line_stream(line);

		std::string word;
		getline(line_stream, word, ',');

		///- //で始まる行はコメント
		if(word.find("//") == 0) {
			continue;
		}

		///- POPコマンド
		if(word.find("POP") == 0) {

			// x
			getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// y
			getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// z
			getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			EnemySpawn(Vec3f(x, y, z));

			/// WAITコマンド
		} else if(word.find("WAIT") == 0) {

			getline(line_stream, word, ',');

			///- 待ち時間
			int32_t waitTime = atoi(word.c_str());

			///- 待機開始
			isWaitEnemySpawn_ = true;
			waitTime_ = waitTime;

			///- コマンドループから抜ける
			break;
		}



	}

}

void GameScene::MultiLockOn() {

	Matrix4x4 matViewport = Mat4::MakeViewport(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	Matrix4x4 matVPV = viewProjection_.matView * viewProjection_.matProjection * matViewport;

	for(auto& enemy : enemies_) {

		Vec3f enemyPosition = Mat4::Transform(enemy->GetWorldPosition(), matVPV);
		Vec2f enemyScreenPosition = Vec2f(enemyPosition.x, enemyPosition.y);

		float length = VectorMethod::Length(enemyScreenPosition - player_->Get3DReticleScreenPosition());
		if(length < 30.0f) {
			enemy->SetIsLocked(true);
			player_->PushBackEnemy(enemy.get());
		}

	}

}
