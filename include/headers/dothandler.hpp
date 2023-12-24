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
        void renderSmallDots(SDL_Renderer* renderer, int centerX, int centerY, int* color);
        void renderMediumDots(SDL_Renderer* renderer, int centerX, int centerY, int* color);
        void renderBigDots(SDL_Renderer* renderer, int centerX, int centerY, int* color);

        int* getSmallDotColor();
        
        void reset();
        size_t getVectorSize();

    private:
        int _bigDotColor[4];
        int _mediumDotColor[4];
        int _smallDotColor[4];
        std::vector<std::vector<int>> _dotPositions;
        double _randomVertexIndex;

        enum fillerDotSize {Small, Medium};
        fillerDotSize _fillerDotSizeToRender;
};

#endif