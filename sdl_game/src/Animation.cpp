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
    gettimeofday(&curTime, NULL);
    if(timercmp(&curTime, &nextAnimationTime, >)) //wenn currenttime > nextAnimationTime
    {
        this->currentAnimation = (this->currentAnimation + 1) % this->animationCount; //loop the animationFrames
        timeradd(&curTime, (&this->animationFrames[this->currentAnimation].getTime()), &nextAnimationTime); //calc next Frame time
    }
}

/*!
 * just delegates to the AnimationFrame draw method
 * @param pos
 */
void Animation::draw(SDL::Point pos) {
    printf("tmpFrame in Animation Render in animation.cpp %p\n", &this->animationFrames[0]);
    this->animationFrames[currentAnimation].draw(pos);
}

AnimationFrame *Animation::addAnimationFrame(const timeval &time) {

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
AnimationFrame::AnimationFrame(Tileset &tileset, uint32_t w, uint32_t h, const timeval &time) : tileset(tileset), w(w), h(h), time(time) {
    this->sprites = new SDL::Point*[this->w];
    for(uint32_t i = 0; i < this->w; ++i)
        this->sprites[i] = new SDL::Point[this->h]; //init dynamic array
}

/*!
 * Returns the duration from the AnimationFrame
 * @return timeval
 */
const timeval &AnimationFrame::getTime() const {
    return time;
}

/*!
 * Adds an SDL::Point in the sprites[][] Array
 * @param gridPos
 * @param tilePos
 */
void AnimationFrame::addSpritePoint(SDL::Point gridPos, SDL::Point tilePos) {
    this->sprites[gridPos.x][gridPos.y] = tilePos;

    printf("points added at: %p\n", this);

    for(int i = 0; i < this->w; i++)
        for(int j = 0; j < this->h; j++)
            printf("animationFrames: %d,%d\n", sprites[i][j].x, sprites[i][j].y); //HIER GEHTS NOCH

    //printf("%d, %d\n", this->sprites[gridPos.x][gridPos.y].x, this->sprites[gridPos.x][gridPos.y].y);
    //printf("sprites von %p bei %p\n", this, (&this->sprites));
}

/*!
 * Should draw the complete sprites[][] starting at the top left
 * @param pos
 */
void AnimationFrame::draw(SDL::Point pos) {
    //TODO draw the entiere sprites[][] starting at the top left

    for(int i = 0; i < this->w; i++) //HIER NICHT MEHR
        for(int j = 0; j < this->h; j++)
            printf("animationFrames: %d,%d\n", sprites[i][j].x, sprites[i][j].y);

    printf("AnimationFrame drawed at: %p\n", this);

    for(int i = 0; i < (int)this->w; i++)
    {
        for(int j = 0; j < (int)this->h; j++)
        {
            //printf("[%d,%d] = (%d, %d) \n", i, j, sprites[i][j].x, sprites[i][j].y); //TODO debug
            SDL::Point p = this->sprites[i][j];
            tileset.Draw(pos + SDL::Point(i * 16, j * 16), sprites[i][j]);
        }
    }
}

AnimationFrame::~AnimationFrame() {
    printf("kille nun animationframe %p\n", this);
}


