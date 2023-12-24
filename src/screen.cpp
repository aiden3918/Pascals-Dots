#include <iostream>
#include <SDL.h>
#include <screen.hpp>
#include <mouse.hpp>
#include <animHandler.hpp>
#include <vector>

Screen::Screen(){} // defines constructor
Screen::~Screen(){} // defines deconstructor (c++ memory thingamabobs)

// define methods initialized in screen.hpp (design principlesm, yay!)
void Screen::init(const char* title, int x, int y, int width, int height, bool fullscreen, int triangleSideLength, int* triangleVertexTop) {
    _isRunning = true;

    // initialize all sdl systems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        _isRunning = false;
    } else {
        std::cout << "SDL startup successful" << std::endl;
    }

    // create a window
    _window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (_window == NULL) {
        std::cout << "Unable to create window" << std::endl;
        _isRunning = false;
    } else {
        std::cout << "Window creation successful" << std::endl;
    }

    // create a renderer
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if (_renderer == NULL) {
        std::cout << "Unable to create window" << std::endl;
        _isRunning = false;
    } else {
        std::cout << "Renderer initalization successful" << std::endl;
    }

    _SIDE_LENGTH = triangleSideLength;

    _TRIANGLE_VERTICES = {{0, 0}, {0, 0}, {0, 0}};
    _TRIANGLE_VERTICES[0][0] = triangleVertexTop[0];
    _TRIANGLE_VERTICES[0][1] = triangleVertexTop[1];
    _TRIANGLE_VERTICES[1][0] = _TRIANGLE_VERTICES[0][0] - (_SIDE_LENGTH / 2);
    _TRIANGLE_VERTICES[1][1] = _TRIANGLE_VERTICES[0][1]  + int(sqrt(3) / 2 * triangleSideLength);
    _TRIANGLE_VERTICES[2][0] = _TRIANGLE_VERTICES[0][0] + (_SIDE_LENGTH / 2);
    _TRIANGLE_VERTICES[2][1] =  _TRIANGLE_VERTICES[0][1] + int(sqrt(3) / 2 * _SIDE_LENGTH);

    std::cout << "Triangle Vertices: {";
    for (auto i: _TRIANGLE_VERTICES) {
        std::cout << "{";
        for (auto j: i) {
            std::cout << j << ", ";
        }
        std::cout << "}, ";
    }
    std::cout << "}" << std::endl;

    std::cin.get();
    _screenCurrentState = Idle;
}

// checks events in SDL queue to act on it
void Screen::handleEvents() {
    _validMousePos = false;

    SDL_PollEvent(&_event);
    switch (_event.type) {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (_screenCurrentState != Idle) return;
            
            SDL_GetMouseState(&_mouseX, &_mouseY);
            std::cout << "origin at top left: (" << _mouseX << ", " << _mouseY << ")" << std::endl;

            _validMousePos = checkIfMouseIsInTriangle(_mouseX, _mouseY, _SIDE_LENGTH, _TRIANGLE_VERTICES[0][0], _TRIANGLE_VERTICES[0][1]);
            std::cout << "Valid mouse position: " << _validMousePos << std::endl;
            break;
    }

}

// note: calls before render
// {DotHandler*} the pointer to the DotHandler class (we only need one)
// updates the screen with anything else after rendering
void Screen::update(DotHandler* dotHandler, AnimationHandler* animHandler) {
    // update stuff per frame here (probably calculations and whatever)
    switch (_screenCurrentState) {
        // lots of testing done without chjanging app state for now; one step at a time
        case Idle:
            if (_validMousePos) {
                dotHandler->updateDotPositions({_mouseX, _mouseY});
                // get and set three random dot positions
                animHandler->setAnimInitDotPositions(animHandler->getThreeRandPos(_TRIANGLE_VERTICES, _mouseX, _mouseY));
                animHandler->setAnimState(true);
                _screenCurrentState = Animation;
            }
            break;
        case Animation:
            {
                if (!animHandler->getAnimState()) _screenCurrentState = FillInDots;
                break;
            }
        case FillInDots:
            {
                std::vector<int> newDot = dotHandler->newRandomDotPosition(getVertices()); // no need to call Screen->getVertices() because already in closest outer bracket scope (design principles yay!)
                std::cout << "newDot: (" << newDot[0] << ", " << newDot[1] << std::endl;
                dotHandler->updateDotPositions(newDot);
                break;
            }
        case WaitForRestart:
            break;
    }
}

// note: calls after update
// responsible for rendering objects
// {DotHandler*} the pointer to the DotHandler class
// {AnimationHandler*} the pointer to the class handling the animation
void Screen::render(DotHandler* dotHandler, AnimationHandler* animHandler) {
    // draw background
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer); // setting renderclear before drawing just sets the background for whatever reason

    // stuff to draw goes under here
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(_renderer, _TRIANGLE_VERTICES[0][0], _TRIANGLE_VERTICES[0][1], _TRIANGLE_VERTICES[1][0], _TRIANGLE_VERTICES[1][1]);
    SDL_RenderDrawLine(_renderer, _TRIANGLE_VERTICES[0][0], _TRIANGLE_VERTICES[0][1], _TRIANGLE_VERTICES[2][0], _TRIANGLE_VERTICES[2][1]);
    SDL_RenderDrawLine(_renderer, _TRIANGLE_VERTICES[1][0], _TRIANGLE_VERTICES[1][1], _TRIANGLE_VERTICES[2][0], _TRIANGLE_VERTICES[2][1]);

    if (_screenCurrentState == Animation) {
        // when animating
        animHandler->animate(dotHandler, _renderer, _mouseX, _mouseY);
    }

    if (_screenCurrentState == FillInDots) dotHandler->renderDots(_renderer);

    SDL_RenderPresent(_renderer);
}

// destroy everything (because this is c++ and we gotta worry about memory and shit) and quit
void Screen::clean() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

// checks if screen is active
// {return} bool to check is screen is running
bool Screen::running() {
    return Screen::_isRunning;
}

// outputs calculated vertices of equilateral triangle
// {return} 2D vector of triangle vertices {{x1, y1}, {x2, y2}, {x3, y3}}
std::vector<std::vector<int>> Screen::getVertices() {
    return Screen::_TRIANGLE_VERTICES;
}
