//
// Created by simon on 08.01.19.
//

#include <EntityState.h>
#include <sys/time.h>

#include "EntityState.h"

EntityState::EntityState() {} //TODO how to set default???

/*!
 * w and h cannot be change in the runtime because of the animation. create a new entitystate
 * if you wish to do that
 * @param w
 * @param h
 */
EntityState::EntityState(uint32_t w, uint32_t h) : w(w), h(h) {}

Tileset EntityState::getTileset() const {
    return this->animation->getTileset();
}

/*!
 * updates the animation
 */
void EntityState::update() {
    this->animation->update();
}

int EntityState::getW() const {
    return w;
}

int EntityState::getH() const {
    return h;
}

/*!
 * just delegates to the Animation draw method
 * @param pos
 */
void EntityState::draw(SDL::Point pos) {
    printf("tmpFrame in EntityState Render in entitystate.cpp %p\n", &this->animation->animationFrames[0]);
    this->animation->draw(pos);
}

Animation *EntityState::createAnimation(Tileset &tileset) {
    Animation *newAnimation = new Animation(tileset, this->w, this->h);
    printf("newAnimation in EntityState %p\n", newAnimation);

    this->animation = newAnimation; //das setzt aber irgendwie wird danach nichts mehr richtig gemacht

    printf("this->animation in EntityState %p\n", this->animation);

    printf("this(EntityState) %p\n", this);

    return newAnimation; //sobald diese function verlassen wird ist die animation fehlerhaft.
}

EntityState::~EntityState() {
    printf("kille nun entitystate %p\n", this);
}

//TODO move in entityState
/*void Entity::addHitbox(SDL::Rect rect) {

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
}*/