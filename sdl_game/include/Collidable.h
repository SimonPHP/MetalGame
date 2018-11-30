//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_COLLIDABLE_H
#define SDL_GAME_COLLIDABLE_H

#include <ostream>
#include "Object.h"

class Collidable : public Object {
    /*
     * Wenn wir ein Object haben mit dem man Kollidieren kann hat es eine Hitbox diese kann sich vom Rechteck des
     * Objects unterscheiden. Doch im normalfall nicht deswegen sollten wir hier noch ne bind funktion einbauen
     * die hitbox auf rect weiterleitet*/
protected:
    SDL::Rect *hitbox;
public:
    Collidable();

    const SDL::Rect &getHitbox();

    void setHitbox(const SDL::Rect &hitbox);

    bool checkCollision(Collidable &secCol);

    //ToDo find a nicer way to do this shit
    void bindHitboxToObjectRect(bool rly);

    friend std::ostream &operator<<(std::ostream &os, const Collidable &collidable1);
};

#endif //SDL_GAME_COLLIDABLE_H
