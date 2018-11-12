//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include <SDL_rect.hpp>
#include <SDL_render.hpp>
#include <ostream>

class object {
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
    SDL::Texture texture;
    //SDL::Renderer renderer; falls man das braucht

public:
    object() {}

    const SDL::Rect &getRect() {
        return rect;
    }

    void setRect(const SDL::Rect &rect) {
        object::rect = rect;
    }

    SDL::Point getPos() {
        return SDL::Point(rect.x, rect.y);
    }

    void setPos(const SDL::Point &pos)
    {
        object::rect.x = pos.x;
        object::rect.y = pos.y;
    }

    const SDL::Texture &getTexture() const {
        return texture;
    }

    void setTexture(const SDL::Texture &texture) {
        object::texture = texture;
    }

    void draw()
    {
        //
    }

    friend std::ostream &operator<<(std::ostream &os, const object &object1) {
        os << "Object rect: (" << object1.rect.x
                << ", " << object1.rect.y
                << ", " << object1.rect.w
                << ", " << object1.rect.h
                << ") ";
        return os;
    }
};

#endif //SDL_GAME_OBJECT_H
