//
// Created by simon on 30.11.18.
//

#include "player.h"

Player::Player() {
    ih = new InputhandlerKeyboard();
}

void Player::events(SDL::Event evt) {
    ih->setInput(evt);
}

void Player::update(const int frame, const float deltaT) {
    if (rect.y == maxY) {
        FALL = true;
    }

    if (FALL) {
        currentAcc += gravitation * deltaT;
        setY(y - (float) currentAcc);
    }

    if (rect.y > 600 - rect.h && currentAcc < 0) {
        setY(600 - rect.h);
        FALL = false;
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
        }
    }
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

const Point &Player::getCamera() const {
    return camera;
}
