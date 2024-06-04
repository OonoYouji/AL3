#include <LockOn.h>

#include <TextureManager.h>

#include "GlobalVariables.h"
#include "MyMath.h"

LockOn::LockOn() {}
LockOn::~LockOn() {}


void LockOn::Initialize() {

	input_ = Input::GetInstance();

	uint32_t textureHandle = TextureManager::GetInstance()->Load("Images/3dReticle.png");
	lockOnMark_.reset(Sprite::Create(
		textureHandle, Vec2f(0.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vec2f(0.5f, 0.5f)));

	minDistance_ = 10.0f;
	maxDistance_ = 30.0f;
	angleRange_ = 20.0f * kDegreeToRadian_;

	const char* groupName = "LockOn";
	GlobalVariables* gv = GlobalVariables::GetInstance();
	gv->CreateGroup(groupName);
	gv->AddItem(groupName, "minDistance", minDistance_);
	gv->AddItem(groupName, "maxDistance", maxDistance_);
	gv->AddItem(groupName, "angleRange", angleRange_);



}


void LockOn::Update(const std::list<std::unique_ptr<Enemy>>& enemies, const ViewProjection& viewProjection) {

	///- ImGuiで編集した値を代入
	ApplyGlobalVariables();

	if(target_) {
		///- ターゲットの解除処理
		if(input_->TriggerKey(DIK_T)) {
			target_ = nullptr;
		} else if(OutOfRange(viewProjection)) {
			target_ = nullptr;
		}

	} else {

		///- ターゲットの探索処理
		if(input_->PushKey(DIK_T)) {
			Search(enemies, viewProjection);
		}


	}

	if(target_) {
		///- ターゲットマークの座標計算
		if(target_) {

			///- worldからscreenに変換しスプライトの座標にする
			lockOnMark_->SetPosition(W2SPosition(target_->GetWorldPosition(), viewProjection));
		}

	}

}


void LockOn::Draw() {

	if(target_) {
		lockOnMark_->Draw();
	}

}


/// <summary>
/// 索敵
/// </summary>
void LockOn::Search(const std::list<std::unique_ptr<Enemy>>& enemies, const ViewProjection& viewProjection) {

	///- ロックオン対象の絞り込み
	std::list<std::pair<float, const Enemy*>> targets;

	for(const auto& enemy : enemies) {

		Vec3f worldPosition = enemy->GetWorldPosition();
		Vec3f viewPosition = Mat4::Transform(worldPosition, viewProjection.matView);

		///- 距離の確認; 条件を満たさなければcontinue
		if(!(minDistance_ <= viewPosition.z && viewPosition.z <= maxDistance_)) {
			continue;
		}

		///- 角度条件をチェック
		if(IsAngleWithinRange(viewPosition)) {
			targets.emplace_back(std::make_pair(viewPosition.z, enemy.get()));
		}

	}

	///- 距離でソートしてロックオン対象を決定
	target_ = nullptr;
	if(!targets.empty()) {
		///- 距離順にソート
		targets.sort([](auto& pair1, auto& pair2) { return pair1.first < pair2.first; });
		target_ = targets.front().second;
	}

}


/// <summary>
/// 範囲外かどうか確認
/// </summary>
bool LockOn::OutOfRange(const ViewProjection& viewProjection) {

	Vec3f viewPosition = Mat4::Transform(target_->GetWorldPosition(), viewProjection.matView);

	///- 距離条件チェック
	if(minDistance_ <= viewPosition.z && viewPosition.z <= maxDistance_) {

		if(IsAngleWithinRange(viewPosition)) {
			return false; //- 範囲内なので
		}

	}

	return true; //- 範囲内判定が出なかったので
}



bool LockOn::IsAngleWithinRange(const Vec3f& viewPosition) {
	///- カメラ前方との角度を計算
	float arcTangent = std::atan2(
		std::sqrt(std::pow(viewPosition.x, 2.0f) + std::pow(viewPosition.y, 2.0f)),
		viewPosition.z

	);

	///- 角度条件をチェック
	if(std::abs(arcTangent) <= angleRange_) {
		return true; //- 範囲内なので
	}

	return false;
}


void LockOn::ApplyGlobalVariables() {
	const char* groupName = "LockOn";
	GlobalVariables* gv = GlobalVariables::GetInstance();
	minDistance_ = gv->GetFloatValue(groupName, "minDistance");
	maxDistance_ = gv->GetFloatValue(groupName, "maxDistance");
	angleRange_ = gv->GetFloatValue(groupName, "angleRange");
}
