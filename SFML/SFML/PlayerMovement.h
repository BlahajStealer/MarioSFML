#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class PlayerMovement
{
	sf::Vector2f Acceleration = sf::Vector2f(0.f,0.f);
	sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f AccelerationFactors = sf::Vector2f(100.f, 100.f);
public:
	void FrameRun(sf::RectangleShape& shape, float yCord);
private:
	void VerticalMovement(void);
	void Gravity(void);
	void Movement(sf::RectangleShape& shape, float yCord);
	
};

