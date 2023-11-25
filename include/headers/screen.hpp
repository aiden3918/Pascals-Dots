#pragma once

#ifndef screen_hpp
#define screen_hpp

// screen class to handle rendering and whatnot
#include <iostream>
#include <SDL.h>

class Screen {
    public:
        Screen();
        ~Screen();

        void init(const char* title, int x, int y, int width, int height, bool isFullScreen);

        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();
    
    private:
        bool _isRunning;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        SDL_Event _event;
        bool _validMousePos;


};

#endif