#include "../Headers/GameProperties.h"

int GameProperties::gameExpectedRenderingFps{30};

int GameProperties::gameBaseDeltaTime{3000};

int GameProperties::aquariumBorderLeft{0};
int GameProperties::aquariumBorderRight{GetSystemMetrics(SM_CXSCREEN)};
int GameProperties::aquariumBorderTop{0};
int GameProperties::aquariumBorderBottom{GetSystemMetrics(SM_CYSCREEN)};

int GameProperties::aquariumCapacity{1};

float GameProperties::boidMovementSpeed{1};
float GameProperties::boidRotationSpeed{1};

float GameProperties::boidHitboxRadius{1};

float GameProperties::boidBorderSightRange{1};
float GameProperties::boidOtherBoidSightRange{1};
float GameProperties::boidPredatorSightRange{1};

float GameProperties::boidSpriteScaleX{1};
float GameProperties::boidSpriteScaleY{1};

float GameProperties::boidCenterRotationMarginOfError{1};
float GameProperties::boidMinimumRotationalDifference{1};
float GameProperties::boidMaximumRotationalDifference{1};

void GameProperties::setupFromFile(const std::string &filepath)
{
    std::string stringBuffer;

    std::ifstream setupFile(filepath);

    while (setupFile>>stringBuffer)
    {
        if (stringBuffer=="gameExpectedRenderingFps")
        {
            setupFile>>gameExpectedRenderingFps;
        }
        else if (stringBuffer=="gameBaseDeltaTime")
        {
            setupFile>>gameBaseDeltaTime;
        }
        else if (stringBuffer=="aquariumBorderLeft")
        {
            setupFile>>aquariumBorderLeft;
        }
        else if (stringBuffer=="aquariumBorderRight")
        {
            setupFile>>aquariumBorderRight;
        }
        else if (stringBuffer=="aquariumBorderTop")
        {
            setupFile>>aquariumBorderTop;
        }
        else if (stringBuffer=="aquariumBorderBottom")
        {
            setupFile>>aquariumBorderBottom;
        }
        else if (stringBuffer=="aquariumCapacity")
        {
            setupFile>>aquariumCapacity;
        }
        else if (stringBuffer=="boidMovementSpeed")
        {
            setupFile>>boidMovementSpeed;
        }
        else if (stringBuffer=="boidRotationSpeed")
        {
            setupFile>>boidRotationSpeed;
        }
        else if (stringBuffer=="boidHitboxRadius")
        {
            setupFile >> boidHitboxRadius;
        }
        else if (stringBuffer=="boidBorderSightRange")
        {
            setupFile>>boidBorderSightRange;
        }
        else if (stringBuffer=="boidOtherBoidSightRange")
        {
            setupFile>>boidOtherBoidSightRange;
        }
        else if (stringBuffer=="boidPredatorSightRange")
        {
            setupFile>>boidPredatorSightRange;
        }
        else if (stringBuffer=="boidSpriteScaleX")
        {
            setupFile>>boidSpriteScaleX;
        }
        else if (stringBuffer=="boidSpriteScaleY")
        {
            setupFile>>boidSpriteScaleY;
        }
        else if (stringBuffer=="boidCenterRotationMarginOfError")
        {
            setupFile>>boidCenterRotationMarginOfError;
        }
        else if (stringBuffer=="boidMinimumRotationalDifference")
        {
            setupFile>>boidMinimumRotationalDifference;
        }
        else if (stringBuffer=="boidMaximumRotationalDifference")
        {
            setupFile>>boidMaximumRotationalDifference;
        }
    }

    setupFile.close();
}