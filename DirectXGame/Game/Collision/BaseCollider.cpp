#include "BaseCollider.h"

#include <BaseGameObject.h>
#include <Model.h>

void BaseCollider::Initialize(BaseGameObject* gameObject, [[maybe_unused]]Model* model) {
	gameObject_ = gameObject;
}
