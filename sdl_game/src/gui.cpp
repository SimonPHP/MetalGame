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
    this->calcRealPos();
}

void GuiElement::calcRealPos() {
    this->realPos = this->getParentPos();
}

SDL::Point GuiElement::getParentPos() {
    if(this->parent == nullptr)
        return SDL::Point(this->rect.x, this->rect.y);
    else
        return SDL::Point(this->rect.x, this->rect.y) + this->parent->getParentPos();
}

GuiElement::GuiElement(SDL::Rect rect) {
    font = TTF::Font("../assets/fonts/luximr.ttf", 16);
    this->setRect(rect);
}


Panel::Panel(SDL::Renderer &renderer, SDL::Rect rect, bool border) : GuiElement(rect) {
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


Button::Button(SDL::Renderer &renderer, SDL::Rect rect, const std::string &text, SDL::Color backgroundColor, std::function<void()> callback) : GuiElement(rect)
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

TileSetSelector::TileSetSelector(SDL::Renderer &renderer, SDL::Point pos) : GuiElement(SDL::Rect(pos.x, pos.y, 0, 0))
{
    this->rect = SDL::Rect(pos.x, pos.y, 0, 0);
}

void TileSetSelector::events(SDL::Event evt) {
    isHover = false;
    isSelected = false;

    switch(evt.type())
    {
        case SDL::Event::Type::MOUSEMOTION:
        {
            if(this->rect.ContainsPoint(SDL::Point(evt.MouseMotion().x, evt.MouseMotion().y)))
            {
                isHover = true;
                SDL::Point tmpMouse = SDL::Point(evt.MouseMotion().x - this->rect.x, evt.MouseMotion().y - this->rect.y);
                printf("tmpMouse x: %d, y: %d \n", tmpMouse.x, tmpMouse.y);
            }
            break;
        }
        case SDL::Event::Type::MOUSEBUTTONDOWN:
            if(this->rect.ContainsPoint(SDL::Point(evt.MouseMotion().x, evt.MouseMotion().y)))
                if(evt.MouseButton().clicks == 1) //1 => single click
                {
                    isSelected = true;
                    //this->callback(); //set selection point
                }
            break;
    }
}

void TileSetSelector::render(SDL::Renderer &renderer) {
    if(isSet)
    {
        for(int x = 0; x < tileset.getSize().x; x++)
        {
            for(int y = 0; y < tileset.getSize().y; y++)
            {
                renderer.DrawRect(SDL::Rect(this->getRect().x + x* tileset.getRealSize().x , this->getRect().y + y*tileset.getRealSize().y, tileset.getRealSize().x, tileset.getRealSize().y));
                this->tileset.Draw(SDL::Point(this->getRect().x + x* tileset.getRealSize().x , this->getRect().y + y*tileset.getRealSize().y), SDL::Point(x, y));
            }
        }
    }
}

void TileSetSelector::setTileset(const Tileset &tileset) {
    TileSetSelector::tileset = tileset;
    isSet = true;
}
