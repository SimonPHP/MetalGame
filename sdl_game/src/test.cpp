//
// Created by simon on 30.11.18.
//

#include <Entity.h>
#include "test.h"

#include "Level.h"

#define TILESIZE 16

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
                spawn = SDL::Point(x, y);
        }
    }

    player.setX((spawn.x+1) * TILESIZE);
    player.setY((spawn.y+1) * TILESIZE);
    player.setH(TILESIZE);
    player.setW(TILESIZE);

    //player.addBoundarie(SDL::Rect(0,0,16,32));
    //player.addBoundarie(SDL::Rect(16,0,16,16));
    //player.addBoundarie(SDL::Rect(16,16,64,16));

    player.addHitbox(SDL::Rect(0,0,32,32));
    player.addHitbox(SDL::Rect(0,128,32,32));

    camera.y = 2500;

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

    const SDL::Uint8 *state = SDL::C::SDL_GetKeyboardState(NULL);

    int speed = 50;

    while (Event::Poll(evt))
    {
        if (game.HandleEvent(evt))
            continue;

        if(evt.type() == Event::Type::MOUSEMOTION)
        {
            mouseX = evt.MouseMotion().x + camera.x;
            mouseY = evt.MouseMotion().y + camera.y;
        }

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

    player.checkCollision(*lev);

}

void TestState::Update(const int frame, const float deltaT)
{

    player.setX(mouseX);
    player.setY(mouseY);

    int playerX = (int)player.getX()/TILESIZE;
    int playerY = (int)player.getY()/TILESIZE;

    if(lev->ppointLayerAttributes[std::max(0,playerX)][std::max(0,playerY+1)] == 0)
        player.setCollisionDown();

    player.update(deltaT);
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
    windowSize.x /= TILESIZE;
    windowSize.y /= TILESIZE;

    //draw map

    renderer.SetDrawColor(SDL::Color(255,0,255));

    if(isLayerBG)
    {
        for(uint32_t y = std::max(0, camera.y/TILESIZE); y < camera.y/TILESIZE + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = std::max(0, camera.x/TILESIZE); x < camera.x/TILESIZE + windowSize.x && x < lev->getWidth(); x++)
            {
                if(lev->ppointLayerBG1[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*TILESIZE - camera.x, y*TILESIZE - camera.y), lev->ppointLayerBG1[x][y]);
                }
                if(lev->ppointLayerBG2[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*TILESIZE - camera.x, y*TILESIZE - camera.y), lev->ppointLayerBG2[x][y]);
                }
                if(lev->ppointLayerBG3[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*TILESIZE - camera.x, y*TILESIZE - camera.y), lev->ppointLayerBG3[x][y]);
                }
            }
        }
    }

    player.render(renderer, camera);

    if(isLayerFG)
    {
        for(uint32_t y = std::max(0, camera.y/TILESIZE); y < camera.y/TILESIZE + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = std::max(0, camera.x/TILESIZE); x < camera.x/TILESIZE + windowSize.x && x < lev->getWidth(); x++)
            {
                if(lev->ppointLayerFG1[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*TILESIZE - camera.x, y*TILESIZE - camera.y), lev->ppointLayerFG1[x][y]);
                }
                if(lev->ppointLayerFG2[x][y].x < 65535)
                {
                    tileSetMap.Draw(SDL::Point(x*TILESIZE - camera.x, y*TILESIZE - camera.y), lev->ppointLayerFG2[x][y]);
                }
            }
        }
    }

    if(isLayerAttribute)
    {
        int transp = 255/2;

        for(uint32_t y = std::max(0, camera.y/TILESIZE); y < camera.y/TILESIZE + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = std::max(0, camera.x/TILESIZE); x < camera.x/TILESIZE + windowSize.x && x < lev->getWidth(); x++)
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
                    renderer.FillRect(SDL::Rect(x*TILESIZE - camera.x, y*TILESIZE - camera.y, 16, 16));
            }
        }
    }

    if(isGrid)
    {
        windowSize = game.getWindowSize();
        renderer.SetDrawColor(255,0,0);
        for(int i = 0; i < lev->getHeigth()+1; i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(0, i*TILESIZE)-camera;
            points[1] = SDL::Point(lev->getWidth()*TILESIZE, i*TILESIZE)-camera;
            renderer.DrawLines(points, 2);
        }

        for(int i = 0; i < lev->getWidth()+1; i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(i*TILESIZE, 0)-camera;
            points[1] = SDL::Point(i*TILESIZE, lev->getHeigth()*TILESIZE)-camera;
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
