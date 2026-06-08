#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include "TypeOfSprite.hpp"


class Fireball
{
public:	
	Fireball(int plDir, sprite &s)
		: fb(s.Fireball)
	{
		dir = plDir;
	}
	void moveFireball(sprite& s, std::vector<std::vector<sf::Sprite>> Sprites, sf::View cam);
	sf::Sprite fb;
	int dir = -1;
	int ydir = 1;
	bool Kill = false;
	~Fireball();
	sf::FloatRect getGlobalBounds() {
		return fb.getGlobalBounds();
	}
private:
	int MaxHeight = 0;
	void offScreen(sf::View cam);
	bool fireballInView(sf::View cam);
};

