#include <iostream>
#include <SDl.h>
#include <vector>
#include <random>
#include <time.h>

#include <dothandler.hpp>

DotHandler::DotHandler(){}
DotHandler::~DotHandler(){}

// inits dot handler by providing pseudo-randomness
void DotHandler::init() {
    srand(time(NULL));
}

// {std::vector<std::vector<int>>} a 2D vector containing the (x, y) coordinates of the three vertices of the triangle
// // find midpoint between current dot position and position of a random vertex
// {return} a vector containing the coordinates of the new dot's position
std::vector<int> DotHandler::newRandomDotPosition(std::vector<std::vector<int>> vertices) {
    _randomVertexIndex = rand() % 3;

    // using midpoint formula {midpt-coords (x, y) = (0.5(x1 + x2), 0.5(y1 + y2))}
    _newRandomDotPos = {vertices[_randomVertexIndex][0] + _currentDotPos[0] / 2, vertices[_randomVertexIndex][1] + _currentDotPos[1] / 2};
    return _newRandomDotPos;
}

// add new dots position to dot positions vectors
void DotHandler::updateDotPositions(std::vector<int> newDot) {
    _dotPositions.push_back(newDot);
}

void DotHandler::renderDots(SDL_Renderer* renderer) {
    for (std::vector<int> dot: _dotPositions) {
        SDL_RenderDrawPoint(renderer, dot[0], dot[1]);
    }
}

// get size of the vector containing all dot's positions in dothandler class
// {return} dotHandler class's data on all dot positions
size_t DotHandler::getVectorSize() {
    return DotHandler::_dotPositions.size();
}

// clear dot position data
void DotHandler::reset() {
    DotHandler::_dotPositions.clear();
}
