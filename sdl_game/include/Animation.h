//
// Created by michael on 30.11.18.
//

#ifndef SDL_GAME_ANIMATION_H
#define SDL_GAME_ANIMATION_H

#include "global.h"
#include <SDL_rect.hpp>
#include <SDL_render.hpp>
#include <ostream>
#include <vector>
#include <array>
#include "tileset.h"
#include <iostream>
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

    Animation();

    std::vector<SDL::Point *> StandartPlayer(std::vector<SDL::Point *> anim);
};
#endif //SDL_GAME_ANIMATION_H
