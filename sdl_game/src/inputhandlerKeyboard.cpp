//
// Created by simon on 30.11.18.
//

#include "inputhandlerKeyboard.h"

#include <SDL_types.h>

InputhandlerKeyboard::InputhandlerKeyboard() {}

void InputhandlerKeyboard::setInput(SDL::Event evt) {
    const SDL::Uint8 *state = SDL::C::SDL_GetKeyboardState(NULL);

    input[InputhandlerKeyboard::Type::LEFT] = state[SDL::C::SDL_SCANCODE_LEFT];
    input[InputhandlerKeyboard::Type::RIGHT] = state[SDL::C::SDL_SCANCODE_RIGHT];
    input[InputhandlerKeyboard::Type::SPACE] = state[SDL::C::SDL_SCANCODE_SPACE];

    switch (evt.type()) {
        case SDL::Event::Type::KEYDOWN:
            break;
    }
}