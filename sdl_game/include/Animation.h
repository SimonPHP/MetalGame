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
    std::vector<std::vector<SDL::Point>> sprites;
public:
    AnimationFrame();
    ~AnimationFrame();
    AnimationFrame(Tileset &tileset, uint32_t w, uint32_t h, unsigned int time);
    void addSpritePoint(SDL::Point gridPos, SDL::Point tilePos);
    void addSprites(SDL::Point gridPos, SDL::Point tilePos);

    unsigned int getTime() const;

    void draw(SDL::Point pos);
};

class Animation {
private:
    Tileset tileset;
    uint32_t w, h;

    //AnimationFrame *animationFrames;
    std::vector<AnimationFrame*> animationFrames;
public:
    const std::vector<AnimationFrame *> &getAnimationFrames() const;

private:

    uint32_t animationCount = 0;
    uint32_t currentAnimation = 0;

    unsigned int nextAnimationTime; //just for an intern calc
    unsigned int curTime; //just for an intern calc
public:
    Animation();
    ~Animation();
    Animation(Tileset &tileset, uint32_t w, uint32_t h);
    Tileset getTileset() const;
    uint32_t addAnimationFrame(unsigned int time);
    AnimationFrame &getAnimationFrame(uint32_t frame) const;

    void addAnimation(SDL::Point gridPos, SDL::Point tilePos, int time, int count);

    void update();
    void draw(SDL::Point pos);
};
#endif //SDL_GAME_ANIMATION_H
