#include <stdio.h>

void initializeGame(int board[]);
void printBoard(int board[]);
void gamePlay(int board[]);
void move(int board[],int cup,int turn);

void initializeGame(int board[]){
    int i,n;
    printf("Please enter the number of stones for each cup: ");
    scanf("%d", &n);
    for(i = 0; i < 14; i++){
        if (i == 6 || i == 13){
            board[i] = 0;
        }
        else board[i] = n;
    }

}
void printBoard(int board[]){
    int i;
    printf("+----+---+---+---+---+---+---+----+\n");
    printf("|    | %d | %d | %d | %d | %d | %d |    |\n", board[12], board[11], board[10], board[9], board[8], board[7]);
    printf("| %d  |---|---|---|---|---|---| %d  |\n", board[6], board[13]);
    printf("|    | %d | %d | %d | %d | %d | %d |    |\n", board[0], board[1], board[2], board[3], board[4], board[5]);
    printf("+----+---+---+---+---+---+---+----+\n");
    printf("Cups:  1   2   3   4   5   6\n");
}

void gamePlay(int board[]){
    int turn = 1, cup;
    if (turn == 1){
        printf("Player's turn\n");
        printf("Please enter the cup number you want to move: ");
        scanf("%d", &cup);
        move(board, cup, turn);
    }
    if (turn == 2){
        printf("Player 2's turn\n");
    }

}

void move(int board[],int cup,int turn){
    int i, n;
    if (turn == 1){
        n = board[cup-1];
        board[cup-1] = 0;
        for (n; n > 0; n--){
            
        }
    }
}
int main(){
    int board[14]; /* 0-5: player 1, 6: store 1, 7-12: player 2, 13: store 2*/
    initializeGame(board);
    printBoard(board);



} 