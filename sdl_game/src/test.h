//
// Created by simon on 12.11.18.
//

#ifndef SDL_GAME_TEST_H
#define SDL_GAME_TEST_H

#include "global.h"
#include "gamebase.h"
#include "object.h"
#include "collidable.h"
#include "tileset.h"
#include "inputhandler.h"
#include "inputhandlerKeyboard.h"

#include <iostream>

class TestState : public GameState
{
    using GameState::GameState;

    TTF::Font font;
    SDL::Texture image;
    SDL::Texture blendedText;

    Tileset tileSet;

    object ob = object();
    collidable co = collidable();
    collidable co2 = collidable();
    collidable co3 = collidable();

    object player = object();

    InputhandlerKeyboard inKey = InputhandlerKeyboard();

public:

    virtual void Init() override
    {
        font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 24);
        // image = IMG::LoadTexture(renderer, "../assets/graphics/background.png");

        /*
        ob.setRect(SDL::Rect(0,0,100,100));
        co.setRect(SDL::Rect(20,20,40,40));
        co.setHitbox(SDL::Rect(10,10,10,10));
        co.bindHitboxToObjectRect(true);
        co.bindHitboxToObjectRect(false);

        co2.setRect(SDL::Rect(10,10,30,30));
        co2.setHitbox(SDL::Rect(10,10,30,30));

        co3.setRect(SDL::Rect(100,100,30,30));
        co3.setHitbox(SDL::Rect(100,100,30,30));
         */

        tileSet = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/platformerPack_character.png" ), SDL::Point(4,2));
        player.setRect(SDL::Rect(100,100,96,96));
        player.setTileset(tileSet);

        std::vector<SDL::Point *> anim;

        /*
        anim.push_back(new SDL::Point(0,0));
        anim.push_back(new SDL::Point(1,0));
        anim.push_back(new SDL::Point(2,0));
        anim.push_back(new SDL::Point(3,0));
        anim.push_back(new SDL::Point(0,1));
        anim.push_back(new SDL::Point(1,1));
        anim.push_back(new SDL::Point(2,1));
        anim.push_back(new SDL::Point(3,1));
         */

        anim.push_back(new SDL::Point(1,0));
        anim.push_back(new SDL::Point(2,0));
        anim.push_back(new SDL::Point(3,0));

        player.setAnimation(anim);
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
            inKey.setInput(evt);
            if (game.HandleEvent(evt))
                continue;
        }
    }

    virtual void Update(const int frame, const float deltaT) override
    {
        //std::cout << ob << std::endl;
        /*
        co.setRect(SDL::Rect(co.getPos().x + 1, co.getPos().y + 2, 40, 40));
        std::cout << co << std::endl;

        std::cout << "co und co2 collide: " << co.checkCollision(co2) << std::endl;
        std::cout << "co und co3 collide: " << co.checkCollision(co3) << std::endl;
         */

        int speed = 2;

        player.setPos(SDL::Point( player.getPos().x + speed * inKey.input[Inputhandler::Type::WALK_RIGHT], player.getPos().y));
        player.setPos(SDL::Point( player.getPos().x - speed * inKey.input[Inputhandler::Type::WALK_LEFT], player.getPos().y));

    }

    virtual void Render(const int frame, const float deltaT) override
    {
        renderer.ClearColor(255,255,255);
        {
            image.Draw(Rect(0, 0, 1024, 768));
            blendedText.SetColorMod(Color(0, 0, 0));
            const Point p(32, 50);
            for (const Point& pd : { Point(-1, -1), Point(1, -1), Point(-1, 1), Point(1, 1), Point(0, 2), Point(2, 0), Point(0, -2), Point(-2, 0) })
                blendedText.Draw(p + pd);
            blendedText.SetColorMod(Color(255, 255, 255));
            blendedText.Draw(p);
        }

        player.draw();

        renderer.Present();
    }
};

#endif //SDL_GAME_TEST_H
