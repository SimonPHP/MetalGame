//
// Created by simon on 22.12.18.
//

#include <Entity.h>
#include <inputhandlerKeyboard.h>
#include <Player.h>

#define TILESIZE 16

Player::Player(){}

Player::Player(Tileset tileset) {
    ih = new InputhandlerKeyboard();
    currentAccY = 0;
    currentAccX = 0;
    speed = 500;
    gravity = 1000;
    jumpHeight = -550;
    health = 100;

    collidedWithEntity = false;

    this->addState(2, 2); //state 0 stehen
    this->addState(2, 2); //state 1 rechts laufen
    this->addState(2, 2); //state 2 links laufen
    this->addState(2, 2); //state 3 springen
    this->addState(2, 2); //state 4 kicken

    unsigned int t1 = 500; //500ms

    int offset = 25;

    this->getStateAt(0)->createAnimation(tileset);
    this->getStateAt(0)->getAnimation()->addAnimation(SDL::Point(0,0), SDL::Point(0,9+offset), t1, 3);

    this->getStateAt(1)->createAnimation(tileset);
    this->getStateAt(1)->getAnimation()->addAnimation(SDL::Point(0,0), SDL::Point(4,11+offset), t1, 4);

    this->getStateAt(2)->createAnimation(tileset);
    this->getStateAt(2)->getAnimation()->addAnimation(SDL::Point(0,0), SDL::Point(0,17+offset), t1, 4);

    this->getStateAt(3)->createAnimation(tileset);
    this->getStateAt(3)->getAnimation()->addAnimation(SDL::Point(0,0), SDL::Point(0,19+offset), t1, 6);

    this->getStateAt(4)->createAnimation(tileset); //animation mit tileset erstellen
    this->getStateAt(4)->getAnimation()->addAnimation(SDL::Point(0,0), SDL::Point(0,7+offset), t1, 3);
    int a = this->getStateAt(4)->getAnimation()->addAnimationFrame(t1);
    this->getStateAt(4)->getAnimation()->getAnimationFrame(a).addSprites(SDL::Point(0,0), SDL::Point(2,7+offset)); //extra frame

    this->getStateAt(0)->addHitbox(SDL::Rect(0,0,15,15)); //hitboxen sind nicht ans grid gebunden
    this->getStateAt(0)->addHitbox(SDL::Rect(16,0,15,15));
    this->getStateAt(0)->addHitbox(SDL::Rect(0,16,15,15));
    this->getStateAt(0)->addHitbox(SDL::Rect(16,16,15,15));

    this->getStateAt(1)->addHitbox(SDL::Rect(0,0,15,15));
    this->getStateAt(1)->addHitbox(SDL::Rect(16,0,15,15));
    this->getStateAt(1)->addHitbox(SDL::Rect(0,16,15,15));
    this->getStateAt(1)->addHitbox(SDL::Rect(16,16,15,15));

    this->getStateAt(2)->addHitbox(SDL::Rect(0,0,15,15));
    this->getStateAt(2)->addHitbox(SDL::Rect(16,0,15,15));
    this->getStateAt(2)->addHitbox(SDL::Rect(0,16,15,15));
    this->getStateAt(2)->addHitbox(SDL::Rect(16,16,15,15));

    this->getStateAt(3)->addHitbox(SDL::Rect(0,0,15,15));
    this->getStateAt(3)->addHitbox(SDL::Rect(16,0,15,15));
    this->getStateAt(3)->addHitbox(SDL::Rect(0,16,15,15));
    this->getStateAt(3)->addHitbox(SDL::Rect(16,16,15,15));

    this->getStateAt(4)->addHitbox(SDL::Rect(0,0,15,15));
    this->getStateAt(4)->addHitbox(SDL::Rect(16,0,15,15));
    this->getStateAt(4)->addHitbox(SDL::Rect(0,16,15,15));
    this->getStateAt(4)->addHitbox(SDL::Rect(16,16,15,15));
}

void Player::events(SDL::Event evt, const float deltaT) {

    ih->setInput(evt); //ih hat dan die ganzen states vom input

    walkLeft = (this->ih->input[Inputhandler::Type::LEFT] == 1);
    walkRight = (this->ih->input[Inputhandler::Type::RIGHT] == 1);
    willJump = (this->ih->input[Inputhandler::Type::UP] == 1);
    willAttack = (this->ih->input[Inputhandler::Type::SPACE] == 1);

    /*
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
    }*/
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

    for(uint32_t i = 0; i < this->getCurrentState()->getHitboxes().size(); i++)
    {
        SDL::Rect curHitbox = this->getCurrentState()->getHitboxes()[i];

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
    }
}

