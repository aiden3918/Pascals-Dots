#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <mouse.hpp>
#include <screen.hpp>
#include <dothandler.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SIDE_LENGTH = 450;

int triangleTopVertex[2] = {WIDTH / 2, 100};
int* triangleTopVertPtr = triangleTopVertex;

const int FPS = 60;
const int framesDelay = 1000 / FPS; 
Uint32 frameStart;
int frameTime; 

Screen* app = nullptr;
DotHandler* dotHandler = nullptr;

int main (int argc, char* argv[]) {

    app = new Screen();
    dotHandler = new DotHandler(); 

    app->init("hehe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN, SIDE_LENGTH, triangleTopVertPtr);
    dotHandler->init();

    while (app->running()) {
        // "frames" are FPS system: keeps track of seconds passed to update screen, then delays that by the number of ms in between frames - ms that elapsed to keep a stable FPS
        frameStart = SDL_GetTicks();

        app->handleEvents();
        app->render();
        app->update(dotHandler);

        frameTime = SDL_GetTicks() - frameStart;

        if (framesDelay > frameTime) SDL_Delay(framesDelay - frameTime);
    }

    app->clean();

    return 0;
}