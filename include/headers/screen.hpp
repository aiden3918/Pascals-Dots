#pragma once

#ifndef screen_hpp
#define screen_hpp

// screen class to handle rendering and whatnot
#include <iostream>
#include <SDL.h>
#include <vector>

#include <dothandler.hpp>
#include <animHandler.hpp>

// pretty much the entire screen including SDL. controls most app-specific functions
class Screen {
    public:
        Screen();
        ~Screen();

        void init(const char* title, int x, int y, int width, int height, bool isFullScreen, int triangleSideLength, int* triangleVertexTop);

        void handleEvents();
        void update(DotHandler* dotHandler, AnimationHandler* animHandler);
        void render(DotHandler* dotHandler, AnimationHandler* animHandler);
        void clean();
        std::vector<std::vector<int>> getVertices();

        bool running();
    
    private:
        bool _isRunning;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        SDL_Event _event;
        bool _validMousePos;

        int _mouseX;
        int _mouseY;

        // {{top x, top y}, {left x, left y}, {right x, right y}}
        std::vector<std::vector<int>> _TRIANGLE_VERTICES;
        int _SIDE_LENGTH;

        enum _screenState {Idle, Animation, FillInDots, WaitForRestart, Reset};
        _screenState _screenCurrentState;


};

#endif