#ifndef Game_h
#define Game_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Game {
    public:
        Game();
        ~Game();
        void init(const char *title, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running() {return isRunning;}
    private:
        void update_food_location();
        void handle_food_aquisition();
        bool isRunning = false;
        int cnt = 0;
        SDL_Window *window;
        SDL_Renderer *renderer;
        enum Direction {UP,DOWN,RIGHT,LEFT};
        int direction;
        float speed{0.3f};
        float headX;
        float headY;
        int cellSize = 32;
        int gameWidthUnits = 20;
        int gameHeightUnits = 16;
        int gameHeight = gameWidthUnits * cellSize;
        int gameWidth = gameHeightUnits * cellSize;
        // snake (including head) should take max third of screen
        int maxBodySize = (gameWidthUnits * gameHeightUnits) / 3 - 1;
        int bodySize = 0;
        bool gotFood = false;
};

#endif