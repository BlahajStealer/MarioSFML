#include "PlayerMovement.h"

using namespace std;
void PlayerMovement::FrameRun(sf::RectangleShape& shape, float yCord) {
    VerticalMovement();
    Gravity();

    Movement(shape, yCord);

}
void PlayerMovement::VerticalMovement(void) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        Acceleration = sf::Vector2f(-AccelerationFactors.x, Acceleration.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        Acceleration = sf::Vector2f(AccelerationFactors.x, Acceleration.y);
    }
    else {
        if (Velocity.x > 0) {
            Acceleration = sf::Vector2f(-AccelerationFactors.x, Acceleration.y);
        }
        else if (Velocity.x < 0) {
            Acceleration = sf::Vector2f(AccelerationFactors.x, Acceleration.y);
        }
    }
}
void PlayerMovement::Gravity(void) {
    Acceleration = sf::Vector2f(Acceleration.x, AccelerationFactors.y);
    
}

void PlayerMovement::Movement(sf::RectangleShape &shape, float yCord) {
    Velocity += Acceleration / 60.f;
    if (yCord < 208) {
        shape.move(Velocity * (1.f / 60.f));

    }
    else {
        shape.move(sf::Vector2f(Velocity.x / 60.f, 0.f));
        shape.setPosition(sf::Vector2f(shape.getPosition().x, 208.f));
    }

}