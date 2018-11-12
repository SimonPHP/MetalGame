//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_COLLIDABLE_H
#define SDL_GAME_COLLIDABLE_H

#include <ostream>
#include "Object.h"

class Collidable : public Object {
    /*
     * Wenn wir ein object haben mit dem man Kollidieren kann hat es eine Hitbox diese kann sich vom Rechteck des
     * Objects unterscheiden. Doch im normalfall nicht deswegen sollten wir hier noch ne bind funktion einbauen
     * die hitbox auf rect weiterleitet*/
protected:
    SDL::Rect *hitbox;
public:
    Collidable() {
        hitbox = new SDL::Rect(0,0,0,0); //um sigsiv zu vermeiden wenn man keine hitbox setzt
    }

    const SDL::Rect &getHitbox() {
        return *hitbox;
    }

    void setHitbox(const SDL::Rect &hitbox) {
        *Collidable::hitbox = hitbox;
    }

    bool checkCollision(Collidable &secCol) {
        return hitbox->CollidesWith(*secCol.hitbox);
    }

    //ToDo find a nicer way to do this shit
    void bindHitboxToObjectRect(bool rly)
    {
        hitbox = rly?&rect:new SDL::Rect(*(new int(hitbox->x)), *(new int(hitbox->y)), *(new int(hitbox->w)), *(new int(hitbox->h)));
    }

    friend std::ostream &operator<<(std::ostream &os, const Collidable &collidable1) {
        os << static_cast<const Object &>(collidable1) << "Collidable hitbox: " "rect: (" << collidable1.hitbox->x
                                                       << ", " << collidable1.hitbox->y
                                                       << ", " << collidable1.hitbox->w
                                                       << ", " << collidable1.hitbox->h
                                                       << ") ";
        return os;
    }
};

#endif //SDL_GAME_COLLIDABLE_H
