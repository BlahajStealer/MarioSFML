#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include "TypeOfSprite.hpp"
#include "PlayerMovement.h"
#include "Board.h"
#include "Camera.h"
#include "Enemy.h"
#include "Misc.h"
void Death(Camera& c, std::vector<Enemy>& G, Board& b, PlayerMovement& pl, sf::View& Cam, sf::Sprite& Shape, int& Framerule, std::string path, sprite& s, int& lives, int LevelType, int Level);
void movePowerUp(sf::Sprite& Powerup, int& powerupDir, std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s);