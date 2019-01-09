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

    timeval time;
    uint32_t w, h; //points size divided by TILESIZE(16) 16 = 1; 32 = 2; etc...
public:
    SDL::Point **sprites;
    AnimationFrame();
    ~AnimationFrame();
    AnimationFrame(Tileset &tileset, uint32_t w, uint32_t h, const timeval &time);
    void addSpritePoint(SDL::Point gridPos, SDL::Point tilePos);
    const timeval &getTime() const;
    void draw(SDL::Point pos);
};

class Animation {
private:
    Tileset tileset;
    uint32_t w, h;



    uint32_t currentAnimation = 0;

    timeval nextAnimationTime; //just for an intern calc
    timeval curTime; //just for an intern calc
public:
    uint32_t animationCount = 0;
    AnimationFrame *animationFrames; //eingentlich private debugging //TODO das wieder private machen
    Animation();
    ~Animation();
    Animation(Tileset &tileset, uint32_t w, uint32_t h);
    Tileset getTileset() const;
    AnimationFrame *addAnimationFrame(const timeval &time);
    void update();
    void draw(SDL::Point pos);
};
#endif //SDL_GAME_ANIMATION_H
