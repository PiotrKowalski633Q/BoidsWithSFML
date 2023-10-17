#ifndef BOIDSWITHSFML_BOID_H
#define BOIDSWITHSFML_BOID_H

#include <cmath>

#include <SFML/Graphics.hpp>

#include "GameProperties.h"
#include "GlobalFunctions.h"

class Boid
{
private:
    enum Border
    {
        None = 0,
        Left = 1,
        Right = 2,
        Top = 3,
        Bottom = 4
    };

    float mPositionX, mPositionY;//boid position on the screen in X,Y coordinates
    float mHitboxSizeX, mHitboxSizeY;//the hitbox size for collision detection, independent of actual texture size
    float mForwardDirectionVectorX, mForwardDirectionVectorY;//a normalized vector starting at boid origin (middle) and pointing towards where the boid should be moving (the same direction as its head indicates)
    float mLeftDirectionVectorX, mLeftDirectionVectorY;//a normalized vector perpendicular to the forward direction vector for vision calculations

    float mRotation;//current rotation in degrees with 0 being boid pointing upwards (towards negative Y)
    float mSpin;//rotation change over time, this value will be added to the mRotation variable each frame
    float mBorderSightRange;//goes left, right and forward, determines how long the left, right and forward direction vectors will be for vision calculation, used to determine borders in sight range
    float mOtherBoidSightRange;//goes left, right and forward, determines how long the left, right and forward direction vectors will be for vision calculation, used to determine boids in sight range
    float mPredatorSightRange;//goes left, right and forward, determines how long the left, right and forward direction vectors will be for vision calculation, used to determine predators in sight range
    float mMovementSpeed;//boid movement speed in units per mBaseDeltaTime time value
    float mRotationSpeed;//boid rotation speed in units per mBaseDeltaTime time value

    bool mIsTurningLeftDueToBorder;//whether boid is currently turning left due to border interaction
    bool mIsTurningRightDueToBorder;//whether boid is currently turning right due to border interaction

    bool mIsTurningLeftDueToPredator;//whether boid is currently turning left due to predator interaction
    bool mIsTurningRightDueToPredator;//whether boid is currently turning right due to predator interaction

    sf::Sprite mSprite;//boid sprite object represents its visuals (mostly texture and its attributes)

    float mBaseDeltaTime;//what time should the program take for one full update

public:
    //the default constructor for initializing all member variables
    Boid();

    //setters for all necessary member variables
    void setPosition(float x, float y);
    void setHitboxSize(float x, float y);
    void setRotation(float degrees);
    void setBorderSightRange(float sightRange);
    void setOtherBoidSightRange(float sightRange);
    void setPredatorSightRange(float sightRange);
    void setMovementSpeed(float movementSpeed);
    void setRotationSpeed(float rotationSpeed);
    void setBaseDeltaTime(float baseDeltaTime);

    //setters for all necessary mSprite variables
    void setSpriteOrigin(float x, float y);
    void setSpriteScale(float scaleX, float scaleY);
    void setSpriteTexture(sf::Texture &texture);
    void setSpriteTextureRectangle(sf::IntRect rectangle);

    //returns information about whether any of the specified border coordinates are within sight range
    Border getBordersWithinSightRange(float borderLeft, float borderRight, float borderTop, float borderBottom);

    //returns all boids (including self) that lie within sight range
    std::vector<Boid *> getBoidsWithinSightRange(std::vector<Boid *> &allBoids);

    //returns all boids (including self) whose hitboxes intersect with the hitbox of this boid
    std::vector<Boid *> getBoidsCollidingWithThisOne(std::vector<Boid *> &allBoids);

    //updates the spin value based on different conditions, returns whether anything was updated, so whether the condition was true
    bool updateSpinBasedOnBorders(float borderLeft, float borderRight, float borderTop, float borderBottom, float centerX, float centerY);
    bool updateSpinBasedOnPredator(float predatorPositionX, float predatorPositionY);
    bool updateSpinBasedOnCollisionsWithOtherBoids(std::vector<Boid*> &allBoids);
    bool updateSpinBasedOnBoidsInSightRange(std::vector<Boid*> &allBoids);

    //adds the mSpin value to mRotation as a way of updating it and then makes sure the mRotation is in <0,360) range
    void applySpin(float deltaTime);

    //calculates the direction vectors based on rotation
    void recalculateForwardDirectionVectorFromRotation();
    void recalculateLeftDirectionVectorFromRotation();

    //changes the boid position based on its forward direction vector and deltaTime
    void applyMovement(float deltaTime);

    //sets the mSprite position and rotation to the ones specified by mPosition and mRotation and then draws it on the screen
    void draw(sf::RenderWindow &window);
};

#endif //BOIDSWITHSFML_BOID_H
