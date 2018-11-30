//
// Created by simon on 30.11.18.
//

#include "Collidable.h"

Collidable::Collidable() {
    hitbox = new SDL::Rect(0, 0, 0, 0); //um sigsiv zu vermeiden wenn man keine hitbox setzt
}

const SDL::Rect &Collidable::getHitbox() {
    return *hitbox;
}

void Collidable::setHitbox(const SDL::Rect &hitbox) {
    *Collidable::hitbox = hitbox;
}

bool Collidable::checkCollision(Collidable &secCol) {
    return hitbox->CollidesWith(*secCol.hitbox);
}

//ToDo find a nicer way to do this shit
void Collidable::bindHitboxToObjectRect(bool rly) {
    hitbox = rly ? &rect : new SDL::Rect(*(new int(hitbox->x)), *(new int(hitbox->y)), *(new int(hitbox->w)),
                                         *(new int(hitbox->h)));
}

std::ostream &operator<<(std::ostream &os, const Collidable &collidable1) {
    os << static_cast<const Object &>(collidable1) << "collidable hitbox: " "rect: (" << collidable1.hitbox->x
       << ", " << collidable1.hitbox->y
       << ", " << collidable1.hitbox->w
       << ", " << collidable1.hitbox->h
       << ") ";
    return os;
}