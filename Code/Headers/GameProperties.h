#ifndef BOIDSWITHSFML_GAMEPROPERTIES_H
#define BOIDSWITHSFML_GAMEPROPERTIES_H

#include <fstream>
#include <wtypes.h>

class GameProperties
{
public:
    static int gameExpectedRenderingFps;

    static int gameBaseDeltaTime;

    static int aquariumBorderLeft;
    static int aquariumBorderRight;
    static int aquariumBorderTop;
    static int aquariumBorderBottom;

    static int aquariumCapacity;

    static float boidMovementSpeed;
    static float boidRotationSpeed;

    static float boidHitboxSizeX;
    static float boidHitboxSizeY;

    static float boidBorderSightRange;
    static float boidOtherBoidSightRange;
    static float boidPredatorSightRange;

    static float boidSpriteScaleX;
    static float boidSpriteScaleY;

    static float boidCenterRotationMarginOfError;
    static float boidMinimumRotationalDifference;
    static float boidMaximumRotationalDifference;

    static void setupFromFile(const std::string &filepath);
};

#endif //BOIDSWITHSFML_GAMEPROPERTIES_H
