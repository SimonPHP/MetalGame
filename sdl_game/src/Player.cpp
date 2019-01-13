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
    speed = 500;
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

    this->getCurrenState()->addHitbox(SDL::Rect(0,0,32,32)); //relativ to player

    /*this->getCurrenState()->addHitbox(SDL::Rect(0,0,16,16)); //relativ to player
    this->getCurrenState()->addHitbox(SDL::Rect(16,0,16,16)); //relativ to player
    this->getCurrenState()->addHitbox(SDL::Rect(0,16,16,16)); //relativ to player
    this->getCurrenState()->addHitbox(SDL::Rect(16,16,16,16)); //relativ to player
     */


    /*this->getCurrenState()->addHitbox(SDL::Point(0,0));
    this->getCurrenState()->addHitbox(SDL::Point(0,1));
    this->getCurrenState()->addHitbox(SDL::Point(1,0));
    this->getCurrenState()->addHitbox(SDL::Point(1,1));*/
}

void Player::events(SDL::Event evt, const float deltaT) {
    //reset collision
    collisionState.set = false;
    collisionState.left = false;
    collisionState.right = false;
    collisionState.up = false;
    collisionState.down = false;

    ih->setInput(evt); //ih hat dan die ganzen states vom input

    walkLeft = false;
    walkRight = false;
    if(this->ih->input[Inputhandler::Type::LEFT] == 1)
    {
        if(currentAccX > 0) //reset speed by direction change
            currentAccX = 0;
        if(currentAccX > -(speed/2)) //start speed
            currentAccX = -(speed/2);
        if(currentAccX > (-speed))
            currentAccX -= this->ih->input[Inputhandler::Type::LEFT]*speed*deltaT;
        walkLeft = true;
    }

    if(this->ih->input[Inputhandler::Type::RIGHT] == 1)
    {
        if(currentAccX < 0) //reset speed by direction change
            currentAccX = 0;
        if(currentAccX < (speed/2)) //start speed
            currentAccX = (speed/2);
        if(currentAccX < speed)
            currentAccX += this->ih->input[Inputhandler::Type::RIGHT]*speed*deltaT;
        walkRight = true;
    }

    if(!walkLeft && !walkRight)
        currentAccX = 0;

    if(!this->collisionState.down)
    {
        this->currentAccY += gravity * deltaT;
    }
}

void Player::checkCollisionWithLevel(Level &level, const float deltaT) {

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

    uint32_t curX = (uint32_t)((this->x));
    uint32_t curY = (uint32_t)((this->y));
    uint32_t nextX = (uint32_t)((this->x + moveX));
    uint32_t nextY = (uint32_t)((this->y + moveY));

    for(uint32_t i = 0; i < this->getCurrenState()->getHitboxesCount(); i++)
    {
        SDL::Rect curHitbox = this->getCurrenState()->getHitboxes()[i];

        curHitbox.x += curX;
        curHitbox.y += curY;
        //curHitbox.w /= 16;
        //curHitbox.h /= 16;

        /*
         * Hitbox
         * pos1------pos2
         * .            .
         * .            .
         * .            .
         * .            .
         * pos3------pos4
         * */

        SDL::Point pos1 = SDL::Point(curHitbox.x/16, curHitbox.y/16);
        SDL::Point pos2 = SDL::Point((curHitbox.x + curHitbox.w)/16, curHitbox.y/16);
        SDL::Point pos3 = SDL::Point(curHitbox.x/16, (curHitbox.y + curHitbox.h)/16);
        SDL::Point pos4 = SDL::Point((curHitbox.x + curHitbox.w)/16, (curHitbox.y + curHitbox.h)/16);

        bool pos1Col = false;
        bool pos2Col = false;
        bool pos3Col = false;
        bool pos4Col = false;
        pos1Col = (level.ppointLayerAttributes[pos1.x][pos1.y] == 0);
        pos2Col = (level.ppointLayerAttributes[pos2.x][pos2.y] == 0);
        pos3Col = (level.ppointLayerAttributes[pos3.x][pos3.y] == 0);
        pos4Col = (level.ppointLayerAttributes[pos4.x][pos4.y] == 0);

        if(pos1Col && (moveY < 0))
            this->collisionState.up = true;
        if(pos2Col && (moveY < 0))
            this->collisionState.up = true;

        if(pos3Col && (moveY > 0))
            this->collisionState.down = true;
        if(pos4Col && (moveY > 0))
            this->collisionState.down = true;

        if(this->collisionState.down)
        {
            //pos1Col = (level.ppointLayerAttributes[pos1.x][pos1.y+1] == 0);
            //pos2Col = (level.ppointLayerAttributes[pos2.x][pos2.y+1] == 0);
            pos3Col = (level.ppointLayerAttributes[pos3.x][pos3.y-1] == 0);
            pos4Col = (level.ppointLayerAttributes[pos4.x][pos4.y-1] == 0);
        }

        if(pos1Col && (moveX < 0))
            this->collisionState.left = true;
        if(pos3Col && (moveX < 0))
            this->collisionState.left = true;

        if(pos2Col && (moveX > 0))
            this->collisionState.right = true;
        if(pos4Col && (moveX > 0))
            this->collisionState.right = true;


        /*if((((int)this->y % 16) == 0))
        {
            if(pos3Col && level.ppointLayerAttributes[pos3.x][pos3.y-1] != 0)
                this->collisionState.left = false;
            if(pos4Col && level.ppointLayerAttributes[pos4.x][pos4.y-1] != 0)
                this->collisionState.right = false;
        }*/

    }
}

void Player::update(const float deltaT) {
    this->getCurrenState()->update();

    if(walkLeft && this->collisionState.left)
    {
        int cor = ((int)this->getX()%16);
        if(cor > 14) //TODO schauen warum das so ne kacke ist
            this->setX((int)this->getX() + cor);
        //this->setX((int)this->getX() + ((int)this->getX()%16)); //korrigiert
        currentAccX = 0;
    }

    if(walkRight && this->collisionState.right)
    {
        int cor = ((int)this->getX()%16);
        if(cor > 14) //TODO hier auch was soll die kacke
            this->setX((int)this->getX() - cor);
        //this->setX((int)this->getX() - ((int)this->getX()%16)); //korrigiert
        currentAccX = 0;
    }


    isFalling = !this->collisionState.down; //wenn kollision mit boden dann nicht mehr falling

    if(!isFalling)
    {
        currentAccY = 0;
        isJumping = false;
        isDoubleJumping = false;
        float cor = ((int)this->getY()%16);
        if(cor < 14)
            this->setY((int)this->getY() - cor);
    }

    if(this->collisionState.up)
    {
        currentAccY = 0;
        float cor = ((int)this->getY()%16);
        if(cor < 14)
            this->setY((int)this->getY() + cor);
    }

    if(this->ih->input[Inputhandler::Type::SPACE] == 1 && !this->collisionState.up)
    {
        if(!isDoubleJumping)
        {
            if(!isJumping)
            {
                this->currentAccY = -800;
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

    this->x += currentAccX * deltaT;
    this->y += currentAccY * deltaT;
}

void Player::render(SDL::Renderer &renderer, SDL::Point camera) {

    EntityState *state = this->getCurrenState();
    this->getCurrenState()->render(renderer, SDL::Point((int) x, (int) y) - camera);

    if(this->collisionState.right || this->collisionState.left)
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
