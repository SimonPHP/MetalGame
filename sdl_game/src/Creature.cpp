//
// Created by simon on 01.01.19.
//

#include <Creature.h>

#include "Creature.h"

Creature::Creature() {

}

float Creature::getHealth() const {
    return health;
}

void Creature::setHealth(float health) {
    Creature::health = health;
}

float Creature::getSpeed() const {
    return speed;
}

void Creature::setSpeed(float speed) {
    Creature::speed = speed;
}

float Creature::getCurrentAccX() const {
    return currentAccX;
}

void Creature::setCurrentAccX(float currentAccX) {
    Creature::currentAccX = currentAccX;
}

float Creature::getCurrentAccY() const {
    return currentAccY;
}

void Creature::setCurrentAccY(float currentAccY) {
    Creature::currentAccY = currentAccY;
}
