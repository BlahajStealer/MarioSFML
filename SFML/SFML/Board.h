#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "TypeOfSprite.hpp"
class Board
{
public:
	void startBoard(sf::RenderWindow &window);
	Board(std::string path);
	std::vector<std::vector<sf::Sprite>> getSprites();
	sprite s = sprite();

private:
	std::string Levels[1];
	char board[16][211];
	std::vector<std::vector<sf::Sprite>> sprites;
	void fillLevel();
	void BuildBoard(int CurrentLevel); //Builds Level in chars
	void InterpretBoard(sf::RenderWindow &window);
};

