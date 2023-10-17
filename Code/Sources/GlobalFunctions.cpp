#include "../Headers/GlobalFunctions.h"

int GlobalFunctions::getRandomValueInRange(int min, int max)
{
    return (rand() % (max-min)) + min;
}

float GlobalFunctions::getObjectRotationFromDirectionVector(float directionVectorX, float directionVectorY)
{
    float rotation = std::atan2(directionVectorY, directionVectorX) * (180/3.141) + 90;
    while (rotation < 0)
    {
        rotation += 360;
    }
    while (rotation >= 360)
    {
        rotation -= 360;
    }
    return rotation;
}