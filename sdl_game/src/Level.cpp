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
    SDL::C::SDL_RWops *rw = SDL::C::SDL_RWFromFile("../assets/levels/1.map", "rb");

    if(rw != NULL)
    {
        uint32_t buf[5] = {};

        SDL_RWread(rw, buf, sizeof(uint32_t), 5);

        this->width = buf[3];
        this->height = buf[4];

        this->width += 5; //überlauf vermeidungs test
        this->height += 5;

        this->layerBG1 = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerBG1[i] = new uint32_t[this->height];

        this->layerBG2 = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerBG2[i] = new uint32_t[this->height];

        this->layerBG3 = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerBG3[i] = new uint32_t[this->height];

        this->layerFG1 = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerFG1[i] = new uint32_t[this->height];

        this->layerFG2 = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerFG2[i] = new uint32_t[this->height];

        this->layerAttributes = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerAttributes[i] = new uint32_t[this->height];

        this->layerEntities = new uint32_t*[this->width];
        for(uint32_t i = 0; i <= this->width; ++i)
            this->layerEntities[i] = new uint32_t[this->height];

        this->width -= 5;
        this->height -= 5;

        for (uint32_t y = 0; y < this->height; y++) {
            for (uint32_t x = 0; x < this->width; x++) {
                SDL_RWread(rw, &this->layerBG1[x][y], sizeof(uint32_t), 1);  // BG1[x][y]
                SDL_RWread(rw, &this->layerBG2[x][y], sizeof(uint32_t), 1);  // BG2[x][y]
                SDL_RWread(rw, &this->layerBG3[x][y], sizeof(uint32_t), 1);  // BG3[x][y]
                SDL_RWread(rw, &this->layerFG1[x][y], sizeof(uint32_t), 1);  // FG1[x][y]
                SDL_RWread(rw, &this->layerFG2[x][y], sizeof(uint32_t), 1);  // FG2[x][y]
                SDL_RWread(rw, &this->layerAttributes[x][y], sizeof(uint32_t), 1);  // Attributes[x][y]
                SDL_RWread(rw, &this->layerEntities[x][y], sizeof(uint32_t), 1);  // Entities[x][y]

                if(this->layerBG1[y][x] > 65535)
                    std::cout << x << ":" << y << "= " << this->layerBG1[y][x] << std::endl;
            }
        }

        SDL::C::Uint32 a;

        std::cout << "DEBUG" << std::endl;

        SDL_RWclose(rw); //gibt manchmal *** Error in `/home/simon/Desktop/Uni sortiert/Semester_5/WPP/MetalGame/sdl_game/cmake-build-debug/sdl_game': corrupted size vs. prev_size: 0x000000000280f440 ***
    }
    return true;
}

uint32_t Level::getWidth() const {
    return width;
}

uint32_t Level::getHeigth() const {
    return height;
};