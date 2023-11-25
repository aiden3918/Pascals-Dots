#include <iostream>
#include <SDL.h>
#include <screen.hpp>
#include <mouse.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SIDE_LENGTH = 450;

const int TRIANGLE_VERTEX_TOP[2] = {WIDTH / 2, 100};
const int TRIANGLE_VERTEX_LEFT[2] = {TRIANGLE_VERTEX_TOP[0] - (SIDE_LENGTH / 2), TRIANGLE_VERTEX_TOP[1] + int(sqrt(3) / 2 * SIDE_LENGTH)};
const int TRIANGLE_VERTEX_RIGHT[2] = {TRIANGLE_VERTEX_TOP[0] + (SIDE_LENGTH / 2), TRIANGLE_VERTEX_TOP[1] + int(sqrt(3) / 2 * SIDE_LENGTH)};

Screen::Screen(){} // defines constructor
Screen::~Screen(){} // defines deconstructor (c++ memory thingamabobs)

// define methods initialized in screen.hpp (design principlesm, yay!)
void Screen::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    _isRunning = true;

    // initialize all sdl systems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        _isRunning = false;
    } else {
        std::cout << "SDL startup successful" << std::endl;
    }

    // create a window
    _window = SDL_CreateWindow("hehe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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
 }

void Screen::handleEvents() {
    SDL_PollEvent(&_event);
    int mouseX, mouseY;
    switch (_event.type) {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "origin at top left: (" << mouseX << ", " << mouseY << ")" << std::endl;
            _validMousePos = checkIfMouseIsInTriangle(mouseX, mouseY, SIDE_LENGTH, TRIANGLE_VERTEX_TOP[0], TRIANGLE_VERTEX_TOP[1]);
            std::cout << "Valid mouse position: " << _validMousePos << std::endl;
            break;
    }

}

void Screen::update() {
    // update stuff per frame here (probably calculations and whatever)
}

void Screen::render() {
    // draw background
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer); // setting renderclear before drawing just sets the background for whatever reason

    // stuff to draw goes under here
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(_renderer, TRIANGLE_VERTEX_TOP[0], TRIANGLE_VERTEX_TOP[1], TRIANGLE_VERTEX_LEFT[0], TRIANGLE_VERTEX_LEFT[1]);
    SDL_RenderDrawLine(_renderer, TRIANGLE_VERTEX_TOP[0], TRIANGLE_VERTEX_TOP[1], TRIANGLE_VERTEX_RIGHT[0], TRIANGLE_VERTEX_RIGHT[1]);
    SDL_RenderDrawLine(_renderer, TRIANGLE_VERTEX_LEFT[0], TRIANGLE_VERTEX_LEFT[1], TRIANGLE_VERTEX_RIGHT[0], TRIANGLE_VERTEX_RIGHT[1]);

    SDL_RenderPresent(_renderer);
}

void Screen::clean() {
    // destroy everything (because this is c++ and we gotta worry about memory and shit) and quit
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Screen::running() {
    return Screen::_isRunning;
}