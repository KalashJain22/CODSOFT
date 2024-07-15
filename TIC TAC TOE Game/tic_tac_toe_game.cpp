#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 3; // Grid size of game
const char X = 'X'; 
const char O = 'O';

struct Score {
    int playerX;
    int playerO;
    int draw;
};

Score score = {0, 0, 0};

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    system("clear");  // For clearing screen
    cout << "\nScore - PlayerX: " << score.playerX << ", PlayerO: " << score.playerO << ", Draw: " << score.draw << endl;
    cout << endl << "Tic Tac Toe" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < BOARD_SIZE - 1) {
                cout << "|";
            }
        }
        if (i < BOARD_SIZE - 1) {
            cout << endl << "---+---+---" << endl;
        }
    }
}

bool check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
           (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
    }
    return false;
}

bool check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int column) {
    return row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE && board[row][column] == ' ';
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    //Automatically moves for players in last empty box
    int count = 0, x, y;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                count++;
                x = i;
                y = j;
            }
        }
    }
    if (count == 1) {
        board[x][y] = player;
        return;
    }

    int row, column;
    do {
        cout << "\n\nPlayer " << player << "'s Move";
        cout << endl << "Enter Row And Column (1-3): ";
        cin >> row >> column;
        row--; column--;  // Converting to zero based
    } while (!is_valid_move(board, row, column));
    board[row][column] = player;
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char current_player = rand() % 2 == 0 ? X : O; //Generating a rndom 1 and 0

    print_board(board);
    while (true) {
        player_move(board, current_player);
        print_board(board);
        if (check_win(board, current_player)) {
            if (current_player == X) {
                score.playerX++;
                print_board(board);
            } else {
                score.playerO++;
                print_board(board);
            }
            cout << "\n\nCongratulations player " << current_player << " won.";
            break;
        }
        if (check_draw(board)) {
            score.draw++;
            print_board(board);
            cout << "\n\nIt's a drawm, Let's play again.";
            break;
        }
        current_player = (current_player == X) ? O : X;
    }
}

int main() {
    srand(time(0));
    int choice;

    cout << endl << "\t*** Welcome To Tic Tac Toe Game ***" << endl;
    cout<< endl << "Press enter to start the game.";
    cin.ignore();

    do {
        play_game();
        cout << endl << "Do You Want To Play Again? (1 for Yes/ 0 for No): ";
        cin >> choice;
    } while (choice == 1);
    
    cout << endl << "\tThanks For Playing, Hope You Enjoyed.";
}
