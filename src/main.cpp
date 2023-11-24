#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main (int argc, char* argv[]) {
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("yes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Unable to create window" << std::endl;
        return 1;
    }

    SDL_Event eventHandler;
    bool isRunning = true;

    while (isRunning) {
        if (SDL_PollEvent(&eventHandler)) {
            if (eventHandler.type == SDL_QUIT) isRunning = false;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}