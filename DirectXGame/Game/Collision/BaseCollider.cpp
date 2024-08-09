#include "BaseCollider.h"

#include <BaseGameObject.h>


void BaseCollider::Initialize(BaseGameObject* gameObject) {
	gameObject_ = gameObject;
}
