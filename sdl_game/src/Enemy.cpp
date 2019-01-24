//
// Created by simon on 24.01.19.
//

#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(Tileset tileset) {
    this->currentAccY = 0;
    this->currentAccX = 10;
    this->speed = 25;

    this->walkRight = true;
    this->walkLeft = false;

    this->addState(3,1);
    this->getState(0)->createAnimation(tileset);
    unsigned int t1 = 500; //500ms
    this->getState(0)->getAnimation()->addAnimationFrame(t1);
    this->getState(0)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,0), SDL::Point(0,5));
    this->getState(0)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,1), SDL::Point(1,5));
    this->getState(0)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,2), SDL::Point(4,4));

    this->getState(0)->addHitbox(SDL::Rect(0,0,48,16));
}


void Enemy::render(SDL::Renderer &renderer, SDL::Point camera) {
    this->getCurrentState()->render(renderer, SDL::Point((int) x, (int) y) - camera);
}

void Enemy::update(const float deltaT) {
    this->getCurrentState()->update();

    if(walkRight)
    {
        if(this->currentAccX < 120)
        {
            this->currentAccX += speed*deltaT;
        }
        else
        {
            walkLeft = true;
            walkRight = false;
        }
    }
    if(walkLeft)
    {
        if(this->currentAccX > -120)
        {
            this->currentAccX -= speed*deltaT;
        }
        else
        {
            walkLeft = false;
            walkRight = true;
        }
    }

    this->x += currentAccX * deltaT;
    this->y += currentAccY * deltaT;
}

void Enemy::checkCollisionWithLevel(Level &level, const float deltaT) {

}