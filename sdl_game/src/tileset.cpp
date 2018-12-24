//
// Created by simon on 30.11.18.
//

#include "tileset.h"
#include <iostream>
#include <SDL_render.hpp>

Tileset::Tileset() {}

Tileset::Tileset(const SDL::Texture &tileset, const SDL::Point &size) : tileset(tileset), size(size) {
    this->realSize = SDL::Point(tileset.w/size.x, tileset.h/size.y);
}

void Tileset::Draw(SDL::Point pos, SDL::Point tile)
{
    tileset.DrawSprite(pos, size, tile);
}

void Tileset::Draw(SDL::Point pos, int tile)
{
    this->Draw(pos, SDL::Point(tile % size.x, tile / size.y));
}

const Point &Tileset::getSize() const {
    return size;
}

const Point &Tileset::getRealSize() const {
    return realSize;
}
