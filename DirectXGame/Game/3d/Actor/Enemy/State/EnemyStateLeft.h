#pragma once

#include <BaseEnemyState.h>

#include <Vector3.h>


namespace EnemyState {

	class Left final : public BaseState {
	public:

		Left() {}
		~Left() {}

		void Update(Enemy* enemy) override;

	private:

		Vec3 move_ = { -1, 0, 0 };
		float speed_ = 5.0f;
	};

}