bool Player::checkCollisionWithEntity(Entity &entity)
{
    for(int i = 0; i < this->getCurrentState()->getHitboxes().size(); i++)
    {
        this->getCurrentState()->getRelhitboxes()[i].x = this->getCurrentState()->getHitboxes()[i].x + this->getX();
        this->getCurrentState()->getRelhitboxes()[i].y = this->getCurrentState()->getHitboxes()[i].y + this->getY();
    }

    int c = 0;
    for(int i = 0; i < this->getCurrentState()->getHitboxes().size(); i++)
    {
        for(int j = 0; j < entity.getCurrentState()->getHitboxes().size(); j++)
        {
            SDL::Rect ent = SDL::Rect(entity.getCurrentState()->getHitboxes()[j].x + entity.getX(), entity.getCurrentState()->getHitboxes()[j].y + entity.getY(), entity.getCurrentState()->getHitboxes()[j].w, entity.getCurrentState()->getHitboxes()[j].h);
            c += this->getCurrentState()->getRelhitboxes()[i].CollidesWith(ent);
        }
    }
    this->collidedWithEntity = (c > 0);
    return (c > 0);
}

void Player::update(const float deltaT) {
    this->getCurrentState()->update();

    //reset collision
    collisionState.set = false;
    collisionState.left = false;
    collisionState.right = false;
    collisionState.up = false;
    collisionState.down = false;

    if(this->currentState != 4)
    {
        if(walkLeft)
        {
            this->setCurrentState(2); //links
        }
        else if(walkRight)
        {
            this->setCurrentState(1); //rechts
        }
        else
        {
            this->setCurrentState(0); //stehen
        }
        if(!this->isJumping && (this->ih->input[Inputhandler::Type::UP] == 1) && !this->collisionState.up)
        {
            this->currentAccY = jumpHeight;
            this->isFalling = true;
            this->isJumping = true;
            this->setCurrentState(3);
        }
        if(this->ih->input[Inputhandler::Type::SPACE] == 1)
        {
            this->isAttacking = true;
            this->nextStateAfterKick = SDL::C::SDL_GetTicks()+this->kickTimer;
            this->setCurrentState(4);
        }
    }

    switch(this->currentState)
    {
        case 0:
        {
            this->currentAccX = 0;
            break;
        }
        case 1:
        {
            if(std::signbit(this->currentAccX))
                this->currentAccX = 10;
            else
                this->currentAccX += speed*deltaT;
            break;
        }
        case 2:
        {
            if(std::signbit(this->currentAccX))
                this->currentAccX -= speed*deltaT;
            else
                this->currentAccX = -10;
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            if(!isFalling)
            {
                if(std::signbit(this->currentAccX)) //wenn negativ
                    this->currentAccX += speed*deltaT;
                else
                    this->currentAccX -= speed*deltaT; //slow down while kicking
            }

            if(this->nextStateAfterKick < SDL::C::SDL_GetTicks())
            {
                this->isAttacking = false;
                this->setCurrentState(0);
            }
            break;
        }
        default:
            break;
    }
    this->currentAccY += gravity*deltaT;

    //hier kollision bestimmen
    float nextX = this->getX() + this->currentAccX*deltaT;
    float nextY = this->getY() + this->currentAccY*deltaT;

    for(uint32_t i = 0; i < this->getCurrentState()->getHitboxes().size(); i++)
    {
        float hitboxX = this->getCurrentState()->getHitboxes()[i].x + this->getX();
        float hitboxY = this->getCurrentState()->getHitboxes()[i].y + this->getY();
        float hitboxNextX = this->getCurrentState()->getHitboxes()[i].x + nextX;
        float hitboxNextY = this->getCurrentState()->getHitboxes()[i].y + nextY;

        int w = this->getCurrentState()->getHitboxes()[i].w;
        int h = this->getCurrentState()->getHitboxes()[i].h;

        SDL::Rect curHitbox = SDL::Rect(hitboxNextX, hitboxY, w, h);
        std::vector<SDL::Point> check(4, SDL::Point(0,0));

        check[0].x = curHitbox.x;
        check[0].y = curHitbox.y;

        check[1].x = curHitbox.x+curHitbox.w;
        check[1].y = curHitbox.y;

        check[2].x = curHitbox.x;
        check[2].y = curHitbox.y+curHitbox.h;

        check[3].x = curHitbox.x+curHitbox.w;
        check[3].y = curHitbox.y+curHitbox.h;

        for(int j = 0; j < 4; j++)
        {
            if(level->ppointLayerAttributes[ check[i].x/TILESIZE ][ check[i].y/TILESIZE ] == 0)
            {
                if(std::signbit(this->currentAccX)) //true if negativ //aka wenns nach links geht
                    this->collisionState.left = true;
                else
                    this->collisionState.right = true;
            }
        }

        curHitbox = SDL::Rect(hitboxX, hitboxNextY, w, h);

        check[0].x = curHitbox.x;
        check[0].y = curHitbox.y;

        check[1].x = curHitbox.x+curHitbox.w;
        check[1].y = curHitbox.y;

        check[2].x = curHitbox.x;
        check[2].y = curHitbox.y+curHitbox.h;

        check[3].x = curHitbox.x+curHitbox.w;
        check[3].y = curHitbox.y+curHitbox.h;

        for(int j = 0; j < 4; j++)
        {
            if(level->ppointLayerAttributes[ check[i].x/TILESIZE ][ check[i].y/TILESIZE ] == 0)
            {
                if(std::signbit(this->currentAccY)) //true if negativ //aka wenns nach oben geht
                    this->collisionState.up = true;
                else
                {
                    this->collisionState.down = true;
                    isFalling = false;
                    //this->health -= this->currentAccY/2000;
                }
            }
        }
    }

    collisionState.set = (collisionState.right || collisionState.left || collisionState.down || collisionState.up);
    if(collisionState.set)
    {
        if(collisionState.right)
        {
            this->currentAccX = 0;
            nextX = (int)((nextX/16)*16)-1;
        }
        if(collisionState.left)
        {
            this->currentAccX = 0;
            nextX = (int)((nextX/16)+1)*16;
        }
        if(collisionState.up)
        {
            this->currentAccY = 0;
            nextY = (int)(((nextY/16)+1)*16)+1;
        }
        if(collisionState.down)
        {
            this->isJumping = false;
            this->currentAccY = 0;
            nextY = (int)((nextY/16)*16)-1;
        }
    }
    this->x = nextX;
    this->y = nextY;
}

