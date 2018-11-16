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
        input[Type::LEFT] = state[SDL::C::SDL_SCANCODE_LEFT];
        input[Type::RIGHT] = state[SDL::C::SDL_SCANCODE_RIGHT];
        input[Type::SPACE] = state[SDL::C::SDL_SCANCODE_SPACE];

        switch (evt.type())
        {
            case SDL::Event::Type::KEYDOWN:
                break;
        }
    }
};

#endif //SDL_GAME_INPUTHANDLERKEYBOARD_H
