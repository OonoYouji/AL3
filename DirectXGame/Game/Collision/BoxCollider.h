#pragma once

#include <BaseCollider.h>



class BoxCollider : public BaseCollider {
public:

	BoxCollider() {}
	~BoxCollider() {}

	void Initialize();


	/// <summary>
	/// 衝突した瞬間呼び出される
	/// </summary>
	/// <param name="collider">衝突相手</param>
	virtual void OnCollisionEnter(BaseCollider* collider) {};

	/// <summary>
	/// 衝突しているとき
	/// </summary>
	/// <param name="collider">衝突相手</param>
	virtual void OnCollisionStay(BaseCollider* collider) {};

	/// <summary>
	/// 離れたとき
	/// </summary>
	/// <param name="collider">衝突していた相手</param>
	virtual void OnCollisionExit(BaseCollider* collider) {};

};