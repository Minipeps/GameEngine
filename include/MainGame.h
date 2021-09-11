#pragma once

#include <deque>
#include <memory>
#include <vector>

#include "GLSLProgram.h"
#include "SDL.h"
#include "Sprite.h"

namespace Engine
{
enum class GameState
{
    PLAY,
    EXIT
};

class MainGame
{
public:
    explicit MainGame(const std::string &assetFolderPath);

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();
    void calculateFPS();

    SDL_Window *m_window;
    int m_screenWidth{1024};
    int m_screenHeight{768};
    GameState m_gameState{GameState::PLAY};

    std::string m_assetFolder;
    std::string m_shaderFolder;

    std::vector<Sprite *> m_sprites;

    GLSLProgram m_colorProgram;

    uint32_t m_fps;
    uint32_t m_maxFps{165};
    uint32_t m_prevFrameTicks;
    std::deque<uint32_t> m_frameTimes;

    float m_time{0.f};
};

} // namespace Engine
