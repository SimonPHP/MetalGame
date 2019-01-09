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

public:
    Creature();
};

#endif //SDL_GAME_CREATURE_H
