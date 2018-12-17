//
// Created by simon on 30.11.18.
//

#ifndef SDL_GAME_LEVEL_H
#define SDL_GAME_LEVEL_H

#include "global.h"
#include "Layer.h"

class Level {
private:
    char *name;
    uint32_t width, heigth;
public:
    uint32_t getWidth() const;

    uint32_t getHeigth() const;

public:
    uint32_t **layerBG1;
    uint32_t **layerBG2;
    uint32_t **layerBG3;
    uint32_t **layerFG1;
    uint32_t **layerFG2;
    uint32_t **layerAttributes;
    uint32_t **layerEntities;

    Level(char *name);
    bool loadLevel(char *name);
};

#endif //SDL_GAME_LEVEL_H
