#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

#include <mouse.hpp>
#include <screen.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SIDE_LENGTH = 450;

Screen* app = nullptr;

int main (int argc, char* argv[]) {

    app = new Screen();

    app->init("hehe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    while (app->running()) {
        app->handleEvents();
        app->update();
        app->render();
    }

    app->clean();

    return 0;
}