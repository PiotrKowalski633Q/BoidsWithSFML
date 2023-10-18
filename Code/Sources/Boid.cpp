#include "../Headers/Boid.h"

Boid::Boid()
:mPositionX(0),
mPositionY(0),
mHitboxSizeX(0),
mHitboxSizeY(0),
mForwardDirectionVectorX(0),
mForwardDirectionVectorY(0),
mRotation(0),
mSpin(0),
mBorderSightRange(0),
mOtherBoidSightRange(0),
mPredatorSightRange(0),
mMovementSpeed(0),
mRotationSpeed(0),
mBaseDeltaTime(0),
mIsTurningLeftDueToBorder(false),
mIsTurningRightDueToBorder(false),
mIsTurningLeftDueToPredator(false),
mBaseColor(255, 255, 255),
mVaryingColor(0, 0, 0),
mIsTurningRightDueToPredator(false)
{

}

void Boid::setPosition(float x, float y)
{
    mPositionX = x;
    mPositionY = y;
}

void Boid::setHitboxSize(float x, float y)
{
    mHitboxSizeX = x;
    mHitboxSizeY = y;
}

void Boid::setRotation(float degrees)
{
    mRotation = degrees;
}

void Boid::setBorderSightRange(float sightRange)
{
    mBorderSightRange = sightRange;
}

void Boid::setOtherBoidSightRange(float sightRange)
{
    mOtherBoidSightRange = sightRange;
}

void Boid::setPredatorSightRange(float sightRange)
{
    mPredatorSightRange = sightRange;
}

void Boid::setMovementSpeed(float movementSpeed)
{
    mMovementSpeed = movementSpeed;
}

void Boid::setRotationSpeed(float rotationSpeed)
{
    mRotationSpeed = rotationSpeed;
}

void Boid::setBaseDeltaTime(float baseDeltaTime)
{
    mBaseDeltaTime = baseDeltaTime;
}

void Boid::setSpriteOrigin(float x, float y)
{
    mSprite.setOrigin(x, y);
}

void Boid::setSpriteScale(float scaleX, float scaleY)
{
    mSprite.setScale(scaleX, scaleY);
}

void Boid::setSpriteTexture(sf::Texture &texture)
{
    mSprite.setTexture(texture);
}

void Boid::setSpriteTextureRectangle(sf::IntRect rectangle)
{
    mSprite.setTextureRect(rectangle);
}

void Boid::setBaseColor(int red, int green, int blue)
{
    mBaseColor = sf::Color(red, green, blue);
}

void Boid::setVaryingColor(int red, int green, int blue)
{
    mVaryingColor = sf::Color(red, green, blue);
}

Boid::Border Boid::getBordersWithinSightRange(float borderLeft, float borderRight, float borderTop, float borderBottom)
{
    float furthestForwardSightPointX = mPositionX + mForwardDirectionVectorX * mBorderSightRange;
    float furthestForwardSightPointY = mPositionY + mForwardDirectionVectorY * mBorderSightRange;

    float furthestLeftSightPointX = mPositionX + mLeftDirectionVectorX * mBorderSightRange;
    float furthestLeftSightPointY = mPositionY + mLeftDirectionVectorY * mBorderSightRange;

    float furthestRightSightPointX = mPositionX + mLeftDirectionVectorX * -1 * mBorderSightRange;
    float furthestRightSightPointY = mPositionY + mLeftDirectionVectorY * -1 * mBorderSightRange;

    if (furthestForwardSightPointX - borderLeft <= 0 || furthestLeftSightPointX  - borderLeft <= 0 || furthestRightSightPointX - borderLeft <= 0)
    {
        return Border::Left;
    }
    else if (borderRight - furthestForwardSightPointX <= 0 || borderRight - furthestLeftSightPointX <= 0 || borderRight - furthestRightSightPointX <= 0)
    {
        return Border::Right;
    }
    else if (furthestForwardSightPointY - borderTop <= 0 || furthestLeftSightPointY - borderTop <= 0 || furthestRightSightPointY - borderTop <= 0)
    {
        return Border::Top;
    }
    else if (borderBottom - furthestForwardSightPointY <= 0 || borderBottom - furthestLeftSightPointY <= 0 || borderBottom - furthestRightSightPointY <= 0)
    {
        return Border::Bottom;
    }
    else
    {
        return Border::None;
    }
}

