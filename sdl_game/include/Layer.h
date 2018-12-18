//
// Created by simon on 30.11.18.
//

#ifndef SDL_GAME_LAYER_H
#define SDL_GAME_LAYER_H

#include "global.h"

class Layer {
private:
    u_int32_t **layerData;
public:
    Layer(u_int32_t **layerData);
    bool loadLayer(u_int32_t **layerData);
};


#endif //SDL_GAME_LAYER_H
