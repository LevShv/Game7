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
	sf::Music* loaded_track;
	~track();

private:
	
	

};

class sound {

public:

	sound();
	sf::Music* step;
	void play(sf::Music*);
	void stop();
	

};

