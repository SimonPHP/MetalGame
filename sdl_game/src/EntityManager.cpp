//
// Created by simon on 25.01.19.
//

#include <EntityManager.h>


EntityManager::EntityManager() {}

void EntityManager::addEntity(Entity *ent) {
    entityList.emplace_back(ent);
}

void EntityManager::update(const float deltaT) {
    for(uint32_t i = 0; i < entityList.size(); i++)
        this->entityList[i]->update(deltaT);
}

void EntityManager::render(SDL::Renderer &renderer, SDL::Point camera) {
    for(uint32_t i = 0; i < entityList.size(); i++)
        this->entityList[i]->render(renderer, camera);
}
