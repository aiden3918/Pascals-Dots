#include <iostream>
#include <SDL.h>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>

#include <screen.hpp>
#include <animHandler.hpp>
#include <dothandler.hpp>

AnimationHandler::AnimationHandler(){}
AnimationHandler::~AnimationHandler(){}

// store frames per step
// {int framesPerStep} - the amount of frames that will elapse per step (animation phase in seconds * FPS)
void AnimationHandler::setFramesPerStep(int framesPerStep) {
    _framesPerStep = framesPerStep;
}

// initiate animationHandler with values
// {Dothandler* dotHandler} - dotHandler class
// {int FPS} - FPS of app
// {int timeLength} - animation length per phase in seconds
void AnimationHandler::init(DotHandler* dotHandler, int FPS, int timeLength) {
    srand(time(NULL));
    _FPS = FPS;
    _timeLength = timeLength;
    _framesPerStep = _FPS * _timeLength;

    _lineColor[0] = 0;
    _lineColor[1] = 0;
    _lineColor[2] = 150;
    _lineColor[3] = 255;

    reset();
}

// reset AnimationHandler for replability
void AnimationHandler::reset() {
    _initialDotPositions = {};
    _chosenVertices = {};

    _animInProgress = false;
    _phaseCounter = 1;
    _frameCounter = 0;
}

// animate the sequence
// {Dothandler* dotHandler} - dotHandler class
// {SDL_Renderer* renderer} - SDL's renderer class
// {int mouseX} - x position of mouse when clicked
// {int mouseY} - y position of mouse when clicked
void AnimationHandler::animate(DotHandler* dotHandler, SDL_Renderer* renderer, int mouseX, int mouseY) {
    dotHandler->renderDots(renderer);

    // probably could use more optimizing here, but i think this is a fair balance between readability and brevity
    // animate the first line and dot traversal
    if (_phaseCounter == 1) {

        // calculate and animate line traversal
        if (_frameCounter < _framesPerStep) animateLineTraversal(renderer, mouseX, mouseY, _chosenVertices[0][0], _chosenVertices[0][1]);
        else if (_frameCounter < _framesPerStep * 2) { 
            // still drawing line
            drawFinishedLine(renderer, _lineColor[0], _lineColor[1], _lineColor[2], _lineColor[3], mouseX, mouseY, _chosenVertices[0][0], _chosenVertices[0][1]);
            // calculate and animate dot traversal
            animateDotTraversal(renderer, dotHandler, mouseX, mouseY, _initialDotPositions[0][0], _initialDotPositions[0][1]);
        } 
        // move on to the next phase
        else nextPhase(dotHandler, _initialDotPositions[0]);

    // repeat 2 more times (again, readability)
    } else if (_phaseCounter == 2) {

        if (_frameCounter < _framesPerStep) animateLineTraversal(renderer, _initialDotPositions[0][0], _initialDotPositions[0][1], _chosenVertices[1][0], _chosenVertices[1][1]);
        else if (_frameCounter < _framesPerStep * 2) { 
            drawFinishedLine(renderer, _lineColor[0], _lineColor[1], _lineColor[2], _lineColor[3], _initialDotPositions[0][0], _initialDotPositions[0][1], _chosenVertices[1][0], _chosenVertices[1][1]);
            animateDotTraversal(renderer, dotHandler, _initialDotPositions[0][0], _initialDotPositions[0][1], _initialDotPositions[1][0], _initialDotPositions[1][1]);
        } 
        else nextPhase(dotHandler, _initialDotPositions[1]);

    } else if (_phaseCounter == 3) {

        if (_frameCounter < _framesPerStep) animateLineTraversal(renderer, _initialDotPositions[1][0], _initialDotPositions[1][1], _chosenVertices[2][0], _chosenVertices[2][1]);
        else if (_frameCounter < _framesPerStep * 2) { 
            drawFinishedLine(renderer, _lineColor[0], _lineColor[1], _lineColor[2], _lineColor[3], _initialDotPositions[1][0], _initialDotPositions[1][1], _chosenVertices[2][0], _chosenVertices[2][1]);
            animateDotTraversal(renderer, dotHandler, _initialDotPositions[1][0], _initialDotPositions[1][1], _initialDotPositions[2][0], _initialDotPositions[2][1]);
        } 
        else nextPhase(dotHandler, _initialDotPositions[2]);

    // finish animation
    } else {
        setAnimState(false);
        return;
    }
}

