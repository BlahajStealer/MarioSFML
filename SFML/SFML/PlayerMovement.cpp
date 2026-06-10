#include "PlayerMovement.h"

using namespace std;

int PlayerMovement::FrameRun(sf::Sprite& shape, float yCord, std::vector<std::vector<sf::Sprite>>& sp,
    sprite& s, std::vector<Enemy>& Enemies, sf::Sprite& powerupOnScreen, sf::View cam, int currentLevel, bool MovingPower) {

    VerticalMovement(shape, s);
    Jump(shape, yCord, s);

    Gravity();

    int whatDidYouHit = Movement(shape, yCord, sp, s, Enemies, powerupOnScreen, cam, currentLevel, MovingPower);

    return whatDidYouHit;
}
void PlayerMovement::marioSizeChange(bool inc, sf::Sprite& shape, sprite& s) { //true = up, false = down
    sf::Vector2f currentScale = shape.getScale();

    if (inc) {
        a.powerup.play();
        MarioSize++;
        if (MarioSize == 1) {
            shape.setTexture(s.Mario, false);
            shape.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 32 }));
            
            shape.setPosition({ shape.getPosition().x, shape.getPosition().y  - 16.f});
            

        }
        else if (MarioSize == 2) {
            shape.setTexture(s.Firemario, false);
            shape.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 32 }));
        }
    }
    else {
        a.powerdown.play();
        MarioSize--;

        if (MarioSize < 0) {
            Died = true;
        }
        else if (MarioSize == 0) {
            shape.setTexture(s.SmallMario, false);
            shape.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
            shape.setPosition({ shape.getPosition().x, shape.getPosition().y + 16.f});
        }
        else if (MarioSize == 1) {
            shape.setTexture(s.Mario, false);
            shape.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 32 }));
        }
    }

    shape.setScale(currentScale);
}
void PlayerMovement::VerticalMovement(sf::Sprite &shape, sprite &s) {
    if (!dontMove) {
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
                    case 0: shape.setTexture(s.SmallMario, false); break;
                    case 1: shape.setTexture(s.Mario, false); break;
                    case 2: shape.setTexture(s.Firemario, false); break;
                    }

                }
                Acceleration = sf::Vector2f(0, Acceleration.y);
                Velocity.x = 0.f;
            }
            Moving = false;
            CrouchedAnim(s, shape);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
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
            Crouching = false;

            Moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

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
            Crouching = false;

            Moving = true;

        }
        else {

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
            Crouching = false;

            Moving = false;

        }
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
int PlayerMovement::Movement(sf::Sprite& shape, float yCord,
    std::vector<std::vector<sf::Sprite>>& Sprites, sprite& s,
    std::vector<Enemy>& enemies, sf::Sprite& powerupOnScreen,
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
        Velocity.x = Velocity.x > 0 ? currentTerminalVelocity : -currentTerminalVelocity;
    }
    else {
        Velocity += Acceleration / 60.f;
    }

    shape.move(sf::Vector2f(Velocity.x / 60.f, 0));

    int playerTileX = static_cast<int>(shape.getPosition().x / 16.f);
    int playerTileY = static_cast<int>(shape.getPosition().y / 16.f);

    int startY = std::max(0, playerTileY - 2);
    int endY = std::min(static_cast<int>(std::size(Sprites)) - 1, playerTileY + 2);
    int startX = std::max(0, playerTileX - 2);
    int endX = std::min(static_cast<int>(std::size(Sprites[0])) - 1, playerTileX + 3);

    for (int i = startY; i <= endY; i++) {
        for (int f = startX; f <= endX; f++) {
            sf::FloatRect shapeBounds = getHitbox(shape);
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();

            if (whatCanIHit(Sprites[i][f], s)) {
                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {
                float previousLeft = shapeBounds.position.x - Velocity.x / 60.f;
                float previousRight = previousLeft + shapeBounds.size.x;

                bool wasOutsideX = (previousRight <= spriteBounds.position.x || previousLeft >= (spriteBounds.position.x + spriteBounds.size.x));

                if (wasOutsideX) {
                    if (&Sprites[i][f].getTexture() == &s.Coin) {
                        WhatDidYouHit = 3;
                        Sprites[i][f].setTexture(currentLevel == 0 ? s.Sky : s.SkyUG);
                    }
                    else if ((&Sprites[i][f].getTexture() == &s.PipeBLSWD || &Sprites[i][f].getTexture() == &s.PipeTLSWD) && Grounded) {
                        WhatDidYouHit = 5;
                    }
                    else if (&Sprites[i][f].getTexture() == &s.Flagpole || &Sprites[i][f].getTexture() == &s.FlagR || &Sprites[i][f].getTexture() == &s.TopFlag) {
                        WhatDidYouHit = 6;
                        Velocity = { 0.f, 0.f };
                    }
                    else if (&Sprites[i][f].getTexture() == &s.Axe) {
                        WhatDidYouHit = 7;


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
    playerTileX = static_cast<int>(shape.getPosition().x / 16.f);
    playerTileY = static_cast<int>(shape.getPosition().y / 16.f);

    startY = std::max(0, playerTileY - 2);
    endY = std::min(static_cast<int>(std::size(Sprites)) - 1, playerTileY + 2);
    startX = std::max(0, playerTileX - 2);
    endX = std::min(static_cast<int>(std::size(Sprites[0])) - 1, playerTileX + 3);
    bool yCollided = false;

    for (int i = startY; i <= endY; i++) {
        for (int f = startX; f <= endX; f++) {
            sf::FloatRect shapeBounds = getHitbox(shape);
            sf::FloatRect spriteBounds = Sprites[i][f].getGlobalBounds();

            if (whatCanIHit(Sprites[i][f], s)) {

                continue;
            }
            else if (shapeBounds.findIntersection(spriteBounds)) {
                float previousTop = shapeBounds.position.y - Velocity.y / 60.f;
                float previousBottom = previousTop + shapeBounds.size.y;

                bool wasOutsideY = (previousBottom <= spriteBounds.position.y || previousTop >= (spriteBounds.position.y + spriteBounds.size.y));

                if (wasOutsideY) {
                    yCollided = true;
                    if (&Sprites[i][f].getTexture() == &s.Coin) {
                        WhatDidYouHit = 3;
                        switch (currentLevel) {
                        case 0:
                            Sprites[i][f].setTexture(s.Sky);
                            break;
                        case 1:
                            Sprites[i][f].setTexture(s.SkyUG);
                            break;

                        }
                    }
                    else {
                        if (Velocity.y >= 0) {
                            Grounded = true;
                            Jumping = false;
                            Velocity.y = 0;

                            shape.setPosition({ shape.getPosition().x, spriteBounds.position.y - shapeBounds.size.y });

                            if ((&shape.getTexture() == &s.FiremarioJump || &shape.getTexture() == &s.MarioJump || &shape.getTexture() == &s.SmallMarioJump) && !movingPower) {
                                switch (MarioSize) {
                                case 0: shape.setTexture(s.SmallMario); break;
                                case 1: shape.setTexture(s.Mario); break;
                                case 2: shape.setTexture(s.Firemario); break;
                                }
                            }
                            if (Crouching && (&Sprites[i][f].getTexture() == &s.PipeTLD || &Sprites[i][f].getTexture() == &s.PipeTRD)) {
                                WhatDidYouHit = 5;
                                if (&Sprites[i][f].getTexture() == &s.PipeTLD) {
                                    MarioSize == 0 ?
                                        shape.setPosition({ Sprites[i][f].getPosition().x + 16.f, Sprites[i][f].getPosition().y - 16 })
                                    :
                                        shape.setPosition({ Sprites[i][f].getPosition().x + 16.f, Sprites[i][f].getPosition().y - 32 });

                                }
                                else {
                                    MarioSize == 0 ?
                                        shape.setPosition({ Sprites[i][f].getPosition().x, Sprites[i][f].getPosition().y - 16 })
                                        :
                                        shape.setPosition({ Sprites[i][f].getPosition().x, Sprites[i][f].getPosition().y - 32 });

                                }
                            }
                            else if (&Sprites[i][f].getTexture() == &s.Axe) {
                                WhatDidYouHit = 7;


                            }
                            else {
                                shape.move({ 0, -Velocity.y / 60.f });
                            }
                        }
                        else {
                            shape.setPosition({ shape.getPosition().x, spriteBounds.position.y + spriteBounds.size.y });
                            Velocity.y = 0;
                            Grounded = false;
                            JumpingFrames = 31;

                            sf::Sprite tempSprite = sf::Sprite(s.Sky, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));
                            tempSprite.setPosition(Sprites[i][f].getPosition());

                            if ((&Sprites[i][f].getTexture() == &s.BreakableBrick || &Sprites[i][f].getTexture() == &s.BreakableBrickUG) && MarioSize != 0) {
                                tempSprite.setTexture(currentLevel == 0 ? s.Sky : s.SkyUG);
                                Sprites[i][f] = tempSprite;
                                WhatDidYouHit = 1;
                            }
                            else if (&Sprites[i][f].getTexture() == &s.LuckyBlock) {
                                if (currentLevel == 0) { tempSprite.setTexture(s.CoinedLB); }
                                else { tempSprite.setTexture(s.CoinedLBUG); }
                                sentCoin = true;
                                JustHitBlock = tempSprite.getPosition();
                                Sprites[i][f] = tempSprite;
                                WhatDidYouHit = 2;
                            }
                            else if (&Sprites[i][f].getTexture() == &s.LuckyBlockPU) {
                                if (currentLevel == 0) { tempSprite.setTexture(s.CoinedLB); }
                                else { tempSprite.setTexture(s.CoinedLBUG); }
                                switch (MarioSize) {
                                case 0: powerupOnScreen.setTexture(s.Mushroom); break;
                                default: powerupOnScreen.setTexture(s.Fireflower); break;
                                }
                                sentPowerup = true;
                                powerupOnScreen.setPosition(Sprites[i][f].getPosition());
                                Sprites[i][f] = tempSprite;
                                WhatDidYouHit = 4;
                            }
                        }
                    }
                    
                }
            }
        }
    }

    for (int i = 0; i < std::size(enemies); i++) {
        sf::FloatRect shapeBounds = getHitbox(shape);
        sf::FloatRect enemyBounds = enemies[i].getSprite().getGlobalBounds();
        if (auto intersection = shapeBounds.findIntersection(enemyBounds)) {
            float previousBottom = (shapeBounds.position.y - Velocity.y / 60.f) + shapeBounds.size.y;
            bool wasAbove = previousBottom <= enemyBounds.position.y;
            if (wasAbove || Velocity.y > 30.f) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                    Velocity.y = (Velocity.y > 0) ? -200 : Velocity.y - 75;
                }
                else {
                    Velocity.y = (Velocity.y > 0) ? -150 : Velocity.y - 60;
                }
                enemies[i].setSprite().setPosition({ 10000000.f, 10000000.f });
            }
        }
    }

    if (!invincible) {
        for (int i = 0; i < std::size(enemies); i++) {
            sf::FloatRect shapeBounds = getHitbox(shape);
            sf::FloatRect enemyBounds = enemies[i].getSprite().getGlobalBounds();
            if (auto intersection = shapeBounds.findIntersection(enemyBounds)) {
                if (intersection->size.x < intersection->size.y) {
                    marioSizeChange(false, shape, s);
                    switchInvincible();
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

    if (yCollided && Velocity.y == 0) {
        Grounded = true;
    }
    else {
        Grounded = false;
    }

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
        TempFireball.setPosition({ shape.getPosition().x, shape.getPosition().y + 8 });
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

void PlayerMovement::WalkingAnim(sprite& s, sf::Sprite& shape) {
    framesPast++;
    




    if (framesPast >= 4) {
        switch (MarioSize) {
        case 0:
            switch (next) {
            case 1:
                shape.setTexture(s.SmallMarioWalk1, false);
                next++;
                break;
            case 2:
                if (&shape.getTexture() == &s.SmallMarioWalk3) {
                    next--;
                }
                else {
                    shape.setTexture(s.SmallMarioWalk3, false); 
                    next++;
                }
                shape.setTexture(s.SmallMarioWalk2, false); 
                break;
            case 3:
                shape.setTexture(s.SmallMarioWalk3, false); 
                next--;
                break;
            }
            break;
        case 1:
            switch (next) {
            case 1:
                shape.setTexture(s.MarioWalk1, false);
                next++;
                break;
            case 2:
                if (&shape.getTexture() == &s.MarioWalk3) {
                    next--;
                }
                else {
                    shape.setTexture(s.MarioWalk3, false);
                    next++;
                }
                shape.setTexture(s.MarioWalk2, false); 
                break;
            case 3:
                shape.setTexture(s.MarioWalk3, false); 
                next--;
                break;
            }
            break;
        case 2:
            switch (next) {
            case 1:
                shape.setTexture(s.FiremarioWalk1, false); 
                next++;
                break;
            case 2:
                if (&shape.getTexture() == &s.FiremarioWalk3) {
                    next--;
                }
                else {
                    shape.setTexture(s.FiremarioWalk3, false); 
                    next++;
                }
                shape.setTexture(s.FiremarioWalk2, false); 
                break;
            case 3:
                shape.setTexture(s.FiremarioWalk3, false); 
                next--;
                break;
            }
            break;
        }
        framesPast = 0;
    }
}
void PlayerMovement::StoppingAnim(sprite& s, sf::Sprite& shape) {
    switch (MarioSize) {
    case 0:
        shape.setTexture(s.SmallMarioStop, false); 
        break;
    case 1:
        shape.setTexture(s.MarioStopping, false); 
        break;
    case 2:
        shape.setTexture(s.FiremarioStopping, false);
        break;
    }
}

void PlayerMovement::CrouchedAnim(sprite& s, sf::Sprite& shape) {
    switch (MarioSize) {
    case 1: {
        sf::Sprite tempSprite(s.MarioCrouched);
        tempSprite.setPosition(shape.getPosition());
        shape = tempSprite;

        break;
    }

    case 2: {
        sf::Sprite tempSprite(s.FiremarioCrouched);
        tempSprite.setPosition(shape.getPosition());
        shape = tempSprite;
        break;
    }

    }
}

bool PlayerMovement::whatCanIHit(sf::Sprite Sprite, sprite &s) {
    if (&Sprite.getTexture() == &s.Sky || &Sprite.getTexture() == &s.SkyUG || &Sprite.getTexture() == &s.FlagL || &Sprite.getTexture() == &s.TreeStem || &Sprite.getTexture() == &s.Chain || &Sprite.getTexture() == &s.Lava || &Sprite.getTexture() == &s.LavaBase) {
        return true;
    }
    else {
        return false;
    }
}