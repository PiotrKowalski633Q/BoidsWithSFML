cmake_minimum_required(VERSION 3.25)
project(BoidsWithSFML)

set(CMAKE_CXX_STANDARD 23)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/Build)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "Dependencies/SFML-2.6.0/lib/cmake/SFML")

file(COPY Resources DESTINATION ${dir}/Build)
file(COPY Dependencies/SFML-2.6.0/bin/openal32.dll DESTINATION ${dir}/Build)

find_package(SFML 2.6.0 REQUIRED COMPONENTS audio graphics window system)

include_directories(Dependencies/SFML-2.6.0/include)


add_executable(BoidsWithSFML
        Code/Sources/main.cpp
        Code/Headers/Boid.h
        Code/Sources/Boid.cpp
        Code/Headers/Aquarium.h
        Code/Sources/Aquarium.cpp
        Code/Headers/Game.h
        Code/Sources/Game.cpp
        Code/Headers/GameProperties.h
        Code/Sources/GameProperties.cpp
        Code/Headers/GlobalFunctions.h
        Code/Sources/GlobalFunctions.cpp)
target_link_libraries(BoidsWithSFML sfml-audio sfml-graphics sfml-window sfml-system)