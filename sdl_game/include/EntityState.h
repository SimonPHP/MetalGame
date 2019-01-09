//
// Created by simon on 01.01.19.
//

#ifndef SDL_GAME_ENTITYSTATE_H
#define SDL_GAME_ENTITYSTATE_H

#include "Animation.h"

//class Entity; //protoype to use in here because cross reference would give *x not name a type*

class EntityState
{
private:
    //Entity *parent;

    uint32_t w, h; //TODO const??
    SDL::Rect *hitboxes; //TODO write
    uint32_t hitboxesCount = 0;
public:
    Animation *animation; //TODO in private schieben
    EntityState();
    ~EntityState();
    EntityState(uint32_t w, uint32_t h);
    Tileset getTileset() const;
    Animation* createAnimation(Tileset &tileset);
    void update();
    void draw(SDL::Point pos);
    int getW() const;
    int getH() const;
};

#endif //SDL_GAME_ENTITYSTATE_H
