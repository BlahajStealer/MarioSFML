#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TypeOfSprite.hpp"
class PlayerMovement
{
	sf::Vector2f Acceleration = sf::Vector2f(0.f,0.f);
	sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f AccelerationFactors = sf::Vector2f(100.f, 300.f);
	bool Moving = false;
	float currentTerminalVelocity = 100;
	float walkingTerminalVelocity = 100;
	float fastTerminalVelocity = 175;
	bool Jumping = false;
	int JumpingFrames = 0;
	bool Grounded = true;
public:
	void FrameRun(sf::Sprite &shape, float yCord, const std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s);
private:
	void VerticalMovement(void);
	void Gravity(void);
	void Movement(sf::Sprite &shape, float yCord, const std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s);
	void Jump(sf::Sprite &shape, float &yCord);
};

