//
// Created by simon on 18.01.19.
//

#ifndef SDL_GAME_MLH_H
#define SDL_GAME_MLH_H

#include <string>
#include <vector>

class mlh
{
public:
    static std::vector<std::string> split(const std::string& str, char tok);
};

#endif //SDL_GAME_MLH_H
