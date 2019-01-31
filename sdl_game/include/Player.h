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
public:
    int getJumpHeight() const;

private:

    int jumpHeight;
public:
    void setJumpHeight(int jumpHeight);

private:

    bool isFalling;
    float gravity;

    bool isJumping = false;

    bool walkLeft = false;
    bool walkRight = false;
    bool willJump = false;
    bool willAttack = false;

    unsigned long kickTimer = 1500;
    unsigned long nextStateAfterKick;
    bool isAttacking;


public:
    float exp = 0;
    EntityState *tmpState;
    Animation *tmpAnimation;
    AnimationFrame *tmpFrame;
    std::vector<Entity*> collidedWith = std::vector<Entity*>(50);
    std::vector<Entity*>::iterator it;
    bool collidedWithEntity;

    bool checkCollisionWithEntity(Entity &entity);

    Level *level;

    void setLevel(Level &level);

    Player();

    ~Player();

    Player(Tileset tileset);

    void events(SDL::Event evt, const float deltaT);

    void checkCollisionWithLevel(Level &level, const float deltaT);

    void update(const float deltaT) override;

    void render(SDL::Renderer &renderer, SDL::Point camera) override;
};

#endif //SDL_GAME_PLAYER_H
