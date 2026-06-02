#include "PlayerMovement.h"

using namespace std;

void PlayerMovement::FrameRun(sf::Sprite &shape, float yCord, const std::vector<std::vector<sf::Sprite>>& sp, sprite &s) {
    VerticalMovement();
    Gravity();
    Jump(shape, yCord);
    Movement(shape, yCord, sp, s);
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
    if (!Grounded) {
        Acceleration = sf::Vector2f(Acceleration.x, AccelerationFactors.y);

    }
    
}
void PlayerMovement::Movement(sf::Sprite &shape, float yCord, const std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s) {


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
    shape.move(sf::Vector2f(Velocity.x / 60.f, 0));

    const sf::Texture* tempText = &s.Sky;
    for (int i = 0; i < size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == tempText) {
                continue;
            }
            else if (auto intersection = shapeBounds.findIntersection(spriteBounds)) {
                float previousLeft = shapeBounds.position.x - Velocity.x / 60.f;
                float previousRight = previousLeft + shapeBounds.size.x;


                bool wasOutsideX = (previousRight <= spriteBounds.position.x 
                    || previousLeft >= (spriteBounds.position.x + spriteBounds.size.x));


                if (wasOutsideX) { //Collided on the X
                    shape.move(sf::Vector2f(-Velocity.x / 60.f, 0));
                    Velocity.x = 0;
                    std::cout << "Collided On X!!";
                }
                  
            }

            
        }
    }
    shape.move(sf::Vector2f(0, Velocity.y / 60.f));

    for (int i = 0; i < size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = shape.getGlobalBounds();
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == tempText) {
                continue;
            }
            else if (auto intersection = shapeBounds.findIntersection(spriteBounds)) {
                float previousTop = shapeBounds.position.y - Velocity.y / 60.f;
                float previousBottom = previousTop + shapeBounds.size.y;

                bool wasOutsideY = (previousTop <= spriteBounds.position.y 
                    || previousTop >= (spriteBounds.position.y + spriteBounds.size.y));

                if (wasOutsideY) { //Collided on the Y
                    shape.move(sf::Vector2f(0, -Velocity.y / 60.f));
                    if (Velocity.y >= 0) {
                        Grounded = true;
                        Jumping = false;
                    }
                    else {
                        JumpingFrames = 31;

                    }
                    break;
                    Velocity.y = 0;
                    

                }
                    
            }

            
        }
    }



    std::cout << "Velocity: " << Velocity.x << ", " << Velocity.y << endl;
    std::cout << "Acceleration: " << Acceleration.x << ", " << Acceleration.y << endl;
    std::cout << "Grounded >> " << Grounded << std::endl;
}
void PlayerMovement::Jump(sf::Sprite &shape, float &yCord) {
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && Velocity.y < 0) {
        JumpingFrames = 31;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !Jumping) {
        JumpingFrames = 0;
        Jumping = true;
        Velocity.y = -100;
        yCord--;
        Acceleration.y = 500;
        Grounded = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && Jumping && JumpingFrames < 30) {
        Velocity.y = -100;
        yCord--;
        Acceleration.y = 500;
        Grounded = false;
        Jumping = true;
        JumpingFrames++;
    }
    
}