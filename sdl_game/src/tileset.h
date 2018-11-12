//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TILESET_H
#define SDL_GAME_TILESET_H

#include <SDL_render.hpp>
#include <iostream>

class Tileset {
private:
    SDL::Texture tileset;
    SDL::Point size;
public:
    Tileset() {}
    Tileset(const SDL::Texture &tileset, const SDL::Point &size) : tileset(tileset), size(size) {}
    void Draw(SDL::Point pos, SDL::Point tile)
    {
        tileset.DrawSprite(pos, size, tile);
    }
};

#endif //SDL_GAME_TILESET_H
