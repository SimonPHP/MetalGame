//
// Created by simon on 18.01.19.
//

#include <mlh.h>
#include <sstream>
#include <iterator>

std::vector<std::string> mlh::split(const std::string& str, char tok) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, tok))
    {
        tokens.push_back(token);
    }
    return tokens;
}
