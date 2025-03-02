/*
================================================================================
Sudoku Solver
    Generates a random interactive sudoku puzzle and solves it. 
================================================================================
Programmer: Vinny Pham
Version: 12/27/2024
================================================================================
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Graphics.cpp"
#include "Sudoku.cpp"
using namespace std;

//====main======================================================================
//==============================================================================
int main(int argc, char* argv[]) {
    Sudoku game;
    bool startScreen = true;
    bool playScreen = false;   
    bool wasPlayScreen = false;
    bool endScreen = false;
    bool pauseEvent = false;


    SDL_Init(SDL_INIT_EVERYTHING);

     // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("Sudoku Solver - Vinny Pham", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    printStartScreen(renderer);
    createDifficultyButton(renderer, 0);

    SDL_Event event;
    Color color;
    bool running = true;
    bool leftClick = false;
    int numInput = -1;
    int startTime = 0;
    int elapsedTime = 0;
    int pausedTime = 0;
    int totalPaused = 0;
    int index = 0;
    int difficulty = 0;
    int x, y;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            // Quit the program
            if (event.type == SDL_QUIT) {
                running = false;
            
            // Get number input
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        numInput = 1;
                        break;
                    case SDLK_2:
                        numInput = 2;
                        break;
                    case SDLK_3:
                        numInput = 3;
                        break;
                    case SDLK_4:
                        numInput = 4;
                        break;
                    case SDLK_5:
                        numInput = 5;
                        break;
                    case SDLK_6:
                        numInput = 6;
                        break;
                    case SDLK_7:
                        numInput = 7;
                        break;
                    case SDLK_8:
                        numInput = 8;
                        break;
                    case SDLK_9:
                        numInput = 9;
                        break;
                    case SDLK_BACKSPACE:
                        numInput = 0;
                        break;
                    default:
                        break;
                }
            
            // Get mouse input
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftClick = true;
                } else {
                    leftClick = false;
                }
            }
        }

        if (pauseEvent) {
            createPauseScreen(renderer, elapsedTime);

            if (leftClick) {
                SDL_GetMouseState(&x, &y);

                // resume
                if (x >= 300 && x <= 500 && y >= 310 && y <= 365) {
                    playScreen = true;
                    pauseEvent = false;
                    totalPaused += SDL_GetTicks() - pausedTime;
                }

                // menu
                if (x >= 300 && x <= 500 && y >= 385 && y <= 445) {
                    startScreen = true;
                    pauseEvent = false;
                    wasPlayScreen = false;

                    printStartScreen(renderer);
                    createDifficultyButton(renderer, 0);
                }
            }
            
        }

        if (startScreen) {
            SDL_GetMouseState(&x, &y);

            if (leftClick) {
                // checks play button
                if (x >= 280 && x <= 515 && y >= 325 && y <= 390) {
                    startScreen = false;
                    playScreen = true;
                    game.generateBoard();
                    printGameScreen(renderer, game);
                }
                
                // checks difficulty button
                if (x >= 280 && x <= 515 && y >= 460 && y <= 525) {
                    difficulty = (difficulty + 1) % 3;
                    game.setDifficulty(difficulty);
                    printStartScreen(renderer);
                    createDifficultyButton(renderer, difficulty);
                }
                
            }
        }
        

        if (playScreen) {
            // Reset timer when play screen is entered
            if (!wasPlayScreen) {
                startTime = SDL_GetTicks();
                wasPlayScreen = true;
            }

            // Calculate elapsed time
            elapsedTime = (SDL_GetTicks() - startTime - totalPaused) /1000;
            createTimer(renderer, elapsedTime);

            // Event handle
            if (leftClick) {
                SDL_GetMouseState(&x, &y);
                printGameScreen(renderer, game);
                cout << x << " " << y << endl;

                // Select cell
                index = selectCell(x, y, renderer);

                // Reset board
                if (x >= 125 && x <= 290 && y >= 700 && y <= 750) {
                    game.resetBoard();
                    printGameScreen(renderer, game);
                }

                // Submit button
                if (x >= 515 && x <= 675 && y >= 700 && y <= 750) {
                    if (!game.isFull()) {
                        renderText(renderer, "Board isn't filled", 40, color.black, 50);
                    } else if (!game.isCorrect()) {
                        renderText(renderer, "Board isn't correct", 40, color.black, 50);
                    } else {
                        playScreen = false;
                        endScreen = true;
                    }
                }
            }

            // Pause button
            if (x >= 650 && x <= 675 && y >= 85 && y <= 110) {
                pauseEvent = true;
                playScreen = false;

                pausedTime = SDL_GetTicks();
            }
            
            // Change number
            if (index != -1 && numInput != -1) {
                int row = index / 9;
                int col = index % 9;
                game.setBoard(row, col, numInput);
                printGameScreen(renderer, game);

                numInput = -1;
                index = -1;
            }
        }

        if (endScreen) {
            printEndScreen(renderer, elapsedTime);
        }
    

        // Reset variables
        leftClick = false;
    }
    
    // Clean up
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}                                     // end main
//==============================================================================
