#pragma once

#include <BaseEnemyState.h>
#include <Vector3.h>

namespace EnemyState {

	class Up final : public BaseState {
	public:

		void Update(Enemy* enemy) override;

	private:

		Vec3 move_ = { 0, 0, 1 };
		float speed_ = 5.0f;
		
	};

}