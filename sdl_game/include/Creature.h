//
// Created by simon on 22.12.18.
//

#ifndef SDL_GAME_CREATURE_H
#define SDL_GAME_CREATURE_H

#include "Entity.h"

class Creature : public Entity
{
protected:
    float health;
    float speed;
    float currentAccX;
    float currentAccY;
public:
    float getHealth() const;

    void setHealth(float health);

    float getSpeed() const;

    void setSpeed(float speed);

    float getCurrentAccX() const;

    void setCurrentAccX(float currentAccX);

    float getCurrentAccY() const;

    void setCurrentAccY(float currentAccY);

public:
    Creature();
};

#endif //SDL_GAME_CREATURE_H
