#pragma once

class BaseGameObject;
class Model;

class BaseCollider {
public:

	virtual ~BaseCollider() = default;

	virtual void Initialize(BaseGameObject* gameObject, Model* model);

	/// <summary>
	/// 当たり判定の可視化
	/// </summary>
	virtual void Draw() {}

public:

	BaseGameObject* gameObject_ = nullptr;

};