#include "Game.h"

SDL_Texture *playerTex;
SDL_Rect prevHead, curHead, food, *body;



Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, bool fullscreen) {
    direction = RIGHT;
    int flags = 0;
    if(fullscreen)  {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)  {
        std::cout << "subsystem initialized!..." << std::endl;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, flags);
        renderer = SDL_CreateRenderer(window,-1,0);
        
        // set head size:
        curHead.h = cellSize;
        curHead.w = cellSize;

        // set food size and initial location:
        food.h = cellSize;
        food.w = cellSize;
        update_food_location();


        isRunning = true;
    }
    // initialize body:
    body = new SDL_Rect[maxBodySize];

    // set body measurements:
    for(int i=0; i<maxBodySize; i++)    {
        body[i].h = cellSize;
        body[i].w = cellSize;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)  {
            isRunning = false;
    }
        else if(event.type == SDL_KEYDOWN)  {
            switch(event.key.keysym.sym)    {
                case SDLK_RIGHT:    {
                    if(direction != LEFT)   {
                        direction = RIGHT;
                    }
                    break;
                }
                case SDLK_LEFT:    {
                    if(direction != RIGHT)   {
                        direction = LEFT;
                    }
                    break;
                }
                case SDLK_UP:    {
                    if(direction != DOWN)   {
                        direction = UP;
                    }
                    break;
                }
                case SDLK_DOWN:    {
                    if(direction != UP)   {
                        direction = DOWN;
                    }
                    break;
                }
                default:
                    break;
            }
        }
}

void Game::update() {

    switch(direction)   {
        case RIGHT: {   
            headX += speed;
            break;
        }
        case LEFT: {  
            headX -= speed;
            break;
        }
        case UP: {   
            headY -= speed;
            break;
        }
        case DOWN: {   
            headY += speed;
            break;
        }
        default:
            break;
    }
    // update head position:
    prevHead.x = curHead.x;
    prevHead.y = curHead.y;

    curHead.x = headX;
    curHead.y = headY;

    curHead.x -= (curHead.x%cellSize);
    curHead.y -= (curHead.y%cellSize);
    
    curHead.x = (curHead.x+Game::gameWidth)%(Game::gameWidth);
    curHead.y = (curHead.y+Game::gameHeight)%(Game::gameHeight);

    if(prevHead.x != curHead.x || prevHead.y != curHead.y)  {

        if(gotFood) {
            handle_food_aquisition();
        }

        // update body position:
        for(int i=bodySize-1; 0 < i; i--)   {
            body[i].x = body[i-1].x;
            body[i].y = body[i-1].y;
        }
        body[0].x = prevHead.x;
        body[0].y = prevHead.y;
    }


    if(curHead.x == food.x && curHead.y == food.y)  {
        gotFood = true;
        // make food dissapeare:
        food.x = -100*cellSize;
        food.y = -100*cellSize;
    }

}

void Game::handle_food_aquisition() {
    update_food_location();
    if(bodySize < maxBodySize) bodySize++;
    speed += 0.02;
    gotFood = false;
}


void Game::update_food_location() {
    food.x = rand()%gameWidth;
    food.y = rand()%gameHeight;
    food.x -= (food.x%cellSize);
    food.y -= (food.y%cellSize);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x69, 0x69, 0x69, 0xFF);
    // draw gridlines:
    for(int x=0; x <= gameWidth; x += cellSize) {
        SDL_RenderDrawLine(renderer,x,0,x,gameHeight);
    }
    for(int y=0; y <= gameHeight; y += cellSize) {
        SDL_RenderDrawLine(renderer,0,y,gameWidth,y);
    }

    // Head:
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &curHead);

    // Body:
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
    for(int i=0; i<bodySize; i++)   {
        SDL_RenderFillRect(renderer, &body[i]);
    }

    // food:
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &food);

    SDL_RenderPresent(renderer);
}


void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
