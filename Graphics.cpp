#include <iostream>
#include <iomanip>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Sudoku.cpp"
#include "Util.h"
using namespace std;

// Function prototypes
void createTitle(SDL_Renderer *renderer);
void createPlayButton(SDL_Renderer *renderer);
void createDifficultyButton(SDL_Renderer *renderer, int difficulty);
void renderNum(SDL_Renderer *renderer, Sudoku game);
void createGrid(SDL_Renderer *renderer);
string formatTime(int time);
void createSubmitButton(SDL_Renderer *renderer);
void createRetryButton(SDL_Renderer *renderer);
void createPauseButton(SDL_Renderer *renderer);
void difficultyText(SDL_Renderer *renderer);

//====printStartScreen==========================================================
//Description: Prints the start screen
//Parameter: rednerer - SDL renderer
//==============================================================================
void printStartScreen(SDL_Renderer *renderer) {
    // Set background color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Create title text
    createTitle(renderer);

    // Create play 
    createPlayButton(renderer);

    // Create difficulty text
    difficultyText(renderer);
}                   // end of printStartScreen
//==============================================================================

//====printGameScreen===========================================================
//Description: Prints the game screen
//Parameter: renderer - SDL renderer, game - Sudoku object
//==============================================================================
void printGameScreen(SDL_Renderer *renderer, Sudoku game) {
    // Set background color (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw grid lines 
    createGrid(renderer);

    // Draw numbers
    renderNum(renderer, game);

    // Draw submit button
    createSubmitButton(renderer);

    // Draw retry button
    createRetryButton(renderer);

    // Draw pause button
    createPauseButton(renderer);

    // Present renderer
    SDL_RenderPresent(renderer);
}                       // end of printGameScreen
//==============================================================================

//====renderText================================================================
// Description: Renders text to the screen
// Parameters: renderer - SDL renderer, text - text to render, y - y position,
//==============================================================================
void renderText(SDL_Renderer *renderer, const char *text, int y, SDL_Color color, int fontSize) {
    Font font;
    TTF_Font *fontPtr;
    switch (fontSize) {
        case 40:
            fontPtr = font.size40;
            break;
        case 50:
            fontPtr = font.size50;
            break;
        case 60:
            fontPtr = font.size60;
            break;
        case 65:
            fontPtr = font.size65;
            break;
        default:
            break;
    }
    SDL_Surface *surface = TTF_RenderText_Solid(fontPtr, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface); // Free the surface after creating the texture

    SDL_Rect textRect;
    textRect.x = (WIDTH - textWidth) / 2;
    textRect.y = y + 10;
    textRect.w = textWidth;
    textRect.h = textHeight;
    

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture); // Clean up the texture
}                        // end of renderText
//==============================================================================

//====drawFilledCircle==========================================================
// Description: Draws a filled circle
// Parameters: renderer - SDL renderer, x - x position, y - y position, radius
//==============================================================================
void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Distance from center in x
            int dy = radius - h; // Distance from center in y
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}                        // end of drawFilledCircle
//==============================================================================

//====renderButton==============================================================
// Description: Renders a button
// Parameters: renderer - SDL renderer, y - y position
//==============================================================================
void renderButton(SDL_Renderer *renderer, int y) {
    int buttonWidth = 175;
    int buttonHeight = 65;
    int buttonX = (800 - buttonWidth) / 2;
    int buttonY = y;

    // Set color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw button rectangle
    SDL_Rect button = {buttonX, buttonY, buttonWidth, buttonHeight};
    SDL_RenderFillRect(renderer, &button);
    SDL_RenderDrawRect(renderer, &button);

    // Draw rounded circle ends for a more button-like appearance
    int circleRadius = (buttonHeight / 2) + 1;  // Half the height for proper proportions
    drawFilledCircle(renderer, buttonX, buttonY + circleRadius - 1, circleRadius);  // Left circle
    drawFilledCircle(renderer, buttonX + 175, buttonY + circleRadius - 1, circleRadius);  // Right circle
}                       // end of renderButton 
//==============================================================================

