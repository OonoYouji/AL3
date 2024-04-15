#include "TimedCall.h"


TimedCall::TimedCall(std::function<void(void)> func, uint32_t time) {
	func_ = func;
	time_ = time;
	isFinished_ = false;
}

TimedCall::~TimedCall() {}


void TimedCall::Update() {
	///- 完了済みならreturn
	if(isFinished_) { return; }

	time_--;
	if(time_ <= 0) {
		isFinished_ = true;
		///- 関数呼び出し
		func_();
	}

}
