#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

// Constants
const int WIDTH = 800;
const int HEIGHT = 800;
const int GRID = 9;
const int BOARD_SIZE = 540;
const int CELL_SIZE = BOARD_SIZE / GRID;

// Enum for difficulty levels
enum Difficulty {
    EASY = 20,
    MEDIUM = 30,
    HARD = 40
};

// Struct for colors
struct Color {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color green = {0, 134, 64, 255};
    SDL_Color skyBlue = {134, 178, 214, 255};
    SDL_Color vibrantBlue = {0, 173, 239, 255};
    SDL_Color gray = {211, 211, 211, 255};
    // Add more colors as needed
};

// Fonts
struct Font {
    TTF_Font *size40 = TTF_OpenFont("src/font/ByteBounce.ttf", 40);
    TTF_Font *size50 = TTF_OpenFont("src/font/ByteBounce.ttf", 50);
    TTF_Font *size60 = TTF_OpenFont("src/font/ByteBounce.ttf", 60);
    TTF_Font *size65 = TTF_OpenFont("src/font/ByteBounce.ttf", 65);
};

#endif // UTIL_H