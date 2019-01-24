//
// Created by simon on 24.01.19.
//

#ifndef SDL_GAME_ENIMY_H
#define SDL_GAME_ENIMY_H

#include "Creature.h"

class Enemy : public Creature
{
private:
    bool walkLeft, walkRight;
public:

    Enemy();
    Enemy(Tileset tileset);

    void events(SDL::Event evt, const float deltaT);

    void checkCollisionWithLevel(Level &level, const float deltaT);

    void update(const float deltaT) override;

    void render(SDL::Renderer &renderer, SDL::Point camera) override;
};

#endif //SDL_GAME_ENIMY_H

