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

    bool col;

    bool isJumping = false;
    bool isDoubleJumping = false;

    timeval doubleJumpTimerTime;
    timeval curTime;
    timeval doubleJumpTimer;

public:

    EntityState *tmpState;
    Animation *tmpAnimation;
    AnimationFrame *tmpFrame;

    Player();

    ~Player();

    Player(Tileset tileset);

    void events(SDL::Event evt);

    void checkCollisionWithLevel(Level &level, float deltaT);

    void update(const float deltaT) override;

    void render(SDL::Renderer &renderer, SDL::Point camera) override;
};

#endif //SDL_GAME_PLAYER_H
