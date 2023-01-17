#include <AudioSystem.h>

#include <iostream>

int main()
{
	auto device = BuD::Audio::AudioSystem::DefaultAudioDevice();
	auto devices = BuD::Audio::AudioSystem::AllAudioDevices();
	
	BuD::Audio::AudioSystem::SetActiveDevice(devices[1]);

	std::filesystem::path homendaPath = "D:\\Prywatne\\Desktop\\homenda_powiadomienie.mp3";
	std::filesystem::path radioheadPath = "..\\radiohead.mp3";

	auto sound = BuD::Audio::AudioSystem::Load(radioheadPath);
	BuD::Audio::AudioSystem::Play(sound);

	char input;
	std::cin.get(input);

	BuD::Audio::AudioSystem::Clear();

	return 0;
}
