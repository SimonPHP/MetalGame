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
    double speed = 200;
    double jumpInitAcc = 20;
    double currentAcc = 0;

    double gravitation = -100;

    bool FALL = false;
    int maxJump = 125;
    int maxY = 0;

    void events(SDL::Event evt)
    {
        ih->setInput(evt);
    }

    void update(const int frame, const float deltaT)
    {
        if(rect.y == maxY)
        {
            FALL = true;
            setAnimation(new SDL::Point(2,1));
        }

        if(FALL)
        {
            currentAcc += gravitation*deltaT;
            setY(y - (float)currentAcc);
        }

        if(rect.y > 600-rect.h && currentAcc < 0)
        {
            setY(600-rect.h);
            FALL = false;
        }

        if(ih->input[Inputhandler::Type::RIGHT] > 0)
        {
            setX(x += (deltaT*speed*ih->input[Inputhandler::Type::RIGHT]));
        }
        if(ih->input[Inputhandler::Type::LEFT] > 0)
        {
            setX(x -= (deltaT*speed*ih->input[Inputhandler::Type::LEFT]));
        }
        if(!FALL)
        {
            if(ih->input[Inputhandler::Type::SPACE] > 0 )
            {
                FALL = true;
                maxY = rect.y - maxJump;
                currentAcc = jumpInitAcc;
                setAnimation(new SDL::Point(1,0));
            }
        }
    }
};

#endif //SDL_GAME_PLAYER_H
