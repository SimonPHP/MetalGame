//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TILESET_H
#define SDL_GAME_TILESET_H

#include "global.h"

#include <iostream>
#include <SDL_render.hpp>

class Tileset {
private:
    SDL::Texture tileset;
    SDL::Point size;
public:
    Tileset();
    Tileset(const SDL::Texture &tileset);
    void Draw(SDL::Point pos, SDL::Point tile);
    void Draw(SDL::Point pos, int tile);
    const Point &getSize() const;
};

#endif //SDL_GAME_TILESET_H
