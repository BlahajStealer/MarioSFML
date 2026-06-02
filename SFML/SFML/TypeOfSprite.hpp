#pragma once
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
class sprite {
public:
	const sf::Texture Brick;
	const sf::Texture BreakableBrick;
	const sf::Texture Coin;
	const sf::Texture FlagL;
	const sf::Texture Flagpole;
	const sf::Texture FlagR;
	const sf::Texture Goomba;
	const sf::Texture LuckyBlock;
	const sf::Texture OtherBrick;
	const sf::Texture PipeBL;
	const sf::Texture PipeBR;
	const sf::Texture PipeTL;
	const sf::Texture PipeTR;
	const sf::Texture Sky;
	const sf::Texture TopFlag;
	sprite()
		: Brick(std::filesystem::path("Tiles/Brick.png"))
		, BreakableBrick(std::filesystem::path("Tiles/BreakableBrick.png"))
		, Coin(std::filesystem::path("Tiles/Coin.png"))
		, FlagL(std::filesystem::path("Tiles/FlagL.png"))
		, Flagpole(std::filesystem::path("Tiles/Flagpole.png"))
		, FlagR(std::filesystem::path("Tiles/FlagR.png"))
		, Goomba(std::filesystem::path("Tiles/Goomba.png"))
		, LuckyBlock(std::filesystem::path("Tiles/LuckyBlock.png"))
		, OtherBrick(std::filesystem::path("Tiles/OtherBrick.png"))
		, PipeBL(std::filesystem::path("Tiles/PipeBL.png"))
		, PipeBR(std::filesystem::path("Tiles/PipeBR.png"))
		, PipeTL(std::filesystem::path("Tiles/PipeTL.png"))
		, PipeTR(std::filesystem::path("Tiles/PipeTR.png"))
		, Sky(std::filesystem::path("Tiles/Sky.png"))
		, TopFlag(std::filesystem::path("Tiles/TopFlag.png"))
	{


	}
};