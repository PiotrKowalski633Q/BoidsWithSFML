#ifndef BOIDSWITHSFML_AQUARIUM_H
#define BOIDSWITHSFML_AQUARIUM_H

#include <wtypes.h>

#include <SFML/Graphics.hpp>

#include "GameProperties.h"
#include "GlobalFunctions.h"
#include "Boid.h"

class Aquarium
{
private:
    float mBorderLeft, mBorderRight, mBorderTop, mBorderBottom;//coordinates for the aquarium borders that will cause boids to start turning (remember that in SFML point 0,0 is in top left corner)

    sf::Texture mBoidTexture;//a common texture shared by all boids
    std::vector<Boid*> mBoids;//vector for all boids within the aquarium

    sf::Texture mBackgroundTexture;//a texture for aquarium background, it will be scaled to fill the screen
    sf::Sprite mBackgroundSprite;//sprite benefiting from the background texture that will draw it

public:
    //default constructor, its objects shouldn't really be used, it exists as a way of making an aquarium object placeholder
    Aquarium();

    //creates an aquarium object with given amount of boids of given texture and background texture
    Aquarium(int capacity, sf::Texture &boidTexture, sf::Texture &backgroundTexture);

    ~Aquarium();

    void setBorders(float borderLeft, float borderRight, float borderTop, float borderBottom);

    //for each boid in the vector sets its properties according to GameProperties as well as random position and rotation
    void setAllBoidsProperties();

    //updates all boids "simultaneously" (changes are not applied until all boids have been processed) using their condition based functions
    void update(float deltaTime, sf::RenderWindow &window);

    //clears the window, draws the aquarium background and then all the boids
    void draw(sf::RenderWindow &window);
};

#endif //BOIDSWITHSFML_AQUARIUM_H