#include "PlayerMovement.h"

using namespace std;

int PlayerMovement::FrameRun(sf::Sprite &shape, float yCord, std::vector<std::vector<sf::Sprite>>& sp, 
    sprite &s, std::vector<Enemy>& Enemies, sf::Sprite& powerupOnScreen, sf::View cam, int currentLevel
,bool MovingPower) {

    VerticalMovement(shape, s);

    Gravity();

    Jump(shape, yCord, s);

    int whatDidYouHit = Movement(shape, yCord, sp, s, Enemies, powerupOnScreen, cam, currentLevel, MovingPower);

    return whatDidYouHit;
}
void PlayerMovement::marioSizeChange(bool inc, sf::Sprite &shape, sprite &s) { //true = up, false = down
    if (inc) {
        a.powerup.play();
        MarioSize++;
        if (MarioSize == 1) {
            sf::Sprite temp(s.Mario, sf::IntRect({ 0, 0 }, { 16,32 }));
            temp.setPosition({ shape.getPosition().x, shape.getPosition().y - 16 });
            shape = temp;
            
        }
        else if (MarioSize == 2) {
            shape.setTexture(s.Firemario);
        }

    }
    else {
        a.powerdown.play();

        MarioSize--;
        if (MarioSize < 0) {
            Died = true;
        }
        else if (MarioSize == 0) {
            sf::Sprite temp(s.SmallMario, sf::IntRect({ 0, 0 }, { 16,16 }));
            temp.setPosition({shape.getPosition().x, shape.getPosition().y + 16.f});
            shape = temp;
        }
        else if (MarioSize == 1) {
            shape.setTexture(s.Mario);
        }
    }

}
void PlayerMovement::VerticalMovement(sf::Sprite &shape, sprite &s) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        Crouching = true;
        if (Velocity.x > 0) {
            if (Grounded) {
                WalkingAnim(s, shape);

                shape.setScale({ 1.f, 1.f });
            }
            Acceleration = sf::Vector2f(-AccelerationFactors.x * 2, Acceleration.y);
        }
        else if (Velocity.x < 0) {
            if (Grounded) {
                WalkingAnim(s, shape);

                shape.setScale({ -1.f, 1.f });

            }
            Acceleration = sf::Vector2f(AccelerationFactors.x * 2, Acceleration.y);
        }

        if (Velocity.x < 4.f && Velocity.x > -4.f && !Moving) {
            if (Grounded) {
                switch (MarioSize) {
                case 0:
                    shape.setTexture(s.SmallMario);
                    break;
                case 1:
                    shape.setTexture(s.Mario);
                    break;
                case 2:
                    shape.setTexture(s.Firemario);
                    break;
                }
            }
            Acceleration = sf::Vector2f(0, Acceleration.y);
            Velocity.x = 0.f;
        }
        Moving = false;
        CrouchedAnim(s, shape);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        Crouching = false;
        if (Velocity.x > 0) {
            Acceleration = sf::Vector2f(-AccelerationFactors.x * 8, Acceleration.y);
            if (Grounded) {
                StoppingAnim(s, shape);
                shape.setScale({ 1.f, 1.f });
            }
        }
        else {
            if (Grounded) {
                WalkingAnim(s, shape);
                shape.setScale({ -1.f, 1.f });

            }
            if (Sprinting) {
                Acceleration = sf::Vector2f(-AccelerationFactors.x * 1.78, Acceleration.y);

            }
            else {
                Acceleration = sf::Vector2f(-AccelerationFactors.x, Acceleration.y);

            }

        }

        Moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        Crouching = false;

        if (Velocity.x < 0) {
            Acceleration = sf::Vector2f(AccelerationFactors.x * 8, Acceleration.y);
            if (Grounded) {
                StoppingAnim(s, shape);

                shape.setScale({ -1.f, 1.f });

            }
        }
        else {
            if (Grounded) {
                WalkingAnim(s, shape);

                shape.setScale({ 1.f, 1.f });


            }
            if (Sprinting) {
                Acceleration = sf::Vector2f(AccelerationFactors.x * 1.78, Acceleration.y);

            }
            else {
                Acceleration = sf::Vector2f(AccelerationFactors.x, Acceleration.y);

            }

        }

        Moving = true;

    }
    else {
        Crouching = false;

        if (Velocity.x > 0) {
            if (Grounded) {
                WalkingAnim(s, shape);

                shape.setScale({ 1.f, 1.f });
            }
            Acceleration = sf::Vector2f(-AccelerationFactors.x * 2, Acceleration.y);
        }
        else if (Velocity.x < 0) {
            if (Grounded) {
                WalkingAnim(s, shape);

                shape.setScale({ -1.f, 1.f });

            }
            Acceleration = sf::Vector2f(AccelerationFactors.x * 2, Acceleration.y);
        }

        if (Velocity.x < 4.f && Velocity.x > -4.f && !Moving) {
            if (Grounded) {
                switch (MarioSize) {
                case 0:
                    shape.setTexture(s.SmallMario);
                    break;
                case 1:
                    shape.setTexture(s.Mario);
                    break;
                case 2:
                    shape.setTexture(s.Firemario);
                    break;
                }
            }
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
    else {
        Velocity.y = 0;
    }
    
}
int PlayerMovement::Movement(sf::Sprite &shape, float yCord,
    std::vector<std::vector<sf::Sprite>>& Sprites, sprite &s,
    std::vector<Enemy> &enemies, sf::Sprite& powerupOnScreen,
    sf::View cam, int currentLevel, bool movingPower) {
    int WhatDidYouHit = 0;

    for (int i = size(Fireballs) - 1; i >= 0; i--) {
        if (Fireballs[i].Kill) {
            Fireballs[i].~Fireball();
            Fireballs.erase(Fireballs.begin() + i);
        }
        else {
            Fireballs[i].moveFireball(s, Sprites, cam);

        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
        currentTerminalVelocity = fastTerminalVelocity;
        Sprinting = true;
    }
    else {
        currentTerminalVelocity = walkingTerminalVelocity;
        Sprinting = false;

    }
    if (Velocity.x > currentTerminalVelocity || Velocity.x < -currentTerminalVelocity) {
        
        Velocity.x = Velocity.x > 0 ? Velocity.x = currentTerminalVelocity : Velocity.x = -currentTerminalVelocity;
    }
    else {
        Velocity += Acceleration / 60.f;

    }
    shape.move(sf::Vector2f(Velocity.x / 60.f, 0));


    for (int i = 0; i < size(Sprites); i++) {

        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = getHitbox(shape);
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if ((& Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG || &Sprites[i][f].getTexture() == &s.FlagL)) {
                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {
                float previousLeft = shapeBounds.position.x - Velocity.x / 60.f;
                float previousRight = previousLeft + shapeBounds.size.x;


                bool wasOutsideX = (previousRight <= spriteBounds.position.x 
                    || previousLeft >= (spriteBounds.position.x + spriteBounds.size.x));


                if (wasOutsideX) { //Collided on the X

                    std::cout << "Collided On X!!";
                    if (&Sprites[i][f].getTexture() == &s.Coin) {
                        WhatDidYouHit = 3;
                        if (currentLevel == 0) {
                            Sprites[i][f].setTexture(s.Sky);

                        }
                        else if (currentLevel == 1) {
                            Sprites[i][f].setTexture(s.SkyUG);

                        }
                    }
                    else if (&Sprites[i][f].getTexture() == &s.PipeBLSWD || &Sprites[i][f].getTexture() == &s.PipeTLSWD) {
                        WhatDidYouHit = 5;
                    }
                    else if (&Sprites[i][f].getTexture() == &s.Flagpole || &Sprites[i][f].getTexture() == &s.FlagR || &Sprites[i][f].getTexture() == &s.FlagL || &Sprites[i][f].getTexture() == &s.TopFlag) {
                        WhatDidYouHit = 6;
                        Velocity = {0.f, 0.f};
                    }
                    else {
                        shape.move(sf::Vector2f(-Velocity.x / 60.f, 0));
                        Velocity.x = 0;
                    }
                }
                  
            }

            
        }
    }

    shape.move(sf::Vector2f(0, Velocity.y / 60.f));
    for (int i = 0; i < std::size(enemies); i++) {
        sf::FloatRect shapeBounds = getHitbox(shape);
        sf::FloatRect enemyBounds = enemies[i].getSprite().getGlobalBounds();
        if (auto intersection = shapeBounds.findIntersection(enemyBounds)) {
            float previousBottom = (shapeBounds.position.y - Velocity.y / 60.f) + shapeBounds.size.y;
            bool wasAbove = previousBottom <= enemyBounds.position.y;
            bool hittingTopHalf = intersection->position.y < enemyBounds.position.y + enemyBounds.size.y / 2.f;
            if (wasAbove || Velocity.y > 30.f || Velocity.y < -30.f) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                    if (Velocity.y > 0) {
                        Velocity.y = -200;

                    }
                    else {
                        Velocity.y -= 75;
                    }
                }
                else {
                    if (Velocity.y > 0) {
                        Velocity.y = -150;

                    }
                    else {
                        Velocity.y -= 60;
                    }
                    
                }
                enemies[i].setSprite().setPosition({ 10000000.f, 10000000.f }); // stomped
            }
        }
    }
    if (!invincible) {
        for (int i = 0; i < std::size(enemies); i++) {
            sf::FloatRect shapeBounds = getHitbox(shape);
            sf::FloatRect enemyBounds = enemies[i].getSprite().getGlobalBounds();
            if (auto intersection = shapeBounds.findIntersection(enemyBounds)) {
                if (intersection->size.x < intersection->size.y) { // side collision
                    marioSizeChange(false, shape, s);
                    switchInvincible();
                }
            }
        }
    }

    bool yCollided = false;
    for (int i = 0; i < size(Sprites); i++) {
        for (int f = 0; f < size(Sprites[0]); f++) {

            sf::FloatRect shapeBounds = getHitbox(shape);
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();
            if (&Sprites[i][f].getTexture() == &s.Sky || &Sprites[i][f].getTexture() == &s.SkyUG || &Sprites[i][f].getTexture() == &s.Coin || &Sprites[i][f].getTexture() == &s.FlagL) {
                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {
                float previousTop = shapeBounds.position.y - Velocity.y / 60.f;
                float previousBottom = previousTop + shapeBounds.size.y;

                bool wasOutsideY = (previousTop <= spriteBounds.position.y 
                    || previousTop >= (spriteBounds.position.y + spriteBounds.size.y));

                if (wasOutsideY) { //Collided on the Y
                    shape.move(sf::Vector2f(0, -Velocity.y / 60.f));
                    yCollided = true;
                    if (&shape.getTexture() == &s.Coin) {
                        WhatDidYouHit = 3;
                        if (currentLevel == 0) {
                            Sprites[i][f].setTexture(s.Sky);

                        }
                        else if (currentLevel == 1) {
                            Sprites[i][f].setTexture(s.SkyUG);

                        }
                    }
                    if (Velocity.y >= 0) { //Collided going down
                        Grounded = true;
                        Jumping = false;
                        if ((&shape.getTexture() == &s.FiremarioJump || &shape.getTexture() == &s.MarioJump || &shape.getTexture() == &s.SmallMarioJump) && !movingPower)
                            switch (MarioSize) {
                            case 0:
                                shape.setTexture(s.SmallMario);
                                break;
                            case 1:
                                shape.setTexture(s.Mario);
                                break;
                            case 2:
                                shape.setTexture(s.Firemario);
                                break;
                            }
                        if (Crouching && (&Sprites[i][f].getTexture() == &s.PipeTLD || &Sprites[i][f].getTexture() == &s.PipeTRD)) {
                            WhatDidYouHit = 5;
                        }
                    }
                    else { //Collided going up
                        sf::Sprite tempSprite = sf::Sprite(s.Sky, sf::IntRect(
                            sf::Vector2i(0, 0),
                            sf::Vector2i(16, 16)));
                        tempSprite.setPosition(Sprites[i][f].getPosition());

                        if ((&Sprites[i][f].getTexture() == &s.BreakableBrick || &Sprites[i][f].getTexture() == &s.BreakableBrickUG) && MarioSize != 0) {
                            if (currentLevel == 0) {
                                tempSprite.setTexture(s.Sky);

                            }
                            else if (currentLevel == 1) {
                                tempSprite.setTexture(s.SkyUG);

                            }
                            Sprites[i][f] = tempSprite;
                            WhatDidYouHit = 1;
                        }
                        else if (&Sprites[i][f].getTexture() == &s.LuckyBlock) {
                            tempSprite.setTexture(s.CoinedLB);
                            sentCoin = true;
                            JustHitBlock = tempSprite.getPosition();
                            Sprites[i][f] = tempSprite;
                            WhatDidYouHit = 2;

                        }
                        else if (&Sprites[i][f].getTexture() == &s.LuckyBlockPU) {
                            tempSprite.setTexture(s.CoinedLB);
                            switch (MarioSize) {
                            case 0:
                                powerupOnScreen.setTexture(s.Mushroom);
                                break;
                            case 1:
                            case 2:
                                powerupOnScreen.setTexture(s.Fireflower);
                                break;

                            default:
                                powerupOnScreen.setTexture(s.Mushroom);
                                break;

                            }
                            sentPowerup = true;
                            powerupOnScreen.setPosition(sf::Vector2f(Sprites[i][f].getPosition().x, (Sprites[i][f].getPosition().y)));
                            Sprites[i][f] = tempSprite;
                            WhatDidYouHit = 4;
                        }
                        Grounded = false;
                        JumpingFrames = 31;

                    }
                    break;
                    Velocity.y = 0;
                    

                }
                else {
                    Grounded = false;
                }
                
                    
            }
            

            
        }
    }
    if (MarioSize == 2) {
        fireflower(s, shape);

    }

    if (shape.getPosition().y > 270) {
        MarioSize = 1;
        marioSizeChange(false, shape, s);
        Died = true;
    }
    if (yCollided) {
        Grounded = true;
    }
    else {
        Grounded = false;
    }



    std::cout << "Velocity: " << Velocity.x << ", " << Velocity.y << endl;
    std::cout << "Acceleration: " << Acceleration.x << ", " << Acceleration.y << endl;
    std::cout << "Grounded >> " << Grounded << std::endl;
    return WhatDidYouHit;
}
void PlayerMovement::Jump(sf::Sprite &shape, float &yCord, sprite &s) {
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && Velocity.y < 0) {
        JumpingFrames = 31;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !Jumping && Grounded) {
        switch (MarioSize) {
        case 0:
            shape.setTexture(s.SmallMarioJump);
            break;
        case 1:
            shape.setTexture(s.MarioJump);
            break;
        case 2:
            shape.setTexture(s.FiremarioJump);
            break;

        }
        a.jump.play();
        JumpingFrames = 0;
        Jumping = true;
        Velocity.y = -200;
        yCord--;
        Acceleration.y = 1000;
        Grounded = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && Jumping && JumpingFrames < 18) {
        Velocity.y = -200;
        yCord--;
        Acceleration.y = 1000;
        Grounded = false;
        Jumping = true;
        JumpingFrames++;
    }
    
}
sf::FloatRect PlayerMovement::getHitbox(sf::Sprite player) {
    sf::FloatRect bounds = player.getGlobalBounds();
    float shrink = 4.f;
    return sf::FloatRect(
        { bounds.position.x + shrink, bounds.position.y },
        {bounds.size.x - shrink * 2, bounds.size.y}
    );
}
void PlayerMovement::fireflower(sprite &s, sf::Sprite shape) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N) && size(Fireballs) < 2 && !HoldingN) {
        HoldingN = true;
        a.fireball.play();
        sf::Sprite TempFireball(s.Fireball, sf::IntRect(sf::Vector2{4,4}, sf::Vector2i{8, 8}));
        TempFireball.setPosition({ shape.getPosition().x + 8, shape.getPosition().y + 8 });
        int dir;
        Velocity.x < 0 ? dir = -1 : dir = 1;
        if (Velocity.x == 0) {
            if (shape.getScale() == sf::Vector2f(-1.f, 1.f)) {
                dir = -1;
            }
        }
        Fireball tempFB(dir, s);
        tempFB.fb = TempFireball;
        Fireballs.push_back(tempFB);

    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
        HoldingN = false;
    }
}

