#pragma once

#include <map>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>

#include "Collider.h"

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class BaseCharacter : public Collider {
public:

	virtual void Initialize(const std::map<std::string, Model*>& models);

	virtual void Update();

	virtual void Draw(const ViewProjection& viewProjection);

protected:

	std::map<std::string, Model*> models_;

	WorldTransform worldTransform_;

public:

	const WorldTransform& GetWorldTransform() const {
		return worldTransform_;
	}


	/// <summary>
	/// 当たり判定の中心を得る
	/// </summary>
	/// <returns></returns>
	Vec3f GetCenterPosition() const override;

};