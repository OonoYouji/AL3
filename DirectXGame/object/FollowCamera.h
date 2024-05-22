#pragma once 

#include <WorldTransform.h>
#include <ViewProjection.h>


/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:

	FollowCamera();
	~FollowCamera();

	void Initialize();
	void Update();

private:

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;


};