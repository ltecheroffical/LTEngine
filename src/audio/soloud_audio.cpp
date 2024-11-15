#include <LTEngine/audio/soloud_audio.hpp>


using namespace LTEngine;
using namespace LTEngine::Audio;


SoLoudAudio::SoLoudAudio() {
	m_soloud.init();
}


u32 SoLoudAudio::loadAudio(const u8 *data, u32 size) {
	u32 id = m_nextResourceId++;
	m_resources[id].loadMem(data, size, true);
	return id;
}

u32 SoLoudAudio::loadStreamedAudio(const u8 *data, u32 size) {
	u32 id = m_nextResourceId++;
	m_streamedResources[id].loadMem(data, size, true);
	return id;
}

void SoLoudAudio::unloadAudio(u32 id) {
	if (m_resources.contains(id)) {
		m_resources.erase(id);
	} else if (m_streamedResources.contains(id)) {
		m_streamedResources.erase(id);
	}
}


void SoLoudAudio::setListenerPosition(Math::Vec2 position) {
	m_soloud.set3dListenerPosition(position.x, position.y, 0.f);
}


void SoLoudAudio::playAudio(u32 id, f32 volume, bool loop) {
	if (m_resources.contains(id)) {
		m_resources[id].setLooping(loop);
		m_soloud.play(m_resources[id], volume);
	} else if (m_streamedResources.contains(id)) {
		m_streamedResources[id].setLooping(loop);
		m_soloud.play(m_streamedResources[id], volume, loop);
	}
}

void SoLoudAudio::playAudioAt(u32 id, Math::Vec2 position, f32 volume, bool loop) {
	if (m_resources.contains(id)) {
		m_resources[id].setLooping(loop);
		m_soloud.play3d(m_resources[id], position.x, position.y, 0.f, 0.f, 0.f, volume);
	} else if (m_streamedResources.contains(id)) {
		m_streamedResources[id].setLooping(loop);
		m_soloud.play3d(m_streamedResources[id], position.x, position.y, 0.f, 0.f, 0.f, volume);
	}
}
