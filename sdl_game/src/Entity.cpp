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
uint32_t Entity::addState(uint32_t w, uint32_t h) {
    EntityState *newState = new EntityState(w, h);
    stateSet.emplace_back(newState);
    return (uint32_t)(stateSet.size()-1);
}

/*!
 * returns the current entityState
 * @return EntityState
 */
EntityState *Entity::getCurrentState() {
    return this->stateSet[currentState];
}

/*!
 * returns the entityState on the given index
 * @param i
 * @return EntityState
 * @throw std::out_of_range
 */
EntityState *Entity::getStateAt(uint32_t i) {
    return (this->stateSet.at(i));
}

/*!
 * returns width from current entitystate
 * @return w
 */
int Entity::getW() const {
    return this->stateSet[currentState]->getW();
}

/*!
 * returns height from current entitystate
 * @return h
 */
int Entity::getH() const {
    return this->stateSet[currentState]->getH();
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

void Entity::setCurrentState(uint32_t currentState) {
    Entity::currentState = currentState;
}

uint32_t Entity::getCurrentsStateNumber() const {
    return currentState;
}

