#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerMovement.h"
using namespace std;
int main()
{
    PlayerMovement pm;
    sf::RenderWindow window(sf::VideoMode({ 256, 240 }), "It's the super Mario Bros. Super Show!");
    window.setFramerateLimit(60);

    sf::RectangleShape shape(sf::Vector2f(16,32));
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        pm.FrameRun(shape, shape.getPosition().y);



        cout << shape.getPosition().x << ", " << shape.getPosition().y << endl;
        window.clear();
        window.draw(shape);
        window.display();
    }
}