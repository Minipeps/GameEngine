#include "MainGame.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    Engine::MainGame mainGame("F:/Programmation/Engine/");
    mainGame.run();

    return EXIT_SUCCESS;
}