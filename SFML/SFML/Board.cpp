#include "Board.h"
Board::Board(std::string path) {

	for (int i = 0; i < std::size(Levels); i++) {
		Levels[i] = "Levels/Level" + std::to_string(i + 1) + ".smb";
	}
	BuildBoard(0);
	fillLevel();

}
std::vector<std::vector<sf::Sprite>> Board::getSprites() {
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
void Board::fillLevel() {

	for (int h = 0; h < 16; h++) {
		std::vector<sf::Sprite> tempor;
		sprites.push_back(tempor);

		for (int d = 0; d < 211; d++) {
			sf::Sprite tempText = sf::Sprite(s.Sky);
			switch (board[h][d]) {
			case '0':
				
				tempText.setTexture(s.Sky);
				break;
			case '1':
				tempText.setTexture(s.Brick);
				break;
			case '2':
				tempText.setTexture(s.LuckyBlock);
				break;
			case '3':
				tempText.setTexture(s.BreakableBrick);
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
void Board::InterpretBoard(sf::RenderWindow &window) {
	for (int i = 0; i < std::size(sprites); i++) {
		for (int f = 0; f < std::size(sprites[i]); f++) {
			window.draw(sprites[i][f]);
		}
	}
}
void Board::startBoard(sf::RenderWindow &window) {
	InterpretBoard(window);
}