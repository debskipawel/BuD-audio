#include <AudioSystem.h>

int main()
{
	auto device = BuD::Audio::AudioSystem::DefaultAudioDevice();
	auto devices = BuD::Audio::AudioSystem::AllAudioDevices();

	std::filesystem::path homendaPath = "D:\\Prywatne\\Desktop\\homenda_powiadomienie.mp3";

	auto sound = BuD::Audio::AudioSystem::Load(homendaPath);

	return 0;
}