//
// Created by simon on 13.11.18.
//

#ifndef SDL_GAME_INPUTHANDLERKEYBOARD_H
#define SDL_GAME_INPUTHANDLERKEYBOARD_H

#include "global.h"
#include <SDL_types.h>
#include "inputhandler.h"

class InputhandlerKeyboard : public Inputhandler {
public:
    InputhandlerKeyboard();
    virtual void setInput(SDL::Event evt) override;
};

#endif //SDL_GAME_INPUTHANDLERKEYBOARD_H
