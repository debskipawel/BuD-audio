#include <AudioSystem.h>

int main()
{
	auto device = BuD::Audio::AudioSystem::DefaultAudioDevice();
	auto devices = BuD::Audio::AudioSystem::AllAudioDevices();

	return 0;
}