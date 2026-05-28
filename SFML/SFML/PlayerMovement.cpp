#include "PlayerMovement.h"

using namespace std;
void PlayerMovement::FrameRun(sf::RectangleShape& shape, float yCord) {
    VerticalMovement();
    Gravity();
    Jump(shape, yCord);
    Movement(shape, yCord);
}
void PlayerMovement::VerticalMovement(void) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (Velocity.x > 0) {
            Acceleration = sf::Vector2f(-AccelerationFactors.x * 2, Acceleration.y);

        }
        else {
            Acceleration = sf::Vector2f(-AccelerationFactors.x, Acceleration.y);

        }
        Moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (Velocity.x < 0) {
            Acceleration = sf::Vector2f(AccelerationFactors.x * 2, Acceleration.y);

        }
        else {
            Acceleration = sf::Vector2f(AccelerationFactors.x, Acceleration.y);

        }
        Moving = true;

    }
    else {
        if (Velocity.x > 0) {
            Acceleration = sf::Vector2f(-AccelerationFactors.x * 2, Acceleration.y);
        }
        else if (Velocity.x < 0) {
            Acceleration = sf::Vector2f(AccelerationFactors.x * 2, Acceleration.y);
        }
        if (Velocity.x < 4.f && Velocity.x > -4.f && !Moving) {
            Acceleration = sf::Vector2f(0, Acceleration.y);
            Velocity.x = 0.f;
        }
        Moving = false;

    }
}
void PlayerMovement::Gravity(void) {
    Acceleration = sf::Vector2f(Acceleration.x, AccelerationFactors.y);
    
}
void PlayerMovement::Movement(sf::RectangleShape &shape, float yCord) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
        currentTerminalVelocity = fastTerminalVelocity;
    }
    else {
        currentTerminalVelocity = walkingTerminalVelocity;
    }
    if (Velocity.x > currentTerminalVelocity || Velocity.x < -currentTerminalVelocity) {
        
        Velocity.x = Velocity.x > 0 ? Velocity.x = currentTerminalVelocity : Velocity.x = -currentTerminalVelocity;
    }
    else {
        Velocity += Acceleration / 60.f;

    }
    
    if (yCord < 208) {
        shape.move(Velocity * (1.f / 60.f));

    }
    else {
        shape.move(sf::Vector2f(Velocity.x / 60.f, 0.f));
        shape.setPosition(sf::Vector2f(shape.getPosition().x, 208.f));
        Jumping = false;
        Velocity.y = 0;
    }
    cout << "Velocity: " << Velocity.x << ", " << Velocity.y << endl;

}
void PlayerMovement::Jump(sf::RectangleShape& shape, float &yCord) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !Jumping) {
        Jumping = true;
        Velocity.y = -210;
        yCord--;
        Acceleration.y = 70;
    }
}