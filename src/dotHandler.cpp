#include <iostream>
#include <SDl.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <dothandler.hpp>

DotHandler::DotHandler(){}
DotHandler::~DotHandler(){}

// inits dot handler by providing pseudo-randomness
void DotHandler::init() {
    srand(time(NULL));
    _bigDotColor[0] = 255;
    _bigDotColor[1] = 0;
    _bigDotColor[2] = 0;
    _bigDotColor[3] = 255;

    _mediumDotColor[0] = 255;
    _mediumDotColor[1] = 255;
    _mediumDotColor[2] = 255;
    _mediumDotColor[3] = 255;
}

// {std::vector<std::vector<int>>} a 2D vector containing the (x, y) coordinates of the three vertices of the triangle
// // find midpoint between current dot position and position of a random vertex
// {return} a vector containing the coordinates of the new dot's position
std::vector<int> DotHandler::newRandomDotPosition(std::vector<std::vector<int>> vertices) {
    _randomVertexIndex = rand() % 3;

    // using midpoint formula {midpt-coords (x, y) = (0.5(x1 + x2), 0.5(y1 + y2))}
    // ERROR HERE: _currentDotPos has not been declared yet
    std::vector<int> newRandomDotPos = {vertices[_randomVertexIndex][0] + _currentDotPos[0] / 2, vertices[_randomVertexIndex][1] + _currentDotPos[1] / 2};
    std::cout << "(" << newRandomDotPos[0] << ", " << newRandomDotPos[1] << ")" << std::endl;  

    return newRandomDotPos;
}

// add new dots position to dot positions vectors
void DotHandler::updateDotPositions(std::vector<int> newDot) {
    _dotPositions.push_back(newDot);
    for (auto i: _dotPositions) {
        std::cout << "{" << i[0] << ", " << i[1] << "}" << std::endl;
    }
}

// render all dots
void DotHandler::renderDots(SDL_Renderer* renderer) {
    // render first initial dot
    renderBigDots(renderer, _dotPositions[0][0], _dotPositions[0][1], _bigDotColor); // this crashes the whole program for whatever reason
    for (int i = 1; i < _dotPositions.size(); i++) {
        renderMediumDots(renderer, _dotPositions[i][0], _dotPositions[i][1], _mediumDotColor);
    }
}

// render a dot with a horizontal diameter of 7 pixels
void DotHandler::renderMediumDots(SDL_Renderer* renderer, int centerX, int centerY, int* color) {
    SDL_SetRenderDrawColor(renderer, _mediumDotColor[0], _mediumDotColor[1], _mediumDotColor[2], _mediumDotColor[3]);
    
    SDL_RenderDrawLine(renderer, centerX - 1, centerY - 3, centerX + 1, centerY - 3); //    ***     it looks better as pixels trust me
    SDL_RenderDrawLine(renderer, centerX - 2, centerY - 2, centerX + 2, centerY - 2); //   *****
    SDL_RenderDrawLine(renderer, centerX - 3, centerY - 1, centerX + 3, centerY - 1); //  *******
    SDL_RenderDrawLine(renderer, centerX - 3, centerY, centerX + 3, centerY); //          *******
    SDL_RenderDrawLine(renderer, centerX - 3, centerY + 1, centerX + 3, centerY + 1); //  *******
    SDL_RenderDrawLine(renderer, centerX - 2, centerY + 2, centerX + 2, centerY + 2); //   *****
    SDL_RenderDrawLine(renderer, centerX - 1, centerY + 3, centerX + 1, centerY + 3); //    ***
}

// render a dot with a horizontal diameter of 9 pixels
void DotHandler::renderBigDots(SDL_Renderer* renderer, int centerX, int centerY, int* color) {
    SDL_SetRenderDrawColor(renderer, _bigDotColor[0], _bigDotColor[1], _bigDotColor[2], _bigDotColor[3]);

    SDL_RenderDrawLine(renderer, centerX - 1, centerY - 4, centerX + 1, centerY - 4); //      ***       
    SDL_RenderDrawLine(renderer, centerX - 3, centerY - 3, centerX + 3, centerY - 3); //    *******
    SDL_RenderDrawLine(renderer, centerX - 3, centerY - 2, centerX + 3, centerY - 2); //    *******
    SDL_RenderDrawLine(renderer, centerX - 4, centerY - 1, centerX + 4, centerY - 1); //   *********
    SDL_RenderDrawLine(renderer, centerX - 4, centerY, centerX + 4, centerY); //           *********
    SDL_RenderDrawLine(renderer, centerX - 4, centerY + 1, centerX + 4, centerY + 1); //   *********
    SDL_RenderDrawLine(renderer, centerX - 3, centerY + 2, centerX + 3, centerY + 2); //    *******
    SDL_RenderDrawLine(renderer, centerX - 3, centerY + 3, centerX + 3, centerY + 3); //    *******
    SDL_RenderDrawLine(renderer, centerX - 1, centerY + 4, centerX + 1, centerY + 4); //      ***
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
