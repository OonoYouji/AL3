#pragma once

#include <cmath>
#include <functional>

class TimedCall {
public:

	TimedCall(std::function<void(void)> func, uint32_t time);
	~TimedCall();

	void Update();
	
	bool IsFinished() const { return isFinished_; };

private: ///- メンバ変数

	std::function<void(void)> func_;
	bool isFinished_;
	uint32_t time_;

};