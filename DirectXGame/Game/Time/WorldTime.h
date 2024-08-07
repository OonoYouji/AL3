#pragma once

class WorldTime final {
	WorldTime() = default;
	~WorldTime() = default;
public:

	static WorldTime* GetInstance() {
		static WorldTime instance;
		return &instance;
	}

	/// <summary>
	/// Frame単位での時間 * 減衰度の時間を返す
	/// </summary>
	/// <returns></returns>
	static float FrameTime() {
		WorldTime* time = GetInstance();
		return time->attenuation_ * time->deltaTime_;
	}


	/// <summary>
	/// フレーム単位の時間を返す
	/// </summary>
	/// <returns></returns>
	static float GetDeltaTime() {
		return GetInstance()->deltaTime_;
	}

	static float GetAttenuation() {
		return GetInstance()->attenuation_;
	}

	/// <summary>
	/// 減衰度のセット
	/// </summary>
	/// <param name="attenuation"></param>
	static void SetAttenuation(float attenuation) {
		GetInstance()->attenuation_ = attenuation;
	}


	void ImGuiDebug();


private:

	float attenuation_ = 1.0f; // 減衰度

	float deltaTime_ = 1.0f / 60.0f;



};