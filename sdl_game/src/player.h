//
// Created by simon on 16.11.18.
//

#ifndef SDL_GAME_PLAYER_H
#define SDL_GAME_PLAYER_H

#include "Collidable.h"
#include "inputhandler.h"
#include "inputhandlerKeyboard.h"
#include "SDL.hpp"

class Player : public Collidable
{
public:
    Player() {
        ih = new InputhandlerKeyboard();
    }

    Inputhandler *getIh() const {
        return ih;
    }

    void setIh(Inputhandler *ih) {
        Player::ih = ih;
    }
    double getSpeed() const {
        return speed;
    }

    void setSpeed(double speed) {
        Player::speed = speed;
    }

    int getMaxJump() const {
        return maxJump;
    }

    void setMaxJump(int maxJump) {
        Player::maxJump = maxJump;
    }

    Inputhandler *ih;
    double speed = 2;

    bool JUMP = false;
    bool FALL = false;
    int maxJump = 125;
    int maxY = 0;

    void events(SDL::Event evt)
    {
        ih->setInput(evt);
    }

    void update()
    {
        if(rect.y == maxY)
        {
            JUMP = false;
            FALL = true;
            setAnimation(new SDL::Point(2,1));
        }

        if(rect.y == 600)
            FALL = false;

        if(JUMP)
        {
            rect.y -= 5;
        }
        if(FALL)
        {
            rect.y += 5;
        }

        if(ih->input[Inputhandler::Type::RIGHT] > 0)
        {
            rect.x += speed*ih->input[Inputhandler::Type::RIGHT];
        }
        if(ih->input[Inputhandler::Type::LEFT] > 0)
        {
            rect.x -= speed*ih->input[Inputhandler::Type::LEFT];
        }
        if(!FALL && !JUMP)
        {
            if(ih->input[Inputhandler::Type::SPACE] > 0 )
            {
                JUMP = true;
                maxY = rect.y - maxJump;
                setAnimation(new SDL::Point(1,0));
            }
        }
    }
};

#endif //SDL_GAME_PLAYER_H
