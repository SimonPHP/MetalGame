//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_COLLIDABLE_H
#define SDL_GAME_COLLIDABLE_H

#include <ostream>
#include "object.h"

class collidable : public object {
    /*
     * Wenn wir ein object haben mit dem man Kollidieren kann hat es eine Hitbox diese kann sich vom Rechteck des
     * Objects unterscheiden. Doch im normalfall nicht deswegen sollten wir hier noch ne bind funktion einbauen
     * die hitbox auf rect weiterleitet*/
protected:
    SDL::Rect *hitbox;
public:
    collidable() {
        hitbox = new SDL::Rect(0,0,0,0); //um sigsiv zu vermeiden wenn man keine hitbox setzt
    }

    const SDL::Rect &getHitbox() {
        return *hitbox;
    }

    void setHitbox(const SDL::Rect &hitbox) {
        *collidable::hitbox = hitbox;
    }

    bool checkCollision(collidable &secCol) {
        return hitbox->CollidesWith(*secCol.hitbox);
    }

    void bindHitboxToObjectRect(bool rly)
    {
        rly?hitbox = &rect:new SDL::Rect(hitbox->x, hitbox->y, hitbox->w, hitbox->h); //neue hitbox mit werten von alter hitbox und nicht mit referenzen
    }

    friend std::ostream &operator<<(std::ostream &os, const collidable &collidable1) {
        os << static_cast<const object &>(collidable1) << "Collidable hitbox: " "rect: (" << collidable1.hitbox->x
                                                       << ", " << collidable1.hitbox->y
                                                       << ", " << collidable1.hitbox->w
                                                       << ", " << collidable1.hitbox->h
                                                       << ") ";
        return os;
    }
};

#endif //SDL_GAME_COLLIDABLE_H
