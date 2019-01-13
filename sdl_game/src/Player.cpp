//
// Created by simon on 22.12.18.
//

#include <Entity.h>
#include <inputhandlerKeyboard.h>
#include <Player.h>
#include <sys/time.h>

Player::Player(){}

Player::Player(Tileset tileset) {
    ih = new InputhandlerKeyboard();
    currentAccY = 0;
    currentAccX = 0;
    speed = 2000;
    gravity = 100;

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

    col = false;

    SDL::Point *collisionPoints = this->getCurrenState()->getCollisionCheckPoints();
    uint32_t collisionPointsCount = this->getCurrenState()->getCollisionCheckPointsCount();

    for(uint32_t i = 0; i < collisionPointsCount; i++)
    {
        uint32_t p_x = (uint32_t)collisionPoints[i].x + ((this->x + this->currentAccX * deltaT) /16);
        uint32_t p_y = (uint32_t)collisionPoints[i].y + ((this->y + this->currentAccY * deltaT) /16);
        if(level.ppointLayerAttributes[p_x][p_y] == 0 //TODO kollision zu viele checkPoints???
           //|| level.ppointLayerAttributes[p_x - 1][p_y - 1] == 0
           //|| level.ppointLayerAttributes[p_x][p_y - 1] == 0
           //|| level.ppointLayerAttributes[p_x - 1][p_y] == 0
                )
            col = true;

        //TODO this is shit
        p_x = (uint32_t)collisionPoints[i].x + ((this->x + this->currentAccX * deltaT/3) /16);
        p_y = (uint32_t)collisionPoints[i].y + ((this->y + this->currentAccY * deltaT/3) /16);
        if(level.ppointLayerAttributes[p_x][p_y] == 0 //TODO kollision zu viele checkPoints???
            //|| level.ppointLayerAttributes[p_x - 1][p_y - 1] == 0
            //|| level.ppointLayerAttributes[p_x][p_y - 1] == 0
            //|| level.ppointLayerAttributes[p_x - 1][p_y] == 0
                )
            col = true;
    }
}

void Player::update(const float deltaT) {
    this->getCurrenState()->update();

    if(!col)
    {
        isFalling = true;
    }

    if(col)
    {
        isFalling = false;
        isJumping = false;
        isDoubleJumping = false;
        this->setY(this->getY() - (int)this->getY()%16);
    }

    if(isFalling)
    {
        currentAccY += gravity * deltaT;
        y += currentAccY;
    }

    if(!isFalling)
    {
        currentAccY = 0;
    }

    if(this->ih->input[Inputhandler::Type::LEFT] == 1)
    {
        if(currentAccX > 0) //reset speed by direction change
            currentAccX = 0;
        if(currentAccX > -150) //start speed
            currentAccX = -150;
        if(currentAccX > (-speed))
            currentAccX -= speed*deltaT/10;
        this->x += currentAccX*deltaT;
    }

    if(this->ih->input[Inputhandler::Type::RIGHT] == 1)
    {
        if(currentAccX < 0) //reset speed by direction change
            currentAccX = 0;
        if(currentAccX < 150) //start speed
            currentAccX = 150;
        if(currentAccX < speed)
            currentAccX += speed*deltaT/10;
        this->x += currentAccX*deltaT;
    }

    if(this->ih->input[Inputhandler::Type::SPACE] == 1)
    {
        if(!isDoubleJumping)
        {
            if(!isJumping)
            {
                this->currentAccY = -32;
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

    //reset collision
    collisionState.set = false;
    collisionState.left = false;
    collisionState.right = false;
    collisionState.up = false;
    collisionState.down = false;
}

void Player::render(SDL::Renderer &renderer, SDL::Point camera) {

    EntityState *state = this->getCurrenState();
    this->getCurrenState()->render(renderer, SDL::Point((int) x, (int) y) - camera);

    if(col)
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
