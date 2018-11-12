//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TEST_H
#define SDL_GAME_TEST_H

#include "global.h"
#include "gamebase.h"
#include "object.h"
#include "collidable.h"

#include <iostream>

class TestState : public GameState
{
    using GameState::GameState;

    TTF::Font font;
    SDL::Texture image;
    SDL::Texture blendedText;

    object ob = object();
    collidable co = collidable();

public:

    virtual void Init() override
    {
        font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 24);
        // image = IMG::LoadTexture(renderer, "../assets/graphics/background.png");

        ob.setRect(SDL::Rect(0,0,100,100));
        co.setRect(SDL::Rect(20,20,40,40));
        co.setHitbox(SDL::Rect(10,10,10,10));
        co.bindHitboxToObjectRect(true);
        co.bindHitboxToObjectRect(false);

    }

    virtual void Uninit() override
    {
        font = TTF::Font();
        image = SDL::Texture();
    }

    virtual void Events(const int frame, const float deltaT) override
    {
        Event::Pump();
        Event evt;
        while (Event::Poll(evt))
        {
            if (game.HandleEvent(evt))
                continue;

            switch (evt.type())
            {
                case Event::Type::KEYDOWN:
                {
                    auto        kd = evt.Keyboard();
                    SDL::Keysym what_key = kd.keysym;
                    if (what_key.scancode() != SDL::Scancode::ESCAPE)
                    {
                        game.SetNextState(1); // continue to game on everything else than ESC
                    }
                    break;
                }
                case Event::Type::MOUSEBUTTONDOWN:
                    game.SetNextState(1);
                    break;
            }
        }
    }

    virtual void Update(const int frame, const float deltaT) override
    {
        //std::cout << ob << std::endl;

        co.setRect(SDL::Rect(co.getPos().x + 1, co.getPos().y + 2, 40, 40));
        std::cout << co << std::endl;
    }

    virtual void Render(const int frame, const float deltaT) override
    {
        {
            //image.Draw(Rect(0, 0, 1024, 768));
            blendedText.SetColorMod(Color(0, 0, 0));
            const Point p(32, 50);
            for (const Point& pd : { Point(-1, -1), Point(1, -1), Point(-1, 1), Point(1, 1), Point(0, 2), Point(2, 0), Point(0, -2), Point(-2, 0) })
                blendedText.Draw(p + pd);
            blendedText.SetColorMod(Color(255, 255, 255));
            blendedText.Draw(p);
        }

        renderer.Present();
    }
};

#endif //SDL_GAME_TEST_H
