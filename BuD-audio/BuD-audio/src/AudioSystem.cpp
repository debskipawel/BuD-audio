#include "AudioSystem.h"
#include "AudioGallery.h"

#include <rtaudio-5.2.0/RtAudio.h>

#include <memory>

static int rt_callback(void* output_buffer, void* input_buffer, uint32_t num_bufferframes, double stream_time, RtAudioStreamStatus status, void* user_data)
{
	constexpr int BUFFER_SIZE = 512;

	if (status) std::cerr << "[rtaudio] buffer over or underflow" << std::endl;

	// Playback
	if (!memcpy_s(output_buffer, BUFFER_SIZE * sizeof(float), (float*)user_data + num_bufferframes * BUFFER_SIZE * sizeof(float), BUFFER_SIZE * sizeof(float)))
	{
		memset(output_buffer, 0, BUFFER_SIZE * sizeof(float));
	}

	return 0;
}


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
	
	std::shared_ptr<SoundEffect> AudioSystem::Load(std::filesystem::path filepath)
	{
		return AudioGallery::Load(filepath);
	}
	
	void AudioSystem::Play(std::shared_ptr<SoundEffect> sound)
	{
		auto rtAudio = CastRTAudio();

		if (!rtAudio)
		{
			return;
		}

		unsigned int sizeInFrames = ((int)sound->m_Buffer.size()) / (BUFFER_SIZE);

		if (s_SampleRate != sound->m_SampleRate)
		{
			s_SampleRate = sound->m_SampleRate;

			RtAudio::StreamParameters outputParams;
			outputParams.deviceId = s_ActiveDevice.Id();
			outputParams.nChannels = s_ActiveDevice.NumChannels();
			outputParams.firstChannel = 0;

			if (rtAudio->isStreamOpen())
			{
				rtAudio->closeStream();
			}
			
			rtAudio->openStream(&outputParams, nullptr, RTAUDIO_FLOAT32, sound->m_SampleRate, &sizeInFrames, &rt_callback, s_Buffer.data());
		}

		errno_t res = 0;

		// should be done on a new thread maybe?
		for (int i = 0; i < sizeInFrames && res != 0; ++i)
		{
			res = memcpy_s(s_Buffer.data(), BUFFER_SIZE, sound->m_Buffer.data() + i * BUFFER_SIZE, BUFFER_SIZE);
		}
	}
}
