//
// Created by simon on 24.01.19.
//

#include <Enemy.h>

#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(Tileset tileset) {
    this->currentAccY = 0;
    this->currentAccX = 10;
    this->speed = 25;

    this->walkRight = true;
    this->walkLeft = false;

    this->addState(3,1);
    this->addState(3,1);

    unsigned int t1 = 500; //500ms

    this->getState(0)->createAnimation(tileset);

    this->getState(0)->getAnimation()->addAnimationFrame(t1);
    this->getState(0)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,0), SDL::Point(7,13));
    this->getState(0)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(1,0), SDL::Point(8,13));
    this->getState(0)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(2,0), SDL::Point(9,13));

    this->getState(0)->getAnimation()->addAnimationFrame(t1);
    this->getState(0)->getAnimation()->getAnimationFrames()[1].addSpritePoint(SDL::Point(0,0), SDL::Point(10,13));
    this->getState(0)->getAnimation()->getAnimationFrames()[1].addSpritePoint(SDL::Point(1,0), SDL::Point(11,13));
    this->getState(0)->getAnimation()->getAnimationFrames()[1].addSpritePoint(SDL::Point(2,0), SDL::Point(12,13));

    t1 = 100;

    this->getState(1)->createAnimation(tileset);

    this->getState(1)->getAnimation()->addAnimationFrame(t1);
    this->getState(1)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,0), SDL::Point(7,13));
    this->getState(1)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(1,0), SDL::Point(8,13));
    this->getState(1)->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(2,0), SDL::Point(9,13));

    this->getState(1)->getAnimation()->addAnimationFrame(t1);
    this->getState(1)->getAnimation()->getAnimationFrames()[1].addSpritePoint(SDL::Point(0,0), SDL::Point(10,13));
    this->getState(1)->getAnimation()->getAnimationFrames()[1].addSpritePoint(SDL::Point(1,0), SDL::Point(11,13));
    this->getState(1)->getAnimation()->getAnimationFrames()[1].addSpritePoint(SDL::Point(2,0), SDL::Point(12,13));

    this->getState(1)->addHitbox(SDL::Rect(0,0,48,16));
}


void Enemy::render(SDL::Renderer &renderer, SDL::Point camera) {
    if(this->currentState == 1)
    {
        renderer.SetDrawColor(Color(255,0,0));
        renderer.FillRect(SDL::Rect(this->getX()-camera.x, this->getY()-camera.y, 48, 16));
    }
    this->getCurrentState()->render(renderer, SDL::Point((int) x, (int) y) - camera);
}

void Enemy::update(const float deltaT) {
    this->getCurrentState()->update();

    double maxAbstand = 300;

    double abstand = sqrt(pow((this->p->getX() - this->getX()), 2) + pow((this->p->getY() - this->getY()), 2));

    if((this->currentState != 1) && (abstand < maxAbstand))
    {
        //this->currentAccX += (((abstand*abstand)/2000) + 20);
        //this->currentAccY += (((abstand*abstand)/2000) + 20);
        this->setCurrentState(1);
    }

    if(this->currentState == 1)
    {
        this->currentAccX -= (this->getX()-this->getPlayer()->getX())*deltaT;
        this->currentAccY -= (this->getY()-this->getPlayer()->getY())*deltaT;
    }
    else {
        if (walkRight) {
            if (this->currentAccX < 120) {
                this->currentAccX += speed * deltaT;
            } else {
                walkLeft = true;
                walkRight = false;
            }
        }
        if (walkLeft) {
            if (this->currentAccX > -120) {
                this->currentAccX -= speed * deltaT;
            } else {
                walkLeft = false;
                walkRight = true;
            }
        }
    }

    if( abs(currentAccX) > 200)
        currentAccX = (std::signbit(currentAccX)?-1:1)*200;
    if( abs(currentAccY) > 200)
        currentAccY = (std::signbit(currentAccY)?-1:1) *200;

    this->x += currentAccX * deltaT;
    this->y += currentAccY * deltaT;
}

void Enemy::checkCollisionWithLevel(Level &level, const float deltaT) {

}

Player *Enemy::getPlayer() const {
    return p;
}

void Enemy::setPlayer(Player *p) {
    Enemy::p = p;
}
