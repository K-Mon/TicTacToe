# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

void printBoard (int board[]) {
    printf("\n---------\n");
    for (int i = 1; i <= 9; i++) {
        if (board[i - 1] == 1) {
            printf("|X|");
        } else if (board[i - 1] == -1){
            printf("|O|");
        } else {
            printf("| |");
        }
        if ((i%3 == 0)) {
            printf("\n---------\n");
        }
    }
}


void getMove(int *int_move, char string[]){
    int flag = 1;
    char move = '9';
    while (flag == 1) {
        // Get the row input
        if ((move == '0') || (move == '1') || (move == '2')) {
            flag = 0;
        } else {
            printf("\nPlease input the %s: ", string);
            move = getchar();
            while(getchar() != '\n');
        }
    }
    *int_move = move - '0';
}

bool check_move (int board[], int index){
    // Check if the move is a valid move
    if (board[index] == 0) {
        return true;
    } else {
        return false;
    }
}

int evaluateBoard(int board[]) {
    int combo[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6},
                        {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};
    for (int i = 0; i < 8; i++) {
        //computer wins
        if ((board[combo[i][0]] == -1) && (board[combo[i][1]] == -1) && (board[combo[i][2]] == -1)) {
            return 1;
        }
        // human wins
        if ((board[combo[i][0]] == 1) && (board[combo[i][1]] == 1) && (board[combo[i][2]] == 1)) {
            return -1;
        } 
    }
    return 0;
}


bool isDraw(int board[]) {
    for (int i = 0; i < 9; i++){
        if (board[i] == 0) {
            return false;
        }
    }
    return true;
}

int minimax (int board[], bool maximizing) {
    int score = evaluateBoard(board);

    if ((score == 1) || (score == -1)) {
        return score;
    } else if (isDraw(board) == true) {
        return 0;
    }

    if (maximizing == true) {
        int value = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = -1;
                int temp_value = minimax(board, !maximizing);
                board[i] = 0;
                if (temp_value > value){
                    value = temp_value;
                }
            }
        }
        return value;

    } else {
        int value = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = 1;
                int temp_value = minimax(board, !maximizing);
                board[i] = 0;
                if (temp_value < value){
                    value = temp_value;
                }
            }
        }
        return value;
    }
}

int computerMove (int board[]) {
    int best_move = 0;
    int best_score = INT_MIN;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            board[i] = -1;
            int score = minimax(board, false);
            board[i] = 0;
            if (score > best_score) {
                best_score = score;
                best_move = i;
            }
        }
    }
    return best_move;
}

int main() {

    // The human player will be 1
    bool game_over = false;
    bool computer_turn = false;
    int board[9] = {0};
    int result = 0;

    while (game_over == false) {
        int index = -10;

        if (computer_turn == true) {
            index = computerMove(board);
            board[index] = -1;
            computer_turn = false;
        } else {

            int valid_move = 0;

            while (valid_move != true) {
                printBoard(board);
                int temp_row = -1; int temp_col = -1;

                getMove(&temp_row, "row");
                getMove(&temp_col, "column");
                index = (3 * temp_row) + temp_col;
                valid_move = check_move(board, index);
                if (valid_move == false) {
                    printf("Invalid move");
                }
            }
            board[index] = 1;
            computer_turn = true;
        }

        result = evaluateBoard(board);

        if ((result == 1) || (result == -1) || (isDraw(board) == true)) {
            if (result == -1) { 
                printf("Result of the game: Human Wins"); 
            } else if (result == 1) {
                printf("Result of the game: Computer Wins");
            } else {
                printf("Result of the game: Draw");
            }
            game_over = true; 
            }
        printf("\n");
    }
    printBoard(board);
}