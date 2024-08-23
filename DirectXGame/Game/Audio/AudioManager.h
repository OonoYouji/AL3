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
private:

	/// ============================================
	/// private : sub class
	/// ============================================

	struct SoundData {
		uint32_t handle;
		std::list<uint32_t> voiceHandles_;
	};

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


	static void Load(const std::string& key, const std::string& filePath);

	/// <summary>
	/// 音の再生
	/// </summary>
	/// <param name="key">再生する音のkey</param>
	/// <param name="isLoop">ループすかどうかフラグ</param>
	/// <param name="volume">再生する音の音量</param>
	/// <returns>voiceHandle</returns>
	static uint32_t PlayAudio(const std::string& key, float volume = 1.0f, bool isLoop = false);


	/// <summary>
	/// 音の停止
	/// </summary>
	/// <param name="voiceHandle">止める音のvoiceHandle</param>
	static void StopAudio(uint32_t voiceHandle);


	/// <summary>
	/// 音の一時停止
	/// </summary>
	/// <param name="voiceHandle">止める音のvoiceHandle</param>
	static void PauseAudio(uint32_t voiceHandle);


	/// <summary>
	/// keyの音をすべて停止する
	/// </summary>
	/// <param name="key">止める音のkey</param>
	static void StopAudioAll(const std::string& key);


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

	std::unordered_map<std::string, SoundData> soundDatas_;

	float masterVolume_ = 0.5f;

private:
	/// ============================================
	/// copy constructer delete
	/// ============================================
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator = (const AudioManager&) = delete;
	AudioManager& operator = (AudioManager&&) = delete;
};