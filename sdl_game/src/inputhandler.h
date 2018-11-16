//
// Created by simon on 13.11.18.
//

#ifndef SDL_GAME_INPUTHANDLER_H
#define SDL_GAME_INPUTHANDLER_H


#include <SDL_events.hpp>
#include <map>

class Inputhandler {
public:
    enum class Type : int {
        LEFT       = 0,
        RIGHT      = 1,
        SPACE      = 2,
    };

    std::map<Inputhandler::Type, float> input;

    Inputhandler() {
        input[Type::LEFT] = 0;
        input[Type::RIGHT] = 0;
        input[Type::SPACE] = 0;
    }

    virtual void setInput(SDL::Event evt) = 0;

    const std::map<Type, float> &getInput() const {
        return input;
    }
};

#endif //SDL_GAME_INPUTHANDLER_H
