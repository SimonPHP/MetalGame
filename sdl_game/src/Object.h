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
    SDL::Rect rect;
    Tileset tileset;
    std::vector<SDL::Point*> animation;
    std::vector<SDL::Point *>::iterator it;
    int animationMaxTime = 24;
    int animationTimer = 1;
    //SDL::Renderer renderer; falls man das braucht

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
    }

    SDL::Point getPos() {
        return SDL::Point(rect.x, rect.y);
    }

    void setPos(const SDL::Point &pos)
    {
        Object::rect.x = pos.x;
        Object::rect.y = pos.y;
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

    void draw()
    {
        if(animationTimer%animationMaxTime == 0)
        {
            if(++it == animation.end()) //++it weil animation.end() auf ein element hinter dem letzten zeigt
                it = animation.begin();
        }
        tileset.Draw(getPos(), **it);
        animationTimer++;
    }

    friend std::ostream &operator<<(std::ostream &os, const Object &object1) {
        os << "Object rect: (" << object1.rect.x
                << ", " << object1.rect.y
                << ", " << object1.rect.w
                << ", " << object1.rect.h
                << ") ";
        return os;
    }
};

#endif //SDL_GAME_OBJECT_H
