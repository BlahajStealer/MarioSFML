#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "PlayerMovement.h"
#include "Board.h"
#include "TypeOfSprite.hpp"
#include "Camera.h"
using namespace std;
int main()
{
    char cwd[MAX_PATH];
    Camera c;
    GetCurrentDirectoryA(MAX_PATH, cwd);
    std::string path = cwd;
    sprite s = sprite();
    Board b = Board(path);
    cout << path;
    PlayerMovement pm;
    sf::RenderWindow window(sf::VideoMode({ 256, 240 }), "It's the super Mario Bros. Super Show!");
    window.setFramerateLimit(60);
    const sf::Texture PlayerTexture = sf::Texture(std::filesystem::path("Tiles/Mario.png"));
    

    sf::Sprite shape = sf::Sprite(PlayerTexture);
    shape.setPosition(sf::Vector2f(16, 192));
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        pm.FrameRun(shape, shape.getPosition().y, b.getSprites(), b.s);

        cout << shape.getPosition().x << ", " << shape.getPosition().y << endl;
        window.clear(sf::Color::Blue);
        b.startBoard(window);
        window.setView(c.MoveCamera(shape));
        window.draw(shape);
        window.display();
        COORD pos = { static_cast<SHORT>(0), static_cast<SHORT>(0) };
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        //SetConsoleCursorPosition(hConsole, pos);
    }
}