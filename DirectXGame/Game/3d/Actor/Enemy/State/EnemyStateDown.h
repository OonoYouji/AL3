#pragma once

#include <BaseEnemyState.h>

#include <Vector3.h>

namespace EnemyState {

	class Down final : public BaseState {
	public:

		Down() {}
		~Down() {}

		void Update(Enemy* enemy) override;

	private:

		Vec3 move_ = { 0, 0, -1 };
		float speed_ = 4.0f;

	};

}