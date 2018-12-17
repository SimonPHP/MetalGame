//
// Created by simon on 30.11.18.
//

#ifndef SDL_GAME_LEVEL_H
#define SDL_GAME_LEVEL_H

#include <map>
#include "global.h"
#include "Layer.h"
#include "tileset.h"

class Level {
private:
    char *name;
    uint32_t width, height;
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

    std::map<SDL::Point, SDL::Point> pointLayerBG1;
    std::map<SDL::Point, SDL::Point> pointLayerBG2;
    std::map<SDL::Point, SDL::Point> pointLayerBG3;
    std::map<SDL::Point, SDL::Point> pointLayerFG1;
    std::map<SDL::Point, SDL::Point> pointLayerFG2;
    std::map<SDL::Point, SDL::Point>::iterator pointLayerIt;

    std::map<SDL::Point, int> pointLayerAttributes;
    std::map<SDL::Point, int>::iterator pointLayerAttributesIt;

    //TODO: entitis layer und iter

    Level(char *name);
    bool loadLevel(char *name);
    void processLevelwithTileset(Tileset set);
};

#endif //SDL_GAME_LEVEL_H
