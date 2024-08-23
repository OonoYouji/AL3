#include <AudioManager.h>

AudioManager* AudioManager::sInstance_ = nullptr;

void AudioManager::Load(const std::string& filePath) {
	sInstance_->soundDataHandles_[filePath] = sInstance_->audio_->LoadWave(filePath);
}



void AudioManager::Initialize() {
	audio_ = Audio::GetInstance();
}

void AudioManager::Finalize() {
	delete sInstance_;
}
