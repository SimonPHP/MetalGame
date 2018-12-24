//
// Created by simon on 23.12.18.
//

#include <gui.h>
#include <sstream>

#include "gui.h"

void GuiHandler::addGuiElement(GuiElement *element) {
    elements.emplace_back(element);
}

void GuiHandler::events(SDL::Event evt) {
    for(it = elements.begin(); it != elements.end(); ++it)
        (*it)->events(evt);
}

void GuiHandler::render(SDL::Renderer &renderer) {
    for(it = elements.begin(); it != elements.end(); ++it)
        (*it)->render(renderer);
}

GuiElement::GuiElement() {
    font = TTF::Font("../assets/fonts/luximr.ttf", 16);
}

const Rect &GuiElement::getRect() const {
    return rect;
}

void GuiElement::setRect(const Rect &rect) {
    GuiElement::rect = rect;
}

void Button::events(SDL::Event evt) {
    isHover = false;
    isClicked = false;

    switch(evt.type())
    {
        case SDL::Event::Type::MOUSEMOTION:
            if(this->rect.ContainsPoint(SDL::Point(evt.MouseMotion().x, evt.MouseMotion().y)))
                isHover = true;
            break;
        case SDL::Event::Type::MOUSEBUTTONDOWN:
            if(this->rect.ContainsPoint(SDL::Point(evt.MouseMotion().x, evt.MouseMotion().y)))
                if(evt.MouseButton().clicks == 1) //1 => single click
                {
                    isClicked = true;
                    this->callback();
                }
            break;
    }
}

void Button::render(SDL::Renderer &renderer) {
    renderer.SetDrawColor(this->backgroundColor);
    renderer.FillRect(this->rect);

    if(isHover)
    {
        renderer.SetDrawColor(Color(170, 170, 170, 170));
        renderer.FillRect(this->rect);
    }
    if(isClicked)
    {
        renderer.SetDrawColor(Color(0, 0, 0));
        renderer.DrawRect(this->rect);
    }

    SDL::C::SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}

Button::Button(SDL::Renderer &renderer, SDL::Rect rect, const std::string &text, SDL::Color backgroundColor, std::function<void()> callback) : GuiElement()
{
    this->text = text;
    this->rect = rect;
    this->backgroundColor = backgroundColor;

    this->callback = std::bind(callback);

    //this->surface = SDL::C::TTF_RenderText_Solid(this->font, text.c_str(), Color(0, 0, 0));
    //this->texture = SDL::C::SDL_CreateTextureFromSurface(renderer, surface);

    std::ostringstream oss;

    oss << this->text;
    {
        this->surface = this->font.RenderUTF8_Blended_Wrapped(oss.str(), Color(0, 0, 0), 320);
        this->texture = SDL::Texture(renderer, this->surface);
        this->texture.SetColorMod(Color(0, 0, 0));
    }

}

Panel::Panel(SDL::Renderer &renderer, SDL::Rect rect, bool border) : GuiElement() {
    this->rect = rect;
    this->border = border;
}

void Panel::addGuiElement(GuiElement *element) {
    SDL::Rect newRect = element->getRect();
    newRect.x += this->getRect().x;
    newRect.y += this->getRect().y;
    element->setRect(newRect);
    elements.emplace_back(element);
}

void Panel::events(SDL::Event evt) {
    for(it = elements.begin(); it != elements.end(); ++it)
        (*it)->events(evt);
}

void Panel::render(SDL::Renderer &renderer) {
    if(border)
    {
        renderer.SetDrawColor(Color(0, 0, 0));
        renderer.DrawRect(this->rect);
    }
    for(it = elements.begin(); it != elements.end(); ++it)
        (*it)->render(renderer);
}
