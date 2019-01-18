//
// Created by simon on 08.01.19.
//

#include <EntityState.h>
#include <sys/time.h>

EntityState::EntityState() {} //TODO how to set default???

/*!
 * w and h cannot be change in the runtime because of the animation. create a new entitystate
 * if you wish to do that
 * @param w
 * @param h
 */
EntityState::EntityState(uint32_t w, uint32_t h) : w(w), h(h) {}

Tileset EntityState::getTileset() const {
    return this->animation->getTileset();
}

/*!
 * updates the animation
 */
void EntityState::update() {
    this->animation->update();
}

int EntityState::getW() const {
    return w;
}

int EntityState::getH() const {
    return h;
}

/*!
 * just delegates to the Animation draw method
 * @param pos
 */
void EntityState::render(SDL::Renderer &renderer, SDL::Point pos) {

    renderer.SetDrawColor(Color(74, 168, 114, 128));

    for(uint32_t i = 0; i < hitboxesCount; i++)
        renderer.FillRect(SDL::Rect( pos.x + 16*hitboxes[i].x, pos.y + 16*hitboxes[i].y, 16, 16));

    this->animation->draw(pos);
}

void EntityState::createAnimation(Tileset &tileset) {
    Animation *newAnimation = new Animation(tileset, this->w, this->h);
    this->animation = newAnimation;
}

EntityState::~EntityState() {
    printf("kille nun entitystate %p\n", this);
}

Animation *EntityState::getAnimation() const {
    return animation;
}


void EntityState::addHitbox(SDL::Rect rect)
{
    SDL::Rect *oldHitboxes;
    oldHitboxes = new SDL::Rect[this->hitboxesCount];
    for(uint32_t i = 0; i < this->hitboxesCount; i++)
        oldHitboxes[i] = this->hitboxes[i]; //save old hitboxes

    this->hitboxesCount++;
    this->hitboxes = new SDL::Rect[this->hitboxesCount];

    for(uint32_t i = 0; i < this->hitboxesCount-1; i++)
        this->hitboxes[i] = oldHitboxes[i]; //restore old hitboxes
    this->hitboxes[this->hitboxesCount-1] = rect;
}

Point *EntityState::getCollisionCheckPoints() const {
    return collisionCheckPoints;
}

uint32_t EntityState::getCollisionCheckPointsCount() const {
    return collisionCheckPointsCount;
}

Rect *EntityState::getHitboxes() const {
    return hitboxes;
}

uint32_t EntityState::getHitboxesCount() const {
    return hitboxesCount;
}
