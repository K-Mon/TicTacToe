# include <stdio.h>
# include <limits.h>

void printBoard(int board[3][3]){
    // Print the board
    printf("  0  1  2\n");
    for (int i = 0; i < 3; i++) {
        printf(" ---------");
        printf("\n");
        printf("%d", i);
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0){ 
                printf("| |"); 
            }
            else if (board[i][j] == 1) { 
                printf("|X|"); 
            }
            else { 
                printf("|O|"); 
            }
        }
        printf("\n");
    }
    printf(" ---------");
}

int get_row(){
    // Get the row input
    int flag = 1;
    char y_move_in; 

    while (flag == 1){
        printf("\nPlease input the row: ");
        y_move_in = getchar();
        while(getchar() != '\n');
        if (y_move_in == '0' || y_move_in == '1' || y_move_in == '2') {
            flag = 0;
        } else {
            printf("%c is an invlaid input. Please enter 0, 1, or 2", y_move_in);
        }
    }
    return (y_move_in - '0');
}

int get_column(){
    // Get the column input
    int flag = 1;
    char x_move_in; 

    while (flag == 1){
        printf("\nPlease input the column: ");
        x_move_in = getchar();
        while(getchar() != '\n');
        if (x_move_in == '0' || x_move_in == '1' || x_move_in == '2') {
            flag = 0;
        } else {
            printf("%c is an invlaid input. Please enter 0, 1, or 2", x_move_in);
        }
    }
    return (x_move_in - '0');
}

int check_move (int board[3][3], int *x_move, int *y_move){
    // Check if the move is a valid move
    printf("%d",board[*x_move][*y_move]);
    if (board[*x_move][*y_move] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_game_over (int board[3][3], int player){
    // Check if a game is over
    int is_over = 0;
    is_over = (((board[0][0] == player) && (board[0][1] == player) && (board[0][2] == player)) ||
        ((board[1][0] == player) && (board[1][1] == player) && (board[1][2] == player)) ||
        ((board[2][0] == player) && (board[2][1] == player) && (board[2][2] == player)) ||
        ((board[0][0] == player) && (board[1][0] == player) && (board[2][0] == player)) ||
        ((board[0][1] == player) && (board[1][1] == player) && (board[2][1] == player)) ||
        ((board[0][2] == player) && (board[1][2] == player) && (board[2][2] == player)) ||
        ((board[0][0] == player) && (board[1][1] == player) && (board[2][2] == player)) ||
        ((board[0][2] == player) && (board[1][1] == player) && (board[2][0] == player)));
    return is_over;
}

int evaluate_win(int board[3][3], int player){
    // Evaluate the game and determine the point distribuition
    if (is_game_over(board, player) == 1) { return 1; }
    else if (is_game_over(board, -player) == 1) { return -1; }
    else { return 0; } 
}

int is_draw(int board[3][3]) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] == 0) { return 0; }
        }
    }
    return 1;
}

int minimax (int board[3][3], int max_player){
    // The minimax function
    int score = evaluate_win(board, max_player);

    if (score == 1 || score == -1 || is_draw(board) == 1) { 
        return score; 
    }

    if (max_player == -1) {
        int value = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = max_player;
                    int value_temp = minimax(board, 1);
                    if (value_temp > value) {
                        value = value_temp;
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
    else {
        int value = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = max_player;
                    int value_temp = minimax(board, -1);
                    if (value_temp < value) {
                        value = value_temp;
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
}

void computer_move (int board[3][3], int *x_move, int *y_move){
    // make the move for the computer
    int best_score = INT_MIN;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] == 0) {
                printf("\n %i, (%i, %i)", (board[i][j] == 0), i, j);
                board[i][j] = -1;
                int score = minimax(board, 1);
                if (score >= best_score) {
                    best_score = score;
                    *x_move = j;
                    *y_move = i;
                }
                board[i][j] = 0;
            }
        }
    }
}

int main (void){

    int valid_move = 0;
    int game_over = 0;
    int board[3][3] = {0};
    int player = 1;

    while (game_over == 0){
        int y_move = -1; int x_move = -1;

        if (player == -1) {
            computer_move(board, &x_move, &y_move);
            printf("\n%i, %i \n", x_move, y_move);
            board[x_move][y_move] = -1;
        }

        if (player == 1) {
            valid_move = 0;
            while (valid_move != 1) {
                printBoard(board);
                y_move = get_row();
                x_move = get_column();
                valid_move = check_move(board, &x_move, &y_move);
                if (valid_move == 0) {
                    printf("Invalid move");
                }
            }
            board[y_move][x_move] = 1;
        }

        game_over = is_game_over(board, player);
        player = player*-1;
        printf("\n");
    } 
    

}
