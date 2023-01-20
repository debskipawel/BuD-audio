#include <AudioSystem.h>

#include <iostream>

int main()
{
	auto device = BuD::Audio::AudioSystem::DefaultAudioDevice();
	auto devices = BuD::Audio::AudioSystem::AllAudioDevices();
	
	BuD::Audio::AudioSystem::SetActiveDevice(devices[0]);

	std::filesystem::path radioheadPath = "..\\radiohead.wv";

	std::cout << "Loading file \"" + radioheadPath.filename().string() << "\"" << std::endl;
	auto sound = BuD::Audio::AudioSystem::Load(radioheadPath);

	if (sound)
	{
		std::cout << "File loaded successfully. Starting playback." << std::endl << std::endl;
		BuD::Audio::AudioSystem::Play(sound);

		char input;
		std::cout << "Playback in progress. Press ENTER to exit. ";
		std::cin.get(input);
	}

	BuD::Audio::AudioSystem::Clear();

	return 0;
}
