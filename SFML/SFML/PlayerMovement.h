#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TypeOfSprite.hpp"
#include "Enemy.h"
#include "Fireball.h"
#include "Audio.hpp"
class PlayerMovement
{
	sf::Vector2f Acceleration = sf::Vector2f(0.f,0.f);
	sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f AccelerationFactors = sf::Vector2f(70.f, 1000.f);
	bool Moving = false;
	float currentTerminalVelocity = 100;
	float walkingTerminalVelocity = 100;
	float fastTerminalVelocity = 125;
	bool Jumping = false;
	int JumpingFrames = 0;
	bool Grounded = true;
	bool Sprinting = false;
	bool invincible = false;
	int MarioSize = 0; //0 = Small, 1 = Large, 2 = Fire
	int invincibilityFramesPassed;
	bool HoldingN = false;
	bool Died = false;
	int framesPast = 0;
	int next = 2;
	bool Crouching = false;

public:
	bool died = false;
	bool sentPowerup = false;
	bool sentCoin = false;
	sf::Vector2f JustHitBlock;
	int FrameRun(sf::Sprite &shape, float yCord, std::vector<std::vector<sf::Sprite>>& Sprites, 
		sprite &s, std::vector<Enemy>& Enemies, sf::Sprite &powerupOnScreen, sf::View cam, 
		int currentLevel, bool Movingpower);
	void incMarioSize() {
		if (MarioSize < 2) {
			MarioSize++;

		}
	}
	void resetVelocity() {
		Velocity = { 0.f, 0.f };
		Acceleration.y = 0.f;
		Grounded = false;
		Jumping = false;
		JumpingFrames = 31;
	}
	int getMarioSize() {
		return MarioSize;
	}
	int getInvincibility() {
		return invincibilityFramesPassed;
	}
	void incInvinc() {
		invincibilityFramesPassed++;
	}
	void endInvinc() {
		invincibilityFramesPassed = 0;
	}
	void switchInvincible() {
		invincible ? invincible = false : invincible = true;
	}	
	bool getInvincible() {
		if (invincible) return true; else return false;
	}
	void marioSizeChange(bool Dir, sf::Sprite &shape, sprite &s);
	std::vector<Fireball> getFireballs() {
		return Fireballs;
	}
	std::vector<Fireball>& setFireballs() {
		return Fireballs;

	}
	bool getDeath() {
		return Died;
	}

private:
	Audios a;
	void WalkingAnim(sprite& s, sf::Sprite &shape);
	void CrouchedAnim(sprite& s, sf::Sprite &shape);
	void StoppingAnim(sprite& s, sf::Sprite &shape);
	static sf::FloatRect getHitbox(sf::Sprite player);
	void VerticalMovement(sf::Sprite &shape, sprite &s);
	void Gravity(void);
	int Movement(sf::Sprite &shape, float yCord, std::vector<std::vector<sf::Sprite>>& Sprites, 
		sprite &s, std::vector<Enemy> &Enemies, sf::Sprite &powerupOnScreen, sf::View cam, int currentLevel,
		bool MovingPower);
	void Jump(sf::Sprite &shape, float &yCord, sprite &s);
	void fireflower(sprite &s, sf::Sprite shape);
	std::vector<Fireball> Fireballs;
};

