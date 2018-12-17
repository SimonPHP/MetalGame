//
// Created by simon on 30.11.18.
//

#include "test.h"

#include "Level.h"

void TestState::Init()
{
    font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 24);
    // image = IMG::LoadTexture(renderer, "../assets/graphics/background.png");

    Animation a;

    tileSet = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/platformerPack_character.png" ), SDL::Point(4,2));

    player.setRect(SDL::Rect(100,600,96,96));
    player.setTileset(tileSet);

    std::vector<SDL::Point *> anim ;
    anim = a.StandartPlayer(anim); // Hier wird die standart animationm festgelegt

    player.setAnimation(anim);
    player.setIh(inKey);

    lev = new Level("0.map");
}

void TestState::Uninit()
{
    font = TTF::Font();
    image = SDL::Texture();
}

void TestState::Events(const int frame, const float deltaT)
{
    Event::Pump();
    Event evt;
    player.events(evt);
    while (Event::Poll(evt))
    {
        if (game.HandleEvent(evt))
            continue;
    }
}

void TestState::Update(const int frame, const float deltaT)
{
    //std::cout << ob << std::endl;
    /*
    co.setRect(SDL::Rect(co.getPos().x + 1, co.getPos().y + 2, 40, 40));
    std::cout << co << std::endl;

    std::cout << "co und co2 collide: " << co.checkCollision(co2) << std::endl;
    std::cout << "co und co3 collide: " << co.checkCollision(co3) << std::endl;
     */
    player.update(frame, deltaT);
}

void TestState::Render(const int frame, const float deltaT)
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

    renderer.SetDrawColor(SDL::Color(0,255,255,255));
    renderer.FillRect(SDL::Rect(0, 600, 1000, 1000));

    //draw map
    /*
    for(uint32_t x = 0; x < lev->getWidth(); x++)
    {
        for(uint32_t y = 0; y < lev->getHeigth(); y++)
        {
            if(lev->layerAttributes[x][y] != 65535)
                renderer.SetDrawColor(SDL::Color(255,0,128));
            else
                renderer.SetDrawColor(SDL::Color(255,255,255));

            renderer.FillRect(SDL::Rect(y*16, x*16, 16, 16));
        }
    }*/


    player.draw();

    renderer.Present();
}
