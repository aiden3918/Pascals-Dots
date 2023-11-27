#pragma once

#ifndef dothandler_hpp
#define dothandler_hpp

#include <SDL.h>
#include <iostream>
#include <vector>

// a class that handles all the actions/calculations regarding the dots that will spawn
class DotHandler {
    public:
        DotHandler();
        ~DotHandler();

        void init();

        std::vector<int> newRandomDotPosition(std::vector<std::vector<int>> vertices); // return the pointer to the array; its a workaround to returning the array itself
        void updateDotPositions(std::vector<int> newDot);
        void renderDots(SDL_Renderer* renderer);
        
        void reset();
        size_t getVectorSize();

    private:
        std::vector<std::vector<int>> _dotPositions;
        std::vector<int> _currentDotPos;
        std::vector<int> _newRandomDotPos; // <- maybe use this one idk
        int _randomVertexIndex;
};

#endif