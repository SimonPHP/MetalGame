//
// Created by simon on 25.01.19.
//

#include <EntityManager.h>


EntityManager::EntityManager() {

}

void EntityManager::addEntity(Entity *ent) {
    Entity **oldEntitys;
    oldEntitys = new Entity*[this->entityCount];
    for(uint32_t i = 0; i < this->entityCount; i++)
        oldEntitys[i] = this->entityList[i]; //save old hitboxes

    this->entityCount++;
    this->entityList = new Entity*[this->entityCount];

    for(uint32_t i = 0; i < this->entityCount-1; i++)
        this->entityList[i] = oldEntitys[i]; //restore old hitboxes
    this->entityList[this->entityCount-1] = ent;
}

void EntityManager::update(const float deltaT) {
    for(int i = 0; i < entityCount; i++)
        this->entityList[i]->update(deltaT);
}

void EntityManager::render(SDL::Renderer &renderer, SDL::Point camera) {
    for(int i = 0; i < entityCount; i++)
        this->entityList[i]->render(renderer, camera);
}
