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

    for(int i = 0; i < hitboxesCount; i++)
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

void EntityState::addHitbox(SDL::Point pos) {
    SDL::Point *oldHitboxes;
    oldHitboxes = new SDL::Point[this->hitboxesCount];
    for(uint32_t i = 0; i < this->hitboxesCount; i++)
        oldHitboxes[i] = this->hitboxes[i]; //save old hitboxes

    this->hitboxesCount++;
    this->hitboxes = new SDL::Point[this->hitboxesCount];

    for(uint32_t i = 0; i < this->hitboxesCount-1; i++)
        this->hitboxes[i] = oldHitboxes[i]; //restore old hitboxes
    this->hitboxes[this->hitboxesCount-1] = pos;


    SDL::Point *oldcollisionCheckPoints;
    oldcollisionCheckPoints = new SDL::Point[this->collisionCheckPointsCount];
    for(uint32_t i = 0; i < this->collisionCheckPointsCount; i++)
        oldcollisionCheckPoints[i] = this->collisionCheckPoints[i]; //save old collisionCheckPoints

    this->collisionCheckPointsCount += 4;
    this->collisionCheckPoints = new SDL::Point[this->collisionCheckPointsCount];

    for(uint32_t i = 0; i < this->collisionCheckPointsCount-1; i++)
        this->collisionCheckPoints[i] = oldcollisionCheckPoints[i]; //restore old collisionCheckPoints

    this->collisionCheckPoints[this->collisionCheckPointsCount-4] = pos;
    this->collisionCheckPoints[this->collisionCheckPointsCount-3] = pos + SDL::Point(0, 1);
    this->collisionCheckPoints[this->collisionCheckPointsCount-2] = pos + SDL::Point(1, 0);
    this->collisionCheckPoints[this->collisionCheckPointsCount-1] = pos + SDL::Point(1, 1);
}

Point *EntityState::getCollisionCheckPoints() const {
    return collisionCheckPoints;
}

uint32_t EntityState::getCollisionCheckPointsCount() const {
    return collisionCheckPointsCount;
}

//TODO move in entityState
/*void Entity::addHitbox(SDL::Rect rect) {

    //TODO: doppelte punkte aus dem array löschen

    SDL::Rect *oldHitboxes;

    oldHitboxes = new SDL::Rect[this->hitboxesCount];
    for(uint32_t i = 0; i < hitboxesCount; i++)
    {
        oldHitboxes[i] = this->hitboxes[i];
    }

    hitboxesCount++;

    this->hitboxes = new SDL::Rect[this->hitboxesCount];

    for(uint32_t i = 0; i < hitboxesCount-1; i++)
    {
        this->hitboxes[i] = oldHitboxes[i];
    }
    this->hitboxes[hitboxesCount-1] = rect;

    //TODO: nicht immer das gesammte array löschen wenn eine hitbox hinzu kommt
    checkPoints.clear();

    int p_x = (int)(x/16);
    int p_y = (int)(y/16);

    checkPoints.emplace_back(SDL::Point(p_x+1, p_y+1));

    for(uint32_t i = 0; i < hitboxesCount; i++)
    {
        int xD = hitboxes[i].w/16;
        int yD = hitboxes[i].h/16;

        int xH = hitboxes[i].x/16;
        int yH = hitboxes[i].y/16;

        for(uint32_t xC = 0; xC < xD; xC++)
        {
            for(uint32_t yC = 0; yC < yD; yC++)
            {
                    checkPoints.emplace_back(SDL::Point(xH +xC + 1, yH + yC + 1));
            }
        }
    }
}*/