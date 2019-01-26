//
// Created by simon on 30.11.18.
//

#include <Animation.h>

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
        this->currentAnimation = (this->currentAnimation + 1) % (this->animationFrames.size()); //loop the animationFrames
        nextAnimationTime = curTime+this->getAnimationFrame(currentAnimation).getTime();
    }
}

/*!
 * just delegates to the AnimationFrame draw method
 * @param pos
 */
void Animation::draw(SDL::Point pos) {
    this->getAnimationFrame(currentAnimation).draw(pos);
}

uint32_t Animation::addAnimationFrame(unsigned int time) {
    AnimationFrame *newAnimationFrame = new AnimationFrame(this->tileset, this->w, this->h, time);
    this->animationFrames.emplace_back(newAnimationFrame);
    return (uint32_t)(this->animationFrames.size()-1);
}

Animation::~Animation() {
    printf("kille nun animation %p\n", this);
}

const std::vector<AnimationFrame *> &Animation::getAnimationFrames() const {
    return animationFrames;
}

void Animation::addAnimation(SDL::Point gridPos, SDL::Point tilePos, int time, int count) {

    for(int i = tilePos.x, currentAnim = 0; i < tilePos.x + (w*count); i+= w, currentAnim++)
    {
        this->addAnimationFrame(time);
        this->getAnimationFrame(currentAnim).addSprites(SDL::Point(gridPos.x,gridPos.y), SDL::Point(i, tilePos.y));
        //printf("%d\n", tilePos.x); //wegen dieser ausgabe bewegt sich der spieler überhaupt im state wtf???
    }
}


//AnimationFrame Class

AnimationFrame::AnimationFrame() {}

AnimationFrame &Animation::getAnimationFrame(uint32_t frame) const {
    return *animationFrames[frame];
}

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
    this->sprites.resize(w, std::vector<SDL::Point>(h, SDL::Point(0,0)));
}
/*!
 * Adds an SDL::Point in the sprites[][] Vector
 * @param gridPos
 * @param tilePos
 */
void AnimationFrame::addSpritePoint(SDL::Point gridPos, SDL::Point tilePos) {
    this->sprites[gridPos.x][gridPos.y] = tilePos;
    //printf("");
}

/*!
 * Should draw the complete sprites[][] starting at the top left
 * @param pos
 */
void AnimationFrame::draw(SDL::Point pos) {
    for(int i = 0; i < (int)this->w; i++)
    {
        for(int j = 0; j < (int)this->h; j++)
        {
            tileset.Draw(pos + SDL::Point(i * 16, j * 16), sprites[i][j]);
        }
    }
}

AnimationFrame::~AnimationFrame() {}

unsigned int AnimationFrame::getTime() const {
    return time;
}

void AnimationFrame::addSprites(SDL::Point gridPos, SDL::Point tilePos) {
    for(int i = gridPos.x, Ti = tilePos.x; i < gridPos.x + w; i++, Ti++)
    {
        for(int j = gridPos.y, Tj = tilePos.y; j < gridPos.y + h; j++, Tj++)
            this->addSpritePoint(SDL::Point(i,j), SDL::Point(Ti, Tj));
    }
}


