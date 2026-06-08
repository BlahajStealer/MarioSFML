#pragma once
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
class sprite {
public:
	const sf::Texture Brick;
	const sf::Texture BrickUG;
	const sf::Texture BreakableBrick;
	const sf::Texture BreakableBrickUG;
	const sf::Texture Coin;
	const sf::Texture FlagL;
	const sf::Texture Flagpole;
	const sf::Texture FlagR;
	const sf::Texture Goomba;
	const sf::Texture GoombaUG;
	const sf::Texture LuckyBlock;
	const sf::Texture OtherBrick;
	const sf::Texture OtherBrickUG;
	const sf::Texture PipeBL;
	const sf::Texture PipeBR;
	const sf::Texture PipeTL;
	const sf::Texture PipeTLD;
	const sf::Texture PipeTR;
	const sf::Texture PipeTRD;
	const sf::Texture PipeTLSWD;
	const sf::Texture PipeTRSW;
	const sf::Texture PipeBLSWD;
	const sf::Texture PipeBRSW;
	const sf::Texture Sky;
	const sf::Texture SkyUG;
	const sf::Texture TopFlag;
	const sf::Texture CoinedLB;
	const sf::Texture CoinedLBUG;

	const sf::Texture LuckyBlockPU;
	const sf::Texture Mushroom;
	const sf::Texture Fireflower;
	const sf::Texture Star;
	const sf::Texture Fireball;


	const sf::Texture SmallMario;
	const sf::Texture SmallMarioDied;
	const sf::Texture SmallMarioFlag1;
	const sf::Texture SmallMarioFlag2;
	const sf::Texture SmallMarioJump;
	const sf::Texture SmallMarioStop;
	const sf::Texture SmallMarioWalk1;
	const sf::Texture SmallMarioWalk2;
	const sf::Texture SmallMarioWalk3;


	const sf::Texture Mario;
	const sf::Texture MarioBottomFlag;
	const sf::Texture MarioCrouched;
	const sf::Texture MarioGrabPole;
	const sf::Texture MarioJump;
	const sf::Texture MarioWalk1;
	const sf::Texture MarioWalk2;
	const sf::Texture MarioWalk3;
	const sf::Texture MarioStopping;


	const sf::Texture Firemario;
	const sf::Texture FiremarioBottomFlag;
	const sf::Texture FiremarioCrouched;
	const sf::Texture FiremarioGrabPole;
	const sf::Texture FiremarioJump;
	const sf::Texture FiremarioWalk1;
	const sf::Texture FiremarioWalk2;
	const sf::Texture FiremarioWalk3;
	const sf::Texture FiremarioStopping;


	const sf::Texture Bush;
	const sf::Texture Cloud;
	const sf::Texture Hill;
	const sf::Texture SmallHill;

	const sf::Texture Mainmenu;
	const sf::Texture MushroomSelector;

	sprite()
		: BrickUG(std::filesystem::path("Tiles/Underground/Brick.png"))
		, Brick(std::filesystem::path("Tiles/Brick.png"))
		, BreakableBrickUG(std::filesystem::path("Tiles/Underground/BreakableBrick.png"))
		, BreakableBrick(std::filesystem::path("Tiles/BreakableBrick.png"))
		, Coin(std::filesystem::path("Tiles/Coin.png"))
		, FlagL(std::filesystem::path("Tiles/FlagL.png"))
		, Flagpole(std::filesystem::path("Tiles/Flagpole.png"))
		, FlagR(std::filesystem::path("Tiles/FlagR.png"))
		, Goomba(std::filesystem::path("Tiles/Goomba.png"))
		, GoombaUG(std::filesystem::path("Tiles/GoombaUG.png"))
		, LuckyBlock(std::filesystem::path("Tiles/LuckyBlock.png"))
		, OtherBrick(std::filesystem::path("Tiles/OtherBrick.png"))
		, OtherBrickUG(std::filesystem::path("Tiles/OtherBrickUG.png"))
		, PipeBL(std::filesystem::path("Tiles/PipeBL.png"))
		, PipeBR(std::filesystem::path("Tiles/PipeBR.png"))
		, PipeTL(std::filesystem::path("Tiles/PipeTL.png"))
		, PipeTLD(std::filesystem::path("Tiles/PipeTLD.png"))
		, PipeTLSWD(std::filesystem::path("Tiles/PipeTLSWD.png"))
		, PipeTRSW(std::filesystem::path("Tiles/PipeSWTR.png"))
		, PipeBLSWD(std::filesystem::path("Tiles/PipeBLSWD.png"))
		, PipeBRSW(std::filesystem::path("Tiles/PipeSWBR.png"))
		, PipeTR(std::filesystem::path("Tiles/PipeTR.png"))
		, PipeTRD(std::filesystem::path("Tiles/PipeTRD.png"))
		, Sky(std::filesystem::path("Tiles/Sky.png"))
		, SkyUG(std::filesystem::path("Tiles/Underground/Sky.png"))
		, TopFlag(std::filesystem::path("Tiles/TopFlag.png"))
		, CoinedLB(std::filesystem::path("Tiles/CoinedLB.png"))
		, CoinedLBUG(std::filesystem::path("Tiles/CoinedLBUG.png"))
		, LuckyBlockPU(std::filesystem::path("Tiles/LuckyBlockPU.png"))


