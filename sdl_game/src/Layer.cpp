//
// Created by simon on 30.11.18.
//

#include "Layer.h"

Layer::Layer(u_int32_t **layerData) : layerData(layerData) {
    loadLayer(layerData);
}

bool Layer::loadLayer(u_int32_t **layerData) {
    return true;
}