//====createTitle===============================================================
// Description: Creates the title
// Parameters: renderer - SDL renderer
//==============================================================================
void createTitle(SDL_Renderer *renderer) {
    Color color;
    char title[] = "Sudoku";

    // Render outline
    TTF_Font *font = TTF_OpenFont("src/font/PixelGame.otf", 180);
    SDL_Surface *surface = TTF_RenderText_Solid(font, title, color.black);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface);  // Free surface after creating texture

    SDL_Rect textRect;
    textRect.x = ((WIDTH - textWidth) / 2);
    textRect.y = 140;
    textRect.w = textWidth;
    textRect.h = textHeight;

    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture); // Clean up the texture
}                   // end of createTitle
//==============================================================================

//====difficultyText============================================================
// Description: Creates the difficulty text
// Parameters: renderer - SDL renderer
//==============================================================================
void difficultyText(SDL_Renderer *renderer) {
    Color color;
    char title[] = "Difficulty";

    // Render outline
    TTF_Font *font = TTF_OpenFont("src/font/PixelGame.otf", 40);
    SDL_Surface *surface = TTF_RenderText_Solid(font, title, color.black);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface);  // Free surface after creating texture

    SDL_Rect textRect;
    textRect.x = ((WIDTH - textWidth) / 2);
    textRect.y = 425;
    textRect.w = textWidth;
    textRect.h = textHeight;

    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture); // Clean up the texture
}                       // end of difficultyText
//==============================================================================

//====createPlayButton==========================================================
// Description: Creates the play button
// Parameters: renderer - SDL renderer
//==============================================================================
void createPlayButton(SDL_Renderer *renderer) {
    Color color;

    renderButton(renderer, 325);

    renderText(renderer, "PLAY", 325, color.white, 65);

    SDL_RenderPresent(renderer);
}                   // end of createPlayButton
//==============================================================================

//====createDifficultyButton====================================================
// Description: Creates the difficulty button
// Parameters: renderer - SDL renderer, difficulty - difficulty level
//==============================================================================
void createDifficultyButton(SDL_Renderer *renderer, int difficulty) {
    const int HEIGHT = 460;
    Color color;
    
    // Create button
    renderButton(renderer, HEIGHT);
    switch (difficulty) {
        case 0:
            renderText(renderer, "EASY", HEIGHT, color.white, 65);
            break;
        case 1:
            renderText(renderer, "MEDIUM", HEIGHT, color.white, 65);
            break;
        case 2:
            renderText(renderer, "HARD", HEIGHT, color.white, 65);
            break;
        default:
            break;
    }

    SDL_RenderPresent(renderer);
}                   // end of createDifficultyButton
//==============================================================================

//====createGrid================================================================
// Description: Creates the grid
// Parameters: renderer - SDL renderer
//==============================================================================
void createGrid(SDL_Renderer *renderer) {
    int offset = (800 - BOARD_SIZE) / 2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black lines

    // Draw vertical lines
    for (int i = 0; i <= 9; ++i) {
        int x = offset + i * CELL_SIZE;
        SDL_RenderDrawLine(renderer, x, offset, x, offset + BOARD_SIZE);
    }

    // Draw horizontal lines
    for (int i = 0; i <= 9; ++i) {
        int y = offset + i * CELL_SIZE;
        SDL_RenderDrawLine(renderer, offset, y, offset + BOARD_SIZE, y);
    }

    // Draw bold lines 
    for (int i = 0; i < 4; i++) {
        int x = offset + i * CELL_SIZE * 3;
        int y = offset + i * CELL_SIZE * 3;

        // Draw vertical bold lines 
        SDL_Rect verticalLine = {x - 1, offset, 3, BOARD_SIZE}; // 3px wide
        SDL_RenderFillRect(renderer, &verticalLine);

        // Draw horizontal bold lines 
        SDL_Rect horizontalLine = {offset, y - 1, BOARD_SIZE, 3}; // 3px tall
        SDL_RenderFillRect(renderer, &horizontalLine);
    }

}                           // end of createGrid
//==============================================================================

