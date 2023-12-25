#pragma once

#ifndef animHandler_hpp
#define animHandler_hpp

// screen class to handle rendering and whatnot
#include <iostream>
#include <SDL.h>
#include <vector>

#include <screen.hpp>
#include <dothandler.hpp>

class AnimationHandler {
    public:
        AnimationHandler();
        ~AnimationHandler();

        void setFramesPerStep(int framesPerStep);

        void init(DotHandler* dotHandler, int FPS, int timeLength);

        std::vector<std::vector<int>> getThreeRandPos(std::vector<std::vector<int>> triangleVertices, int mouseX, int mouseY);
        void setAnimInitDotPositions(std::vector<std::vector<int>> initialDotPosits);

        void animate(DotHandler* dotHandler, SDL_Renderer* renderer, int mouseX, int mouseY);
        void animateLineTraversal(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
        void animateDotTraversal(SDL_Renderer* renderer, DotHandler* dotHandler, int x1, int y1, int x2, int y2);
        void drawFinishedLine(SDL_Renderer* renderer, int r, int g, int b, int a, int x1, int y1, int x2, int y2);
        void nextPhase(DotHandler* dotHandler, std::vector<int> dotPosToUpdate);

        void reset();

        bool getAnimState();
        void setAnimState(bool val);
    
    private:
        int _FPS;
        int _timeLength;
        int _phaseCounter;
        float _traversalLength;
        int _frameCounter;
        int _framesPerStep;

        std::vector<int> _coordsOne;
        std::vector<int> _coordsTwo;

        std::vector<std::vector<int>> _initialDotPositions; 
        std::vector<std::vector<int>> _chosenVertices;

        int _lineColor[4];

        bool _animInProgress;

};

#endif