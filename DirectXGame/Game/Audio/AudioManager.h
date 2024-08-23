#pragma once

#include <unordered_map>
#include <memory>
#include <list>
#include <string>
#include <cmath>

#include <Audio.h>

/// ===================================================
/// 効果音、BGMの管理クラス
/// ===================================================
class AudioManager final {
	AudioManager() {}
	~AudioManager() {}
public:

	/// ============================================
	/// public : static methods
	/// ============================================

	static inline AudioManager* GetInstance() {
		if(!sInstance_) {
			sInstance_ = new AudioManager();
		}
		return sInstance_;
	}


	static void Load(const std::string& filePath);

public:

	/// ============================================
	/// public : methods
	/// ============================================

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();



private:

	/// ============================================
	/// private : static objects
	/// ============================================
	static AudioManager* sInstance_;

private:

	/// ============================================
	/// private : objects
	/// ============================================

	Audio* audio_ = nullptr;

	std::unordered_map<std::string, uint32_t> soundDataHandles_;

private:
	/// ============================================
	/// copy constructer delete
	/// ============================================
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator = (const AudioManager&) = delete;
	AudioManager& operator = (AudioManager&&) = delete;
};