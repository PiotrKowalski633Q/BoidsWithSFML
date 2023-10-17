#include <iostream>

#include "../Headers/GameProperties.h"
#include "../Headers/Game.h"

int main()
{
    srand(time(NULL));
    std::cout << "Hello, Boids!" << std::endl;

    GameProperties::setupFromFile("Resources/properties.txt");

    Game game1 = Game();
    game1.run();
    return 0;
}