void Player::render(SDL::Renderer &renderer, SDL::Point camera) {

    EntityState *state = this->getCurrentState();
    this->getCurrentState()->render(renderer, SDL::Point((int) x, (int) y) - camera);

    renderer.SetDrawColor(SDL::Color(255, 0, 0));
    renderer.FillRect(SDL::Rect(20, WINDOW_Y-150, 160*(this->health/100),25));

    renderer.SetDrawColor(SDL::Color(0, 255, 0));
    renderer.FillRect(SDL::Rect(200, WINDOW_Y-150, exp*25,25));

    /*renderer.SetDrawColor(SDL::Color(0, 255, 0, 128));
    renderer.FillRect(SDL::Rect(100,250,16,16));
    renderer.FillRect(SDL::Rect(80,250,16,16));
    renderer.FillRect(SDL::Rect(90,230,16,16));
    renderer.FillRect(SDL::Rect(90,270,16,16));

    renderer.SetDrawColor(SDL::Color(255, 0, 0, 128));
    if(this->collisionState.right)
        renderer.FillRect(SDL::Rect(100,250,16,16));
    if(this->collisionState.left)
        renderer.FillRect(SDL::Rect(80,250,16,16));
    if(this->collisionState.up)
        renderer.FillRect(SDL::Rect(90,230,16,16));
    if(this->collisionState.down)
        renderer.FillRect(SDL::Rect(90,270,16,16));*/
}

Player::~Player() {
    printf("kille nun player %p\n", this);
}

void Player::setJumpHeight(int jumpHeight) {
    Player::jumpHeight = jumpHeight;
}

int Player::getJumpHeight() const {
    return jumpHeight;
}

void Player::setLevel(Level &level) {
    Player::level = &level;
}
