//
// Created by simon on 30.11.18.
//

#include "Level.h"

#include "global.h"

#include <SDL_types.h>

Level::Level(char *name) : name(name) {
    loadLevel(name);
}

bool Level::loadLevel(char *name) {
    SDL::C::SDL_RWops *rw = SDL::C::SDL_RWFromFile("../assets/levels/0.map", "rb");

    if(rw != NULL)
    {
        uint32_t buf[5] = {};

        SDL_RWread(rw, buf, sizeof(uint32_t), 5);

        this->width = buf[3];
        this->height = buf[4];

        this->layerBG1 = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerBG1[i] = new uint32_t[this->height];

        this->layerBG2 = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerBG2[i] = new uint32_t[this->height];

        this->layerBG3 = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerBG3[i] = new uint32_t[this->height];

        this->layerFG1 = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerFG1[i] = new uint32_t[this->height];

        this->layerFG2 = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerFG2[i] = new uint32_t[this->height];

        this->layerAttributes = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerAttributes[i] = new uint32_t[this->height];

        this->layerEntities = new uint32_t*[this->width];
        for(uint32_t i = 0; i < this->width; ++i)
            this->layerEntities[i] = new uint32_t[this->height];

        for (uint32_t y = 0; y < this->height; y++) {
            for (uint32_t x = 0; x < this->width; x++) {
                SDL_RWread(rw, &this->layerBG1[x][y], sizeof(uint32_t), 1);  // BG1[x][y]
                SDL_RWread(rw, &this->layerBG2[x][y], sizeof(uint32_t), 1);  // BG2[x][y]
                SDL_RWread(rw, &this->layerBG3[x][y], sizeof(uint32_t), 1);  // BG3[x][y]
                SDL_RWread(rw, &this->layerFG1[x][y], sizeof(uint32_t), 1);  // FG1[x][y]
                SDL_RWread(rw, &this->layerFG2[x][y], sizeof(uint32_t), 1);  // FG2[x][y]
                SDL_RWread(rw, &this->layerAttributes[x][y], sizeof(uint32_t), 1);  // Attributes[x][y]
                SDL_RWread(rw, &this->layerEntities[x][y], sizeof(uint32_t), 1);  // Entities[x][y]
            }
        }

/*        for (uint32_t y = 0; y < this->height; y++) {
            for (uint32_t x = 0; x < this->width; x++) {
                std::cout << this->layerAttributes[x][y] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "DEBUG" << std::endl;*/

        SDL_RWclose(rw); //gibt manchmal *** Error in `/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/sdl_game': corrupted size vs. prev_size: 0x000000000280f440 ***
    }
    return true;
}

void Level::processLevelwithTileset(Tileset set) {

    this->ppointLayerBG1 = new SDL::Point*[this->width];
    for(uint32_t i = 0; i < this->width; ++i)
        this->ppointLayerBG1[i] = new SDL::Point[this->height];

    this->ppointLayerBG2 = new SDL::Point*[this->width];
    for(uint32_t i = 0; i < this->width; ++i)
        this->ppointLayerBG2[i] = new SDL::Point[this->height];

    this->ppointLayerBG3 = new SDL::Point*[this->width];
    for(uint32_t i = 0; i < this->width; ++i)
        this->ppointLayerBG3[i] = new SDL::Point[this->height];

    this->ppointLayerFG1 = new SDL::Point*[this->width];
    for(uint32_t i = 0; i < this->width; ++i)
        this->ppointLayerFG1[i] = new SDL::Point[this->height];

    this->ppointLayerFG2 = new SDL::Point*[this->width];
    for(uint32_t i = 0; i < this->width; ++i)
        this->ppointLayerFG2[i] = new SDL::Point[this->height];


    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerBG1[x][y] < 65535)
            {
                this->ppointLayerBG1[x][y] = SDL::Point(layerBG1[x][y] % set.getSize().x, layerBG1[x][y] / set.getSize().y);
            }
            else
            {
                this->ppointLayerBG1[x][y] = SDL::Point(65535, 65535);
            }
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerBG1[x][y] < 65535)
            {
                this->ppointLayerBG2[x][y] = SDL::Point(layerBG2[x][y] % set.getSize().x, layerBG2[x][y] / set.getSize().y);
            }
            else
            {
                this->ppointLayerBG2[x][y] = SDL::Point(65535, 65535);
            }
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerBG3[x][y] < 65535)
            {
                this->ppointLayerBG3[x][y] = SDL::Point(layerBG3[x][y] % set.getSize().x, layerBG3[x][y] / set.getSize().y);
            }
            else
            {
                this->ppointLayerBG3[x][y] = SDL::Point(65535, 65535);
            }
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerFG1[x][y] < 65535)
            {
                this->ppointLayerFG1[x][y] = SDL::Point(layerFG1[x][y] % set.getSize().x, layerFG1[x][y] / set.getSize().y);
            }
            else
            {
                this->ppointLayerFG1[x][y] = SDL::Point(65535, 65535);
            }
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerFG2[x][y] < 65535)
            {
                this->ppointLayerFG2[x][y] = SDL::Point(layerFG2[x][y] % set.getSize().x, layerFG2[x][y] / set.getSize().y);
            }
            else
            {
                this->ppointLayerFG2[x][y] = SDL::Point(65535, 65535);
            }
        }
    }


    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerBG1[x][y] < 65535)
            {
                this->pointLayerBG1[SDL::Point(x, y)] = SDL::Point(layerBG1[x][y] % set.getSize().x, layerBG1[x][y] / set.getSize().y);
            }
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerBG2[x][y] < 65535)
                this->pointLayerBG2[SDL::Point(x, y)] = SDL::Point(layerBG2[x][y] % set.getSize().x, layerBG2[x][y] / set.getSize().y);
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerBG3[x][y] < 65535)
                this->pointLayerBG3[SDL::Point(x, y)] = SDL::Point(layerBG3[x][y] % set.getSize().x, layerBG3[x][y] / set.getSize().y);
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerFG1[x][y] < 65535)
                this->pointLayerFG1[SDL::Point(x, y)] = SDL::Point(layerFG1[x][y] % set.getSize().x, layerFG1[x][y] / set.getSize().y);
        }
    }

    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerFG2[x][y] < 65535)
                this->pointLayerFG2[SDL::Point(x, y)] = SDL::Point(layerFG2[x][y] % set.getSize().x, layerFG2[x][y] / set.getSize().y);
        }
    }

    //attributeLayer
    for (uint32_t y = 0; y < this->height; y++) {
        for (uint32_t x = 0; x < this->width; x++) {
            if (this->layerAttributes[x][y] < 65535)
                this->pointLayerAttributes[SDL::Point(x, y)] = this->layerAttributes[x][y];
        }
    }
}

uint32_t Level::getWidth() const {
    return width;
}

uint32_t Level::getHeigth() const {
    return height;
};

