#pragma once

class BaseGameObject;

class BaseCollider {
public:

	virtual ~BaseCollider() = default;

	void Initialize(BaseGameObject* gameObject);

	/// <summary>
	/// 衝突した瞬間呼び出される
	/// </summary>
	/// <param name="collider">衝突相手</param>
	virtual void OnCollisionEnter([[maybe_unused]] BaseCollider* collider) {};

	/// <summary>
	/// 衝突しているとき
	/// </summary>
	/// <param name="collider">衝突相手</param>
	virtual void OnCollisionStay([[maybe_unused]] BaseCollider* collider) {};

	/// <summary>
	/// 離れたとき
	/// </summary>
	/// <param name="collider">衝突していた相手</param>
	virtual void OnCollisionExit([[maybe_unused]] BaseCollider* collider) {};

public:

	BaseGameObject* gameObject_ = nullptr;

};