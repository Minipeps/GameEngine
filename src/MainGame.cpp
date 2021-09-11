#include "MainGame.h"

#include <iostream>
#include <string>

#include "Errors.h"
#include "ImageLoader.h"

namespace Engine
{
// Constructor, just initializes private member variables
MainGame::MainGame(const std::string &assetFolderPath) : m_screenWidth(1024),
                                                         m_screenHeight(768),
                                                         m_gameState(GameState::PLAY),
                                                         m_assetFolder(assetFolderPath),
                                                         m_shaderFolder(m_assetFolder + "shaders/"),
                                                         m_maxFps(165),
                                                         m_time(0)
{
}

// This runs the game
void MainGame::run()
{
    initSystems();

    // Initialize our sprite. (temporary)
    m_sprites.push_back(new Sprite());
    m_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, m_assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    m_sprites.push_back(new Sprite());
    m_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, m_assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    m_sprites.push_back(new Sprite());
    m_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, m_assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    m_sprites.push_back(new Sprite());
    m_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, m_assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    // This only returns when the game ends
    gameLoop();
}

//  Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems()
{
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Tell SDL that we want a double buffered window so we dont get
    // any flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Open an SDL window
    m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
    if (!m_window)
    {
        fatalError("SDL Window could not be created!");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Set up our OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
    if (!glContext)
    {
        fatalError("SDL_GL context could not be created!");
    }

    // Load OpenGL using glad
    if (!gladLoadGL())
    {
        fatalError("Could not load OpenGL");
    }

    // Display OpenGL version.
    std::printf("*** OpenGL version %s ***\n", glGetString(GL_VERSION));

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Set the background color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // VSync (set to 1 to enable)
    SDL_GL_SetSwapInterval(0);

    initShaders();
}

void MainGame::initShaders()
{
    m_colorProgram.compileShaders(m_shaderFolder + "colorShading.vert", m_shaderFolder + "colorShading.frag");
    m_colorProgram.addAttribute("vertexPosition");
    m_colorProgram.addAttribute("vertexColor");
    m_colorProgram.addAttribute("vertexUV");
    m_colorProgram.linkShaders();
}

// This is the main game loop for our program
void MainGame::gameLoop()
{
    // Will run until we set m_gameState to EXIT
    while (m_gameState != GameState::EXIT)
    {
        auto startTicks = SDL_GetTicks();

        processInput();
        m_time += .05f;
        drawGame();
        calculateFPS();

        auto frameTicks = SDL_GetTicks() - startTicks;
        // Limit fps
        auto idealFrameTime = 1000 / m_maxFps;
        if (idealFrameTime > frameTicks)
        {
            SDL_Delay(idealFrameTime - frameTicks);
        }
    }
}

// Processes input with SDL
void MainGame::processInput()
{
    SDL_Event evnt;
    // Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt))
    {
        switch (evnt.type)
        {
        case SDL_QUIT:
            m_gameState = GameState::EXIT;
            break;
        case SDL_MOUSEMOTION:
            break;
        }
    }
}

// Draws the game using the almighty OpenGL
void MainGame::drawGame()
{
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_colorProgram.use();

    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    GLint timeLocation = m_colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, m_time);

    // Draw our sprite!
    for (const auto &sprite : m_sprites)
    {
        sprite->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    m_colorProgram.unuse();

    // Swap our buffer and draw everything to the screen!
    SDL_GL_SwapWindow(m_window);
}

// Compute FPS using circular mean on 10 successive frames
void MainGame::calculateFPS()
{
    auto m_currentFrameTick = SDL_GetTicks();

    auto frameTime{m_currentFrameTick - m_prevFrameTicks};
    m_frameTimes.push_front(frameTime);

    if (m_frameTimes.size() > 10)
    {
        m_frameTimes.pop_back();
    }

    auto frameTimeAverage{0u};
    for (const auto &t : m_frameTimes)
    {
        frameTimeAverage += t;
    }
    frameTimeAverage /= 10;

    m_fps = frameTimeAverage == 0 ? 0 : 1000 / frameTimeAverage;

    // Swap ticks to keep previous tick in second component
    m_prevFrameTicks = m_currentFrameTick;
}

} // namespace Engine
