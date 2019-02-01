//
// Created by simon on 30.11.18.
//

#include <global.h>
#include <thread>
#include <Entity.h>
#include "test.h"
#include "Level.h"
#include <mlh.h>
#include <math.h>

#define TILESIZE 16
#define ZOOM 1.2

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
    this->tex = new SDL::Texture(renderer);
    this->tex->createBlank(WINDOW_X, WINDOW_Y); //größe bestimmen

    SDL::C::Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    this->mus = SDL::C::Mix_LoadMUS("../assets/music/ichtudirweh.mp3");
    SDL::C::Mix_PlayMusic(this->mus, -1);

    font = TTF::Font("../assets/fonts/RobotoSlab-Bold.ttf", 12);

    //tileSet = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/platformerPack_character_scaled.png" ));
    //tileSetMap = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/tilesetmetall.png" ), SDL::Point(16,100));
    //tileSetMap = Tileset(IMG::LoadTexture( renderer, "../assets/graphics/1.png" ), SDL::Point(16,38));

    SDL::C::SDL_Surface *surf = SDL::C::IMG_Load("../assets/graphics/tilesetmetall.png");
    SDL::C::SDL_SetColorKey(surf, SDL::C::SDL_TRUE, 0);
    Texture tex = Texture(renderer, SDL::C::SDL_CreateTextureFromSurface(renderer, surf));
    tileSetMap = Tileset(tex);

    backTex = IMG::LoadTexture(renderer, "../assets/graphics/back.jpg");

    lev = new Level("11.map");
    lev->processLevelwithTileset(tileSetMap);

    SDL::Point spawn = SDL::Point(0, 0);

    for(uint32_t y = 0; y < lev->getHeigth(); y++)
    {
        for(uint32_t x = 0; x < lev->getWidth(); x++)
        {
            if (lev->ppointLayerEntities[x][y] == 3)
                spawn = SDL::Point(x, y);
        }
    }

    player = new Player(tileSetMap);

    player->setLevel(*lev);

    player->setX((spawn.x+1) * TILESIZE);
    player->setY((spawn.y+1) * TILESIZE);

    this->manager = new EntityManager();

    for(int i = 0; i < this->enemyVec.size(); i++)
    {
        this->enemyVec[i] = new Enemy(tileSetMap);
        this->enemyVec[i]->setX(20000);
        this->enemyVec[i]->setY(50000);
        this->enemyVec[i]->setPlayer(player);
        this->manager->addEntity(this->enemyVec[i]);
    }

    for(uint32_t y = 0; y < lev->getHeigth(); y++)
    {
        for(uint32_t x = 0; x < lev->getWidth(); x++)
        {
            if (lev->ppointLayerEntities[x][y] == 1)
            {
                this->enemyVec[curEnemyPos]->setX(x*16);
                this->enemyVec[curEnemyPos]->setY(y*16);
                curEnemyPos++;
            }
        }
    }

    this->manager->addEntity(player);

    t1 = std::thread(&TestState::handleConsole, this);
}

void TestState::Uninit()
{
    font = TTF::Font();
    image = SDL::Texture();
    t1.join();
    //SDL::C::Mix_Close();
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

    //player->checkCollisionWithLevel(*lev, deltaT);
}

void TestState::Update(const int frame, const float deltaT)
{
    int playerX = (int)player->getX()/TILESIZE;
    int playerY = (int)player->getY()/TILESIZE;

    this->manager->update(deltaT);

    if(player->getCurrentsStateNumber() == 4)
    {
        for(int i = 0; i < this->enemyVec.size(); i++)
        {
            if(player->checkCollisionWithEntity(*enemyVec[i]))
            {
                enemyVec[i]->setX(10000);
                player->exp++;
            }
        }
    } else
    {
        for(int i = 0; i < this->enemyVec.size(); i++)
        {
            if(player->checkCollisionWithEntity(*enemyVec[i]))
            {
                player->setHealth(player->getHealth()-1);

                if(player->getHealth() == 0)
                {
                    player->setX(100);
                    player->setY(500);
                    player->setHealth(100);
                }

            }
        }
    }



    /*SDL::Rect p = SDL::Rect(player->getCurrentState()->getHitboxes()[0].x + player->getX(), player->getCurrentState()->getHitboxes()[0].y + player->getY(), player->getCurrentState()->getHitboxes()[0].w, player->getCurrentState()->getHitboxes()[0].h);
    SDL::Rect e = SDL::Rect(enemy->getCurrentState()->getHitboxes()[0].x + enemy->getX(), enemy->getCurrentState()->getHitboxes()[0].y + player->getY(), enemy->getCurrentState()->getHitboxes()[0].w, enemy->getCurrentState()->getHitboxes()[0].h);

    if(p.CollidesWith(e))
    {
        printf("KOLLISION\n");
    }*/

    //player->setX(mouseX); //only debug
    //player->setY(mouseY);

    camera.x = player->getX() - WINDOW_X/(ZOOM*2);
    camera.y = player->getY() - WINDOW_Y/(ZOOM*2);

}

void TestState::Render(const int frame, const float deltaT)
{
    tex->setAsRenderTarget(); //als target setzten
    //hier sollte man normal rendern können

    renderer.ClearColor(255,255,255);

    backTex.Draw(SDL::Rect(0,0,WINDOW_X,WINDOW_Y));


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

    this->manager->render(renderer, camera);

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

    renderer.setRenderTargetDefault(); //reset draw target
    tex->Draw(SDL::Point(0,0), ZOOM);
    renderer.Present();
}
