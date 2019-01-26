//
// Created by simon on 01.01.19.
//

#ifndef SDL_GAME_ENTITYSTATE_H
#define SDL_GAME_ENTITYSTATE_H

#include "Animation.h"

//class Entity; //protoype to use in here because cross reference would give *x not name a type*

class EntityState
{
private:
    Animation *animation;
    uint32_t w, h; //TODO const??

    std::vector<SDL::Rect> hitboxes;
    std::vector<SDL::Rect> relhitboxes;

private:

    SDL::Point *collisionCheckPoints; //TODO needed??
    uint32_t collisionCheckPointsCount = 0; //TODO needed??

public:
    Animation *getAnimation() const;

    const std::vector<Rect> &getHitboxes() const;
    std::vector<Rect> &getRelhitboxes();

    EntityState();
    ~EntityState();
    EntityState(uint32_t w, uint32_t h);
    Tileset getTileset() const;
    void createAnimation(Tileset &tileset);
    //void addHitbox(SDL::Point pos);
    void addHitbox(SDL::Rect rect);

    Point *getCollisionCheckPoints() const;
    uint32_t getCollisionCheckPointsCount() const;

    void update();
    void render(SDL::Renderer &renderer, SDL::Point pos);
    int getW() const;
    int getH() const;
};

#endif //SDL_GAME_ENTITYSTATE_H
