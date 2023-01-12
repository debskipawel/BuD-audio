#pragma once

#include "AudioDevice.h"

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

		private:
			AudioSystem() = delete;

			inline static AudioDevice s_ActiveDevice = AudioDevice::INVALID;
			inline static void* s_Audio = nullptr;
		};
	}
}
