//
// Created by michael on 30.11.18.
//

#ifndef SDL_GAME_ANIMATION_H
#define SDL_GAME_ANIMATION_H

#include <SDL_rect.hpp>
#include <SDL_render.hpp>
#include <ostream>
#include <vector>
#include <array>
#include "tileset.h"
#include <iostream>
#include "global.h"
#include "gamebase.h"
#include "Object.h"
#include "Collidable.h"
#include "tileset.h"
#include "inputhandler.h"
#include "inputhandlerKeyboard.h"
#include "player.h"
#include "editor.h"

class Animation {
private:

public:

    Animation(){}

    std::vector<SDL::Point *> StandartPlayer(std::vector<SDL::Point *> anim) {


            anim.push_back(new SDL::Point(1, 0));
            anim.push_back(new SDL::Point(2, 0));
            anim.push_back(new SDL::Point(3, 0));

        return anim;
    }


};
#endif //SDL_GAME_ANIMATION_H
