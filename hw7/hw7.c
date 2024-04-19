#include <stdio.h>

void initializeGame(int board[]);
void printBoard(int board[]);
void gamePlay(int board[]);
int move(int board[],int cup,int turn);

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
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("+  Computer  |                                   |   Player   +\n");
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("|            | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |            |\n", board[12], board[11], board[10], board[9], board[8], board[7]);
    printf("|    %2d      |-----|-----|-----|-----|-----|-----|     %d      |\n", board[13], board[6]);
    printf("|            | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |            |\n", board[0], board[1], board[2], board[3], board[4], board[5]);
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("Cups:           1     2     3     4     5     6\n");
}

void gamePlay(int board[]){
    int first_turn = 1, turn=1, cup,computerspoint = 0, playerspoint = 0,i,largestnum=0,largestadress;
    while (turn!=0){
        if (turn == 1){
            printf("Player's turn\n");
            while (cup < 1 || cup > 6){
                printf("Please enter the cup number you want to move: ");
                scanf("%d", &cup);
                if (cup < 1 || cup > 6){
                    printf("Invalid cup number\n");
                }
            }
            turn=move(board, cup, turn);
        }
        if (turn == 2){
            printf("Computer's turn\n");
            for(i=7 ; i<13;i++){
                cup=i;
                if (board[cup+board[cup]]==i || cup+i==13){
                    move(board, cup, turn);
                    break;
                }
                if (board[cup]>largestnum){
                    largestadress=cup;
                    largestnum=board[cup];
                }
            }
            turn=move(board, largestadress, turn);
        }
    }
    
}

int move(int board[],int cup,int turn){
    int i, n, result;
    i = cup;
    board[cup-1] = 0;
    if (turn == 1){
        n = board[cup-1];
        for (n; n > 0; n--){
            if (i!=13){ /*board13 is computer's large cup*/
                board[i] += 1;                
            }
            if (n ==1){
                if (i==6 || board[i] == 1){                
                    printf("+-------------------------------------------------------------+\n");
                    printf("+---------------------- Player's point!!! --------------------+\n");
                    result=1;
                }
                else result=2;
            }
            i++;
            if (i == 14) i=0;
        }
    }
    if (turn == 2){        
        printf("Computer's move: %d\n",cup);
        n = board[cup];
        for (n; n > 0; n--){
            if (i!=6){ /*board6 is player's large cup*/
                board[i] += 1;                
            }
            if (n ==1){
                if (i==13 || board[i] == 1){                
                    printf("+-------------------------------------------------------------+\n");
                    printf("+---------------------- Computer's point!!! ------------------+\n");
                    result=2;
                }
                else result=1;
            }
            i++;
            if (i == 14) i=0;
        }
    }
    printBoard(board);
    return result;
}
int main(){
    int board[14]; /* 0-5: player 1, 6: store 1, 7-12: player 2, 13: store 2*/
    initializeGame(board);
    printBoard(board);
    gamePlay(board);
    return 0;
} 