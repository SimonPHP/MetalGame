//
// Created by simon on 22.12.18.
//

#include <Entity.h>
#include <inputhandlerKeyboard.h>
#include <Player.h>
#include <sys/time.h>

#define TILESIZE 16

Player::Player(){}

Player::Player(Tileset tileset) {
    ih = new InputhandlerKeyboard();
    currentAccY = 0;
    currentAccX = 0;
    speed = 50;
    gravity = 1000;

    tmpState = this->addState(2, 2);

    this->getCurrenState()->createAnimation(tileset);

    timeval t1;

    t1.tv_usec = 500*1000; //500ms

    this->doubleJumpTimerTime.tv_usec = 50*1000; //50ms

    this->getCurrenState()->getAnimation()->addAnimationFrame(t1);
    this->getCurrenState()->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,0), SDL::Point(0,7));
    this->getCurrenState()->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(0,1), SDL::Point(0,8));
    this->getCurrenState()->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(1,0), SDL::Point(1,7));
    this->getCurrenState()->getAnimation()->getAnimationFrames()[0].addSpritePoint(SDL::Point(1,1), SDL::Point(1,8));

    this->getCurrenState()->addHitbox(SDL::Point(0,0));
    this->getCurrenState()->addHitbox(SDL::Point(0,1));
    this->getCurrenState()->addHitbox(SDL::Point(1,0));
    this->getCurrenState()->addHitbox(SDL::Point(1,1));
}

void Player::events(SDL::Event evt){
    ih->setInput(evt); //ih hat dan die ganzen states vom input
}

void Player::checkCollisionWithLevel(Level &level, float deltaT) {

    //reset collision
    collisionState.set = false;
    collisionState.left = false;
    collisionState.right = false;
    collisionState.up = false;
    collisionState.down = false;

    SDL::Point *collisionPoints = this->getCurrenState()->getCollisionCheckPoints();
    uint32_t collisionPointsCount = this->getCurrenState()->getCollisionCheckPointsCount();

    float moveX = this->currentAccX * deltaT;
    float moveY = this->currentAccY * deltaT;

    if(moveX > TILESIZE || moveX < -TILESIZE)
    {
        printf("x: %f\n", moveX);
    }
    if(moveY > TILESIZE || moveY < -TILESIZE)
    {
        printf("y: %f\n", moveY);
    }

    uint32_t curX = (uint32_t)((this->x) /16);
    uint32_t curY = (uint32_t)((this->y) /16);
    uint32_t nextX = (uint32_t)((this->x + moveX) /16);
    uint32_t nextY = (uint32_t)((this->y + moveY) /16);

    for(uint32_t i = 0; i < collisionPointsCount; i++)
    {
        uint32_t p_xCur = (uint32_t)collisionPoints[i].x + curX;
        uint32_t p_yCur = (uint32_t)collisionPoints[i].y + curY;
        uint32_t p_xNext = (uint32_t)collisionPoints[i].x + nextX;
        uint32_t p_yNext = (uint32_t)collisionPoints[i].y + nextY;

        if(level.ppointLayerAttributes[p_xCur][p_yNext] == 0) //only x
        {
            this->collisionState.set = true;
            if(currentAccY < 0)
            {
                this->collisionState.up = true;
            }
            else if(currentAccY > 0)
            {
                this->collisionState.down = true;
            }
        }

        if(level.ppointLayerAttributes[p_xNext][p_yCur] == 0) //only y
        {
            this->collisionState.set = true;
            if(currentAccX < 0)
            {
                this->collisionState.left = true;
            }
            else if(currentAccX > 0)
            {
                this->collisionState.right = true;
            }
        }

        if(level.ppointLayerAttributes[p_xNext][p_yNext] == 0) //both
        {
            this->collisionState.set = true;
            if(currentAccX < 0)
            {
                this->collisionState.left = true;
            }
            else if(currentAccX > 0)
            {
                this->collisionState.right = true;
            }
            if(currentAccY < 0)
            {
                this->collisionState.up = true;
            }
            else if(currentAccY > 0)
            {
                this->collisionState.down = true;
            }
        }
    }
}

void Player::update(const float deltaT) {
    this->getCurrenState()->update();

    isFalling = !this->collisionState.down; //wenn kollision mit boden dann nicht mehr falling

    if(isFalling)
    {
        currentAccY += gravity * deltaT*deltaT;
    }
    else
    {
        currentAccY = 0;
        isJumping = false;
        isDoubleJumping = false;
        this->setY((int)this->getY() - ((int)this->getY()%16));
    }

    if(this->collisionState.up)
    {
        currentAccY = 0;
        this->setY((int)this->getY() + ((int)this->getY()%16)); //TODO durch die decke glitchen weil kollision point von oben ne kollision nach unten hat
    }

    walkLeft = false;
    walkRight = false;
    if(this->ih->input[Inputhandler::Type::LEFT] == 1 && !this->collisionState.left)
    {
        if(currentAccX > 0) //reset speed by direction change
            currentAccX = 0;
        if(currentAccX > -(speed/2)) //start speed
            currentAccX = -(speed/2);
        if(currentAccX > (-speed))
            currentAccX -= speed*deltaT*deltaT;
        walkLeft = true;
    }

    if(this->ih->input[Inputhandler::Type::RIGHT] == 1  && !this->collisionState.right)
    {
        if(currentAccX < 0) //reset speed by direction change
            currentAccX = 0;
        if(currentAccX < (speed/2)) //start speed
            currentAccX = (speed/2);
        if(currentAccX < speed)
            currentAccX += speed*deltaT*deltaT;
        walkLeft = true;
    }

    if(!walkLeft && !walkRight)
        currentAccX = 0;


    if(this->ih->input[Inputhandler::Type::SPACE] == 1 && !this->collisionState.up)
    {
        if(!isDoubleJumping)
        {
            if(!isJumping)
            {
                this->currentAccY = -10;
                this->isFalling = true;
                this->isJumping = true;
            }
            else
            {
                gettimeofday(&this->curTime, NULL);
                if(timercmp(&this->curTime, &this->doubleJumpTimer, >)) //wenn currenttime > doubleJumpTimer
                {
                    this->isDoubleJumping = true;
                    timeradd(&this->curTime, &this->doubleJumpTimerTime, &this->doubleJumpTimer); //calc next Frame time
                }
            }
        }
    }

    this->x += currentAccX;
    this->y += currentAccY;
}

void Player::render(SDL::Renderer &renderer, SDL::Point camera) {

    EntityState *state = this->getCurrenState();
    this->getCurrenState()->render(renderer, SDL::Point((int) x, (int) y) - camera);

    if(this->collisionState.set)
        renderer.SetDrawColor(SDL::Color(255, 0, 0, 128));
    else
        renderer.SetDrawColor(SDL::Color(40, 107, 214, 128));

    int w = this->getCurrenState()->getW();
    int h = this->getCurrenState()->getH();

    renderer.FillRect(SDL::Rect(x - camera.x, y - camera.y, w*16, h*16));
}

Player::~Player() {
    printf("kille nun player %p\n", this);
}

float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    Player::speed = speed;
}

float Player::getGravity() const {
    return gravity;
}

void Player::setGravity(float gravity) {
    Player::gravity = gravity;
}
