#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"

#include <iostream>
#include <string>

// Constructor, just initializes private member variables
MainGame::MainGame(const std::string& assetFolderPath) :
    _screenWidth(1024),
    _screenHeight(768),
    _time(0.0f),
    _window(nullptr),
    _gameState(GameState::PLAY),
    _maxFps(100.0f),
    _assetFolder(assetFolderPath),
    _shaderFolder(_assetFolder + "shaders/")
{}

// Destructor
MainGame::~MainGame()
{
}

// This runs the game
void MainGame::run() {
    initSystems();
    
    // Initialize our sprite. (temporary)
    _sprites.push_back(new Sprite());
    _sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, _assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
    
    _sprites.push_back(new Sprite());
    _sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, _assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
    
    _sprites.push_back(new Sprite());
    _sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, _assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
    
    _sprites.push_back(new Sprite());
    _sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, _assetFolder + "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
    
    // This only returns when the game ends
    gameLoop();
}

//  Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Tell SDL that we want a double buffered window so we dont get
    // any flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Open an SDL window
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // Set up our OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
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
    
    /*
    // Set up glew (optional but recommended)
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize glew!");
    */
    
    // Set the background color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    
    // Turn on VSync (set value to 1)
    SDL_GL_SetSwapInterval(0);
    
    initShaders();
}

void MainGame::initShaders() {
    _colorProgram.compileShaders(_shaderFolder + "colorShading.vert", _shaderFolder + "colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

// This is the main game loop for our program
void MainGame::gameLoop() {
    
    // Will loop until we set _gameState to EXIT
    while (_gameState != GameState::EXIT) {
        float startTicks = SDL_GetTicks();
        
        
        processInput();
        _time += 0.05;
        drawGame();
        calculateFPS();
        
        // print every 10 frames
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            // std::cout << _fps << std::endl;
            frameCounter = 0;
        }
        
        float frameTicks = SDL_GetTicks() - startTicks;
        // Limit fps
        float idealFrameTime = 1000.0f / _maxFps;
        if (idealFrameTime > frameTicks) {
            SDL_Delay(idealFrameTime - frameTicks);
        }
    }
}

// Processes input with SDL
void MainGame::processInput() {
    SDL_Event evnt;
    
    // Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                break;
        }
    }
}

// Draws the game using the almighty OpenGL
void MainGame::drawGame() {
    
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    _colorProgram.use();
    
    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);
    
    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);
    
    
    // Draw our sprite!
    for (int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->draw();
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    _colorProgram.unuse();
    
    // Swap our buffer and draw everything to the screen!
    SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    
    static float prevTicks = SDL_GetTicks();
    
    float currentTicks;
    currentTicks = SDL_GetTicks();
    
    _frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
    
    prevTicks = currentTicks;
    
    int count;
    
    currentFrame++;
    
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }
    
    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;
    
    if (frameTimeAverage != 0) {
        _fps = 1000 / frameTimeAverage;
    } else {
        _fps = 0.0f;
    }
}