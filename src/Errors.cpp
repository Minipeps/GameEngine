#include "Errors.h"

#include <iostream>

#include "SDL.h"

namespace Engine
{
// Prints out an error message and exits the game
void fatalError(const std::string &errorString)
{
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
    exit(-1);
}

} // namespace Engine
