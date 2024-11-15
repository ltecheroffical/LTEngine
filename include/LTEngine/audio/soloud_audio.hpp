#pragma once

#include <unordered_map>

#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>

#include <LTEngine/audio/audio.hpp>


namespace LTEngine::Audio {
	class SoLoudAudio : public Audio {
	public:
		SoLoudAudio();
		~SoLoudAudio();

		u32 loadAudio(const u8 *data, u32 size) override;
		u32 loadStreamedAudio(const u8 *data, u32 size);
		void unloadAudio(u32 id) override;

		void setListenerPosition(Math::Vec2 position) override;

		void playAudio(u32 id, f32 volume = -1.f, bool loop = false) override;
		void playAudioAt(u32 id, Math::Vec2 position, f32 volume = 1.f, bool loop = false) override;

	private:
		SoLoud::Soloud m_soloud;

		std::unordered_map<u32, SoLoud::Wav> m_resources;
		std::unordered_map<u32, SoLoud::WavStream> m_streamedResources;

		u32 m_nextResourceId;
	};
} // namespace LTEngine::Audio
