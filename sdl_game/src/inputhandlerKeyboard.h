//
// Created by simon on 13.11.18.
//

#ifndef SDL_GAME_INPUTHANDLERKEYBOARD_H
#define SDL_GAME_INPUTHANDLERKEYBOARD_H

#include <SDL_types.h>
#include "inputhandler.h"



class InputhandlerKeyboard : public Inputhandler {
public:
    InputhandlerKeyboard() {}

    virtual void setInput(SDL::Event evt) override {
        const SDL::Uint8 *state = SDL::C::SDL_GetKeyboardState(NULL);

        set_WALK_RIGHT(state[SDL::C::SDL_SCANCODE_RIGHT]);
        set_WALK_LEFT(state[SDL::C::SDL_SCANCODE_LEFT]);
        set_JUMP(state[SDL::C::SDL_SCANCODE_SPACE]);
    }
};

#endif //SDL_GAME_INPUTHANDLERKEYBOARD_H
