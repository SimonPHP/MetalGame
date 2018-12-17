//
// Created by simon on 30.11.18.
//

#include "test.h"

#include "Level.h"

void TestState::Init()
{
    font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 12);
    // image = IMG::LoadTexture(renderer, "../assets/graphics/background.png");

    Animation a;

    tileSet = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/platformerPack_character.png" ), SDL::Point(4,2));

    tileSetMap = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/1.png" ), SDL::Point(16,38));

    player.setRect(SDL::Rect(100,600,96,96));
    player.setTileset(tileSet);

    std::vector<SDL::Point *> anim ;
    anim = a.StandartPlayer(anim); // Hier wird die standart animationm festgelegt

    player.setAnimation(anim);
    player.setIh(inKey);

    lev = new Level("0.map");
    lev->processLevelwithTileset(tileSetMap);
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
    //player.events(evt);

    const SDL::Uint8 *state = SDL::C::SDL_GetKeyboardState(NULL);

    int speed = 50;

    while (Event::Poll(evt))
    {
        if (game.HandleEvent(evt))
            continue;

        if(state[SDL::C::SDL_SCANCODE_F1])
            isLayerBG1 = !isLayerBG1;

        if(state[SDL::C::SDL_SCANCODE_F2])
            isLayerBG2 = !isLayerBG2;

        if(state[SDL::C::SDL_SCANCODE_F3])
            isLayerBG3 = !isLayerBG3;

        if(state[SDL::C::SDL_SCANCODE_F4])
            isLayerFG1 = !isLayerFG1;

        if(state[SDL::C::SDL_SCANCODE_F5])
            isLayerFG2 = !isLayerFG2;

        if(state[SDL::C::SDL_SCANCODE_F6])
            isLayerAttribute = !isLayerAttribute;

        if(state[SDL::C::SDL_SCANCODE_F7])
            isLayerEntity = !isLayerEntity;

        if(state[SDL::C::SDL_SCANCODE_F8])
            isGrid = !isGrid;

        if(state[SDL::C::SDL_SCANCODE_F12])
            isShowHelp = !isShowHelp;

        //camera movement experimental only debug
        if(state[SDL::C::SDL_SCANCODE_LEFT])
            camera.x += speed;
        if(state[SDL::C::SDL_SCANCODE_RIGHT])
            camera.x -= speed;

        if(state[SDL::C::SDL_SCANCODE_UP])
            camera.y += speed;
        if(state[SDL::C::SDL_SCANCODE_DOWN])
            camera.y -= speed;
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

    //layer 1
    if(isLayerBG1)
    {
        for(lev->pointLayerIt = lev->pointLayerBG1.begin(); lev->pointLayerIt != lev->pointLayerBG1.end(); lev->pointLayerIt++)
        {
            tileSetMap.Draw(SDL::Point(lev->pointLayerIt->first.x*16 + camera.x, lev->pointLayerIt->first.y*16 + camera.y), lev->pointLayerIt->second);
        }
    }

    //layer2
    if(isLayerBG2)
    {
        for(lev->pointLayerIt = lev->pointLayerBG2.begin(); lev->pointLayerIt != lev->pointLayerBG2.end(); lev->pointLayerIt++)
        {
            tileSetMap.Draw(SDL::Point(lev->pointLayerIt->first.x*16 + camera.x, lev->pointLayerIt->first.y*16 + camera.y), lev->pointLayerIt->second);
        }
    }

    //layer3
    if(isLayerBG3)
    {
        for(lev->pointLayerIt = lev->pointLayerBG3.begin(); lev->pointLayerIt != lev->pointLayerBG3.end(); lev->pointLayerIt++)
        {
            tileSetMap.Draw(SDL::Point(lev->pointLayerIt->first.x*16 + camera.x, lev->pointLayerIt->first.y*16 + camera.y), lev->pointLayerIt->second);
        }
    }

    player.draw();

    //forgroundlayer1
    if(isLayerFG1)
    {
        for(lev->pointLayerIt = lev->pointLayerFG1.begin(); lev->pointLayerIt != lev->pointLayerFG1.end(); lev->pointLayerIt++)
        {
            tileSetMap.Draw(SDL::Point(lev->pointLayerIt->first.x*16 + camera.x, lev->pointLayerIt->first.y*16 + camera.y), lev->pointLayerIt->second);
        }
    }

    //forgroundlayer2
    if(isLayerFG2)
    {
        for(lev->pointLayerIt = lev->pointLayerFG2.begin(); lev->pointLayerIt != lev->pointLayerFG2.end(); lev->pointLayerIt++)
        {
            tileSetMap.Draw(SDL::Point(lev->pointLayerIt->first.x*16 + camera.x, lev->pointLayerIt->first.y*16 + camera.y), lev->pointLayerIt->second);
        }
    }

    if(isLayerAttribute)
    {
        int transp = 255/2;
        for(lev->pointLayerAttributesIt = lev->pointLayerAttributes.begin(); lev->pointLayerAttributesIt != lev->pointLayerAttributes.end(); lev->pointLayerAttributesIt++)
        {
            switch(lev->pointLayerAttributesIt->second)
            {
                case 0:
                {
                    renderer.SetDrawColor(255,0,0,transp);
                    break;
                }
                case 1:
                {
                    renderer.SetDrawColor(0,255,0,transp);
                    break;
                }
            }
            renderer.FillRect(SDL::Rect(lev->pointLayerAttributesIt->first.x*16 + camera.x, lev->pointLayerAttributesIt->first.y*16 + camera.y, 16, 16));
        }
    }

    if(isGrid)
    {
        //grid noch nicht komplett optimized
        int TILESIZE = 16;
        renderer.SetDrawColor(255,0,0);
        for(int i = 0; i <= lev->getHeigth(); i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(camera.x, i*16 + camera.y);
            points[1] = SDL::Point(camera.x + 16*lev->getWidth(), i*16 + camera.y);
            renderer.DrawLines(points, 2);
        }

        for(int i = 0; i <= lev->getWidth(); i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(i*16 + camera.x, camera.y);
            points[1] = SDL::Point(i*16 + camera.x, camera.y + 16*lev->getHeigth());
            renderer.DrawLines(points, 2);
        }
    }

    if(isShowHelp)
    {
        std::ostringstream oss;

        oss << "F1 BGLayer 1 " << (isLayerBG1?"true":"false") << "\n";
        oss << "F2 BGLayer 2 " << (isLayerBG2?"true":"false") << "\n";
        oss << "F3 BGLayer 3 " << (isLayerBG3?"true":"false") << "\n";
        oss << "F4 FGLayer 1 " << (isLayerFG1?"true":"false") << "\n";
        oss << "F5 FGLayer 2 " << (isLayerFG2?"true":"false") << "\n";
        oss << "F6 Attributes " << (isLayerAttribute?"true":"false") << "\n";
        oss << "F7 Entities " << (isLayerEntity?"true":"false") << "\n";
        oss << "F8 Grid " << (isGrid?"true":"false") << "\n";
        oss << "F12 Help " << (isShowHelp?"true":"false") << "\n";
        {
            Color c(0, 0, 0);
            //SDL::C::TTF_SetFontHinting(font, ((t & 0x600) >> 9));
            //SDL::C::TTF_SetFontOutline(font, 1);
            Surface surf = font.RenderUTF8_Blended_Wrapped(oss.str(), c, 640);
            Texture t2(renderer, surf);
            t2.SetColorMod(Color(0, 0, 0));
            const Point p(5, 5);
            t2.SetColorMod(Color(0, 0, 0));
            t2.Draw(p);
        }
    }

    /*
    //draw map
    for(uint32_t y = camera.y; y < lev->getHeigth(); y++)
    {
        for(uint32_t x = camera.x; x < lev->getWidth(); x++)
        {
            if(lev->layerAttributes[x][y] == 65535)
                renderer.SetDrawColor(SDL::Color(255,0,128));
            else
            {
                //renderer.SetDrawColor(SDL::Color(255,255,0));
                tileSetMap.Draw(SDL::Point(x*16 + camera.x, y*16 + camera.y), lev->layerAttributes[x][y]);
            }
            //renderer.FillRect(SDL::Rect(x*16 + camera.x, y*16 + camera.y, 16, 16));
            renderer.DrawRect(SDL::Rect(x*16 + camera.x, y*16 + camera.y, 16, 16));
        }
    }*/
    renderer.Present();
}
