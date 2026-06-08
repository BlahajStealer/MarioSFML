#include "Fireball.h"

void Fireball::moveFireball(sprite &s, std::vector<std::vector<sf::Sprite>> Sprites, sf::View cam) {
    offScreen(cam);
    sf::Vector2f prevPos = fb.getPosition();

    std::cout << "\n\n" << fb.getPosition().x << ", " << fb.getPosition().y << "\n\n";
    fb.move({ 2.5f * dir,0 });
    for (int i = 0; i < std::size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = fb.getGlobalBounds();
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG) {

                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {

                float prevRight = prevPos.x + shapeBounds.size.x;


                bool wasOutsideX = (prevRight <= spriteBounds.position.x
                    || prevPos.x >= (spriteBounds.position.x + spriteBounds.size.x));


                if (wasOutsideX) { //Collided on the X
                    fb.setPosition({ prevPos.x, fb.getPosition().y });
                    dir = -dir;
                    Kill = true;
                }

            }


        }
    }
    if (fb.getPosition().y < MaxHeight) {
        ydir = -ydir;
    }
    fb.move({ 0, 2.f * ydir});

    for (int i = 0; i < size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = fb.getGlobalBounds();
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG) {
                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {
                float previousTop = shapeBounds.position.y - 2.2f;
                float previousBottom = previousTop + shapeBounds.size.y;

                bool wasAbove = previousBottom <= spriteBounds.position.y;

                if (wasAbove) { //Collided on the Y
                    if (MaxHeight == 0) {
                        MaxHeight = fb.getPosition().y - 20;
                    }
                    fb.setPosition({ fb.getPosition().x, prevPos.y });
                    ydir = -ydir;
                    break;
                }
            }
        }
    }
    
}

void Fireball::offScreen(sf::View cam) {

    if (!fireballInView(cam)) {
        Kill = true;
    }
}
bool Fireball::fireballInView(sf::View cam) {

    sf::Vector2f viewSize = cam.getSize();
    sf::Vector2f topLeft = cam.getCenter() - (viewSize / 2.f);
    sf::FloatRect camBounds(topLeft, viewSize);


    if (camBounds.findIntersection(fb.getGlobalBounds())) {
        return true;
    }
    return false;
}
Fireball::~Fireball() {

}