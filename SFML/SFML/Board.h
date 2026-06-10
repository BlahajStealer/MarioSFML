#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "TypeOfSprite.hpp"
#include "Enemy.h"
class Board
{
public:
	void reset(std::string path, std::vector<Enemy>& Goombas, int LevelType, int Level);

	void startBoard(sf::RenderWindow &window, int levelType, sf::Sprite Powerup, sf::Sprite shape, bool goingDown, int Level);
	Board(std::string path, std::vector<Enemy>& Goombas, int LevelType);
	std::vector<std::vector<sf::Sprite>>& getSprites();
	sprite s = sprite();
	void fillSubBoard(int levelType);
	void BuildSubBoard(int currentSub);
	void fillLevel(std::vector<Enemy>& enemies, int LevelType);
	void BuildBoard(int CurrentLevel); //Builds Level in chars

private:
	std::string Levels[4];
	std::string subLevels[4];
	char board[16][211];
	char subBoard[16][18];
	std::vector<std::vector<sf::Sprite>> sprites;
	void InterpretBoard(sf::RenderWindow &window, int levelType, sf::Sprite Powerup, sf::Sprite shape, bool goingDown, int Level);
};

