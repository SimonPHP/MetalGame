//
// Created by simon on 22.12.18.
//

#include <Entity.h>

#include "Entity.h"

/*!
 * Creates a new EntityState and add it to the stateSet.
 * @param w
 * @param h
 * @return EntityState*
 */
EntityState *Entity::addState(uint32_t w, uint32_t h) {

    EntityState *newState = new EntityState(w, h);

    EntityState *tmpStateSet = new EntityState[this->maxStates];
    for(uint32_t i = 0; i < this->maxStates; i++)
        tmpStateSet[i] = this->stateSet[i]; //save old states

    this->maxStates++; //inc
    this->stateSet = new EntityState[this->maxStates];

    for(uint32_t i = 0; i < this->maxStates-1; i++)
        this->stateSet[i] = tmpStateSet[i]; //restore states
    this->stateSet[this->maxStates-1] = *newState; //plus new state

    return newState;
}

/*!
 * returns the current entityState
 * @return EntityState
 */
EntityState *Entity::getCurrenState() {
    int cur = 0; //debug point line delete after debugging //TODO debbuging delete
    return &(this->stateSet[currentState]);
}

/*!
 * returns the entityState on the given index
 * @param i
 * @return EntityState
 * @throw out of bounds error
 */
EntityState *Entity::getState(uint32_t i) {
    if(i < this->maxStates)
        return &(this->stateSet[i]);
    throw std::invalid_argument("out of bounds in stateSet");
}

/*!
 * returns width from current entitystate
 * @return w
 */
int Entity::getW() const {
    return this->stateSet[currentState].getW();
}

/*!
 * returns height from current entitystate
 * @return h
 */
int Entity::getH() const {
    return this->stateSet[currentState].getH();
}

//TODO overthink collision
void Entity::setCollisionLeft() {
    collisionState.set = true;
    collisionState.left = true;
}

void Entity::setCollisionRight() {
    collisionState.set = true;
    collisionState.right = true;
}

void Entity::setCollisionUp() {
    collisionState.set = true;
    collisionState.up = true;
}

void Entity::setCollisionDown() {
    collisionState.set = true;
    collisionState.down = true;
}

float Entity::getX() const {
    return x;
}

void Entity::setX(float x) {
    Entity::x = x;
}

float Entity::getY() const {
    return y;
}

void Entity::setY(float y) {
    Entity::y = y;
}


