#pragma once

class Enemy;

namespace EnemyState {

	class BaseState {
	public:

		virtual ~BaseState() = default;

		virtual void Update(Enemy* enemy) = 0;

	};

}