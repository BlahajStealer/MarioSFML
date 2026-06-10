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
    ShowWindow(GetConsoleWindow(), SW_HIDE);
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
    int Level = 3;
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
    bool goingDown = false;
    int goingDownFrames = 0;
    bool comingUp = false;
    bool hitFlagPole = false;
    bool walkAway = false;
    int walkAwayFrames = false;
    bool hitAxe = false;
    bool talking2Toad = false;
    int castleFrames = 0;
    while (window.isOpen())
    {


        shape.setOrigin(sf::Vector2f(8.f, 0.f));

        FrameRule++;
        if (FrameRule >= 21) {

            FrameRule = 0;
            if (!walkAway && !hitFlagPole && !comingUp && !goingDown) {
                Time--;

            }
        }

        if (Lives <= 0) {
            std::exit(true);

        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if (!deathScreen && !MainMenu && !subArea) {

            if (Level == 2 && !musicPlaying) {
                musicPlaying = true;
                a.Underground.setLooping(true);
                a.Underground.play();
            }
            else if (Level == 4 && !musicPlaying) {
                musicPlaying = true;
                a.Castle.setLooping(true);
                a.Castle.play();
            }
            else if (!musicPlaying) {
                musicPlaying = true;
                a.Overworld.setLooping(true);
                a.Overworld.play();
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
                
                goingDown = true;
                a.powerdown.play();

                continue;
            case 6:
                hitFlagPole = true;
                shape.setPosition({ shape.getPosition().x + 6.f, shape.getPosition().y });


                break;
            case 7:
                hitAxe = true;
                break;
            default:
                break;
            }
            cout << shape.getPosition().x << ", " << shape.getPosition().y << endl;
            if (currentArea == 0) {
                window.clear(sf::Color(0x4DA6FFFF));

            }
            else if (currentArea == 1) {
                window.clear(sf::Color::Black);

            }


            //Animations, refactor into misc
            if (hitFlagPole) {
                
                shape.move({ 0.f, 1.f });
                pm.resetVelocity();
                switch (pm.getMarioSize()) {
                case 0:
                    shape.setTexture(b.s.SmallMarioFlag1);
                    break;
                case 1:
                    shape.setTexture(b.s.MarioGrabPole);
                    break;
                case 2:
                    shape.setTexture(b.s.FiremarioGrabPole);
                    break;
                }
                if (pm.getMarioSize() == 0) {
                    if (shape.getPosition().y >= 240.f - 48.f) {
                        shape.setPosition({ shape.getPosition().x, 240.f - 48.f });
                        if (pm.getMarioSize() == 0) {
                            shape.setTexture(b.s.SmallMarioFlag2);

                        }
                        else if (pm.getMarioSize() == 1) {
                            shape.setTexture(b.s.MarioBottomFlag);

                        }
                        else {
                            shape.setTexture(b.s.FiremarioBottomFlag);

                        }
                        shape.setScale({ -1.f, 1.f });
                        hitFlagPole = false;
                        walkAway = true;

                    }
                }
                else {
                    if (shape.getPosition().y >= 240.f - 64.f) {
                        shape.setPosition({ shape.getPosition().x, 240.f - 64.f });
                        if (pm.getMarioSize() == 0) {
                            shape.setTexture(b.s.SmallMarioFlag2);

                        }
                        else if (pm.getMarioSize() == 1) {
                            shape.setTexture(b.s.MarioBottomFlag);

                        }
                        else {
                            shape.setTexture(b.s.FiremarioBottomFlag);

                        }
                        shape.setScale({ -1.f, 1.f });
                        hitFlagPole = false;
                        walkAway = true;

                    }
                }

            }
            if (walkAway) {
                walkAwayFrames++;
                pm.getVelocity().x = 80.f;
                pm.WalkingAnim(b.s, shape);
                if (walkAwayFrames == 80) {
                    walkAway = false;
                    walkAwayFrames = 0;
                    Level++;
                    a.Overworld.stop();
                    a.Castle.stop();
                    a.Underground.stop();
                    musicPlaying = false;
                    deathScreen = true;
                    switchingLevels = true;
                }

            }
            if (goingDown) {
                goingDownFrames++;
                pm.resetVelocity();
                if (Level == 2) {
                    shape.move({ 0.85f, 0.f });

                }
                else {
                    shape.move({ 0.f, .25f });

                }
                if (goingDownFrames >= 60) {
                    a.Overworld.stop();
                    a.Underground.stop();
                    a.Castle.stop();
                    Goombas.clear();
                    goingDownFrames = 0;
                    goingDown = false;
                    currentArea == 1 ? currentArea = 0 : currentArea = 1;
                    subArea = true;
                    musicPlaying = false;
                    b.getSprites().clear();
                    b.fillSubBoard(currentArea);
                    shape.setPosition({ 48.f, 32.f });
                    pm.resetVelocity();
                }

            }
            if (comingUp) {
                goingDownFrames++;
                pm.resetVelocity();
                pm.getMarioSize() == 0 ? shape.move({ 0.f, -.55f }) : shape.move({ 0.f, -.85f });
                if (goingDownFrames >= 60) {
                    goingDownFrames = 0;
                    comingUp = false;
                }
            }
            if (hitAxe) {
                pm.getVelocity().x = 80.f;
                pm.WalkingAnim(s, shape);
                if (shape.getPosition().x >= 2464.f) {
                    pm.resetVelocity();
                    hitAxe = false;
                    talking2Toad = true;
                }
            }


            if (Coins >= 100) {
                Lives++;
                Coins = 0;
            }


            if (!movingPowerup) {
                movePowerUp(PowerUp, powerupDir, b.getSprites(), b.s);

            }
            if (!walkAway && !hitFlagPole) {
                Cam = c.MoveCamera(shape, false);

            }
            else {

            }
            window.setView(Cam);
            b.startBoard(window, currentArea, PowerUp, shape, goingDown, Level);






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


            if (!goingDown && !comingUp) {
                window.draw(shape);

            }

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
                goingDown = true;

                continue;
            case 6:
                hitFlagPole = true;
                shape.setPosition({ shape.getPosition().x + 6.f, shape.getPosition().y });


            default:
                break;
            }
            if (Coins >= 100) {
                Lives++;
                Coins = 0;
            }
            cout << shape.getPosition().x << ", " << shape.getPosition().y << endl;
            currentArea == 1 ? window.clear(sf::Color::Black) : window.clear(sf::Color(0x4DA6FFFF));
            b.startBoard(window, currentArea, PowerUp, shape, goingDown, Level);
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
            if (hitFlagPole) {

                shape.move({ 0.f, 1.f });
                pm.resetVelocity();
                switch (pm.getMarioSize()) {
                case 0:
                    shape.setTexture(b.s.SmallMarioFlag1);
                    break;
                case 1:
                    shape.setTexture(b.s.MarioGrabPole);
                    break;
                case 2:
                    shape.setTexture(b.s.FiremarioGrabPole);
                    break;
                }
                if (pm.getMarioSize() == 0) {
                    if (shape.getPosition().y >= 240.f - 48.f) {
                        shape.setPosition({ shape.getPosition().x, 240.f - 48.f });
                    }
                }
                else {
                    if (shape.getPosition().y >= 240.f - 64.f) {
                        shape.setPosition({ shape.getPosition().x, 240.f - 64.f });
                    }
                }
                if (pm.getMarioSize() == 0) {
                    shape.setTexture(b.s.SmallMarioFlag2);

                }
                else if (pm.getMarioSize() == 1) {
                    shape.setTexture(b.s.MarioBottomFlag);

                }
                else {
                    shape.setTexture(b.s.FiremarioBottomFlag);

                }
                shape.setScale({ -1.f, 1.f });
                hitFlagPole = false;
                walkAway = true;
            }
            if (walkAway) {
                walkAwayFrames++;
                pm.getVelocity().x = 80.f;
                pm.WalkingAnim(b.s, shape);
                if (walkAwayFrames == 10) {
                    walkAway = false;
                    walkAwayFrames = 0;
                    Level++;
                    a.Overworld.stop();
                    a.Underground.stop();
                    musicPlaying = false;
                    deathScreen = true;
                    switchingLevels = true;
                    Goombas.clear();
                    subArea = false;
                }
            }


            if (goingDown) {
                goingDownFrames++;
                pm.resetVelocity();
                shape.move({ .75f, 0.f });
                if (goingDownFrames == 60) {
                    comingUp = true;
                    goingDownFrames = 0;
                    goingDown = false;
                    Goombas.clear();
                    a.Underground.stop();
                    currentArea == 0 ? currentArea = 1 : currentArea = 0;
                    a.powerdown.play();
                    subArea = false;
                    musicPlaying = false;
                    b.getSprites().clear();
                    b.fillLevel(Goombas, currentArea);
                    shape.setPosition({ 2657.f, 160.f+32.f });
                    pm.resetVelocity();
                }

            }
            if (!goingDown) {
                window.draw(shape);

            }

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
            switch (Level) {
            case 1:
            case 3:
                shape.setPosition(sf::Vector2f(48, 192));
                break;
            case 2:
                shape.setPosition(sf::Vector2f(48, 32));
                break;
            case 4:
                if (pm.getMarioSize() == 0) {
                    shape.setPosition(sf::Vector2f(16, 112));

                }
                else {
                    shape.setPosition(sf::Vector2f(16, 96));

                }
                break;
            default:
                break;
            }
            if (deathFrames >= 255) {
                deathFrames = 0;
                deathScreen = false;
                Time = 400;
                if (switchingLevels) {
                    if (Level == 2 || Level == 4) {
                        currentArea = 1;
                    }
                    else {
                        currentArea = 0;
                    }
                    b.BuildBoard(Level-1);
                    b.BuildSubBoard(Level-1);
                    Goombas.clear();
                    b.getSprites().clear();
                    b.fillLevel(Goombas, currentArea);
                    pm.resetVelocity();
                    switch (Level) {
                    case 1:
                    case 3:
                        shape.setPosition(sf::Vector2f(48, 192));
                        break;
                    case 2:
                        shape.setPosition(sf::Vector2f(48, 32));
                        break;
                    case 4:
                        if (pm.getMarioSize() == 0) {
                            shape.setPosition(sf::Vector2f(16, 112));

                        }
                        else {
                            shape.setPosition(sf::Vector2f(16, 96));

                        }
                        break;
                    default:
                        break;




                    }
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
        if (talking2Toad) {
            sf::Text toad(MarioFont);
            toad.setString("Thank You Mario!\n\nBut our princess is in\nanother castle");
            toad.setCharacterSize(32);
            toad.setPosition({ 144.f,300.f});
            window.draw(toad);
            if (castleFrames >= 580) {
                return 0;
            }
        }
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