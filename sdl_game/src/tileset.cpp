//
// Created by simon on 30.11.18.
//

#include "tileset.h"
#include <iostream>
#include <SDL_render.hpp>

Tileset::Tileset() {}

Tileset::Tileset(const SDL::Texture &tileset) : tileset(tileset) {
    this->size = SDL::Point(tileset.width() / 16, tileset.height() / 16);
    this->realSize = SDL::Point(tileset.width() /this->size.x, tileset.height() /this->size.y);
}

void Tileset::Draw(SDL::Point pos, SDL::Point tile)
{
    tileset.DrawSprite(pos, size, tile);
}

void Tileset::Draw(SDL::Point pos, int tile)
{
    this->Draw(pos, SDL::Point(tile % size.x, tile / size.x));
}

const Point &Tileset::getSize() const {
    return size;
}

const Point &Tileset::getRealSize() const {
    return realSize;
}
