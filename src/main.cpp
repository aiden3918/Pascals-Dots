#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SIDE_LENGTH = 450;

const int TRIANGLE_VERTEX_TOP[2] = {WIDTH / 2, 100};
const int TRIANGLE_VERTEX_LEFT[2] = {TRIANGLE_VERTEX_TOP[0] - (SIDE_LENGTH / 2), TRIANGLE_VERTEX_TOP[1] + int(sqrt(3) / 2 * SIDE_LENGTH)};
const int TRIANGLE_VERTEX_RIGHT[2] = {TRIANGLE_VERTEX_TOP[0] + (SIDE_LENGTH / 2), TRIANGLE_VERTEX_TOP[1] + int(sqrt(3) / 2 * SIDE_LENGTH)};

int main (int argc, char* argv[]) {
    // initialize everything
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        return -1;
    } else {
        std::cout << "SDL startup successful" << std::endl;
    }

    SDL_Window *window = SDL_CreateWindow("hehe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Unable to create window" << std::endl;
        return 1;
    }

    SDL_Event eventHandler;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    bool isRunning = true;

    // program loop
    while (isRunning) {
        SDL_Delay(10);

        // handle polling events
        SDL_PollEvent(&eventHandler);
        int mouseX, mouseY;
        switch (eventHandler.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouseX, &mouseY);
                std::cout << "(" << mouseX << ", " << mouseY << ")" << std::endl;
                break;
        }

        // draw background test
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); // setting renderclear before drawing just sets the background for whatever reason

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, TRIANGLE_VERTEX_TOP[0], TRIANGLE_VERTEX_TOP[1], TRIANGLE_VERTEX_LEFT[0], TRIANGLE_VERTEX_LEFT[1]);
        SDL_RenderDrawLine(renderer, TRIANGLE_VERTEX_TOP[0], TRIANGLE_VERTEX_TOP[1], TRIANGLE_VERTEX_RIGHT[0], TRIANGLE_VERTEX_RIGHT[1]);
        SDL_RenderDrawLine(renderer, TRIANGLE_VERTEX_LEFT[0], TRIANGLE_VERTEX_LEFT[1], TRIANGLE_VERTEX_RIGHT[0], TRIANGLE_VERTEX_RIGHT[1]);

        SDL_RenderPresent(renderer);
    }

    // destroy everything (because this is c++ and we gotta worry about memory and shit) and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}