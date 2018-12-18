//
// Created by simon on 30.11.18.
//

#include "player.h"

Player::Player() {
    ih = new InputhandlerKeyboard();
}


Inputhandler *Player::getIh() const {
    return ih;
}

void Player::setIh(Inputhandler *ih) {
    Player::ih = ih;
}

double Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(double speed) {
    Player::speed = speed;
}

int Player::getMaxJump() const {
    return maxJump;
}

void Player::setMaxJump(int maxJump) {
    Player::maxJump = maxJump;
}


void Player::events(SDL::Event evt) {
    ih->setInput(evt);
}

void Player::update(const int frame, const float deltaT) {
    if (rect.y == maxY) {
        FALL = true;
        setAnimation(new SDL::Point(2, 1));
    }

    if (FALL) {
        currentAcc += gravitation * deltaT;
        setY(y - (float) currentAcc);
    }

    if (rect.y > 600 - rect.h && currentAcc < 0) {
        setY(600 - rect.h);
        FALL = false;

        //dev env
        std::vector<SDL::Point *> anim;
        anim.push_back(new SDL::Point(1, 0));
        anim.push_back(new SDL::Point(2, 0));
        anim.push_back(new SDL::Point(3, 0));
        setAnimation(anim);
        //dev env end
    }

    if (ih->input[Inputhandler::Type::RIGHT] > 0) {
        setX(x += (deltaT * speed * ih->input[Inputhandler::Type::RIGHT]));
    }
    if (ih->input[Inputhandler::Type::LEFT] > 0) {
        setX(x -= (deltaT * speed * ih->input[Inputhandler::Type::LEFT]));
    }
    if (!FALL) {
        if (ih->input[Inputhandler::Type::SPACE] > 0) {
            FALL = true;
            maxY = rect.y - maxJump;
            currentAcc = jumpInitAcc;
            setAnimation(new SDL::Point(1, 0));
        }
    }
}