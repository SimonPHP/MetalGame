//
// Created by simon on 30.11.18.
//

#ifndef SDL_GAME_LEVEL_H
#define SDL_GAME_LEVEL_H

#include <map>
#include "global.h"
#include "tileset.h"

class Level {
private:
    std::string name;
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

    SDL::Point **ppointLayerBG1;
    SDL::Point **ppointLayerBG2;
    SDL::Point **ppointLayerBG3;
    SDL::Point **ppointLayerFG1;
    SDL::Point **ppointLayerFG2;

    int **ppointLayerAttributes;
    int **ppointLayerEntities;

    std::map<SDL::Point, int> pointLayerAttributes;

    //TODO: entitis layer und iter

    Level(std::string name);
    bool loadLevel(std::string name);
    void processLevelwithTileset(Tileset set);
};

#endif //SDL_GAME_LEVEL_H
