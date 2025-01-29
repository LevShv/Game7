#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

class track
{
public:
	std::string Main = "Main.wav";

	void play(std::string song);
	void stop();
	~track();

private:
	sf::Music* loaded_track;
};

