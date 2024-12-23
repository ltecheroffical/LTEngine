#ifndef _LTENGINE_AUDIO_HPP_
#define _LTENGINE_AUDIO_HPP_

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/os/file.hpp>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Audio {
	class Audio {
	public:
		virtual ~Audio() = default;

		virtual u32 loadAudio(OS::File *file) = 0;
		virtual void unloadAudio(u32 id) = 0;

		virtual void setAudioLoop(u32 id, bool loop) = 0;
		virtual void setAudioVolume(u32 id, f32 volume) = 0;

		virtual void setListenerPosition(Math::Vec2 position) = 0;

		virtual void playAudio(u32 id, f32 volume = 1.f) = 0;
		virtual void playAudioAt(u32 id, Math::Vec2 position, f32 volume = 1.f) = 0;
	};
} // namespace LTEngine::Audio

#endif
