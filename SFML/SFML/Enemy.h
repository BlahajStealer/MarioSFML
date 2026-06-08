#pragma once
#include <SFML\Graphics.hpp>
#include "TypeOfSprite.hpp"
#include <iostream>
class Enemy
{
private:
	int cordX;
	int cordY;
	int TypeOfEnemy;
	int dir = -1; //-1 is left 1 is right;
	sf::Vector2f speed = { .5f, 2.2f};
	sf::Sprite shape;
	void Move(std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s);
	void Die();
	bool EnemyInCam(sf::View cam);
public:
	sf::Sprite getSprite() {
		return shape;
	}
	sf::Sprite &setSprite() {
		return shape;
	}
	Enemy(int x, int y, int ID, sprite& s) : shape(s.Goomba)
	{

		cordX = x * 16;
		cordY = y * 16;
		shape.setPosition(sf::Vector2f{ (float)cordX, (float)cordY });
		TypeOfEnemy = ID;
	}
	void runEnemy(sf::View cam, std::vector<std::vector<sf::Sprite>>& Sprites, sf::RenderWindow& window, sprite &s);

};

