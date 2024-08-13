#pragma once

#include <BaseEnemyState.h>
#include <Vector3.h>

namespace EnemyState {

	class Chase final : public BaseState {
	public:

		Chase() {}
		~Chase() {}

		void Update(Enemy* enemy) override;

	private:

		Vec3 move_{};
		float speed_ = 4.0f;

	};

}