std::vector<Boid *> Boid::getBoidsWithinSightRange(std::vector<Boid *> &allBoids)
{
    std::vector<Boid *> boidsInSightRange;

    float furthestForwardSightPointX = mPositionX + mForwardDirectionVectorX * mOtherBoidSightRange;
    float furthestForwardSightPointY = mPositionY + mForwardDirectionVectorY * mOtherBoidSightRange;

    float furthestLeftSightPointX = mPositionX + mLeftDirectionVectorX * mOtherBoidSightRange;
    float furthestLeftSightPointY = mPositionY + mLeftDirectionVectorY * mOtherBoidSightRange;

    float furthestRightSightPointX = mPositionX + mLeftDirectionVectorX * -1 * mOtherBoidSightRange;
    float furthestRightSightPointY = mPositionY + mLeftDirectionVectorY * -1 * mOtherBoidSightRange;

    for (int i = 0; i < allBoids.size(); i++)
    {
        if      (
                (allBoids[i]->mPositionX <= mPositionX || allBoids[i]->mPositionX <= furthestForwardSightPointX || allBoids[i]->mPositionX <= furthestLeftSightPointX || allBoids[i]->mPositionX <= furthestRightSightPointX) &&
                (allBoids[i]->mPositionX >= mPositionX || allBoids[i]->mPositionX >= furthestForwardSightPointX || allBoids[i]->mPositionX >= furthestLeftSightPointX || allBoids[i]->mPositionX >= furthestRightSightPointX) &&
                (allBoids[i]->mPositionY <= mPositionY || allBoids[i]->mPositionY <= furthestForwardSightPointY || allBoids[i]->mPositionY <= furthestLeftSightPointY || allBoids[i]->mPositionY <= furthestRightSightPointY) &&
                (allBoids[i]->mPositionY >= mPositionY || allBoids[i]->mPositionY >= furthestForwardSightPointY || allBoids[i]->mPositionY >= furthestLeftSightPointY || allBoids[i]->mPositionY >= furthestRightSightPointY)
                )//condition for other boids to be in sight range
        {
            boidsInSightRange.push_back(allBoids[i]);
        }
    }

    return boidsInSightRange;
}

std::vector<Boid *> Boid::getBoidsCollidingWithThisOne(std::vector<Boid *> &allBoids)
{
    std::vector<Boid *> boidsCollidingWithThisOne;

    float selfLeftBorder = mPositionX - (mHitboxSizeX/2);
    float selfRightBorder = mPositionX + (mHitboxSizeX/2);
    float selfTopBorder = mPositionY - (mHitboxSizeY/2);
    float selfBottomBorder = mPositionY + (mHitboxSizeY/2);

    float otherLeftBorder;
    float otherRightBorder;
    float otherTopBorder;
    float otherBottomBorder;

    for (int i = 0; i < allBoids.size(); i++)
    {
        otherLeftBorder = allBoids[i]->mPositionX - (mHitboxSizeX/2);
        otherRightBorder = allBoids[i]->mPositionX + (mHitboxSizeX/2);
        otherTopBorder = allBoids[i]->mPositionY - (mHitboxSizeY/2);
        otherBottomBorder = allBoids[i]->mPositionY + (mHitboxSizeY/2);

        if      (
                (
                        (selfLeftBorder <= otherLeftBorder && selfRightBorder >= otherLeftBorder) ||
                        (otherLeftBorder <= selfLeftBorder && otherRightBorder >= selfLeftBorder)
                ) &&
                (
                        (selfTopBorder <= otherTopBorder && selfBottomBorder >= otherTopBorder) ||
                        (otherTopBorder <= selfTopBorder && otherBottomBorder >= selfTopBorder)
                )
                )//condition for boids to collide
        {
            boidsCollidingWithThisOne.push_back(allBoids[i]);
        }
    }

    return boidsCollidingWithThisOne;
}

