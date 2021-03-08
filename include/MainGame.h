#pragma once

#include "GLSLProgram.h"
#include "Sprite.h"

#include "SDL.h"

#include <deque>
#include <memory>
#include <vector>

namespace Engine {

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
    MainGame( const std::string& assetFolderPath );

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();
    void calculateFPS();

    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    std::string _assetFolder;
    std::string _shaderFolder;

    std::vector<Sprite*> _sprites;

    GLSLProgram _colorProgram;

    float _fps;
    float _maxFps;
    float _prevFrameTicks;
    std::deque<float> _frameTimes;

    float _time;
};

} // namespace Engine