//====renderNum=================================================================
// Description: Renders the numbers to the screen
// Parameters: renderer - SDL renderer, game - Sudoku object
//==============================================================================
void renderNum(SDL_Renderer *renderer, Sudoku game) {
    TTF_Font *font = TTF_OpenFont("src/font/ByteBounce.ttf", 40);

    int offset = (800 - BOARD_SIZE) / 2;
    Color colors;
    SDL_Color color;

    // Iterate through board
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            string numStr = to_string(game.getBoard(row, col));
            if (numStr == "0") {   // skip empty cell
                continue;
            }
            
            // select color
            if (game.isNewNum(row, col)) {
                color = colors.vibrantBlue;
            } else {
                color = colors.black;
            }
            
            // Render number
            const char* num = numStr.c_str();
            SDL_Surface *surface = TTF_RenderText_Solid(font, num, color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            // Get dimensions 
            int textWidth = surface->w;
            int textHeight = surface->h;
            SDL_FreeSurface(surface);  // Free surface after creating texture

            SDL_Rect numRect = {
                offset + col * CELL_SIZE + (CELL_SIZE - textWidth) / 2,
                offset + row * CELL_SIZE + (CELL_SIZE - textHeight) / 2,
                textWidth,
                textHeight
            };

            SDL_RenderCopy(renderer, texture, nullptr, &numRect);
            SDL_DestroyTexture(texture);  // Free texture after rendering
        }
    }

}                        // end of renderNum
//==============================================================================

//====createTimer===============================================================
// Description: Creates the timer
// Parameters: renderer - SDL renderer, elapsedTime - time elapsed
//==============================================================================
void createTimer(SDL_Renderer *renderer, int elapsedTime) {
    Color color;

    // Format time
    string timeText = formatTime(elapsedTime);

    // Create a surface and texture for the text
    TTF_Font *font = TTF_OpenFont("src/font/ByteBounce.ttf", 40);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, timeText.c_str(), color.black);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Text dimensions
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface); // Free surface after creating texture
    SDL_Rect textRect = {190 - textWidth / 2, 100 - textHeight / 2, textWidth, textHeight};

    // Create a slightly larger rectangle as a background
    SDL_Rect backgroundRect = {
        textRect.x - 5, // Add padding on the left
        textRect.y - 5, // Add padding on the top
        textRect.w + 5, // Add padding to width
        textRect.h + 5  // Add padding to height
    };

    // Render the white rectangle & text
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &backgroundRect);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Present the updated screen
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textTexture);
}                       // end of createTimer
//==============================================================================

//====formatTime================================================================
// Description: Formats the time
// Parameters: time - time in seconds
// Return: formatted time
//==============================================================================
string formatTime(int time) {
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;
    int seconds = time % 60;
    ostringstream oss;

    oss << setfill('0') << setw(2) << hours << ":" 
                        << setw(2) << minutes << ":" 
                        << setw(2) << seconds;
    return oss.str();
}                            // end of formatTime
//==============================================================================

//====createSubmitButton========================================================
// Description: Creates the submit button
// Parameters: renderer - SDL renderer
//==============================================================================
void createSubmitButton(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // set black
    char text[] = "Submit";
    Color color;
    int thickness = 5;

    for (int i = 0; i < thickness; i++) {
        SDL_Rect button = {520 - i, 700 - i, 150 + 2 * i, 50 + 2 * i};
        SDL_RenderDrawRect(renderer, &button);
    }

    TTF_Font *font = TTF_OpenFont("src/font/ByteBounce.ttf", 50);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color.black);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface); // Free surface after creating texture

    SDL_Rect textRect;
    textRect.x = 537;
    textRect.y = 705;
    textRect.w = textWidth;
    textRect.h = textHeight;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture); // Clean up the texture
}                   // end of createSubmitButton
//==============================================================================

//====createRetryButton=========================================================
// Description: Creates the retry button
// Parameters: renderer - SDL renderer
//==============================================================================
void createRetryButton(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // set black
    char text[] = "Reset";
    Color color;
    int thickness = 5;

    for (int i = 0; i < thickness; i++) {
        SDL_Rect button = {130 - i, 700 - i, 150 + 2 * i, 50 + 2 * i};
        SDL_RenderDrawRect(renderer, &button);
    }

    TTF_Font *font = TTF_OpenFont("src/font/ByteBounce.ttf", 50);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color.black);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface); // Free surface after creating texture

    SDL_Rect textRect;
    textRect.x = 157;
    textRect.y = 705;
    textRect.w = textWidth;
    textRect.h = textHeight;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture); // Clean up the texture
}                       // end of createRetryButton
//==============================================================================

