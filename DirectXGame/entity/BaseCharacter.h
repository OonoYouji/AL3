#pragma once

#include <map>

#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>


/// <summary>
/// キャラクターの基底クラス
/// </summary>
class BaseCharacter {
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

};