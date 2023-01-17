#pragma once

#include "AudioDevice.h"
#include "SoundEffect.h"

#include <filesystem>
#include <vector>

namespace BuD
{
	namespace Audio
	{
		class AudioSystem
		{
		public:
			static std::vector<AudioDevice> AllAudioDevices();
			static AudioDevice DefaultAudioDevice();
			
			static void SetActiveDevice(const AudioDevice& device);

			static void Clear();

			static std::shared_ptr<SoundEffect> Load(std::filesystem::path filepath);
			static void Play(std::shared_ptr<SoundEffect> sound);

		private:
			AudioSystem() = delete;

			inline static const int BUFFER_SIZE = 512;

			inline static AudioDevice s_ActiveDevice = AudioDevice::INVALID;
			
			inline static void* s_Audio = nullptr;
			inline static std::vector<uint8_t> s_Buffer = std::vector<uint8_t>(BUFFER_SIZE);
			inline static uint32_t s_SampleRate = -1;
		};
	}
}
