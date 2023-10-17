#include "../Headers/Aquarium.h"

Aquarium::Aquarium()
{

}

Aquarium::Aquarium(int capacity, sf::Texture &boidTexture, sf::Texture &backgroundTexture)
:mBoidTexture(boidTexture),
mBackgroundTexture(backgroundTexture)
{
    for (int i=0; i<capacity; i++)
    {
        Boid *boid = new Boid();
        mBoids.push_back(boid);
    }

    mBackgroundSprite.setTexture(backgroundTexture);
    mBackgroundSprite.setOrigin(0,0);
    mBackgroundSprite.setScale(GetSystemMetrics(SM_CXSCREEN)/1920.0, GetSystemMetrics(SM_CYSCREEN)/1080.0);
    mBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    mBackgroundSprite.setPosition(0,0);
    mBackgroundSprite.setRotation(0);
}

Aquarium::~Aquarium()
{

}

void Aquarium::setBorders(float borderLeft, float borderRight, float borderTop, float borderBottom)
{
    mBorderLeft = borderLeft;
    mBorderRight = borderRight;
    mBorderTop = borderTop;
    mBorderBottom = borderBottom;
}

void Aquarium::setAllBoidsProperties()
{
    for (int i=0; i<mBoids.size(); i++)
    {
        mBoids[i]->setPosition(GlobalFunctions::getRandomValueInRange(mBorderLeft, mBorderRight), GlobalFunctions::getRandomValueInRange(mBorderTop, mBorderBottom));
        mBoids[i]->setHitboxSize(GameProperties::boidHitboxSizeX, GameProperties::boidHitboxSizeY);
        mBoids[i]->setRotation(GlobalFunctions::getRandomValueInRange(0, 360));
        mBoids[i]->setBorderSightRange(GameProperties::boidBorderSightRange);
        mBoids[i]->setOtherBoidSightRange(GameProperties::boidOtherBoidSightRange);
        mBoids[i]->setPredatorSightRange(GameProperties::boidPredatorSightRange);
        mBoids[i]->setMovementSpeed(GameProperties::boidMovementSpeed);
        mBoids[i]->setRotationSpeed(GameProperties::boidRotationSpeed);
        mBoids[i]->setBaseDeltaTime(GameProperties::gameBaseDeltaTime);
        mBoids[i]->setSpriteTexture(mBoidTexture);
        mBoids[i]->setSpriteOrigin(100, 100);
        mBoids[i]->setSpriteScale(GameProperties::boidSpriteScaleX, GameProperties::boidSpriteScaleY);
        mBoids[i]->setSpriteTextureRectangle(sf::IntRect(0, 0, 200, 200));
    }
}

void Aquarium::update(float deltaTime, sf::RenderWindow &window)
{
    for (int i=0; i<mBoids.size(); i++)
    {
        bool areAnyBordersInSightRange = mBoids[i]->updateSpinBasedOnBorders(mBorderLeft, mBorderRight, mBorderTop, mBorderBottom, mBorderRight/2, mBorderBottom/2);
        if (!areAnyBordersInSightRange)
        {
            bool isPredatorInSightRange = mBoids[i]->updateSpinBasedOnPredator(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            if (!isPredatorInSightRange)
            {
                bool areThereAnyCollisionsWithOtherBoids = mBoids[i]->updateSpinBasedOnCollisionsWithOtherBoids(mBoids);
                if (!areThereAnyCollisionsWithOtherBoids)
                {
                    mBoids[i]->updateSpinBasedOnBoidsInSightRange(mBoids);
                }
            }
        }

        mBoids[i]->applySpin(deltaTime);
        mBoids[i]->recalculateForwardDirectionVectorFromRotation();
        mBoids[i]->recalculateLeftDirectionVectorFromRotation();
        mBoids[i]->applyMovement(deltaTime);
    }
}

void Aquarium::draw(sf::RenderWindow &window)
{
    window.draw(mBackgroundSprite);
    for (int i=0; i<mBoids.size(); i++)
    {
        mBoids[i]->draw(window);
    }
}