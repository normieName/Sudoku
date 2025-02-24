// Sudoku.h - header file

using namespace std;

class Sudoku {
private:
    const int SIZE = 9;
    int rows;
    int cols;
    int board[9][9];
    int solvedBoard[9][9];
    int unsolvedBoard[9][9];
    int difficulty;

public:
    Sudoku();
    ~Sudoku();
    void generateBoard();
    bool fillBoard(int x, int y);
    bool checkValid(int x, int y, int num);
    void randomNum(int arr[]);
    void setDifficulty(int num);
    bool checkSolution();
    int solutionCounter(int x, int y);
    void removeNums();
    void printBoard();
    int getBoard(int x, int y);
    void setBoard(int x, int y, int num);
    bool isFull();
    bool isCorrect();
    bool isNewNum(int x, int y);
    void resetBoard();
};