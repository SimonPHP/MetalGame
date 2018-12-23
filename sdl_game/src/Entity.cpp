//
// Created by simon on 22.12.18.
//

#include <Entity.h>

#include "Entity.h"

void Entity::setCollisionLeft() {
    collisionState.set = true;
    collisionState.left = true;
}

void Entity::setCollisionRight() {
    collisionState.set = true;
    collisionState.right = true;
}

void Entity::setCollisionUp() {
    collisionState.set = true;
    collisionState.up = true;
}

void Entity::setCollisionDown() {
    collisionState.set = true;
    collisionState.down = true;
}

void Entity::addBoundarie(SDL::Rect rect) {
    //boundaries Array vergrößern

    SDL::Rect *oldBoundaries;

    oldBoundaries = new SDL::Rect[this->boundariesCount];
    for(uint32_t i = 0; i < boundariesCount; i++)
    {
        oldBoundaries[i] = this->boundaries[i];
    }

    boundariesCount++;

    this->boundaries = new SDL::Rect[this->boundariesCount];

    for(uint32_t i = 0; i < boundariesCount-1; i++)
    {
        this->boundaries[i] = oldBoundaries[i];
    }
    this->boundaries[boundariesCount-1] = rect;
}

void Entity::addHitbox(SDL::Rect rect) {

    //TODO: doppelte punkte aus dem array löschen

    SDL::Rect *oldHitboxes;

    oldHitboxes = new SDL::Rect[this->hitboxesCount];
    for(uint32_t i = 0; i < hitboxesCount; i++)
    {
        oldHitboxes[i] = this->hitboxes[i];
    }

    hitboxesCount++;

    this->hitboxes = new SDL::Rect[this->hitboxesCount];

    for(uint32_t i = 0; i < hitboxesCount-1; i++)
    {
        this->hitboxes[i] = oldHitboxes[i];
    }
    this->hitboxes[hitboxesCount-1] = rect;

    //TODO: nicht immer das gesammte array löschen wenn eine hitbox hinzu kommt
    checkPoints.clear();

    int p_x = (int)(x/16);
    int p_y = (int)(y/16);

    checkPoints.emplace_back(SDL::Point(p_x+1, p_y+1));

    for(uint32_t i = 0; i < hitboxesCount; i++)
    {
        int xD = hitboxes[i].w/16;
        int yD = hitboxes[i].h/16;

        int xH = hitboxes[i].x/16;
        int yH = hitboxes[i].y/16;

        for(uint32_t xC = 0; xC < xD; xC++)
        {
            for(uint32_t yC = 0; yC < yD; yC++)
            {
                    checkPoints.emplace_back(SDL::Point(xH +xC + 1, yH + yC + 1));
            }
        }
    }
}
