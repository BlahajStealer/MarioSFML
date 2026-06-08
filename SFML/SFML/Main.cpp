#include "PlayerMovement.h"
#include "Board.h"
#include "TypeOfSprite.hpp"
#include "Camera.h"
#include "Enemy.h"
#include "Misc.h"
#include "Audio.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
using namespace std;
int main()
{
    Audios a = Audios();
    int powerupDir = -1;
    char cwd[MAX_PATH];
    Camera c;
    GetCurrentDirectoryA(MAX_PATH, cwd);
    std::string path = cwd;
    sprite s = sprite();
    std::vector<Enemy> Goombas;
    sf::Sprite PowerUp(s.Mushroom);
    Board b = Board(path, Goombas, 0);
    cout << path;
    PlayerMovement pm;
    sf::RenderWindow window(sf::VideoMode({ 1024, 960 }), "It's the super Mario Bros. Super Show!");
    sf::Font MarioFont;
    MarioFont.setSmooth(false);
    if (!MarioFont.openFromFile("Font/SMB.otf")) {
        system("PAUSE");
    }
    window.setFramerateLimit(60);
    const sf::Texture PlayerTexture = sf::Texture(b.s.SmallMario);
    int Score = 0;
    int Time = 400;
    int Coins = 0;
    int Lives = 3;
    int World = 1;
    int Level = 1;
    bool deathScreen = false;
    int deathFrames = 0;
    sf::View Cam;
    sf::Sprite shape = sf::Sprite(PlayerTexture);
    shape.setPosition(sf::Vector2f(48, 192));
    int currentArea = 0; //0 = Overworld, 1 = Underground
    int FrameRule = 0;
    bool musicPlaying = false;
    bool MainMenu = true;
    bool selected1P = true;
    bool subArea = false;
    bool shouldBreak = false;
    bool movingPowerup = false;
    int startingPosPowerup;
    bool CoinOutOfBlock = false;
    float maxCoinHeight;
    bool switchingLevels = false;
    sf::Sprite spareCoin(b.s.Coin);
    while (window.isOpen())
    {
        shape.setOrigin(sf::Vector2f(8.f, 0.f));

        FrameRule++;
        if (FrameRule >= 21) {

            FrameRule = 0;
            Time--;
        }

        

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if (!deathScreen && !MainMenu && !subArea) {
            if (currentArea == 0 && !musicPlaying) {
                musicPlaying = true;
                a.Overworld.setVolume(50.f);
                a.Overworld.setLooping(true);
                a.Overworld.play();
            }
            else if (currentArea == 1 && !musicPlaying) {
                musicPlaying = true;
                a.Underground.setVolume(50.f);
                a.Underground.setLooping(true);
                a.Underground.play();
            }

            if (pm.getInvincible()) {
                pm.incInvinc();
                if (pm.getInvincibility() >= 158) {
                    pm.switchInvincible();
                    pm.endInvinc();
                }
            }
            int whatDidYouHit = pm.FrameRun(shape, shape.getPosition().y, b.getSprites(), b.s, Goombas,
                PowerUp, Cam, currentArea, movingPowerup);
            if (pm.sentPowerup) {
                movingPowerup = true;
                pm.sentPowerup = false;
                startingPosPowerup = PowerUp.getPosition().y;
            }
            if (movingPowerup) {
                PowerUp.move({ 0, -.3f });
                if (PowerUp.getPosition().y <= startingPosPowerup - 18) {
                    movingPowerup = false;
                }
            }
            switch (whatDidYouHit) {
            case 1:
                Score += 50;
                a.brickBreak.play();
                break;
            case 2:
                Score += 200;
                a.coin.play();

                Coins++;
                break;
            case 3:
                Score += 100;
                a.coin.play();
                Coins++;
                break;
            case 4:
                a.item.play();
                break;
            case 5:
                a.Overworld.stop();
                Goombas.clear();

                currentArea = 1;
                a.powerdown.play();
                subArea = true;
                musicPlaying = false;
                b.getSprites().clear();
                b.fillSubBoard();
                shape.setPosition({ 48.f, 32.f });
                pm.resetVelocity();

                continue;
            case 6:
                Level++;
                a.Overworld.stop();
                a.Underground.stop();
                musicPlaying = false;
                deathScreen = true;
                switchingLevels = true;

                break;
            default:
                break;
            }
            if (Coins >= 100) {
                Lives++;
                Coins = 0;
            }

            cout << shape.getPosition().x << ", " << shape.getPosition().y << endl;
            if (currentArea == 0) {
                window.clear(sf::Color(0x4DA6FFFF));

            }
            else if (currentArea == 1) {
                window.clear(sf::Color::Black);

            }
            if (!movingPowerup) {
                movePowerUp(PowerUp, powerupDir, b.getSprites(), b.s);

            }
            Cam = c.MoveCamera(shape, false);
            window.setView(Cam);
            b.startBoard(window, currentArea, PowerUp);






            for (int i = size(Goombas) - 1; i >= 0; i--) {

                Goombas[i].runEnemy(Cam, b.getSprites(), window, b.s);
                for (int f = std::size(pm.getFireballs()) - 1; f >= 0; f--) {
                    sf::FloatRect shapeBounds = Goombas[i].getSprite().getGlobalBounds();
                    sf::FloatRect spriteBounds = pm.getFireballs()[f].getGlobalBounds();
                    if (shapeBounds.findIntersection(spriteBounds)) {
                        Goombas.erase(Goombas.begin() + i);
                        pm.setFireballs().erase(pm.setFireballs().begin() + f);
                        Score += 100;
                    }
                }

            }



            window.draw(shape);

            if (pm.getDeath() || Time <= 0) {
                if (currentArea == 0) {
                    a.Overworld.stop();
                }
                a.death.play();
                musicPlaying = false;
                Death(c, Goombas, b, pm, Cam, shape, FrameRule, path, b.s, Lives, currentArea, Level);
                deathScreen = true;
                window.clear(sf::Color::Black);
            }

            for (int i = 0; i < size(pm.getFireballs()); i++) {
                window.draw(pm.getFireballs()[i].fb);
            }
            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect spriteBounds = PowerUp.getGlobalBounds();
            if (shapeBounds.findIntersection(spriteBounds) && !movingPowerup) {
                PowerUp.setTexture(b.s.Mushroom);
                PowerUp.setPosition({ 9999999.f, 9999999.f });
                if (pm.getMarioSize() != 2) {
                    pm.marioSizeChange(true, shape, s);

                }
                Score += 1000;
            }
            if (pm.sentCoin) {
                pm.sentCoin = false;
                CoinOutOfBlock = true;
                spareCoin.setPosition(pm.JustHitBlock);
                maxCoinHeight = spareCoin.getPosition().y - 32;
            }
            
            if (CoinOutOfBlock) {
                spareCoin.move({ 0.f,-5.f });
                if (spareCoin.getPosition().y < maxCoinHeight) {
                    spareCoin.setPosition({ 999999.f,9999999.f });
                    CoinOutOfBlock = false;
                }
            }
            window.draw(spareCoin);
        }
        else if (MainMenu) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
                selected1P ? selected1P = false : selected1P = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                MainMenu = false;
                deathScreen = true;
            }
            Time = 400;
            window.clear(sf::Color::Black);
            sf::Sprite mushroomSelector(b.s.MushroomSelector);
            selected1P ? mushroomSelector.setPosition({ 220.f,540.f }) : mushroomSelector.setPosition({ 220.f,600.f });
            mushroomSelector.setScale({ 4.f,4.f });
            sf::Sprite Mainmenu(b.s.Mainmenu);
            Mainmenu.setScale({ 4.f,4.f });
            sf::Text UnPlayerGame(MarioFont);
            UnPlayerGame.setCharacterSize(32);
            UnPlayerGame.setPosition({ 300.f, 540.f });
            UnPlayerGame.setString("1 Player Game");            
            sf::Text DosPlayerGame(MarioFont);
            DosPlayerGame.setCharacterSize(32);
            DosPlayerGame.setPosition({ 300.f, 600.f });
            DosPlayerGame.setString("2 Player Game");
            window.draw(Mainmenu);
            window.draw(mushroomSelector);
            window.draw(UnPlayerGame);
            window.draw(DosPlayerGame);
        }
        else if (subArea) {
            Cam = c.MoveCamera(shape, true);
            window.setView(Cam);
            if (currentArea == 0 && !musicPlaying) {
                musicPlaying = true;
                a.Overworld.setVolume(50.f);
                a.Overworld.setLooping(true);
                a.Overworld.play();
            }
            else if (currentArea == 1 && !musicPlaying) {
                musicPlaying = true;
                a.Underground.setVolume(50.f);
                a.Underground.setLooping(true);
                a.Underground.play();
            }

            if (pm.getInvincible()) {
                pm.incInvinc();
                if (pm.getInvincibility() >= 158) {
                    pm.switchInvincible();
                    pm.endInvinc();
                }
            }

            int whatDidYouHit = pm.FrameRun(shape, shape.getPosition().y, b.getSprites(), b.s, Goombas,
                PowerUp, Cam, currentArea, movingPowerup);

            switch (whatDidYouHit) {
            case 1:
                Score += 50;
                a.brickBreak.play();
                break;
            case 2:
                Score += 200;
                a.coin.play();


                Coins++;
                break;
            case 3:
                Score += 100;
                a.coin.play();
                Coins++;
                break;
            case 4:
                a.item.play();
                break;
            case 5:
                Goombas.clear();
                a.Underground.stop();
                currentArea = 0;
                a.powerdown.play();
                subArea = false;
                musicPlaying = false;
                b.getSprites().clear();
                b.fillLevel(Goombas, currentArea);
                shape.setPosition({ 2657.f, 160.f });
                pm.resetVelocity();
                continue;
            default:
                break;
            }
            if (Coins >= 100) {
                Lives++;
                Coins = 0;
            }
            cout << shape.getPosition().x << ", " << shape.getPosition().y << endl;
            window.clear(sf::Color::Black);
            b.startBoard(window, currentArea, PowerUp);
            Cam = c.MoveCamera(shape, true);
            window.setView(Cam);

            for (int i = size(Goombas) - 1; i >= 0; i--) {

                Goombas[i].runEnemy(Cam, b.getSprites(), window, b.s);
                for (int f = std::size(pm.getFireballs()) - 1; f >= 0; f--) {
                    sf::FloatRect shapeBounds = Goombas[i].getSprite().getGlobalBounds();
                    sf::FloatRect spriteBounds = pm.getFireballs()[f].getGlobalBounds();
                    if (shapeBounds.findIntersection(spriteBounds)) {
                        Goombas.erase(Goombas.begin() + i);
                        pm.setFireballs().erase(pm.setFireballs().begin() + f);
                        Score += 100;
                    }
                }

            }

            window.draw(shape);

            if (pm.getDeath() || Time <= 0) {
                if (currentArea == 0) {
                    a.Overworld.stop();
                }
                a.death.play();
                musicPlaying = false;
                Death(c, Goombas, b, pm, Cam, shape, FrameRule, path, b.s, Lives, currentArea, Level);
                deathScreen = true;
                window.clear(sf::Color::Black);
            }
            movePowerUp(PowerUp, powerupDir, b.getSprites(), b.s);

            for (int i = 0; i < size(pm.getFireballs()); i++) {
                window.draw(pm.getFireballs()[i].fb);
            }
            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect spriteBounds = PowerUp.getGlobalBounds();
            if (shapeBounds.findIntersection(spriteBounds) && !movingPowerup) {
                PowerUp.setTexture(b.s.Mushroom);
                PowerUp.setPosition({ 0.f, 0.f });
                if (pm.getMarioSize() != 2) {
                    pm.marioSizeChange(true, shape, s);

                }
                Score += 1000;
            }
            window.draw(PowerUp);
        }
        else {
            deathFrames++;
            window.clear(sf::Color::Black);
            Time = 0;
            if (deathFrames >= 255) {
                deathFrames = 0;
                deathScreen = false;
                Time = 400;
                if (switchingLevels) {
                    currentArea++;
                    b.BuildBoard(1);
                    b.BuildSubBoard(1);
                    Goombas.clear();
                    b.getSprites().clear();
                    b.fillLevel(Goombas, currentArea);
                    pm.resetVelocity();
                    shape.setPosition(sf::Vector2f(48, 192));
                    switchingLevels = false;

                }
            }
            
        }

        sf::View hudView = window.getDefaultView();
        window.setView(hudView);

        sf::Text ScoreText(MarioFont);
        std::ostringstream scoreOss;
        scoreOss << std::setw(6) << std::setfill('0') << Score;
        std::string scoreString = scoreOss.str();        
        std::ostringstream coinOss;
        coinOss << std::setw(2) << std::setfill('0') << Coins;
        std::string CoinString = coinOss.str();        
        std::ostringstream timeOSS;
        timeOSS << std::setw(3) << std::setfill('0') << Time;
        std::string timeString = timeOSS.str();

        ScoreText.setString("MARIO\t\t\tWORLD\tTIME\n" + scoreString + "   Cx" + 
            CoinString + "\t " + std::to_string(World) + "-" + std::to_string(Level)
            + "\t  " + timeString);
        ScoreText.setCharacterSize(32);
        
        ScoreText.setPosition({ 24.f, 16.f});
        window.draw(ScoreText);

        if (deathScreen) {
            sf::Text WorldText(MarioFont);
            WorldText.setString("WORLD " + std::to_string(World) + "-" + std::to_string(Level));
            WorldText.setCharacterSize(32);
            WorldText.setPosition({ 375.f, 250.f });
            window.draw(WorldText);
            sf::Text LiveText(MarioFont);
            sf::Sprite lifeMario(s.SmallMario);
            lifeMario.setScale({ 3.f,3.f });
            lifeMario.setPosition({ 405.f, 325.f });
            LiveText.setString("   x  " + std::to_string(Lives));
            LiveText.setCharacterSize(32);
            LiveText.setPosition({ 405.f, 340.f });
            window.draw(LiveText);
            window.draw(lifeMario);
        }
        window.setView(Cam);

        //Write everything before here
        window.display();
    }
}