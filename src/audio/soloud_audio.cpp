#include <vector>

#include <LTEngine/audio/soloud_audio.hpp>


using namespace LTEngine;
using namespace LTEngine::Audio;


SoLoudAudio::SoLoudAudio() {
	m_soloud.init();
}


u32 SoLoudAudio::loadAudio(OS::File *file) {
	u32 id = m_nextResourceId++;
	std::vector<u8> data(file->size());
	file->readAll(data.data());
	m_resources[id].loadMem(data.data(), data.size(), true);
	return id;
}

u32 SoLoudAudio::loadStreamedAudio(const char *path) {
	u32 id = m_nextResourceId++;
	m_streamedResources[id].load(path);
	return id;
}

void SoLoudAudio::unloadAudio(u32 id) {
	if (m_streamedResources.contains(id)) {
		m_streamedResources.erase(id);
		return;
	}
	m_resources.erase(id);
}


void SoLoudAudio::setAudioLoop(u32 id, bool loop) {
	if (m_streamedResources.contains(id)) {
		m_streamedResources[id].setLooping(loop);
		return;
	}
	m_resources.at(id).setLooping(loop);
}

void SoLoudAudio::setAudioVolume(u32 id, f32 volume) {
	if (m_streamedResources.contains(id)) {
		m_streamedResources[id].setVolume(volume);
		return;
	}
	m_resources.at(id).setVolume(volume);
}


void SoLoudAudio::setListenerPosition(Math::Vec2 position) {
	m_soloud.set3dListenerPosition(position.x, position.y, 0.f);
}


void SoLoudAudio::playAudio(u32 id, f32 volume) {
	if (m_streamedResources.contains(id)) {
		m_soloud.play(m_streamedResources[id], volume);
		return;
	}
	m_soloud.play(m_resources.at(id), volume);
}

void SoLoudAudio::playAudioAt(u32 id, Math::Vec2 position, f32 volume) {
	if (m_streamedResources.contains(id)) {
		m_soloud.play3d(m_streamedResources[id], position.x, position.y, 0.f, 0.f, 0.f, volume);
		return;
	}
	m_soloud.play3d(m_resources.at(id), position.x, position.y, 0.f, 0.f, 0.f, volume);
}