//====printEndScreen============================================================
// Description: Prints the end screen
// Parameters: renderer - SDL renderer, elapsedTime - time elapsed
//==============================================================================
void printEndScreen(SDL_Renderer *renderer, int elapsedTime) {
    // Set background color (light gray)
    SDL_SetRenderDrawColor(renderer, 155, 161, 157, 255);
    SDL_RenderClear(renderer);

    // Create title text
    renderText(renderer, "Congratulations!", 200, {0, 0, 0, 255}, 65);

    // Format time
    string timeText = formatTime(elapsedTime);
    renderText(renderer, timeText.c_str(), 300, {0, 0, 0, 255}, 65);

    // Present the updated screen
    SDL_RenderPresent(renderer);
}                       // end of printEndScreen
//==============================================================================

//====selectCell================================================================
// Description: Selects a cell
// Parameters: x - x position, y - y position, renderer - SDL renderer
// Return: index of selected cell
//==============================================================================
int selectCell(int x, int y, SDL_Renderer *renderer) {
    int offset = (800 - BOARD_SIZE) / 2;
    int index = -1;
    int thickness = 3;

    // checks if x & y inside grid
    bool inside = x >= offset && x < offset + BOARD_SIZE && y >= offset && y < offset + BOARD_SIZE;
    if (inside) {
        // Calculate the row and column of the cell
        int selectedCol = (x - offset) / CELL_SIZE;
        int selectedRow = (y - offset) / CELL_SIZE;

        // Calculate the top-left corner of the cell
        int cellX = offset + selectedCol * CELL_SIZE;
        int cellY = offset + selectedRow * CELL_SIZE;

        // Render a red box over the selected cell
        SDL_SetRenderDrawColor(renderer, 0, 173, 239, 255); // vibrant blue
        for (int i = 0; i < thickness; i++) {
            SDL_Rect thickRect = { cellX - i, cellY - i, CELL_SIZE + 2 * i, CELL_SIZE + 2 * i };
            SDL_RenderDrawRect(renderer, &thickRect);
        }

        // Determine index of selected cell
        index = selectedRow * 9 + selectedCol;
    }

    SDL_RenderPresent(renderer);
    return index;
}                           // end of selectCell
//==============================================================================

//====createPauseButton=========================================================
// Description: Creates the pause button
// Parameters: renderer - SDL renderer
//==============================================================================
void createPauseButton(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // Set black color for the pause button

    const int x = 655, y = 90, width = 6, height = 20;

    // Draw two vertical bars for the pause button
    for (int offset = 0; offset < 2; offset++) {
        SDL_Rect bar = {x + offset * 10, y, width, height};
        SDL_RenderFillRect(renderer, &bar);  // Fill the rectangle
        SDL_RenderDrawRect(renderer, &bar);  // Draw the outline
    }
}               // end of createPauseButton
//==============================================================================

//====createPauseScreen=========================================================
// Description: Creates the pause screen
// Parameters: renderer - SDL renderer, time - time elapsed
//==============================================================================
void createPauseScreen(SDL_Renderer *renderer, int time) {
    // transparent background
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 2);   // set white
    SDL_Rect background = {0, 0, 800, 800};
    SDL_RenderFillRect(renderer, &background);
    SDL_RenderDrawRect(renderer, &background);

    // background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // set white
    SDL_Rect square = {200, 200, 400, 300};
    SDL_RenderFillRect(renderer, &square);
    SDL_RenderDrawRect(renderer, &square);

    // outline
    int thickness = 12;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // set black
    for (int i = 0; i < thickness; i++) {
        SDL_Rect square = {200 - i, 200 - i, 400 + 2 * i, 300 + 2 * i};
        SDL_RenderDrawRect(renderer, &square);
    }

    Color color;
    renderText(renderer, "Paused", 225, color.black, 65);

    // resume button
    int outline = 5;
    for (int i = 0; i < outline; i++) {
        SDL_Rect button = {300 - i, 315 - i, 200 + 2 * i, 50 + 2 * i};
        SDL_RenderDrawRect(renderer, &button);
    }
    renderText(renderer, "Resume", 315, color.black, 60);

    // menu button
    for (int i = 0; i < outline; i++) {
        SDL_Rect button = {300 - i, 390 - i, 200 + 2 * i, 50 + 2 * i};
        SDL_RenderDrawRect(renderer, &button);
    }
    renderText(renderer, "Menu", 390, color.black, 60);

    // Present renderer
    SDL_RenderPresent(renderer);
}                       // end of createPauseScreen
//==============================================================================