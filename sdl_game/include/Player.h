//
// Created by simon on 22.12.18.
//

#ifndef SDL_GAME_PLAYER_H
#define SDL_GAME_PLAYER_H

#include "Creature.h"
#include "inputhandler.h"
#include "Level.h"

class Player : public Creature
{
private:
    Inputhandler *ih;

    float speed;

    float currentAccX;
    float currentAccY;

    bool isFalling;
    float gravity;

    bool isJumping = false;
    bool isDoubleJumping = false;

    bool walkLeft = false;
    bool walkRight = false;

    timeval doubleJumpTimerTime;
    timeval curTime;
    timeval doubleJumpTimer;

public:

    EntityState *tmpState;
    Animation *tmpAnimation;
    AnimationFrame *tmpFrame;

    float getSpeed() const;

    void setSpeed(float speed);

    float getGravity() const;

    void setGravity(float gravity);

    Player();

    ~Player();

    Player(Tileset tileset);

    void events(SDL::Event evt);

    void checkCollisionWithLevel(Level &level, float deltaT);

    void update(const float deltaT) override;

    void render(SDL::Renderer &renderer, SDL::Point camera) override;
};

#endif //SDL_GAME_PLAYER_H
