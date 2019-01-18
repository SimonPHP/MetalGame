//
// Created by michael on 30.11.18.
//

#ifndef SDL_GAME_ANIMATION_H
#define SDL_GAME_ANIMATION_H

#include "global.h"
#include "tileset.h"

class AnimationFrame {
private:
    Tileset tileset;

    unsigned int time;
    uint32_t w, h; //points size divided by TILESIZE(16) 16 = 1; 32 = 2; etc...
public:
    SDL::Point **sprites;
    AnimationFrame();
    ~AnimationFrame();
    AnimationFrame(Tileset &tileset, uint32_t w, uint32_t h, unsigned int time);
    void addSpritePoint(SDL::Point gridPos, SDL::Point tilePos);

    unsigned int getTime() const;

    void draw(SDL::Point pos);
};

class Animation {
private:
    Tileset tileset;
    uint32_t w, h;

    AnimationFrame *animationFrames;

    uint32_t animationCount = 0;
    uint32_t currentAnimation = 0;

    unsigned int nextAnimationTime; //just for an intern calc
    unsigned int curTime; //just for an intern calc
public:
    Animation();
    ~Animation();
    Animation(Tileset &tileset, uint32_t w, uint32_t h);
    Tileset getTileset() const;
    AnimationFrame *addAnimationFrame(unsigned int time);
    AnimationFrame *getAnimationFrames() const;
    void update();
    void draw(SDL::Point pos);
};
#endif //SDL_GAME_ANIMATION_H