bool Boid::updateSpinBasedOnBorders(float borderLeft, float borderRight, float borderTop, float borderBottom, float centerX, float centerY)
{
    Border border = getBordersWithinSightRange(borderLeft, borderRight, borderTop, borderBottom);

    if (border == Border::None)
    {
        mIsTurningLeftDueToBorder = false;
        mIsTurningRightDueToBorder = false;
        mSpin = 0;
        return false;
    }
    else
    {
        if (!mIsTurningLeftDueToBorder && !mIsTurningRightDueToBorder)
        {
            if (border == Border::Left)
            {
                if (mRotation <= 270 && mRotation >= 180)
                {
                    mIsTurningLeftDueToBorder = true;
                }
                else if (mRotation >= 270 && mRotation <= 360)
                {
                    mIsTurningRightDueToBorder = true;
                }
            }
            else if (border == Border::Right)
            {
                if (mRotation <= 90 && mRotation >= 0)
                {
                    mIsTurningLeftDueToBorder = true;
                }
                else if (mRotation >= 90 && mRotation <= 180)
                {
                    mIsTurningRightDueToBorder = true;
                }
            }
            else if (border == Border::Top)
            {
                if (mRotation <= 360 && mRotation >= 270)
                {
                    mIsTurningLeftDueToBorder = true;
                }
                else if (mRotation >= 0 && mRotation <= 90)
                {
                    mIsTurningRightDueToBorder = true;
                }
            }
            else //border == bottom
            {
                if (mRotation <= 180 && mRotation >= 90)
                {
                    mIsTurningLeftDueToBorder = true;
                }
                else if (mRotation >= 180 && mRotation <= 270)
                {
                    mIsTurningRightDueToBorder = true;
                }
            }
        }
    }

    float vectorTowardsCenterX = centerX - mPositionX;
    float vectorTowardsCenterY = centerY - mPositionY;

    float rotationTowardsCenter = GlobalFunctions::getObjectRotationFromDirectionVector(vectorTowardsCenterX, vectorTowardsCenterY);

    float rotationalDifference = std::abs(rotationTowardsCenter - mRotation);
    if (rotationalDifference > 180)
    {
        rotationalDifference = 360-rotationalDifference;
    }

    if (rotationalDifference > GameProperties::boidCenterRotationMarginOfError)
    {
        if (mIsTurningLeftDueToBorder)
        {
            mSpin -= mRotationSpeed;
        }
        else if (mIsTurningRightDueToBorder)
        {
            mSpin += mRotationSpeed;
        }
    }

    return true;
}

bool Boid::updateSpinBasedOnPredator(float predatorPositionX, float predatorPositionY)
{
    float furthestForwardSightPointX = mPositionX + mForwardDirectionVectorX * mPredatorSightRange;
    float furthestForwardSightPointY = mPositionY + mForwardDirectionVectorY * mPredatorSightRange;

    float furthestLeftSightPointX = mPositionX + mLeftDirectionVectorX * mPredatorSightRange;
    float furthestLeftSightPointY = mPositionY + mLeftDirectionVectorY * mPredatorSightRange;

    float furthestRightSightPointX = mPositionX + mLeftDirectionVectorX * -1 * mPredatorSightRange;
    float furthestRightSightPointY = mPositionY + mLeftDirectionVectorY * -1 * mPredatorSightRange;

    if      (
            (predatorPositionX <= mPositionX || predatorPositionX <= furthestForwardSightPointX || predatorPositionX <= furthestLeftSightPointX || predatorPositionX <= furthestRightSightPointX) &&
            (predatorPositionX >= mPositionX || predatorPositionX >= furthestForwardSightPointX || predatorPositionX >= furthestLeftSightPointX || predatorPositionX >= furthestRightSightPointX) &&
            (predatorPositionY <= mPositionY || predatorPositionY <= furthestForwardSightPointY || predatorPositionY <= furthestLeftSightPointY || predatorPositionY <= furthestRightSightPointY) &&
            (predatorPositionY >= mPositionY || predatorPositionY >= furthestForwardSightPointY || predatorPositionY >= furthestLeftSightPointY || predatorPositionY >= furthestRightSightPointY)
            )//condition for predator to be in sight range
    {
        if (!mIsTurningLeftDueToPredator && !mIsTurningRightDueToPredator)
        {
            if ( (furthestForwardSightPointX - mPositionX)*(predatorPositionY - furthestForwardSightPointY) - (furthestForwardSightPointY - mPositionY)*(predatorPositionX - furthestForwardSightPointX) > 0 )
                //condition for the predator to be on right side of boid forward vector
            {
                mIsTurningLeftDueToPredator = true;
            }
            else
            {
                mIsTurningRightDueToPredator = true;
            }
        }
    }
    else
    {
        mIsTurningLeftDueToPredator = false;
        mIsTurningRightDueToPredator = false;
        mSpin = 0;
        return false;
    }

    if (mIsTurningLeftDueToPredator)
    {
        mSpin -= mRotationSpeed;
    }
    else if (mIsTurningRightDueToPredator)
    {
        mSpin += mRotationSpeed;
    }

    return true;
}

