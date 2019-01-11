//
// Created by simon on 22.12.18.
//

#ifndef SDL_GAME_ENTITY_H
#define SDL_GAME_ENTITY_H

/*
 * Enity Class
 * Position und render funktion
 * Keine Update funktion da eine Entity auch statisch sein kann.
 * Eine Kiste muss nicht unbedingt geupdatet werden.
 * */

#include "global.h"
#include "Level.h"
#include "EntityState.h"

class Entity{
protected:
    //std::vector<EntityState *> stateSet;
    //std::vector<EntityState *>::iterator currentState;

    EntityState *stateSet;
    uint32_t currentState = 0; //pos of currentState
    uint32_t maxStates = 0;

    float x, y;

    struct {
        bool set, left, right, up, down;
    }collisionState;

public:
    virtual void checkCollision(Level &level) = 0;
    virtual void update(const float deltaT) = 0;
    virtual void render(SDL::Renderer &renderer, SDL::Point camera) = 0;

    EntityState* addState(uint32_t w, uint32_t h);

    EntityState* getCurrenState();
    EntityState* getState(uint32_t i);

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);

    int getW() const; //from currentState
    int getH() const; //from currentState

    void setCollisionLeft();
    void setCollisionRight();
    void setCollisionUp();
    void setCollisionDown();
};

#endif //SDL_GAME_ENTITY_H
