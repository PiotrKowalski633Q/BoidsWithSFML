#include "../Headers/Game.h"

Game::Game()
:mWindow(sf::RenderWindow( sf::VideoMode( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 32 ), "BoidsWithSFML", sf::Style::Fullscreen )),
mTimeSinceLastFrame(0),
mRenderingFrameTimer(0),
mExpectedRenderingFps(GameProperties::gameExpectedRenderingFps),
mAquarium(),
mIsGamePaused(false)
{

}

void Game::gameLoop()//main loop, it will continuously poll events, read them and terminate only if the window closes
{
    mFrameBegin = std::chrono::steady_clock::now();

    while (mWindow.isOpen())
    {
        mFrameEnd = std::chrono::steady_clock::now();
        mTimeSinceLastFrame = std::chrono::duration_cast<std::chrono::microseconds>(mFrameEnd - mFrameBegin).count();
        mRenderingFrameTimer += mTimeSinceLastFrame;
        mFrameBegin = std::chrono::steady_clock::now();

        processInput();

        if (!mIsGamePaused)
        {
            update(mTimeSinceLastFrame);
            if (1000000.0/mRenderingFrameTimer <= mExpectedRenderingFps)
            {
                draw();
                mRenderingFrameTimer -= 1000000.0/mExpectedRenderingFps;
            }
        }

    }
}

void Game::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent( event ))
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            mWindow.close();
            break;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            mIsGamePaused = true;
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        {
            mIsGamePaused = false;
        }
    }
}

void Game::update(float deltaTime)
{
    mAquarium.update(deltaTime, mWindow);
}

void Game::draw()
{
    mWindow.clear();
    mAquarium.draw(mWindow);
    mWindow.display();
}

void Game::run()
{
    sf::Texture boidTexture, backgroundTexture;
    boidTexture.loadFromFile("Resources/Images/boid.png");
    backgroundTexture.loadFromFile("Resources/Images/reef.png");
    mAquarium = Aquarium(GameProperties::aquariumCapacity, boidTexture, backgroundTexture);
    mAquarium.setBorders(GameProperties::aquariumBorderLeft, GameProperties::aquariumBorderRight, GameProperties::aquariumBorderTop, GameProperties::aquariumBorderBottom);
    mAquarium.setAllBoidsProperties();

    sf::Music music;
    music.openFromFile("Resources/Music/ambient-classical-guitar.ogg");
    music.setLoop(true);
    music.play();

    gameLoop();
}