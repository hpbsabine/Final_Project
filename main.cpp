#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int BOARD_SIZE = 5;

// Class representing a single cell on the game board
class Cell {
public:
    char symbol; // Symbol representing the state of the cell
    bool isHit; // Whether the cell has been hit or not

    Cell() : symbol('~'), isHit(false) {} // Constructor initializes the cell

    // Function to check if the cell has been hit
    bool isCellHit() const {
        return isHit;
    }

    // Function to mark the cell as hit
    void markAsHit() {
        isHit = true;
    }

    // Function to set the symbol of the cell
    void setSymbol(char sym) {
        symbol = sym;
    }
};

// Class representing the game board
class Board {
private:
    vector<vector<Cell>> grid; // 2D vector to hold the cells

public:
    // Constructor initializes the game board with cells
    Board() {
        grid.resize(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
    }

    // Function to display the game board
    void display(bool showShips = false) const {
        cout << "  ";
        for (int i = 0; i < BOARD_SIZE; ++i)
            cout << i << " ";
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (grid[i][j].isCellHit()) {
                    if (grid[i][j].symbol == 'S') {
                        cout << "H ";
                    } else {
                        cout << "X ";
                    }
                } else if (showShips && grid[i][j].symbol == 'S') {
                    cout << "S ";
                } else {
                    cout << "~ ";
                }
            }
            cout << endl;
        }
    }

    // Function to mark a cell as hit
    void markCell(int row, int col) {
        grid[row][col].markAsHit();
    }

    // Function to set the symbol of a cell
    void setSymbol(int row, int col, char sym) {
        grid[row][col].setSymbol(sym);
    }

    // Function to check if a cell has been hit
    bool isCellHit(int row, int col) const {
        return grid[row][col].isCellHit();
    }

    // Function to check if a cell contains a ship symbol
    bool isShipCell(int row, int col) const {
        return grid[row][col].symbol == 'S';
    }
};

// Forward declaration of functions
bool checkGameOver(const Board &board);

// Function to randomly place ships on the game board
void placeShips(Board &board, int numShips) {
    srand(time(0));
    for (int i = 0; i < numShips; ++i) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        board.setSymbol(row, col, 'S');
    }
}

// Function for the player's move
void playerMove(Board &computerBoard) {
    int row, col;
    cout << "Enter your move (row column): ";
    while (!(cin >> row >> col) || row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || computerBoard.isCellHit(row, col)) {
        cout << "Invalid move. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (computerBoard.isShipCell(row, col)) {
        cout << "You hit a ship!\n";
    } else {
        cout << "You missed.\n";
    }

    computerBoard.markCell(row, col);
}

// Function for the computer's move
void computerMove(Board &playerBoard) {
    int row, col;
    row = rand() % BOARD_SIZE;
    col = rand() % BOARD_SIZE;

    cout << "Computer's move: " << row << " " << col << endl;

    if (playerBoard.isShipCell(row, col)) {
        cout << "Computer hit your ship!\n";
    } else {
        cout << "Computer missed.\n";
    }

    playerBoard.markCell(row, col);
}

// Function to play the game
void playGame(Board &playerBoard, Board &computerBoard) {
    placeShips(playerBoard, 3); // Place 3 ships on the player's board
    placeShips(computerBoard, 3); // Place 3 ships on the computer's board

    cout << "Welcome to Battleship!\n";
    cout << "Your board:\n";
    playerBoard.display(true); // Show player's ships
    cout << "Computer's board:\n";
    computerBoard.display();

    int turns = 0;
    while (true) {
        cout << "===== Turn " << (++turns) << " =====\n";
        playerMove(computerBoard); // Player's move
        cout << "Your board after your move:\n";
        playerBoard.display(true); // Show player's ships
        if (checkGameOver(computerBoard)) { // Check if all computer's ships are sunk
            cout << "Congratulations! You've sunk all the computer's ships in " << turns << " turns!\n";
            break;
        }

        cout << "===== Computer's Turn =====\n";
        computerMove(playerBoard); // Computer's move
        cout << "Computer's board after its move:\n";
        computerBoard.display();
        if (checkGameOver(playerBoard)) { // Check if all player's ships are sunk
            cout << "Oh no! The computer has sunk all your ships.\n";
            break;
        }
    }
}

// Function to check if all ships are sunk
bool checkGameOver(const Board &board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board.isShipCell(i, j) && !board.isCellHit(i, j)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    Board playerBoard;
    Board computerBoard;
    playGame(playerBoard, computerBoard);
    return 0;
}