// animate the line "crossing" at any point in the animation
// {SDL_Renderer* renderer} - SDL's renderer class
// {int x1} - initial x position of line
// {int y1} - initial y position of line
// {int x2} - final x position of line
// {int y2} - final y position of line
void AnimationHandler::animateLineTraversal(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    // traversed x: Tx = a + k(c-a)
    // traversed y: Ty = b + k(d-b)
    // works for both forwards and backwards
    // initial coords (a, b)
    // final coords (c, d) 
    // k is the % traversed in decimal
    int traversedX = (int)round(((float)x1 + ((float)_frameCounter / (float)_framesPerStep) * (float)(x2 - x1)));
    int traversedY = (int)round(((float)y1 + ((float)_frameCounter / (float)_framesPerStep) * (float)(y2 - y1)));

    SDL_SetRenderDrawColor(renderer, _lineColor[0], _lineColor[1], _lineColor[2], _lineColor[3]);
    SDL_RenderDrawLine(renderer, x1, y1, traversedX, traversedY);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    _frameCounter++;
}

// animate the dot "travelling" at any point in the animation
// {SDL_Renderer* renderer} - SDL's renderer class
// {Dothandler* dotHandler} - dotHandler class
// {int x1} - initial x position of dot
// {int y1} - initial y position of dot
// {int x2} - final x position of dot
// {int y2} - final y position of dot
void AnimationHandler::animateDotTraversal(SDL_Renderer* renderer, DotHandler* dotHandler, int x1, int y1, int x2, int y2) {
    int traversedX = (int)round(((float)x1 + ((float)(_frameCounter - _framesPerStep) / (float)_framesPerStep) * (float)(x2 - x1)));
    int traversedY = (int)round(((float)y1 + ((float)(_frameCounter - _framesPerStep) / (float)_framesPerStep) * (float)(y2 - y1)));

    dotHandler->renderSmallDots(renderer, traversedX, traversedY, dotHandler->getSmallDotColor());
    _frameCounter++;
}

// SDL_RenderDrawLine() with extra steps for the animation process
// I don't think this needs much of an explanation... :P
void AnimationHandler::drawFinishedLine(SDL_Renderer* renderer, int r, int g, int b, int a, int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

// set the animation to the next phase by resetting necessary counters and finalizing dot positions
// {Dothandler* dotHandler} - dotHandler class
// {std::vector<int> dotPosToUpdate} - the (x, y) of the finalized dot's position
void AnimationHandler::nextPhase(DotHandler* dotHandler, std::vector<int> dotPosToUpdate) {
    dotHandler->updateDotPositions(dotPosToUpdate);
    _phaseCounter++;
    _frameCounter = 0;
}


// generates three random dot positions according to the rules of dot generation for animation
// {std::vector<std::vector<int>> triangleVertices} - the vertices of the triangle
// {int mouseX} the x-position of the mouse when clicked
// {int mouseY} the y-position of the mouse when clicked
// {return} - a vector containing a vector of 2 integers containing three dot positions
std::vector<std::vector<int>> AnimationHandler::getThreeRandPos(std::vector<std::vector<int>> triangleVertices, int mouseX, int mouseY) {
    // initializations
    std::vector<std::vector<int>> threeRandPos;
    int randIndex;
    // two coords to use midpoint formula
    std::vector<int> coordsOne = {mouseX, mouseY};
    // this will always be the coordinate of a random vertex
    std::vector<int> coordsTwo;
    for (int i = 0; i < 3; i++) {
        // random triangle vertex
        randIndex = rand() % 3;
        _chosenVertices.push_back(triangleVertices[randIndex]);
        coordsTwo = triangleVertices[randIndex];
        // find midpoint
        threeRandPos.push_back({(coordsOne[0] + coordsTwo[0]) / 2, (coordsOne[1] + coordsTwo[1]) / 2});
        // take new calculated coords from midpt formula and make it the new first coord
        coordsOne = threeRandPos.back();
    } 

    for (auto i: threeRandPos) {
        std::cout << "(" << i[0] << ", " << i[1] << ")" << std::endl; 
    }

    return threeRandPos;
}

// store the initial dot positions in the animation
// {std::vector<std::vector<int>> initialDotPosits} - vector of vectors containing dot positions
void AnimationHandler::setAnimInitDotPositions(std::vector<std::vector<int>> initialDotPosits) {
    _initialDotPositions = initialDotPosits;
}

// tells whether the animation is done
// {return} _animInProgress: whether the animation is in progress or not (bool)
bool AnimationHandler::getAnimState() {
    return _animInProgress;
}

// set the state of the animation (whether it is done or not)
// {bool val} - state to set animation handler to
void AnimationHandler::setAnimState(bool val) {
    _animInProgress = val;
}
