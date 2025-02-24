// Sudoku.cpp - implementation file 
#ifndef SUDOKU_H
#define SUDOKU_H

#include "Sudoku.h"
#include "Util.h"
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

// Constructor
Sudoku::Sudoku() {
    this->rows = 9;
    this->cols = 9;
    this->difficulty = EASY;
}

// Destructor
Sudoku::~Sudoku() {}

//====generateBoard=============================================================
// Description: Generates a random sudoku board
//==============================================================================
void Sudoku::generateBoard() {
    // Initialize the board with zeros or any other default value
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }

    // fill the board
    fillBoard(0, 0);

    // copy the solved board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            solvedBoard[i][j] = board[i][j];
        }
    }

    // remove the nums
    removeNums();

    // copy the unsolved board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            unsolvedBoard[i][j] = board[i][j];
        }
    }
}                       // end of generateBoard
//==============================================================================

//====fillBoard================================================================
// Description: Fills the board with random numbers
// Parameters: x - row, y - column
// Return: true if the board is filled, false otherwise
//==============================================================================
bool Sudoku::fillBoard(int x, int y) {
    // base case: if the puzzle is filled
    if (x == SIZE) {
        return true;
    }

    // iterates through each cell
    int nextRow = (y == SIZE - 1) ? x + 1 : x;
    int nextCol = (y + 1) % SIZE;

    // shuffle through numbers
    int numbers[SIZE] = {0};
    randomNum(numbers);

    for (int num : numbers) {
        // check if number is valid 
        if (checkValid(x, y, num)) {
            board[x][y] = num;

            // recursive call: move to next cell
            if (fillBoard(nextRow, nextCol)) {
                return true;
            }

            // backtrack
            board[x][y] = 0;
        }
    }

    // no valid number found for this cell
    return false;
}                       // end of fillBoard
//==============================================================================

//====checkValid===============================================================
// Description: Checks if a number is valid in a cell
// Parameters: x - row, y - column, num - number to check
// Return: true if the number is valid, false otherwise
//==============================================================================
bool Sudoku::checkValid(int x, int y, int num) {
    const int SUBGRID = 3;

    // check row and column
    for (int i = 0; i < SIZE; i++) {
        if (board[x][i] == num || board[i][y] == num) {
            return false;
        }
    }

    // check sub-grid (3x3)
    int startRow = x - x % SUBGRID;
    int startCol = y - y % SUBGRID;
    for (int r = startRow; r < startRow + SUBGRID; r++) {
        for (int c = startCol; c < startCol + SUBGRID; c++) {
            if (board[r][c] == num) {
                return false;
            }
        }
    }

    return true;
}                         // end of checkValid
//==============================================================================

//====randomNum================================================================
// Description: Fills an array with numbers 1-9 and shuffles them
// Parameters: arr - array to fill
//==============================================================================
void Sudoku::randomNum(int arr[]) {
    // fill array with numbers 1-9
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    // shuffle array 
    random_device rd;
    mt19937 gen(rd());  // Mersenne Twister engine
    shuffle(arr, arr + SIZE, gen);
}                        // end of randomNum
//==============================================================================

//====setDifficulty============================================================
// Description: Sets the difficulty level
// Parameters: num - difficulty level
//==============================================================================
void Sudoku::setDifficulty(int num) {
    switch (num) {
        case 0:
            this->difficulty = EASY;
            break;
        case 1:
            this->difficulty = MEDIUM;
            break;
        case 2:
            this->difficulty = HARD;
            break;
        default:
            cout << "Invalid difficult level" << endl;
    }
}                    // end of setDifficulty
//==============================================================================

//====checkSolution============================================================
// Description: Checks if the puzzle has a unique solution
// Return: true if the puzzle has a unique solution, false otherwise
//==============================================================================
bool Sudoku::checkSolution() {
    int solutions = solutionCounter(0, 0);

    if (solutions != 1) {
        return false;
    }

    return true;
}                    // end of checkSolution
//==============================================================================

//====solutionCounter==========================================================
// Description: Counts the number of solutions for the puzzle
// Parameters: x - row, y - column
// Return: number of solutions
//==============================================================================
int Sudoku::solutionCounter(int x, int y) {
    int solutions = 0;

    // base case: if puzzle is solvable
    if (x == SIZE) {
        return 1;   // found a solution
    }

    // Calculate next cell position
    int nextRow = (y == SIZE - 1) ? x + 1 : x;
    int nextCol = (y + 1) % SIZE;

    // check if cell is filled
    if (board[x][y] != 0) {
        // Skip filled cells and move to the next
        return solutionCounter(nextRow, nextCol);
    }

    // Try placing numbers 1-9
    for (int i = 1; i <= SIZE; i++) {
        if (checkValid(x, y, i)) {
            board[x][y] = i;

            // accumlate solutions
            solutions += solutionCounter(nextRow, nextCol);

            // reset cell to 0
            board[x][y] = 0;
        }
    }

    return solutions;
}                        // end of solutionCounter
//==============================================================================

//====removeNums===============================================================
// Description: Removes numbers from the board
//==============================================================================
void Sudoku::removeNums() {
    // random number 0-8
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, SIZE - 1);

    // remove numbers from board
    int removed = 0;
    while (removed < difficulty) {
        // generate random x and y coords
        int x = dis(gen);
        int y = dis(gen);

        // check if cell is empty
        if (board[x][y] == 0) {
            continue;
        }

        // remove number
        int temp = board[x][y];
        board[x][y] = 0;

        // check if puzzle is still solvable
        if (!checkSolution()) {
            board[x][y] = temp;
        } else {
            removed++;
        }
    }
}                         // end of removeNums
//==============================================================================

//====printBoard===============================================================
// Description: Prints the board
//==============================================================================
void Sudoku::printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";

            if ((j + 1) % 3 == 0) {
                cout << "|";
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0) {
            cout << "---------------------" << endl;
        }
    }
}                      // end of printBoard
//==============================================================================

//====getBoard================================================================
// Description: Returns the board
// Parameters: x - row, y - column
// Return: number at the specified cell
//==============================================================================
int Sudoku::getBoard(int x, int y) {
    return board[x][y];
}                      // end of getBoard
//==============================================================================

//====setBoard==========================================================
// Description: Sets the board
// Parameters: x - row, y - column, num - number to set
//==============================================================================
void Sudoku::setBoard(int x, int y, int num) {
    if (unsolvedBoard[x][y] == 0) {
        board[x][y] = num;
    }
}                   // end of setBoard
//==============================================================================

//====isFull==================================================================
// Description: Checks if the board is full
// Return: true if the board is full, false otherwise
//==============================================================================
bool Sudoku::isFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}                        // end of isFull
//==============================================================================

//====isCorrect===============================================================
// Description: Checks if the board is correct
// Return: true if the board is correct, false otherwise
//==============================================================================
bool Sudoku::isCorrect() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != solvedBoard[i][j]) {
                return false;
            }
        }
    }

    return true;
}                           // end of isCorrect
//==============================================================================

//====isNewNum================================================================
// Description: Checks if a number is new
// Parameters: x - row, y - column
// Return: true if the number is new, false otherwise
//==============================================================================
bool Sudoku::isNewNum(int x, int y) {
    if (board[x][y] == unsolvedBoard[x][y]) {
        return false;
    }

    return true;
}                        // end of isNewNum
//==============================================================================

//====resetBoard==============================================================
// Description: Resets the board
//==============================================================================
void Sudoku::resetBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = unsolvedBoard[i][j];
        }
    }
}
//==============================================================================

#endif