bool Boid::updateSpinBasedOnCollisionsWithOtherBoids(std::vector<Boid*> &allBoids)
{
    std::vector<Boid *> boidsCollidingWithThisOne = getBoidsCollidingWithThisOne(allBoids);

    if (boidsCollidingWithThisOne.size() <= 1)
    {
        mSpin = 0;
        return false;
    }

    int closestBoidNumber = 0;
    float closestBoidDistance = std::numeric_limits<float>::max();

    for (int i = 0; i < boidsCollidingWithThisOne.size(); i++)
    {
        float boidDistance = std::sqrt(pow(std::abs(boidsCollidingWithThisOne[i]->mPositionX-mPositionX), 2)+pow(std::abs(boidsCollidingWithThisOne[i]->mPositionY-mPositionY), 2));
        if (boidDistance<closestBoidDistance && boidsCollidingWithThisOne[i]!=this)
        {
            closestBoidNumber = i;
            closestBoidDistance = boidDistance;
        }
    }

    float directionVectorTowardsClosestBoidX = boidsCollidingWithThisOne[closestBoidNumber]->mPositionX-mPositionX;
    float directionVectorTowardsClosestBoidY = boidsCollidingWithThisOne[closestBoidNumber]->mPositionY-mPositionY;

    float rotationTowardsClosestBoid = GlobalFunctions::getObjectRotationFromDirectionVector(directionVectorTowardsClosestBoidX, directionVectorTowardsClosestBoidY);

    float rotationalDifference = std::abs(rotationTowardsClosestBoid - mRotation);
    if (rotationalDifference > 180)
    {
        rotationalDifference = 360-rotationalDifference;
    }

    if ((rotationTowardsClosestBoid - mRotation <= 180 && rotationTowardsClosestBoid - mRotation >=0) || 360 - mRotation + rotationTowardsClosestBoid - 0 <= 180)
    {
        mSpin -= std::min(mRotationSpeed, rotationalDifference);
    }
    else
    {
        mSpin += std::min(mRotationSpeed, rotationalDifference);
    }

    return true;
}

bool Boid::updateSpinBasedOnBoidsInSightRange(std::vector<Boid *> &allBoids)
{
    std::vector<Boid *> boidsInSightRange = getBoidsWithinSightRange(allBoids);

    if (boidsInSightRange.size() <= 1)
    {
        mSpin = 0;
        return false;
    }

    float sumOfForwardDirectionVectorsXOfBoidsInSightRange = 0;
    float sumOfForwardDirectionVectorsYOfBoidsInSightRange = 0;

    int numberOfBoidsInSightRange = boidsInSightRange.size();

    for (int i = 0; i < numberOfBoidsInSightRange; i++)
    {
        sumOfForwardDirectionVectorsXOfBoidsInSightRange += boidsInSightRange[i]->mForwardDirectionVectorX;
        sumOfForwardDirectionVectorsYOfBoidsInSightRange += boidsInSightRange[i]->mForwardDirectionVectorY;
    }

    float averageRotationOfOtherBoidsInSightRange = GlobalFunctions::getObjectRotationFromDirectionVector(sumOfForwardDirectionVectorsXOfBoidsInSightRange, sumOfForwardDirectionVectorsYOfBoidsInSightRange);

    float rotationalDifference = std::abs(averageRotationOfOtherBoidsInSightRange - mRotation);
    if (rotationalDifference > 180)
    {
        rotationalDifference = 360-rotationalDifference;
    }

    if (rotationalDifference >= GameProperties::boidMinimumRotationalDifference && rotationalDifference <= GameProperties::boidMaximumRotationalDifference)
    {
        if ((averageRotationOfOtherBoidsInSightRange - mRotation <= 180 && averageRotationOfOtherBoidsInSightRange - mRotation >=0) || 360 - mRotation + averageRotationOfOtherBoidsInSightRange - 0 <= 180)
        {
            mSpin += std::min(mRotationSpeed, rotationalDifference);
        }
        else
        {
            mSpin -= std::min(mRotationSpeed, rotationalDifference);
        }
    }

    return true;
}

