#include "SoundBuffer.h"

namespace BuD::Audio::Internal
{
    Frame SoundBuffer::ReadFrame(size_t frameSize)
    {
        if (!m_SampleSizeChangeIndices.empty() && m_ReadEnd >= m_SampleSizeChangeIndices.front())
        {
            m_CurrentSampleRate = m_SampleRates.front();

            m_SampleSizeChangeIndices.pop();
            m_SampleRates.pop();
        }

        if (m_WriteEnd - m_ReadEnd <= 0)
        {
            m_WriteEnd = m_ReadEnd = 0;
            return { nullptr, 0 };
        }

        auto ptr = &m_Buffer[m_ReadEnd];
        auto size = std::min(m_WriteEnd - m_ReadEnd, frameSize);

        m_ReadEnd += frameSize;

        return { ptr, size };
    }
    
    void SoundBuffer::Write(float* inputBuffer, size_t sampleCount, size_t sampleRate)
    {
        m_SampleSizeChangeIndices.push(m_WriteEnd);
        m_SampleRates.push(sampleRate);

        auto newWriteEnd = m_WriteEnd + sampleCount;

        if (newWriteEnd >= m_Buffer.size())
        {
            m_Buffer.resize(newWriteEnd * 2);
        }

        void* writePtr = &m_Buffer[m_WriteEnd];
        memcpy(writePtr, inputBuffer, sampleCount * sizeof(float));

        m_WriteEnd = newWriteEnd;
    }
}
