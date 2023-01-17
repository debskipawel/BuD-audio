#include <AudioSystem.h>

int main()
{
	auto device = BuD::Audio::AudioSystem::DefaultAudioDevice();
	auto devices = BuD::Audio::AudioSystem::AllAudioDevices();
	
	BuD::Audio::AudioSystem::SetActiveDevice(devices[1]);

	std::filesystem::path homendaPath = "D:\\Prywatne\\Desktop\\homenda_powiadomienie.mp3";

	auto sound = BuD::Audio::AudioSystem::Load(homendaPath);
	BuD::Audio::AudioSystem::Play(sound);

	BuD::Audio::AudioSystem::Clear();

	return 0;
}