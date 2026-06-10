#pragma once
#include "Enemy.h"
#include <random>
#include <stdio.h>
#include <vector>
#include "BowserFireball.h"
#include "Sprite.h"
class Bowser : public Enemy
{
	void Jump();
	void Fireball();
	void Animation();
	bool Jumping = false;
	sf::Sprite BowserAnims[4];
	std::vector<BowserFireball> fireballs;
};

