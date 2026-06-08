#pragma once
#include <SFML/Audio.hpp>

class Audios {
public:
	sf::Music Overworld;
	sf::Music Underground;
	
	sf::Music brickBreak;
	sf::Music coin;
	sf::Music death;
	sf::Music fireball;
	sf::Music item;
	sf::Music jump;
	sf::Music powerup;
	sf::Music powerdown;

	Audios() {
		Overworld.openFromFile("Music\\Overworld.mp3");
		Underground.openFromFile("Music\\Underground.mp3");


		brickBreak.openFromFile("SoundEffects\\brickBreak.wav");
		coin.openFromFile("SoundEffects\\coin.wav");
		death.openFromFile("SoundEffects\\death.wav");
		fireball.openFromFile("SoundEffects\\fireball.wav");
		item.openFromFile("SoundEffects\\item.wav");
		jump.openFromFile("SoundEffects\\jump.wav");
		powerup.openFromFile("SoundEffects\\powerup.wav");
		powerdown.openFromFile("SoundEffects\\pipepowerdown.wav");
	}
};