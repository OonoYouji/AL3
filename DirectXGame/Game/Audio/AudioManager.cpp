#include <AudioManager.h>

AudioManager* AudioManager::sInstance_ = nullptr;

void AudioManager::Load(const std::string& key, const std::string& filePath) {
	uint32_t handle = sInstance_->audio_->LoadWave(filePath);
	sInstance_->soundDatas_[key].handle = handle;
}

uint32_t AudioManager::PlayAudio(const std::string& key, float volume, bool isLoop) {
	return sInstance_->audio_->PlayWave(
		sInstance_->soundDatas_.at(key).handle,	/// 再生する音のハンドル
		isLoop,									/// ループフラグ
		volume * sInstance_->masterVolume_		/// 再生する音の大きさ
	);
}

void AudioManager::StopAudio(uint32_t voiceHandle) {
	sInstance_->audio_->StopWave(voiceHandle);
}

void AudioManager::PauseAudio(uint32_t voiceHandle) {
	sInstance_->audio_->PauseWave(voiceHandle);
}

void AudioManager::StopAudioAll(const std::string& key) {
	for(auto& voiceHandle : sInstance_->soundDatas_.at(key).voiceHandles_) {
		sInstance_->audio_->StopWave(voiceHandle);
	}
}



void AudioManager::Initialize() {
	audio_ = Audio::GetInstance();
}

void AudioManager::Finalize() {
	delete sInstance_;
}
