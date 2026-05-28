#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
class sprite {
	std::string srcDir = __FILE__;
	sf::Texture Brick;
	sf::Texture BreakableBrick;
	sf::Texture Coin;
	sf::Texture FlagL;
	sf::Texture Brick;
	sf::Texture Flagpole;
	sf::Texture FlagR;
	sf::Texture Goomba;
	sf::Texture LuckyBlock;
	sf::Texture OtherBrick;
	sf::Texture PipeBL;
	sf::Texture PipeBR;
	sf::Texture PipeTL;
	sf::Texture PipeTR;
	sf::Texture Sky;
	sf::Texture TopFlag;
	sprite() {
		std::string filePath = __FILE__;
		Brick.loadFromFile(filePath + "\\Tiles\\Brick.png");
		BreakableBrick.loadFromFile(filePath + "\\Tiles\\BreakableBrick.png");
		Coin.loadFromFile(filePath + "\\Tiles\\Coin.png");
		FlagL.loadFromFile(filePath + "\\Tiles\\FlagL.png");
		Flagpole.loadFromFile(filePath + "\\Tiles\\Flagpole.png");
		FlagR.loadFromFile(filePath + "\\Tiles\\FlagR.png");
		Goomba.loadFromFile(filePath + "\\Tiles\\Goomba.png");
		LuckyBlock.loadFromFile(filePath + "\\Tiles\\LuckyBlock.png");
		OtherBrick.loadFromFile(filePath + "\\Tiles\\OtherBrick.png");
		PipeBL.loadFromFile(filePath + "\\Tiles\\PipeBL.png");
		PipeBR.loadFromFile(filePath + "\\Tiles\\PipeBR.png");
		PipeTL.loadFromFile(filePath + "\\Tiles\\PipeTL.png");
		PipeTR.loadFromFile(filePath + "\\Tiles\\PipeTR.png");
		Sky.loadFromFile(filePath + "\\Tiles\\Sky.png");
		TopFlag.loadFromFile(filePath + "\\Tiles\\TopFlag.png");
	}
};