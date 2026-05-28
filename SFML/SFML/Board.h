#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
class Board
{
public:
	void startBoard();
	Board();

private:
	std::string path = __FILE__;
	std::string Levels[1];
	char board[16][211];
	void BuildBoard(int CurrentLevel); //Builds Level in chars
	void InterpretBoard();
};

