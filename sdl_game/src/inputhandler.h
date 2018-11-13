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
        WALK_LEFT       = 0,
        WALK_RIGHT      = 1,
        JUMP            = 2,
    };

    std::map<Inputhandler::Type, float> input;

    Inputhandler() {
        input[Type::WALK_LEFT] = 0;
        input[Type::WALK_RIGHT] = 0;
        input[Type::JUMP] = 0;
    }

    virtual void setInput(SDL::Event evt) = 0;

    const std::map<Type, float> &getInput() const {
        return input;
    }

    void set_WALK_LEFT(float intensitiy)
    {
        input[Type::WALK_LEFT] = intensitiy;
    }
    void set_WALK_RIGHT(float intensitiy)
    {
        input[Type::WALK_RIGHT] = intensitiy;
    }
    void set_JUMP(float intensitiy)
    {
        input[Type::JUMP] = intensitiy;
    }
};

#endif //SDL_GAME_INPUTHANDLER_H