		, Mushroom(std::filesystem::path("Tiles/Mushroom.png"))
		, Fireflower(std::filesystem::path("Tiles/Fireflower.png"))
		, Star(std::filesystem::path("Tiles/Star.png"))
		, Fireball(std::filesystem::path("Tiles/Fireball.png"))


		, SmallMario(std::filesystem::path("Tiles/MarioAnims/Small/SmallMario.png"))
		, SmallMarioDied(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioDied.png"))
		, SmallMarioFlag1(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioFlag1.png"))
		, SmallMarioFlag2(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioFlag2.png"))
		, SmallMarioJump(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioJump.png"))
		, SmallMarioStop(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioStop.png"))
		, SmallMarioWalk1(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioWalk1.png"))
		, SmallMarioWalk2(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioWalk2.png"))
		, SmallMarioWalk3(std::filesystem::path("Tiles/MarioAnims/Small/SmallMarioWalk3.png"))


		, Mario(std::filesystem::path("Tiles/MarioAnims/Big/Mario.png"))
		, MarioBottomFlag(std::filesystem::path("Tiles/MarioAnims/Big/MarioBottomFlag.png"))
		, MarioCrouched(std::filesystem::path("Tiles/MarioAnims/Big/MarioCrouched.png"))
		, MarioGrabPole(std::filesystem::path("Tiles/MarioAnims/Big/MarioGrabPole.png"))
		, MarioJump(std::filesystem::path("Tiles/MarioAnims/Big/MarioJump.png"))
		, MarioWalk1(std::filesystem::path("Tiles/MarioAnims/Big/MarioWalk1.png"))
		, MarioWalk2(std::filesystem::path("Tiles/MarioAnims/Big/MarioWalk2.png"))
		, MarioWalk3(std::filesystem::path("Tiles/MarioAnims/Big/MarioWalk3.png"))
		, MarioStopping(std::filesystem::path("Tiles/MarioAnims/Big/MarioStopping.png"))	

		, Firemario(std::filesystem::path("Tiles/MarioAnims/Fireflower/Mario.png"))
		, FiremarioBottomFlag(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioBottomFlag.png"))
		, FiremarioCrouched(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioCrouched.png"))
		, FiremarioGrabPole(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioGrabPole.png"))
		, FiremarioJump(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioJump.png"))
		, FiremarioWalk1(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioWalk1.png"))
		, FiremarioWalk2(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioWalk2.png"))
		, FiremarioWalk3(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioWalk3.png"))
		, FiremarioStopping(std::filesystem::path("Tiles/MarioAnims/Fireflower/MarioStopping.png"))
		
		, Bush(std::filesystem::path("Tiles/BackgroundElements/Bush.png"))
		, Cloud(std::filesystem::path("Tiles/BackgroundElements/Cloud.png"))
		, Hill(std::filesystem::path("Tiles/BackgroundElements/Hill.png"))
		, SmallHill(std::filesystem::path("Tiles/BackgroundElements/SmallHill.png"))

		, Mainmenu(std::filesystem::path("Tiles/MainMenu.png"))
		, MushroomSelector(std::filesystem::path("Tiles/MushroomSelect.png"))
	{


	}
};