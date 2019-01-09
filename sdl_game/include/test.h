//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TEST_H
#define SDL_GAME_TEST_H

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

class TestState : public GameState
{
    using GameState::GameState;

    TTF::Font font;
    SDL::Texture image;
    SDL::Texture blendedText;

    Tileset tileSet;
    Tileset tileSetMap;

    Player *player;

    InputhandlerKeyboard *inKey = new InputhandlerKeyboard();

    Level *lev;

    SDL::Point camera = SDL::Point(0,0);

    bool isLayerBG = true;
    bool isLayerFG = true;

    bool isLayerAttribute = true;
    bool isLayerEntity = true;
    bool isGrid = true;

    bool isShowHelp = true;

    SDL::C::Sint32 mouseX;
    SDL::C::Sint32 mouseY;

public:
    virtual void Init() override;


    virtual void Uninit() override;


    virtual void Events(const int frame, const float deltaT) override;


    virtual void Update(const int frame, const float deltaT) override;


    virtual void Render(const int frame, const float deltaT) override;

};

#endif //SDL_GAME_TEST_H
