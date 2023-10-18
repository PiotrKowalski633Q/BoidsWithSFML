#ifndef BOIDSWITHSFML_GLOBALFUNCTIONS_H
#define BOIDSWITHSFML_GLOBALFUNCTIONS_H

#include <cstdlib>
#include <cmath>

class GlobalFunctions
{
public:
    static int getRandomValueInRange(int min, int max);

    static float getObjectRotationFromDirectionVector(float directionVectorX, float directionVectorY);

    //a function implemented so that the varying color doesn't default to gray due to being the average of colors of nearby boids, it zeroes the smallest RGB component and maxes out the highest one
    static void increaseColorIntensity(float &r, float &g, float &b);
};

#endif //BOIDSWITHSFML_GLOBALFUNCTIONS_H
