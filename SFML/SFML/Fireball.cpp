#include "Fireball.h"

void Fireball::moveFireball(sprite& s, const std::vector<std::vector<sf::Sprite>>& Sprites, sf::View cam) {
    offScreen(cam);
    sf::Vector2f prevPos = fb.getPosition();
    sf::FloatRect shapeBounds = fb.getGlobalBounds();

    fb.move({ 2.5f * dir, 0 });
    shapeBounds = fb.getGlobalBounds();

    int tileX = static_cast<int>(fb.getPosition().x / 16.f);
    int tileY = static_cast<int>(fb.getPosition().y / 16.f);

    int startY = std::max(0, tileY - 1);
    int endY = std::min(static_cast<int>(Sprites.size()) - 1, tileY + 2);
    int startX = std::max(0, tileX - 1);
    int endX = std::min(static_cast<int>(Sprites[0].size()) - 1, tileX + 2);

    for (int i = startY; i <= endY; i++) {
        for (int f = startX; f <= endX; f++) {
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG || &Sprites[i][f].getTexture() == &s.Coin) {
                continue;
            }

            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (shapeBounds.findIntersection(spriteBounds)) {
                float prevRight = prevPos.x + shapeBounds.size.x;
                bool wasOutsideX = (prevRight <= spriteBounds.position.x || prevPos.x >= (spriteBounds.position.x + spriteBounds.size.x));

                if (wasOutsideX) {
                    fb.setPosition({ prevPos.x, fb.getPosition().y });
                    dir = -dir;
                    break;
                }
            }
        }
    }

    prevPos = fb.getPosition();
    fb.move({ 0, 2.2f * ydir });
    shapeBounds = fb.getGlobalBounds();

    tileX = static_cast<int>(fb.getPosition().x / 16.f);
    tileY = static_cast<int>(fb.getPosition().y / 16.f);
    startY = std::max(0, tileY - 1);
    endY = std::min(static_cast<int>(Sprites.size()) - 1, tileY + 2);
    startX = std::max(0, tileX - 1);
    endX = std::min(static_cast<int>(Sprites[0].size()) - 1, tileX + 2);

    for (int i = startY; i <= endY; i++) {
        for (int f = startX; f <= endX; f++) {
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG || &Sprites[i][f].getTexture() == &s.Coin) {
                continue;
            }
            else {
                sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
                if (shapeBounds.findIntersection(spriteBounds)) {
                    float previousTop = shapeBounds.position.y - 2.2f;
                    bool wasAbove = (previousTop + shapeBounds.size.y) <= spriteBounds.position.y;

                    if (wasAbove) {
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
    if (MaxHeight >= fb.getPosition().y) {
        ydir = -ydir;
    }
}
Fireball::~Fireball() {
}

void Fireball::offScreen(sf::View cam) {
    if (!fireballInView(cam)) {
        Kill = true;
    }
}

bool Fireball::fireballInView(sf::View cam) {
    sf::Vector2f viewSize = cam.getSize();
    sf::Vector2f viewCenter = cam.getCenter();

    float camLeft = viewCenter.x - (viewSize.x / 2.f);
    float camRight = viewCenter.x + (viewSize.x / 2.f);

    if (fb.getPosition().x >= camLeft && fb.getPosition().x <= camRight) {
        return true;
    }
    return false;
}