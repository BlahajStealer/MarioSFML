#include "Enemy.h"

void Enemy::runEnemy(sf::View cam, std::vector<std::vector<sf::Sprite>>& Sprites, sf::RenderWindow& window, sprite& s) {
    if (EnemyInCam(cam)) {
        Move(Sprites, s);
    }
    window.draw(shape);
}

void Enemy::Move(std::vector<std::vector<sf::Sprite>>& Sprites, sprite& s) {
    sf::Vector2f prevPos = shape.getPosition();
    sf::FloatRect shapeBounds = shape.getGlobalBounds();


    shape.move({ speed.x * dir, 0 });
    shapeBounds = shape.getGlobalBounds(); 

    int tileX = static_cast<int>(shape.getPosition().x / 16.f);
    int tileY = static_cast<int>(shape.getPosition().y / 16.f);

    int startY = std::max(0, tileY - 1);
    int endY = std::min(static_cast<int>(Sprites.size()) - 1, tileY + 2);
    int startX = std::max(0, tileX - 1);
    int endX = std::min(static_cast<int>(Sprites[0].size()) - 1, tileX + 2);

    for (int i = startY; i <= endY; i++) {
        for (int f = startX; f <= endX; f++) {
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG || &Sprites[i][f].getTexture() == &s.TreeStem) {
                continue;
            }

            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (shapeBounds.findIntersection(spriteBounds)) {
                float prevRight = prevPos.x + shapeBounds.size.x;
                bool wasOutsideX = (prevRight <= spriteBounds.position.x || prevPos.x >= (spriteBounds.position.x + spriteBounds.size.x));

                if (wasOutsideX) {
                    shape.setPosition(prevPos);
                    dir = -dir;
                    break;
                }
            }
        }
    }

    prevPos = shape.getPosition();
    shape.move(sf::Vector2f(0, speed.y));
    shapeBounds = shape.getGlobalBounds();

    tileX = static_cast<int>(shape.getPosition().x / 16.f);
    tileY = static_cast<int>(shape.getPosition().y / 16.f);
    startY = std::max(0, tileY - 1);
    endY = std::min(static_cast<int>(Sprites.size()) - 1, tileY + 2);
    startX = std::max(0, tileX - 1);
    endX = std::min(static_cast<int>(Sprites[0].size()) - 1, tileX + 2);

    for (int i = startY; i <= endY; i++) {
        for (int f = startX; f <= endX; f++) {
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG || &Sprites[i][f].getTexture() == &s.TreeStem) {
                continue;
            }

            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (shapeBounds.findIntersection(spriteBounds)) {
                float previousTop = shapeBounds.position.y - speed.y;
                bool wasOutsideY = (previousTop <= spriteBounds.position.y || previousTop >= (spriteBounds.position.y + spriteBounds.size.y));

                if (wasOutsideY) {
                    shape.move(sf::Vector2f(0, -speed.y));
                    break;
                }
            }
        }
    }
}
bool Enemy::EnemyInCam(sf::View cam) {
    sf::Vector2f viewSize = cam.getSize();
    sf::Vector2f viewCenter = cam.getCenter();

    // Calculate left and right edges of the camera view
    float camLeft = viewCenter.x - (viewSize.x / 2.f);
    float camRight = viewCenter.x + (viewSize.x / 2.f);

    // Activates the enemy if it's within or slightly off-screen to the right
    if (shape.getPosition().x >= camLeft - 16.f && shape.getPosition().x <= camRight + 100.f) {
        return true;
    }
    return false;
}