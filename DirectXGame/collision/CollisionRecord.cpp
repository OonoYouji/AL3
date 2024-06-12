#include "CollisionRecord.h"

#include <algorithm>


CollisionRecord::CollisionRecord() {}

CollisionRecord::~CollisionRecord() {}

void CollisionRecord::AddLog(uint32_t log) {
	logs_.push_back(log);
}

bool CollisionRecord::CheckLog(uint32_t number) {
	return (std::find(logs_.begin(), logs_.end(), number) != logs_.end());
}

void CollisionRecord::Clear() {
	logs_.clear();
}
