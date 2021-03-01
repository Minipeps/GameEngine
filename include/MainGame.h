#pragma once

#include "GLSLProgram.h"
#include "Sprite.h"

#include "SDL.h"

#include <string>
#include <vector>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame(const std::string& assetFolderPath);
    ~MainGame();
    
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
    float _frameTime;
    
    float _time;
};

