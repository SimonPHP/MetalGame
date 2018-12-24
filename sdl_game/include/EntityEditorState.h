//
// Created by simon on 23.12.18.
//

#ifndef SDL_GAME_ENTITYEDITOR_H
#define SDL_GAME_ENTITYEDITOR_H

#include "global.h"
#include "gamebase.h"
#include "tileset.h"
#include "inputhandler.h"
#include "inputhandlerKeyboard.h"
#include "Animation.h"
#include "Player.h"
#include "Level.h"

#include <iostream>
#include <SDL_types.h>

class EntityEditor : public GameState
{
    using GameState::GameState;




public:
    virtual void Init() override;


    virtual void Uninit() override;


    virtual void Events(const int frame, const float deltaT) override;


    virtual void Update(const int frame, const float deltaT) override;


    virtual void Render(const int frame, const float deltaT) override;
};

#endif //SDL_GAME_ENTITYEDITOR_H
