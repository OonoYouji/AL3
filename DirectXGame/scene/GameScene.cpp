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

	///- 右上の軸表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	player_ = std::make_unique<Player>();
	player_->Init(Model::Create(), TextureManager::Load("uvChecker.png"));

	enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());
	enemy_->Init(Model::Create(), { 5.0f,2.0f, 50.0f }, TextureManager::Load("sample.png"));

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
	} else {
		///- 行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

#endif // _DEBUG

	/// ------------------------------
	/// ↓ 以降がゲームの更新処理
	/// ------------------------------

	if(isPause_) { return; }


	player_->Update();


	if(enemy_.get()) {
		enemy_->Update();
	}

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


	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

	std::list<Collider*> colliders;
	colliders.push_back(player_.get());
	colliders.push_back(enemy_.get());

	for(auto& playerBullet : playerBullets) {
		colliders.push_back(playerBullet.get());
	}

	for(auto& enemyBullet : enemyBullets) {
		colliders.push_back(enemyBullet.get());
	}


	auto itrA = colliders.begin();
	for(; itrA != colliders.end(); ++itrA) {

		Collider* colliderA = *itrA;

		auto itrB = itrA;
		itrB++;

		for(; itrB != colliders.end(); ++itrB) {
			Collider* colliderB = *itrB;

			///- ペアとの当たり判定
			CheckCollisionPair(colliderA, colliderB);

		}

	}



}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	///- 衝突フィルタリング
	if((colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) == 0
	   || (colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()) == 0) {
		return;
	}

	Vec3f posA = colliderA->GetWorldPosition();
	Vec3f posB = colliderB->GetWorldPosition();
	float radius = colliderA->GetRadius() + colliderB->GetRadius();

	///- 衝突判定を取る
	if(VectorMethod::Length(posB - posA) < radius) {

		colliderA->OnCollision();
		colliderB->OnCollision();

	}

}
