//
// Created by simon on 30.11.18.
//

#include <Animation.h>
#include <sys/time.h>

#include "Animation.h"

Animation::Animation() {}

/*!
 * creates an Animation for the Entity.
 * The Animation has multiply AnimationFrames
 * @param tileset
 * @param w
 * @param h
 */
Animation::Animation(Tileset &tileset, uint32_t w, uint32_t h) : tileset(tileset), w(w), h(h)
{
    //TODO dont know
}

/*!
 * First set of the Tileset, maybe different Animations have different Tilesets
 * @param tileset
 */
Tileset Animation::getTileset() const {
    return tileset;
}

/*!
 * checks if its time for the next animationFrame and sets it.
 * If its reach the last animation it just start over again
 */
void Animation::update() {

    curTime = SDL::C::SDL_GetTicks();

    if(curTime > nextAnimationTime) //wenn currenttime > nextAnimationTime
    {
        this->currentAnimation = (this->currentAnimation + 1) % this->animationCount; //loop the animationFrames
        nextAnimationTime = curTime+this->getAnimationFrames()[currentAnimation].getTime();
    }
}

/*!
 * just delegates to the AnimationFrame draw method
 * @param pos
 */
void Animation::draw(SDL::Point pos) {
    this->animationFrames[currentAnimation].draw(pos);
}

AnimationFrame *Animation::addAnimationFrame(unsigned int time) {

    AnimationFrame *newAnimationFrame = new AnimationFrame(this->tileset, this->w, this->h, time);

    AnimationFrame *tmpAnimationFrameSet = new AnimationFrame[this->animationCount];
    for(uint32_t i = 0; i < this->animationCount; i++)
        tmpAnimationFrameSet[i] = this->animationFrames[i]; //save old states

    this->animationCount++;
    this->animationFrames = new AnimationFrame[this->animationCount]; //new array

    for(uint32_t i = 0; i < this->animationCount-1; i++)
        this->animationFrames[i] = tmpAnimationFrameSet[i]; //restore states
    this->animationFrames[this->animationCount-1] = *newAnimationFrame; //plus new state

    return newAnimationFrame;
}

Animation::~Animation() {
    printf("kille nun animation %p\n", this);
}

AnimationFrame *Animation::getAnimationFrames() const {
    return animationFrames;
}


//AnimationFrame Class

AnimationFrame::AnimationFrame() {}

/*!
 * Alloc memory for the sprites[][] the Player ist represented with
 * +---+---------+-------+
 * |   |    0    |   1   |
 * +---+---------+-------+
 * | 0 | nullptr | (0,1) |
 * | 1 | (1,0)   | (1,1) |
 * | 2 | (2,0)   | (2,1) |
 * +---+---------+-------+
 * @param tileset //only for Drawing //TODO maybe find a workaround so it doesnt need to be passed
 * @param w
 * @param h
 * @param time
 */
AnimationFrame::AnimationFrame(Tileset &tileset, uint32_t w, uint32_t h, unsigned int time) : tileset(tileset), w(w), h(h), time(time) {
    this->sprites = new SDL::Point*[this->w];
    for(uint32_t i = 0; i < this->w; ++i)
        this->sprites[i] = new SDL::Point[this->h]; //init dynamic array
}

/*!
 * Adds an SDL::Point in the sprites[][] Array
 * @param gridPos
 * @param tilePos
 */
void AnimationFrame::addSpritePoint(SDL::Point gridPos, SDL::Point tilePos) {
    this->sprites[gridPos.x][gridPos.y] = tilePos;
}

/*!
 * Should draw the complete sprites[][] starting at the top left
 * @param pos
 */
void AnimationFrame::draw(SDL::Point pos) {
    //TODO draw the entiere sprites[][] starting at the top left

    for(int i = 0; i < (int)this->w; i++)
    {
        for(int j = 0; j < (int)this->h; j++)
        {
            SDL::Point p = this->sprites[i][j];
            tileset.Draw(pos + SDL::Point(i * 16, j * 16), sprites[i][j]);
        }
    }
}

AnimationFrame::~AnimationFrame() {
    printf("kille nun animationframe %p\n", this);
}

unsigned int AnimationFrame::getTime() const {
    return time;
}


