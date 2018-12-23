//
// Created by simon on 22.12.18.
//

#ifndef SDL_GAME_ENTITY_H
#define SDL_GAME_ENTITY_H

/*
 * Enity Class
 * Position und render funktion
 * Keine Update funktion da eine Entity auch statisch sein kann.
 * Eine Kiste muss nicht unbedingt geupdatet werden.
 * */


#include "global.h"
#include "Level.h"

class Entity{
protected:
    float x, y;
    float w, h;
    SDL::Rect *boundaries;
    SDL::Rect *hitboxes;

    uint32_t boundariesCount = 0;
    uint32_t hitboxesCount = 0;

    struct {
        bool set, left, right, up, down;
    }collisionState;

    std::vector<SDL::Point> checkPoints;
    std::vector<SDL::Point>::iterator it;
public:
    const std::vector<Point> &getCheckPoints() const;

    void setCheckPoints(const std::vector<Point> &checkPoints);

public:
    virtual void render(SDL::Renderer &renderer, SDL::Point camera) = 0;
    virtual void checkCollision(Level &level) = 0;

    void setCollisionLeft();
    void setCollisionRight();
    void setCollisionUp();
    void setCollisionDown();

    void addBoundarie(SDL::Rect rect);
    void addHitbox(SDL::Rect rect);

    float getX() const {
        return x;
    }

    void setX(float x) {
        Entity::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(float y) {
        Entity::y = y;
    }

    float getW() const {
        return w;
    }

    void setW(float w) {
        Entity::w = w;
    }

    float getH() const {
        return h;
    }

    void setH(float h) {
        Entity::h = h;
    }
};

#endif //SDL_GAME_ENTITY_H
