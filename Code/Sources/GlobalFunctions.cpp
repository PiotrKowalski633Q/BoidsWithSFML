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

void GlobalFunctions::increaseColorIntensity(float &r, float &g, float &b)
{
    if (r < g && r < b)//Red is the smallest RGB component
    {
        r = r/2;
        if (g < b)
        {
            b = 255;
        }
        else
        {
            g = 255;
        }
    }
    else if (g < b)//Green is the smallest RGB component
    {
        g = g/2;
        if (r < b)
        {
            b = 255;
        }
        else
        {
            r = 255;
        }
    }
    else//Blue is the smallest RGB component
    {
        b = b/2;
        if (r < g)
        {
            g = 255;
        }
        else
        {
            r = 255;
        }
    }
}