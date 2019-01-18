//
// Created by simon on 30.11.18.
//

#include <global.h>

#include <thread>

#include <Entity.h>
#include "test.h"

#include "Level.h"
#include <mlh.h>

#define TILESIZE 16

void TestState::handleConsole(){
    std::cout << "DEV CONSOLE" << std::endl;

    std::string command;

    bool run = true;

    while (run) //TODO mehr befehle einbauen
    {
        std::getline(std::cin, command);
        std::vector<std::string> commands = mlh::split(command, ' ');

        if(commands[0] == "exit")
            run = false;
        else if(commands[0] == "set")
        {
            if( commands.size() < 2 )
                std::cout << "zu wenig parameter" << std::endl;
            else if(commands[1] == "speed")
            {
                this->player->setSpeed(stoi(commands[2]));
            }
            else if(commands[1] == "jump")
            {
                this->player->setJumpHeight(stoi(commands[2]));
            }
        }
        else
            printf("unknown command: %s", command.c_str());
    }
    std::printf("EXIT DEV CONSOLE\n");
}

void TestState::Init()
{
    font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 12);

    tileSet = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/platformerPack_character_scaled.png" ));
    //tileSetMap = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/tilesetmetall.png" ), SDL::Point(16,100));
    //tileSetMap = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/1.png" ), SDL::Point(16,38));

    SDL::C::SDL_Surface *surf = SDL::C::IMG_Load("../assets/graphics/tilesetmetallneu.png");
    SDL::C::SDL_SetColorKey(surf, SDL::C::SDL_TRUE, 0);
    Texture tex = Texture(renderer, SDL::C::SDL_CreateTextureFromSurface(renderer, surf));
    tileSetMap = Tileset(tex);

    lev = new Level("8.map");
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

    player = new Player(tileSetMap);

    player->setX((spawn.x+1) * TILESIZE);
    player->setY((spawn.y+1) * TILESIZE);

    t1 = std::thread(&TestState::handleConsole, this);
}

void TestState::Uninit()
{
    font = TTF::Font();
    image = SDL::Texture();
    t1.join();
}

void TestState::Events(const int frame, const float deltaT)
{
    Event::Pump();
    Event evt;

    player->events(evt, deltaT);

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

/*
        if(state[SDL::C::SDL_SCANCODE_LEFT])
            camera.x -= speed;
        if(state[SDL::C::SDL_SCANCODE_RIGHT])
            camera.x += speed;

        if(state[SDL::C::SDL_SCANCODE_UP])
            camera.y -= speed;
        if(state[SDL::C::SDL_SCANCODE_DOWN])
            camera.y += speed;
*/
    }

    player->checkCollisionWithLevel(*lev, deltaT);
}

void TestState::Update(const int frame, const float deltaT)
{
    int playerX = (int)player->getX()/TILESIZE;
    int playerY = (int)player->getY()/TILESIZE;
    player->update(deltaT);

    //player->setX(mouseX); //only debug
    //player->setY(mouseY);

    camera.x = player->getX() - WINDOW_X/2;
    camera.y = player->getY() - WINDOW_Y/2;

}

void TestState::Render(const int frame, const float deltaT)
{
    renderer.ClearColor(255,255,255);
    {
        image.Draw(Rect(0, 0, WINDOW_X, WINDOW_Y));
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
        for(uint32_t y = (uint32_t)std::max(0, camera.y/TILESIZE); y < (uint32_t)camera.y/TILESIZE + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = (uint32_t)std::max(0, camera.x/TILESIZE); x < (uint32_t)camera.x/TILESIZE + windowSize.x && x < lev->getWidth(); x++)
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

    player->render(renderer, camera);

    if(isLayerFG)
    {
        for(uint32_t y = (uint32_t)std::max(0, camera.y/TILESIZE); y < (uint32_t)camera.y/TILESIZE + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = (uint32_t)std::max(0, camera.x/TILESIZE); x < (uint32_t)camera.x/TILESIZE + windowSize.x && x < lev->getWidth(); x++)
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

        for(uint32_t y = (uint32_t)std::max(0, camera.y/TILESIZE); y < (uint32_t)camera.y/TILESIZE + windowSize.y && y < lev->getHeigth(); y++)
        {
            for(uint32_t x = (uint32_t)std::max(0, camera.x/TILESIZE); x < (uint32_t)camera.x/TILESIZE + windowSize.x && x < lev->getWidth(); x++)
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
        for(uint32_t i = 0; i < lev->getHeigth()+1; i++)
        {
            SDL::Point points[2];
            points[0] = SDL::Point(0, i*TILESIZE)-camera;
            points[1] = SDL::Point(lev->getWidth()*TILESIZE, i*TILESIZE)-camera;
            renderer.DrawLines(points, 2);
        }

        for(uint32_t i = 0; i < lev->getWidth()+1; i++)
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
