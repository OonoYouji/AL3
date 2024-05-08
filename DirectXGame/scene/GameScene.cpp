#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

#include "VectorMethod.h"

GameScene::GameScene() {}
GameScene::~GameScene() {

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();


	/// -------------------------
	/// メンバ変数の初期化
	/// -------------------------

	///- カメラの初期化
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	isDebugCameraActive_ = false;
	viewProjection_.Initialize();

	///- RailCamera Initialize
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Init(Vec3f(0.0f, 0.0f, -30.0f), Vec3f(0.0f, 0.0f, 0.0f));


	///- 右上の軸表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	PrimitiveDrawer::GetInstance()->Initialize();
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	///- Player Initialize
	player_ = std::make_unique<Player>();
	Vec3f playerPosition = Vec3f(0.0f, 0.0f, 30.0f);
	player_->Init(Model::Create(), TextureManager::Load("uvChecker.png"), playerPosition);
	player_->SetParent(&railCamera_->GetWorldTransform());

	///- Enemy Initialize
	enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());
	enemy_->Init(Model::Create(), { 5.0f,2.0f, 50.0f }, TextureManager::Load("sample.png"));

	///- Skydome Initialize
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	///- RailSpline3D
	railSpline3D_ = std::make_unique<RailSpline3D>();
	railSpline3D_->Init();



	///- CollisionManager Initialize
	collisionManager_ = std::make_unique<CollisionManager>();
	collisionManager_->Init();

}

void GameScene::Update() {
#ifdef _DEBUG

	/// -------------------------------------------
	/// ImGui Debug
	/// -------------------------------------------

	ImGui::Begin("GameScene");

	if(ImGui::Button("Reset Scene")) {
		Initialize();
	}

	ImGui::Checkbox("debugCamera isActive", &isDebugCameraActive_);

	ImGui::Spacing();

	ImGui::Checkbox("pause", &isPause_);


	ImGui::End();



	/// -------------------------------------------
	/// DebugCamera Update
	/// -------------------------------------------

	if(isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		///- 行列の転送
		viewProjection_.TransferMatrix();
	}

#endif // _DEBUG

	/// ------------------------------
	/// ↓ 以降がゲームの更新処理
	/// ------------------------------


	if(isPause_) { return; }


	///- カメラをレールカメラに切り替える
	if(!isDebugCameraActive_) {
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		///- 行列の転送
		viewProjection_.TransferMatrix();
	}




	player_->Update();

	if(enemy_.get()) {
		enemy_->Update();
	}

	skydome_->Update();


	///- 衝突判定を取る
	CheckAllCollision();

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
	player_->Draw(viewProjection_);

	if(enemy_.get()) {
		enemy_->Draw(viewProjection_);
	}

	skydome_->Draw(viewProjection_);


	railSpline3D_->Draw(viewProjection_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

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
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

	collisionManager_->PushBackCollider(player_.get());
	collisionManager_->PushBackCollider(enemy_.get());

	for(auto& playerBullet : playerBullets) {
		collisionManager_->PushBackCollider(playerBullet.get());
	}

	for(auto& enemyBullet : enemyBullets) {
		collisionManager_->PushBackCollider(enemyBullet.get());
	}


}
