#pragma once

#include <queue>
#include <vector>

namespace BuD::Audio
{
	namespace Internal
	{
		struct Frame
		{
			float* FramePtr;
			size_t Size;
		};

		class SoundBuffer
		{
		public:
			SoundBuffer() = default;
			~SoundBuffer() = default;

			size_t GetSampleRate() const { return m_CurrentSampleRate; }

			Frame ReadFrame(size_t frameSize);
			void Write(float* inputBuffer, size_t sampleCount, size_t sampleSize);

		protected:
			std::vector<float> m_Buffer;

			size_t m_ReadEnd, m_WriteEnd;
			size_t m_CurrentSampleRate;

			std::queue<size_t> m_SampleSizeChangeIndices;
			std::queue<size_t> m_SampleRates;
		};
	}
}
