//
// Created by simon on 23.12.18.
//

#ifndef SDL_GAME_GUI_H
#define SDL_GAME_GUI_H

#include "global.h"
#include <SDL_ttf.h>
#include <SDL_events.hpp>
#include <string>
#include <SDL_render.hpp>
#include <functional>
#include "tileset.h"
#include "Entity.h"

class GuiElement;

class GuiHandler {
private:
    std::vector<GuiElement*> elements;
    std::vector<GuiElement*>::iterator it;
public:
    void addGuiElement(GuiElement *element);
    void events(SDL::Event evt);
    void render(SDL::Renderer &renderer);
};


class GuiElement {
protected:
    SDL::Rect rect;
    GuiElement *parent = nullptr;
public:
    GuiElement *getParent() const;
    void setParent(GuiElement *parent);
    const Rect &getRect() const;
    void setRect(const Rect &rect);

protected:
    Font font;

public:
    GuiElement();
    virtual void events(SDL::Event evt) = 0;
    virtual void render(SDL::Renderer &renderer) = 0;
};

class Panel : public GuiElement {
private:
    std::vector<GuiElement*> elements;
    std::vector<GuiElement*>::iterator it;
    bool border;
public:
    Panel(SDL::Renderer &renderer, SDL::Rect rect, bool border);
    void addGuiElement(GuiElement *element);
    void events(SDL::Event evt);
    void render(SDL::Renderer &renderer);
};

class Button : public GuiElement {
private:
    SDL::Color backgroundColor;
    std::string text;
    Surface surface;
    Texture texture;
    bool isHover;
    bool isClicked;

    std::function<void()> callback;

public:
    Button(SDL::Renderer &renderer, SDL::Rect rect, const std::string &text, SDL::Color backgroundColor, std::function<void()> callback);
    void events(SDL::Event evt);
    void render(SDL::Renderer &renderer);
};

class TileSetSelector : public GuiElement {
    Tileset tileset;
    bool isSet; //tileset has to be loaded manually
    bool isHover;
    bool isSelected;
    SDL::Point selection; //selected tile
    SDL::Point hover; //hovered tile
public:
    void setTileset(const Tileset &tileset);

    TileSetSelector(SDL::Renderer &renderer, SDL::Point pos);
    void events(SDL::Event evt);
    void render(SDL::Renderer &renderer);
};

class EntityStateShow : public GuiElement {
private:
    int gridSize = 16;
    bool isGrid;
    bool isHover;
    SDL::Point hover;
    int rows, columns;
    Entity *entity;
public:
    EntityStateShow(SDL::Renderer &renderer, SDL::Rect rect, Entity *entity, bool isGrid);
    void toggleGrid();
    void events(SDL::Event evt);
    void render(SDL::Renderer &renderer);
};

#endif //SDL_GAME_GUI_H
