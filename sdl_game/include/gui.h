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
public:
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

#endif //SDL_GAME_GUI_H
