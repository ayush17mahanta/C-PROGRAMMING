#include <iostream>
using namespace std;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void displayBoard() {
    for (int i = 0; i < 9; i += 3) {
        cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << endl;
        if (i < 6) cout << "---|---|---" << endl;
    }
}

bool checkWin(char player) {
    for (int i = 0; i < 3; ++i)
        if ((board[i] == player && board[i + 3] == player && board[i + 6] == player) ||
            (board[3 * i] == player && board[3 * i + 1] == player && board[3 * i + 2] == player))
            return true;
    return (board[0] == player && board[4] == player && board[8] == player) ||
           (board[2] == player && board[4] == player && board[6] == player);
}

bool checkDraw() {
    for (char cell : board) if (cell == ' ') return false;
    return true;
}

void playGame() {
    char currentPlayer = 'X';
    while (true) {
        displayBoard();
        int move;
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;
        move--;
        if (move < 0 || move >= 9 || board[move] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[move] = currentPlayer;
        if (checkWin(currentPlayer)) {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }
        if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    char playAgain;
    do {
        fill(begin(board), end(board), ' ');  // Reset the board
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}
