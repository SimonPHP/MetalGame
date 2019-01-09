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
#include "Player.h"
#include "Level.h"
#include "gui.h"

#include <iostream>
#include <SDL_types.h>

class EntityEditorState : public GameState
{
    using GameState::GameState;

    GuiHandler handler;

    //left Panle
    Panel *leftPanel;

    Panel *mainMenuPanelLeft;
    Button *bNew;
    Button *bOpen;
    Button *bSave;
    Button *bSaveAt;

    Panel *stageViewPanel;

    EntityStateShow *entityShow1; //debug
    Player *craa; //debug

    Panel *stagePropsPanel;

    //right Panel
    Panel *rightPanel;
    Panel *mainMenuPanelRight;
    Panel *tileSetSelectionPanel;
    Button *loadTileSetButton;

    TileSetSelector *tileSetSelector;

    Panel *rightMenuPanel;

    bool isTileSet = false;
    Tileset playerTileSet;

public:

    typedef void (*callback)(void);

    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Events(const int frame, const float deltaT) override;
    virtual void Update(const int frame, const float deltaT) override;
    virtual void Render(const int frame, const float deltaT) override;

    void loadTileset(std::string tileSetPathConfig);
    void openTileset();
};

#endif //SDL_GAME_ENTITYEDITOR_H
