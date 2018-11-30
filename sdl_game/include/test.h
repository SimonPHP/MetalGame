//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TEST_H
#define SDL_GAME_TEST_H

#include "global.h"
#include "gamebase.h"
#include "Object.h"
#include "Collidable.h"
#include "tileset.h"
#include "inputhandler.h"
#include "inputhandlerKeyboard.h"
#include "Animation.h"
#include "player.h"

#include <iostream>

class TestState : public GameState
{
    using GameState::GameState;

    TTF::Font font;
    SDL::Texture image;
    SDL::Texture blendedText;

    Tileset tileSet;

    Object ob = Object();
    Collidable co = Collidable();
    Collidable co2 = Collidable();
    Collidable co3 = Collidable();
    Player player = Player();

    InputhandlerKeyboard *inKey = new InputhandlerKeyboard();

public:

    virtual void Init() override;


    virtual void Uninit() override;


    virtual void Events(const int frame, const float deltaT) override;


    virtual void Update(const int frame, const float deltaT) override;


    virtual void Render(const int frame, const float deltaT) override;

};

#endif //SDL_GAME_TEST_H
