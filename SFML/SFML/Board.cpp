#include "Board.h"

void Board::reset(std::string path, std::vector<Enemy> &Goombas, int levelType, int Level) {
	sprites.clear();
	for (int i = 0; i < std::size(Levels); i++) {
		Levels[i] = "Levels/Level" + std::to_string(i + 1) + ".smb";
	}
	for (int i = 0; i < std::size(subLevels); i++) {
		subLevels[i] = "subLevels\\subLevel" + std::to_string(i + 1) + ".smb";
	}
	BuildSubBoard(Level - 1);

	BuildBoard(Level - 1);
	fillLevel(Goombas, levelType);
}
Board::Board(std::string path, std::vector<Enemy>& Goombas, int levelType) {
	for (int i = 0; i < std::size(Levels); i++) {
		Levels[i] = "Levels/Level" + std::to_string(i + 1) + ".smb";
	}
	for (int i = 0; i < std::size(subLevels); i++) {
		subLevels[i] = "subLevels\\subLevel" + std::to_string(i + 1) + ".smb";
	}
	BuildBoard(0);
	BuildSubBoard(0);

	fillLevel(Goombas, levelType);
}
std::vector<std::vector<sf::Sprite>>& Board::getSprites() {
	return sprites;
}
void Board::BuildBoard(int CurrentLevel) {
	std::string used;

	used = Levels[CurrentLevel];

	std::ifstream outFile(used);

	for (int i = 0; i < std::size(board); i++) {
		std::string line = "";

		std::getline(outFile, line);

		for (int f = 0; f < std::size(board[0]); f++) {

			board[i][f] = line[f];

		}

	}


}
void Board::BuildSubBoard(int currentSub) {
	std::string used;

	used = subLevels[currentSub];

	std::ifstream outFile(used);
	if (!outFile.is_open()) {
		std::cout << "ERROR: Could not open Sub level" << used << std::endl;
		system("PAUSE");
	}
	for (int i = 0; i < std::size(subBoard); i++) {
		std::string line = "";

		std::getline(outFile, line);

		for (int f = 0; f < std::size(subBoard[i]); f++) {

			subBoard[i][f] = (f < (int)line.size()) ? line[f] : '0'; 

		}

	}
}
void Board::fillLevel(std::vector<Enemy>& Goombas, int LevelType) {

	for (int h = 0; h < 16; h++) {
		std::vector<sf::Sprite> tempor;
		sprites.push_back(tempor);

		for (int d = 0; d < 211; d++) {
			sf::Sprite tempText = sf::Sprite(s.Sky);
			switch (board[h][d]) {
			case '0':
				if (LevelType == 0) {
					tempText.setTexture(s.Sky);

				}
				else if (LevelType == 1) {
					tempText.setTexture(s.SkyUG);

				}
				break;
			case '1':
				if (LevelType == 0) {
					tempText.setTexture(s.Brick);

				}
				else if (LevelType == 1) {
					tempText.setTexture(s.BrickUG);

				}
				break;
			case '2':
				tempText.setTexture(s.LuckyBlock);
				break;
			case '3':
				if (LevelType == 0) {
					tempText.setTexture(s.BreakableBrick);

				}
				else if (LevelType == 1) {
					tempText.setTexture(s.BreakableBrickUG);

				}
				break;
			case '4': {
				if (LevelType == 0) {
					tempText.setTexture(s.Sky);

				}
				else if (LevelType == 1) {
					tempText.setTexture(s.SkyUG);

				}
				Enemy tempGoomba(d, h, 0, s);
				Goombas.push_back(tempGoomba);
				break;

			}

			case '5':
				tempText.setTexture(s.PipeTL);
				break;
			case '6':
				tempText.setTexture(s.PipeTR);
				break;
			case '7':
				tempText.setTexture(s.PipeBL);
				break;
			case '8':
				tempText.setTexture(s.PipeBR);
				break;
			case '9':
				if (LevelType == 0) {
					tempText.setTexture(s.OtherBrick);

				}
				else if (LevelType == 1) {
					tempText.setTexture(s.OtherBrickUG);

				}
				break;
			case 'a':
				tempText.setTexture(s.Flagpole);
				break;
			case 'b':
				tempText.setTexture(s.TopFlag);
				break;
			case 'c':
				tempText.setTexture(s.FlagR);
				break;
			case 'd':
				tempText.setTexture(s.FlagL);
				break;
			case 'e': {
				tempText.setTexture(s.LuckyBlockPU);

				break;
			case 'f':
				tempText.setTexture(s.Coin);
				break;
			}
			case 'g':
				tempText.setTexture(s.PipeTLD);
				break;
			case 'h':
				tempText.setTexture(s.PipeTRD);
				break;

			default:
				tempText.setTexture(s.Sky);
				break;
			}
			tempText.setPosition(sf::Vector2f(d * 16, h * 16));
			sprites[h].push_back(tempText);
		}
		std::cout << std::endl;
	}
}
void Board::fillSubBoard() {
	for (int h = 0; h < 16; h++) {
		std::vector<sf::Sprite> tempor;
		sprites.push_back(tempor);

		for (int d = 0; d < 18; d++) {
			sf::Sprite tempText = sf::Sprite(s.Sky);
			switch (subBoard[h][d]) {
			case '0':

				tempText.setTexture(s.SkyUG);
				break;
			case '1':
				tempText.setTexture(s.BrickUG);
				break;
			case '2':
				tempText.setTexture(s.LuckyBlock);
				break;
			case '3':
				tempText.setTexture(s.BreakableBrickUG);
				break;

			case '5':
				tempText.setTexture(s.PipeTL);
				break;
			case '6':
				tempText.setTexture(s.PipeTR);
				break;
			case '7':
				tempText.setTexture(s.PipeBL);
				break;
			case '8':
				tempText.setTexture(s.PipeBR);
				break;
			case '9':
				tempText.setTexture(s.OtherBrick);
				break;
			case 'a':
				tempText.setTexture(s.Flagpole);
				break;
			case 'b':
				tempText.setTexture(s.TopFlag);
				break;
			case 'c':
				tempText.setTexture(s.FlagR);
				break;
			case 'd':
				tempText.setTexture(s.FlagL);
				break;
			case 'e': {
				tempText.setTexture(s.LuckyBlockPU);

				break;
			case 'f':
				tempText.setTexture(s.Coin);
				break;
			}
			case 'g':
				tempText.setTexture(s.PipeTLD);
				break;
			case 'h':
				tempText.setTexture(s.PipeTRD);
				break;
			case 'i':
				tempText.setTexture(s.PipeTLSWD);
				break;
			case 'j':
				tempText.setTexture(s.PipeBLSWD);
				break;
			case 'k':
				tempText.setTexture(s.PipeTRSW);
				break;
			case 'l':
				tempText.setTexture(s.PipeBRSW);
				break;
			default:
				tempText.setTexture(s.Sky);
				break;
			}
			tempText.setPosition(sf::Vector2f(d * 16, h * 16));
			sprites[h].push_back(tempText);
		}
		std::cout << std::endl;
	}
}
void Board::InterpretBoard(sf::RenderWindow &window, int levelType, sf::Sprite Powerup) {
	std::vector<sf::Sprite> notSky;
	for (int i = 0; i < std::size(sprites); i++) {
		for (int f = 0; f < std::size(sprites[i]); f++) {
			if (&sprites[i][f].getTexture() != &s.Sky && &sprites[i][f].getTexture() != &s.SkyUG) {
				notSky.push_back(sprites[i][f]);
			}
			else {
				window.draw(sprites[i][f]);

			}

		}
	}
	if (levelType == 0) {
		std::vector<sf::Sprite> Hills(5, sf::Sprite(s.Hill));
		std::vector<sf::Sprite> Bush3(5, sf::Sprite(s.Bush));
		std::vector<sf::Sprite> SmallHill(5, sf::Sprite(s.SmallHill));
		std::vector<sf::Sprite> Bush1(5, sf::Sprite(s.Bush));
		std::vector<sf::Sprite> Bush2(5, sf::Sprite(s.Bush));
		std::vector<sf::Sprite> Cloud1(5, sf::Sprite(s.Cloud));
		std::vector<sf::Sprite> Cloud2(5, sf::Sprite(s.Cloud));
		std::vector<sf::Sprite> Cloud3(5, sf::Sprite(s.Cloud));
		std::vector<sf::Sprite> Cloud4(5, sf::Sprite(s.Cloud));
		for (int i = 0; i < 5; i++) {
			Hills[i].setPosition({ 0.f * 16.f + (i * 48.f * 16), 192.f });
			Bush3[i].setPosition({ 13.f * 16.f + (i * 48.f * 16), 192.f });
			SmallHill[i].setPosition({ 17.f * 16.f + (i * 48.f * 16), 192.f });
			Bush1[i].setPosition({ 25.f * 16.f + (i * 48.f * 16), 192.f });
			Bush2[i].setPosition({ 43.f * 16.f + (i * 48.f * 16), 192.f });
			Cloud1[i].setPosition({ 10.f * 16.f + (i * 48.f * 16), 40.f });
			Cloud2[i].setPosition({ 21.f * 16.f + (i * 48.f * 16), 24.f });
			Cloud3[i].setPosition({ 29.f * 16.f + (i * 48.f * 16), 40.f });
			Cloud4[i].setPosition({ 39.f * 16.f + (i * 48.f * 16), 24.f });
			window.draw(Hills[i]);
			window.draw(Bush3[i]);
			window.draw(SmallHill[i]);
			window.draw(Bush1[i]);
			window.draw(Bush2[i]);
			window.draw(Cloud1[i]);
			window.draw(Cloud2[i]);
			window.draw(Cloud3[i]);
			window.draw(Cloud4[i]);
		}
	}

	window.draw(Powerup);
	for (int i = 0; i < size(notSky); i++) {
		window.draw(notSky[i]);
	}
}
void Board::startBoard(sf::RenderWindow &window, int levelType, sf::Sprite Powerup) {
	InterpretBoard(window, levelType, Powerup);
}