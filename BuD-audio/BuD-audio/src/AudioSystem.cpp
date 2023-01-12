#include "AudioSystem.h"

#include <rtaudio-5.2.0/RtAudio.h>

#include <memory>

namespace BuD::Audio
{
	#define CastRTAudio() reinterpret_cast<RtAudio*>(s_Audio)

	std::vector<AudioDevice> AudioSystem::AllAudioDevices()
	{
		std::unique_ptr<RtAudio> rtAudio = std::unique_ptr<RtAudio>(new RtAudio);

		auto devicesCount = rtAudio->getDeviceCount();
		auto devices = std::vector<AudioDevice>(devicesCount);

		for (int i = 0; i < devicesCount; ++i)
		{
			auto deviceInfo = rtAudio->getDeviceInfo(i);
			auto device = AudioDevice(deviceInfo.name, i, deviceInfo.outputChannels);
			
			devices[i] = device;
		}

		return devices;
	}
	
	AudioDevice AudioSystem::DefaultAudioDevice()
	{
		std::unique_ptr<RtAudio> rtAudio = std::unique_ptr<RtAudio>(new RtAudio);

		auto defaultDeviceId = rtAudio->getDefaultOutputDevice();
		auto deviceInfo = rtAudio->getDeviceInfo(defaultDeviceId);

		auto device = AudioDevice(deviceInfo.name, defaultDeviceId, deviceInfo.outputChannels);

		return device;
	}
	
	void AudioSystem::SetActiveDevice(const AudioDevice& device)
	{
		if (!s_Audio)
		{
			s_Audio = new RtAudio;
		}

		auto audio = CastRTAudio();
		
		if (audio->isStreamOpen())
		{
			audio->closeStream();
		}

		s_ActiveDevice = device;
	}
	
	void AudioSystem::Clear()
	{
		if (!s_Audio)
		{
			return;
		}

		auto audio = CastRTAudio();
		delete audio;

		s_Audio = nullptr;
		s_ActiveDevice = AudioDevice::INVALID;
	}
}
