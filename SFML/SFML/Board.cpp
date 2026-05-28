#include "Board.h"
Board::Board() {
	for (int i = 0; i < std::size(Levels); i++) {
		Levels[i] = path + "\\Levels\\Level" + std::to_string(i + 1);
	}
}
void Board::BuildBoard(int CurrentLevel) {
	std::string used;
	used = Levels[CurrentLevel];
	std::ifstream outFile(used);

	for (int i = 0; i < std::size(board); i++) {
		std::string line = "";
		std::getline(outFile, line);
		for (int f = 0; f < std::size(board[0]); f++) {
			board[i][f] = line[i];
		}
	}
}