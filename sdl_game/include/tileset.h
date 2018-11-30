//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TILESET_H
#define SDL_GAME_TILESET_H

#include <iostream>
#include <SDL_render.hpp>

class Tileset {
private:
    SDL::Texture tileset;
    SDL::Point size;
public:
    Tileset();
    Tileset(const SDL::Texture &tileset, const SDL::Point &size);
    void Draw(SDL::Point pos, SDL::Point tile);
};

#endif //SDL_GAME_TILESET_H
