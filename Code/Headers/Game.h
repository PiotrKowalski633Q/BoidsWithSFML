#ifndef BOIDSWITHSFML_GAME_H
#define BOIDSWITHSFML_GAME_H

#include <chrono>
#include <wtypes.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameProperties.h"
#include "Aquarium.h"

class Game
{
    sf::RenderWindow mWindow;

    std::chrono::steady_clock::time_point mFrameBegin;
    std::chrono::steady_clock::time_point mFrameEnd;
    double mTimeSinceLastFrame;
    double mRenderingFrameTimer;
    double mExpectedRenderingFps;

    Aquarium mAquarium;

    bool mIsGamePaused;

public:
    Game();

private:
    void gameLoop();

    void processInput();
    void update(float deltaTime);
    void draw();

public:
    void run();
};

#endif //BOIDSWITHSFML_GAME_H
