//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "global.h"

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
    Object() ;

    const SDL::Rect &getRect() ;

    void setRect(const SDL::Rect &rect) ;

    SDL::Point getPos() ;

    float getX() ;
    float getY() ;

    void setPos(const SDL::Point &pos);

    void setPos(float _x, float _y);

    void setX(float x) ;

    void setY(float y) ;

    const Tileset &getTileset() const;

    void setTileset(const Tileset &tileset);

    const std::vector<SDL::Point *> &getAnimation() const;

    void setAnimation(const std::vector<SDL::Point *> &animation);

    void setAnimation(SDL::Point *animation);

    void draw();

    friend std::ostream &operator<<(std::ostream &os, const Object &object1);
};

#endif //SDL_GAME_OBJECT_H
