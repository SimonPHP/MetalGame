//
// Created by simon on 30.11.18.
//

#include "inputhandler.h"


Inputhandler::Inputhandler() {
    input[Inputhandler::Type::LEFT] = 0;
    input[Inputhandler::Type::RIGHT] = 0;
    input[Inputhandler::Type::SPACE] = 0;
}

const std::map<Inputhandler::Type, float> &Inputhandler::getInput() const {
    return input;
}
