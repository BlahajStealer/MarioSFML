#include "Misc.h"

void movePowerUp(sf::Sprite &Powerup, int &powerupDir, std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s) {
    sf::Vector2f prevPos = Powerup.getPosition();

    if (&Powerup.getTexture() != &s.Fireflower) {
        Powerup.move({ .6f * powerupDir,0 });
        for (int i = 0; i < std::size(Sprites); i++) {
            for (int f = 0; f < size(Sprites[0]); f++) {

                sf::FloatRect shapeBounds = Powerup.getGlobalBounds();
                sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
                if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG) {

                    continue;
                }
                else if (shapeBounds.findIntersection(spriteBounds)) {

                    float prevRight = prevPos.x + shapeBounds.size.x;


                    bool wasOutsideX = (prevRight <= spriteBounds.position.x
                        || prevPos.x >= (spriteBounds.position.x + spriteBounds.size.x));


                    if (wasOutsideX) { //Collided on the X
                        Powerup.setPosition({ prevPos.x, Powerup.getPosition().y });
                        powerupDir = -powerupDir;
                    }

                }


            }
        }
        Powerup.move({ 0, 2.2f });

        for (int i = 0; i < size(Sprites); i++) {
            for (int f = 0; f < size(Sprites[0]); f++) {

                sf::FloatRect shapeBounds = Powerup.getGlobalBounds();
                sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
                if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG) {
                    continue;
                }
                else if (shapeBounds.findIntersection(spriteBounds)) {
                    float previousTop = shapeBounds.position.y - 2.2f;
                    float previousBottom = previousTop + shapeBounds.size.y;

                    bool wasAbove = previousBottom <= spriteBounds.position.y;

                    if (wasAbove) { //Collided on the Y
                        Powerup.setPosition({ Powerup.getPosition().x, prevPos.y });
                        break;
                    }
                }
            }
        }
    }

}

void Death(Camera &c, std::vector<Enemy> &G, Board &b, PlayerMovement &pl, sf::View &Cam, sf::Sprite &Shape, int &Framerule, std::string path, sprite &s, int &lives, int LevelType, int level) {
    c = Camera();
    G.clear();

    b.reset(path, G, LevelType, level);

    pl = PlayerMovement();

    sf::View tempCam;

    Cam = tempCam;

    Shape.setPosition(sf::Vector2f(48, 192));

    Shape.setTexture(s.SmallMario);
    Framerule = 0;
    lives--;

}