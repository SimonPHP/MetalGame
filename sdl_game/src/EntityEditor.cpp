//
// Created by simon on 23.12.18.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include "EntityEditorState.h"

void EntityEditorState::loadTileset(std::string tileSetPathConfig)
{
    std::string tileSetPath;
    std::string x, y;

    //get folder of tilesetPath
    std::vector<std::string> path;
    std::size_t current, previous = 0;
    current = tileSetPathConfig.find('/');
    while (current != std::string::npos) {
        path.push_back(tileSetPathConfig.substr(previous, current - previous));
        previous = current + 1;
        current = tileSetPathConfig.find('/', previous);
    }
    path.erase(path.begin());

    std::vector<std::string>::iterator it;

    for(it = path.begin(); it != path.end(); ++it) //rebuild path without filename
    {
        tileSetPath += "/";
        tileSetPath += *it;
    }

    std::ifstream myfile(tileSetPathConfig);
    if(myfile.is_open())
    {
        std::string tileSetName;
        std::getline (myfile, x);
        std::getline (myfile, y);
        std::getline (myfile, tileSetName);

        int _x, _y;

        _x = atoi(x.c_str());
        _y = atoi(y.c_str());

        myfile.close();
        this->playerTileSet = Tileset(IMG::LoadTexture( this->renderer, (tileSetPath + "/" + tileSetName).c_str() ), SDL::Point(_x, _y));
        this->isTileSet = true;
    }
}

void EntityEditorState::openTileset()
{
    char file[1024];
    FILE *f = popen("zenity --file-selection", "r");
    fgets(file, 1024, f); //linux way for fileselection dialog

    std::string fileName = file;
    loadTileset(fileName.substr(0, fileName.size()-1)); //cut of \n
}

void openDialog()
{
    char file[1024];
    FILE *f = popen("zenity --file-selection", "r");
    fgets(file, 1024, f); //linux way for fileselection dialog
    std::cout << "Open: " << file << std::endl;

    std::string fileName = file;

    std::string line;
    std::ifstream myfile(fileName.substr(0, fileName.size()-1)); //cut of \n on the end of the filename
    if(myfile.is_open())
    {
        while ( std::getline (myfile, line) )
        {
            std::cout << line << '\n';
        }
        myfile.close();
    }
    else
    {
        std::cout << "Fehler beim Öffnen: " << strerror(errno) << std::endl;
    }

}

void save()
{
    char file[1024];
    FILE *f = popen("zenity --file-selection --save", "r");
    fgets(file, 1024, f); //linux way for fileselection dialog
    std::cout << "SAVED " << file << std::endl; //remeber to cut of \n from file
}

void EntityEditorState::Init()
{
    SDL::Point winSize = game.getWindowSize();

    float leftPanelWidth = ((float)(winSize.x)/(float)3) * 2;
    float rightPanelWidth = (float)(winSize.x)/(float)3;

    float winHeigth = ((float)(winSize.y)/(float)5); //gefünftelt

    //left panel
    leftPanel = new Panel(renderer, SDL::Rect(0, 0, leftPanelWidth, winSize.y), true);
    mainMenuPanelLeft = new Panel(renderer, SDL::Rect(0, 0, leftPanelWidth, 25), true);

    leftPanel->addGuiElement(mainMenuPanelLeft);

    stageViewPanel = new Panel(renderer, SDL::Rect(0, 25, leftPanelWidth, winHeigth*4), true);
    stagePropsPanel = new Panel(renderer, SDL::Rect(0, winHeigth*4 + 25, leftPanelWidth, winHeigth), true);

    leftPanel->addGuiElement(stageViewPanel);
    leftPanel->addGuiElement(stagePropsPanel);

    bNew = new Button(renderer, SDL::Rect(0,0,100,25), "New", Color(102, 102, 102), std::bind(openDialog)); //position relativ from panel
    bOpen = new Button(renderer, SDL::Rect(105,0,100,25), "Open", Color(102, 102, 102), std::bind(openDialog));
    bSave = new Button(renderer, SDL::Rect(210,0,100,25), "Save", Color(102, 102, 102), std::bind(save));
    bSaveAt = new Button(renderer, SDL::Rect(315,0,100,25), "Save as", Color(102, 102, 102), std::bind(save));

    mainMenuPanelLeft->addGuiElement(bNew);
    mainMenuPanelLeft->addGuiElement(bOpen);
    mainMenuPanelLeft->addGuiElement(bSave);
    mainMenuPanelLeft->addGuiElement(bSaveAt);

    //right panel
    rightPanel = new Panel(renderer, SDL::Rect(leftPanelWidth, 0, rightPanelWidth, winSize.y), true);
    mainMenuPanelRight = new Panel(renderer, SDL::Rect(0, 0, rightPanelWidth, 25), true);
    rightPanel->addGuiElement(mainMenuPanelRight);

    tileSetSelectionPanel = new Panel(renderer, SDL::Rect(0, 25, rightPanelWidth,winSize.y/2), true);
    loadTileSetButton = new Button(renderer, SDL::Rect(0, 0, 100, 25), "Open", Color(102, 102, 102), std::bind(&EntityEditorState::openTileset, this));
    mainMenuPanelRight->addGuiElement(loadTileSetButton);

    rightMenuPanel = new Panel(renderer, SDL::Rect(0, winSize.y/2 + 25, rightPanelWidth,winSize.y/2), true);

    rightPanel->addGuiElement(tileSetSelectionPanel);
    rightPanel->addGuiElement(rightMenuPanel);

    handler.addGuiElement(leftPanel);
    handler.addGuiElement(rightPanel);
}

void EntityEditorState::Uninit()
{
    //noting to do here
}

void EntityEditorState::Events(const int frame, const float deltaT)
{
    Event::Pump();
    Event evt;

    while (Event::Poll(evt))
    {
        if (game.HandleEvent(evt))
            continue;

        handler.events(evt);
    }
}

void EntityEditorState::Update(const int frame, const float deltaT)
{
    //nothing to do here
}

void EntityEditorState::Render(const int frame, const float deltaT)
{
    renderer.ClearColor(255,255,255);
    handler.render(renderer);

    if(isTileSet)
    {
        for(int x = 0; x < playerTileSet.getSize().x; x++)
        {
            for(int y = 0; y < playerTileSet.getSize().y; y++)
            {
                this->playerTileSet.Draw(SDL::Point(tileSetSelectionPanel->getRect().x + x* playerTileSet.getRealSize().x , tileSetSelectionPanel->getRect().y + y*playerTileSet.getRealSize().y), SDL::Point(x, y));
            }
        }
    }

    renderer.Present();
}