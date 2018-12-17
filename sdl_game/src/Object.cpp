//
// Created by simon on 30.11.18.
//

#include "Object.h"

    Object::Object() {
        animation.push_back(new SDL::Point(0,0)); //erstes tile als standard
        it = animation.begin();
    }

    const SDL::Rect &Object::getRect() {
        return rect;
    }

    void Object::setRect(const SDL::Rect &rect) {
        Object::rect = rect;
        x = rect.x;
        y = rect.y;
    }

    SDL::Point Object::getPos() {
        return SDL::Point(rect.x, rect.y);
    }

    float Object::getX() {
        return x;
    }

    float Object::getY() {
        return y;
    }

    void Object::setPos(const SDL::Point &pos)
    {
        Object::rect.x = pos.x;
        Object::rect.y = pos.y;
    }

    void Object::setPos(float _x, float _y)
    {
        x = _x;
        y = _y;

        Object::rect.x =(int)_x;
        Object::rect.y = (int)_y;
    }

    void Object::setX(float x) {
        Object::x = x;
        Object::rect.x = x;
    }

    void Object::setY(float y) {
        Object::y = y;
        Object::rect.y = y;
    }

    const Tileset &Object::getTileset() const {
        return tileset;
    }

    void Object::setTileset(const Tileset &tileset) {
        Object::tileset = tileset;
    }

    const std::vector<SDL::Point *> &Object::getAnimation() const {
        return animation;
    }

    void Object::setAnimation(const std::vector<SDL::Point *> &animation) {
        Object::animation = animation;
        animationTimer = 1;
        it = Object::animation.begin();
    }

    void Object::setAnimation(SDL::Point *animation) {
        Object::animation.clear();
        Object::animation.push_back(animation);
        animationTimer = 1;
        it = Object::animation.begin();
    }

    void Object::draw()
    {
        //wenn nur ein sprite dann ist das hier unten unnötig noch irgendwie umbauen
        if(animationTimer%animationMaxTime == 0)
        {
            if(++it == animation.end()) //++pointLayerIt weil animation.end() auf ein element hinter dem letzten zeigt
                it = animation.begin();
        }
        tileset.Draw(getPos(), **it);
        animationTimer++;
    }

    std::ostream &operator<<(std::ostream &os, const Object &object1) {
        os << "Object rect: (" << object1.x
           << ", " << object1.y
           << ", " << object1.rect.w
           << ", " << object1.rect.h
           << ") ";
        return os;
    }