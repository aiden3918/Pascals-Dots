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

    _smallDotColor[0] = 255;
    _smallDotColor[1] = 255;
    _smallDotColor[2] = 255;
    _smallDotColor[3] = 255;

    _fillerDotSizeToRender = Small;
}

// {std::vector<std::vector<int>>} a 2D vector containing the (x, y) coordinates of the three vertices of the triangle
// // find midpoint between current dot position and position of a random vertex
// {return} a vector containing the coordinates of the new dot's position
std::vector<int> DotHandler::newRandomDotPosition(std::vector<std::vector<int>> vertices) {
    _randomVertexIndex = rand() % 3;

    // using midpoint formula {midpt-coords (x, y) = (0.5(x1 + x2), 0.5(y1 + y2))}
    // (x1, y1) coords of random triangle vertex
    // (x2, y2) coords of most recent dot
    std::vector<int> newRandomDotPos = {(vertices[_randomVertexIndex][0] + _dotPositions[getVectorSize() - 1][0]) / 2, (vertices[_randomVertexIndex][1] + _dotPositions[getVectorSize() - 1][1]) / 2};
    std::cout << "(" << newRandomDotPos[0] << ", " << newRandomDotPos[1] << ")" << std::endl;  

    return newRandomDotPos;
}

// add new dots position to dot positions vectors
void DotHandler::updateDotPositions(std::vector<int> newDot) {
    _dotPositions.push_back(newDot);
}

// render all dots
void DotHandler::renderDots(SDL_Renderer* renderer) {
    for (int i = 1; i < _dotPositions.size(); i++) {
        (_fillerDotSizeToRender == Small) ? renderSmallDots(renderer, _dotPositions[i][0], _dotPositions[i][1], _smallDotColor) : renderMediumDots(renderer, _dotPositions[i][0], _dotPositions[i][1], _mediumDotColor);
    }
    // render first initial dot
    renderBigDots(renderer, _dotPositions[0][0], _dotPositions[0][1], _bigDotColor); 
}

// render a dot with a horizontal diameter of 3 pixels
void DotHandler::renderSmallDots(SDL_Renderer* renderer, int centerX, int centerY, int* color) {
    SDL_SetRenderDrawColor(renderer, _smallDotColor[0], _smallDotColor[1], _smallDotColor[2], _smallDotColor[3]);
    //                                                                                                                         ***     it looks better as pixels trust me
    for (int i = 0; i < 3; i++) SDL_RenderDrawLine(renderer, centerX - 1, centerY - 1 + i, centerX + 1, centerY - 1 + i); //   ***     
    //                                                                                                                         ***
}  

// render a dot with a horizontal diameter of 5 pixels
void DotHandler::renderMediumDots(SDL_Renderer* renderer, int centerX, int centerY, int* color) {
    SDL_SetRenderDrawColor(renderer, _mediumDotColor[0], _mediumDotColor[1], _mediumDotColor[2], _mediumDotColor[3]);
    
    SDL_RenderDrawLine(renderer, centerX - 1, centerY - 2, centerX + 1, centerY - 2); //                                        *** 
    for (int i = 0; i < 3; i++) SDL_RenderDrawLine(renderer, centerX - 2, centerY - 1 + i, centerX + 2, centerY - 1 + i); //   *****     
    SDL_RenderDrawLine(renderer, centerX - 1, centerY + 2, centerX + 1, centerY + 2); //                                       *****
} //                                                                                                                           *****
//                                                                                                                              ***                

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

int* DotHandler::getSmallDotColor() {
    return _smallDotColor;
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