bool Boid::updateColorBasedOnBoidsInSightRange(std::vector<Boid*> &allBoids)
{
    std::vector<Boid *> boidsInSightRange = getBoidsWithinSightRange(allBoids);

    if (boidsInSightRange.size() <= 1)
    {
        mVaryingColor = sf::Color(0, 0, 0);
        return false;
    }

    float sumOfRedColorFactorsOfBoidsInSightRange = 0;
    float sumOfGreenColorFactorsOfBoidsInSightRange = 0;
    float sumOfBlueColorFactorsOfBoidsInSightRange = 0;

    int numberOfBoidsInSightRange = boidsInSightRange.size();

    for (int i = 0; i < numberOfBoidsInSightRange; i++)
    {
        if ((boidsInSightRange[i]->mVaryingColor.r == 0 && boidsInSightRange[i]->mVaryingColor.g == 0 && boidsInSightRange[i]->mVaryingColor.b == 0) || boidsInSightRange[i] == this)
        {
            sumOfRedColorFactorsOfBoidsInSightRange += boidsInSightRange[i]->mBaseColor.r;
            sumOfGreenColorFactorsOfBoidsInSightRange += boidsInSightRange[i]->mBaseColor.g;
            sumOfBlueColorFactorsOfBoidsInSightRange += boidsInSightRange[i]->mBaseColor.b;
        }
        else
        {
            sumOfRedColorFactorsOfBoidsInSightRange += boidsInSightRange[i]->mVaryingColor.r;
            sumOfGreenColorFactorsOfBoidsInSightRange += boidsInSightRange[i]->mVaryingColor.g;
            sumOfBlueColorFactorsOfBoidsInSightRange += boidsInSightRange[i]->mVaryingColor.b;
        }
    }

    float averageRedColorFactorsOfBoidsInSightRange = sumOfRedColorFactorsOfBoidsInSightRange/numberOfBoidsInSightRange;
    float averageGreenColorFactorsOfBoidsInSightRange = sumOfGreenColorFactorsOfBoidsInSightRange/numberOfBoidsInSightRange;
    float averageBlueColorFactorsOfBoidsInSightRange = sumOfBlueColorFactorsOfBoidsInSightRange/numberOfBoidsInSightRange;

    GlobalFunctions::increaseColorIntensity(averageRedColorFactorsOfBoidsInSightRange, averageGreenColorFactorsOfBoidsInSightRange, averageBlueColorFactorsOfBoidsInSightRange);

    mVaryingColor = sf::Color(averageRedColorFactorsOfBoidsInSightRange, averageGreenColorFactorsOfBoidsInSightRange, averageBlueColorFactorsOfBoidsInSightRange);

    return true;
}

void Boid::applySpin(float deltaTime)
{
    mRotation += mSpin * (deltaTime / mBaseDeltaTime);
    while (mRotation >= 360)
    {
        mRotation -= 360;
    }
    while (mRotation < 0)
    {
        mRotation += 360;
    }
    mSpin = 0;
}

void Boid::recalculateForwardDirectionVectorFromRotation()
{
    mForwardDirectionVectorX = std::sin(mRotation * 3.141 / 180);
    mForwardDirectionVectorY = -1 * std::cos(mRotation * 3.141 / 180);
}

void Boid::recalculateLeftDirectionVectorFromRotation()
{
    float rotationToTheLeft = mRotation+270;
    if (rotationToTheLeft>=360)
    {
        rotationToTheLeft-=360;
    }
    mLeftDirectionVectorX = std::sin(rotationToTheLeft * 3.14 / 180);
    mLeftDirectionVectorY = -1 * std::cos(rotationToTheLeft * 3.14 / 180);
}

void Boid::applyMovement(float deltaTime)
{
    mPositionX += mForwardDirectionVectorX * (deltaTime / mBaseDeltaTime) * mMovementSpeed;
    mPositionY += mForwardDirectionVectorY * (deltaTime / mBaseDeltaTime) * mMovementSpeed;
}

void Boid::draw(sf::RenderWindow &window)
{
    mSprite.setPosition(mPositionX, mPositionY);
    mSprite.setRotation(mRotation);
    if (mVaryingColor.r == 0 && mVaryingColor.g == 0 && mVaryingColor.b == 0)
    {
        mSprite.setColor(mBaseColor);
    }
    else
    {
        mSprite.setColor(mVaryingColor);
    }
    window.draw(mSprite);
}