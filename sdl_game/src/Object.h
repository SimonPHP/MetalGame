//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include <SDL_rect.hpp>
#include <SDL_render.hpp>
#include <ostream>
#include <vector>

#include "tileset.h"

class Object {
    /*
     * Da wir wahrscheinlich nur Rechteckige Objecte haben werden können wir die Position und maße direkt aus einem
     * Rect bestimmen.
     * Jedes Object sollte malbar sein eventeull noch ne funktion fürs kurzeitige aussetzen diese objectes bereitstellen
     * Mit den Texturen habe ich grade ein problem da wir ja alles von Tiles Rendern lassen müsste man dem Object
     * das Tileset mitgeben und die Position der Grafik dieses Objectes.
     * Also am besten eine Referenz auf die einmal geladene Texture so das sie nicht für jedes Object einzeln
     * gespeichert wird. Und die größe und Position noch mitgeben und schaune ob es dort abweichungen geben kann.
     * */
protected:
    float x, y;
    SDL::Rect rect;
    Tileset tileset;
    std::vector<SDL::Point*> animation;
    std::vector<SDL::Point *>::iterator it;
    int animationMaxTime = 12;  //eventuell noch mit ins animation array nehmen damit verschiedene sprites
                                // unterschiedlich lang geladen bleiben können
    int animationTimer = 1;

public:
    Object() {
        animation.push_back(new SDL::Point(0,0)); //erstes tile als standard
        it = animation.begin();
    }

    const SDL::Rect &getRect() {
        return rect;
    }

    void setRect(const SDL::Rect &rect) {
        Object::rect = rect;
        x = rect.x;
        y = rect.y;
    }

    SDL::Point getPos() {
        return SDL::Point(rect.x, rect.y);
    }

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    void setPos(const SDL::Point &pos)
    {
        Object::rect.x = pos.x;
        Object::rect.y = pos.y;
    }

    void setPos(float _x, float _y)
    {
        x = _x;
        y = _y;

        Object::rect.x =(int)_x;
        Object::rect.y = (int)_y;
    }

    void setX(float x) {
        Object::x = x;
        Object::rect.x = x;
    }

    void setY(float y) {
        Object::y = y;
        Object::rect.y = y;
    }

    const Tileset &getTileset() const {
        return tileset;
    }

    void setTileset(const Tileset &tileset) {
        Object::tileset = tileset;
    }

    const std::vector<SDL::Point *> &getAnimation() const {
        return animation;
    }

    void setAnimation(const std::vector<SDL::Point *> &animation) {
        Object::animation = animation;
        animationTimer = 1;
        it = Object::animation.begin();
    }

    void setAnimation(SDL::Point *animation) {
        Object::animation.clear();
        Object::animation.push_back(animation);
        animationTimer = 1;
        it = Object::animation.begin();
    }

    void draw()
    {
        //wenn nur ein sprite dann ist das hier unten unnötig noch irgendwie umbauen
        if(animationTimer%animationMaxTime == 0)
        {
            if(++it == animation.end()) //++it weil animation.end() auf ein element hinter dem letzten zeigt
                it = animation.begin();
        }
        tileset.Draw(getPos(), **it);
        animationTimer++;
    }

    friend std::ostream &operator<<(std::ostream &os, const Object &object1) {
        os << "Object rect: (" << object1.x
                << ", " << object1.y
                << ", " << object1.rect.w
                << ", " << object1.rect.h
                << ") ";
        return os;
    }
};

#endif //SDL_GAME_OBJECT_H
