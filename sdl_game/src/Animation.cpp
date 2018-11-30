//
// Created by simon on 30.11.18.
//

#include "Animation.h"

Animation::Animation(){}

std::vector<SDL::Point *> Animation::StandartPlayer(std::vector<SDL::Point *> anim) {
    anim.push_back(new SDL::Point(1, 0));
    anim.push_back(new SDL::Point(2, 0));
    anim.push_back(new SDL::Point(3, 0));

    return anim;
}
