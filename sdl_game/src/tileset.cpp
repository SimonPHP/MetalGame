//
// Created by simon on 30.11.18.
//

#include "tileset.h"
#include <iostream>
#include <SDL_render.hpp>

Tileset::Tileset() {}

Tileset::Tileset(const SDL::Texture &tileset, const SDL::Point &size) : tileset(tileset), size(size) {}

void Tileset::Draw(SDL::Point pos, SDL::Point tile)
{
    tileset.DrawSprite(pos, size, tile);
}