void PlayerMovement::WalkingAnim(sprite &s, sf::Sprite &shape) {
    framesPast++;
    if (framesPast >= 4) {
        switch (MarioSize) {
        case 0:
            switch (next) {
            case 1:
                shape.setTexture(s.SmallMarioWalk1);
                next++;
                break;
            case 2:
                if (&shape.getTexture() == &s.SmallMarioWalk3) {
                    next--;

                }
                else {
                    shape.setTexture(s.SmallMarioWalk3);
                    next++;
                }
                shape.setTexture(s.SmallMarioWalk2);
                break;
            case 3:
                shape.setTexture(s.SmallMarioWalk3);
                next--;
                break;
            }
            break;
        case 1:
            switch (next) {
            case 1:
                shape.setTexture(s.MarioWalk1);
                next++;
                break;
            case 2:
                if (&shape.getTexture() == &s.MarioWalk3) {
                    next--;

                }
                else {
                    shape.setTexture(s.MarioWalk3);
                    next++;
                }
                shape.setTexture(s.MarioWalk2);
                break;
            case 3:
                shape.setTexture(s.MarioWalk3);
                next--;
                break;
            }
            break;
        case 2:
            switch (next) {
            case 1:
                shape.setTexture(s.FiremarioWalk1);
                next++;
                break;
            case 2:
                if (&shape.getTexture() == &s.FiremarioWalk3) {
                    next--;

                }
                else {
                    shape.setTexture(s.FiremarioWalk3);
                    next++;
                }
                shape.setTexture(s.FiremarioWalk2);
                break;
            case 3:
                shape.setTexture(s.FiremarioWalk3);
                next--;
                break;
            }
            break;
        }
        framesPast = 0;
    }


}
void PlayerMovement::StoppingAnim(sprite &s, sf::Sprite &shape) {
    switch (MarioSize) {
    case 0:
        shape.setTexture(s.SmallMarioStop);
        break;
    case 1:
        shape.setTexture(s.MarioStopping);
        break;
    case 2:
        shape.setTexture(s.FiremarioStopping);
        break;
    }
}
void PlayerMovement::CrouchedAnim(sprite &s, sf::Sprite &shape) {
    switch (MarioSize) {
    case 1:
        shape.setTexture(s.MarioCrouched);
        break;
    case 2:
        shape.setTexture(s.FiremarioCrouched);
        break;
    }
}
