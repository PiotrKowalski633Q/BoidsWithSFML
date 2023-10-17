#ifndef BOIDSWITHSFML_GLOBALFUNCTIONS_H
#define BOIDSWITHSFML_GLOBALFUNCTIONS_H

#include <cstdlib>
#include <cmath>

class GlobalFunctions
{
public:
    static int getRandomValueInRange(int min, int max);

    static float getObjectRotationFromDirectionVector(float directionVectorX, float directionVectorY);
};

#endif //BOIDSWITHSFML_GLOBALFUNCTIONS_H
