//
// Created by simon on 30.11.18.
//

#include "test.h"

#include "Level.h"

void TestState::Init()
{
    font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 12);

    tileSet = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/platformerPack_character.png" ), SDL::Point(4,2));
    tileSetMap = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/1.png" ), SDL::Point(16,38));

    lev = new Level("0.map");
    lev->processLevelwithTileset(tileSetMap);

    SDL::Point spawn = SDL::Point(0, 0);

    for(uint32_t y = 0; y < lev->getHeigth(); y++)
    {
        for(uint32_t x = 0; x < lev->getWidth(); x++)
        {
            if (lev->ppointLayerAttributes[x][y] == 1)
                spawn = SDL::Point(x*16, y*16);
        }
    }
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
            isLayerBG = !isLayerBG;

        if(state[SDL::C::SDL_SCANCODE_F2])
            isLayerFG = !isLayerFG;

        if(state[SDL::C::SDL_SCANCODE_F3])
            isLayerAttribute = !isLayerAttribute;

        if(state[SDL::C::SDL_SCANCODE_F4])
            isLayerEntity = !isLayerEntity;

        if(state[SDL::C::SDL_SCANCODE_F5])
            isGrid = !isGrid;

        if(state[SDL::C::SDL_SCANCODE_F12])
            isShowHelp = !isShowHelp;

        //camera movement experimental only debug
        if(state[SDL::C::SDL_SCANCODE_LEFT])
            camera.x -= speed;
        if(state[SDL::C::SDL_SCANCODE_RIGHT])
            camera.x += speed;

        if(state[SDL::C::SDL_SCANCODE_UP])
            camera.y -= speed;
        if(state[SDL::C::SDL_SCANCODE_DOWN])
            camera.y += speed;
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

    Point windowSize = game.getWindowSize();
    windowSize.x /= 16;
    windowSize.y /= 16;

    //draw map

    renderer.SetDrawColor(SDL::Color(255,0,255));

    if(isLayerBG)
    {
        for(uint32_t y = std::max(0, camera.y/16); y < camera.y/16 + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = std::max(0, camera.x/16); x < camera.x/16 + windowSize.x && x < lev->getWidth(); x++)
            {
                if(lev->ppointLayerBG1[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*16 - camera.x, y*16 - camera.y), lev->ppointLayerBG1[x][y]);
                }
                if(lev->ppointLayerBG2[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*16 - camera.x, y*16 - camera.y), lev->ppointLayerBG2[x][y]);
                }
                if(lev->ppointLayerBG3[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*16 - camera.x, y*16 - camera.y), lev->ppointLayerBG3[x][y]);
                }
            }
        }
    }

    player.draw();


    if(isLayerFG)
    {
        for(uint32_t y = std::max(0, camera.y/16); y < camera.y/16 + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = std::max(0, camera.x/16); x < camera.x/16 + windowSize.x && x < lev->getWidth(); x++)
            {
                if(lev->ppointLayerFG1[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*16 - camera.x, y*16 - camera.y), lev->ppointLayerFG1[x][y]);
                }
                if(lev->ppointLayerFG2[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*16 - camera.x, y*16 - camera.y), lev->ppointLayerFG2[x][y]);
                }
            }
        }
    }

    if(isLayerAttribute)
    {
        int transp = 255/2;

        for(uint32_t y = std::max(0, camera.y/16); y < camera.y/16 + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = std::max(0, camera.x/16); x < camera.x/16 + windowSize.x && x < lev->getWidth(); x++)
            {
                bool drawAttr = true;
                switch(lev->ppointLayerAttributes[x][y])
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
                    default:
                    {
                        drawAttr = false; //if there is no attribute dont draw
                    }
                }
                if(drawAttr)
                    renderer.FillRect(SDL::Rect(x*16 - camera.x, y*16 - camera.y, 16, 16));
            }
        }
    }

    if(isGrid)
    {
        windowSize = game.getWindowSize();
        int TILESIZE = 16;
        renderer.SetDrawColor(255,0,0);
        for(int i = 0; i < lev->getHeigth()+1; i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(0, i*16)-camera;
            points[1] = SDL::Point(lev->getWidth()*16, i*16)-camera;
            renderer.DrawLines(points, 2);
        }

        for(int i = 0; i < lev->getWidth()+1; i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(i*16, 0)-camera;
            points[1] = SDL::Point(i*16, lev->getHeigth()*16)-camera;
            renderer.DrawLines(points, 2);
        }
    }

    if(isShowHelp)
    {
        std::ostringstream oss;

        oss << "F1 BGLayer 1 " << (isLayerBG?"true":"false") << "\n";
        oss << "F2 FGLayer 2 " << (isLayerFG?"true":"false") << "\n";
        oss << "F3 Attributes " << (isLayerAttribute?"true":"false") << "\n";
        oss << "F4 Entities " << (isLayerEntity?"true":"false") << "\n";
        oss << "F5 Grid " << (isGrid?"true":"false") << "\n";
        oss << "F12 Help " << (isShowHelp?"true":"false") << "\n";
        {
            Surface surf = font.RenderUTF8_Blended_Wrapped(oss.str(), Color(0, 0, 0), 320);
            Texture t2(renderer, surf);
            t2.SetColorMod(Color(0, 0, 0));
            const Point p(5, 5);
            renderer.SetDrawColor(170, 170, 170, 128);
            renderer.FillRect(SDL::Rect(p.x, p.y, surf.w(), surf.h()));
            t2.Draw(p);
        }
    }

    renderer.Present();
}
