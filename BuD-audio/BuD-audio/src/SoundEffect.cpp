#include "SoundEffect.h"

namespace BuD::Audio
{
	SoundEffect::SoundEffect(std::vector<float> buffer, uint32_t sampleRate, uint32_t channelCount, float lengthSeconds)
		: m_BitRate(0), m_Buffer(buffer), m_SampleRate(sampleRate), m_ChannelCount(channelCount), m_LengthInSeconds(lengthSeconds)
	{
	}
}
