//
// Created by simon on 22.12.18.
//

#include <Entity.h>
#include <inputhandlerKeyboard.h>
#include "Player.h"

Player::Player() {
    ih = new InputhandlerKeyboard();
    currentAccY = 0;
    currentAccX = 0;
    speed = 200;
    gravity = 100;
}

void Player::events(SDL::Event evt){
    ih->setInput(evt); //ih hat dan die ganzen states
}

void Player::checkCollision(Level &level) {

    col = false;

    for(it = checkPoints.begin(); it != checkPoints.end(); ++it)
    {
        int p_x = it->x + (int)(x/16); //spieler position muss noch mit auf die checkPoints gerechnet werden
        int p_y = it->y + (int)(y/16);
        if(level.ppointLayerAttributes[p_x][p_y] == 0
           || level.ppointLayerAttributes[p_x - 1][p_y - 1] == 0
           || level.ppointLayerAttributes[p_x][p_y - 1] == 0
           || level.ppointLayerAttributes[p_x - 1][p_y] == 0
                )
            col = true;
    }
}

void Player::update(const float deltaT) {

    /*
    if(!collisionState.down)
    {
        isFalling = true;
    }

    if(collisionState.down)
    {
        isFalling = false;
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
     */

    //reset collision
    collisionState.set = false;
    collisionState.left = false;
    collisionState.right = false;
    collisionState.up = false;
    collisionState.down = false;
}

void Player::render(SDL::Renderer &renderer, SDL::Point camera) {
    renderer.SetDrawColor(SDL::Color(255, 163, 71));
    for(uint32_t i = 0; i < boundariesCount; i++)
    {
        int x = boundaries[i].x;
        int y = boundaries[i].y;
        int w = boundaries[i].w;
        int h = boundaries[i].h;
        renderer.FillRect(SDL::Rect(this->x + x - camera.x, this->y + y - camera.y, w, h));
    }

    if(col)
        renderer.SetDrawColor(SDL::Color(255, 0, 0, 128));
    else
        renderer.SetDrawColor(SDL::Color(40, 107, 214, 128));

    for(uint32_t i = 0; i < hitboxesCount; i++)
    {
        int x = hitboxes[i].x;
        int y = hitboxes[i].y;
        int w = hitboxes[i].w;
        int h = hitboxes[i].h;
        renderer.FillRect(SDL::Rect(this->x + x - camera.x, this->y + y - camera.y, w, h));
    }


    /*if(col)
        renderer.SetDrawColor(SDL::Color(0, 97, 255));
    else
        renderer.SetDrawColor(SDL::Color(255, 163, 71));

    renderer.FillRect(SDL::Rect(x-w - camera.x, y-h - camera.y, w, h));*/
}
