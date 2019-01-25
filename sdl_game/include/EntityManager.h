//
// Created by simon on 25.01.19.
//

#ifndef SDL_GAME_ENTITYMANAGER_H
#define SDL_GAME_ENTITYMANAGER_H

#include <Entity.h>
#include <global.h>

class EntityManager {
private:
    Entity **entityList;
    int entityCount = 0;
public:
    EntityManager();
    void addEntity(Entity *ent);
    void update(const float deltaT);
    void render(SDL::Renderer &renderer, SDL::Point camera);
};

#endif //SDL_GAME_ENTITYMANAGER_H
