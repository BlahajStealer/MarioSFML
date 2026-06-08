#include "Enemy.h"

void Enemy::runEnemy(sf::View cam, std::vector<std::vector<sf::Sprite>>& Sprites, sf::RenderWindow &window, sprite &s) {
    std::cout << shape.getGlobalBounds().position.x << ", " << shape.getGlobalBounds().position.y << "\n";

    if (EnemyInCam(cam)) {
		Move(Sprites, s);
	}
    window.draw(shape);
}
void Enemy::Move(std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s) {
    sf::Vector2f prevPos = shape.getPosition();


    shape.move({speed.x * dir, 0});
    for (int i = 0; i < size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG) {

                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {

                float prevRight = prevPos.x + shapeBounds.size.x;


                bool wasOutsideX = (prevRight <= spriteBounds.position.x
                    || prevPos.x >= (spriteBounds.position.x + spriteBounds.size.x));


                if (wasOutsideX) { //Collided on the X

                    shape.setPosition(prevPos);
                    dir = -dir;
                }

            }


        }
    }
    shape.move(sf::Vector2f(0, speed.y));
    for (int i = 0; i < size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG) {
                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {
                float previousTop = shapeBounds.position.y - speed.y;
                float previousBottom = previousTop + shapeBounds.size.y;

                bool wasOutsideY = (previousTop <= spriteBounds.position.y
                    || previousTop >= (spriteBounds.position.y + spriteBounds.size.y));

                if (wasOutsideY) { //Collided on the Y
                    shape.move(sf::Vector2f(0, -speed.y));
                    break;
                }
            }
        }
    }
}
void Enemy::Die() {

}
bool Enemy::EnemyInCam(sf::View cam) {

	sf::Vector2f viewSize = cam.getSize();
	sf::Vector2f topLeft = cam.getCenter() - (viewSize / 2.f);
	sf::FloatRect camBounds(topLeft, viewSize);

    
    if (camBounds.findIntersection(shape.getGlobalBounds())) {
        return true;
    }
	return false;
}