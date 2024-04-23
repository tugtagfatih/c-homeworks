#include <stdio.h>

void initializeGame(int board[]);
void printBoard(int board[]);
void gamePlay(int board[]);
int move(int board[],int cup,int turn);

void initializeGame(int board[]){
    int i,n=0;
    while (n<1){
        printf("Please enter the number of stones for each cup: ");
        scanf("%d", &n);
        if(n>1) {
            for(i = 0; i < 14; i++){
                if (i == 6 || i == 13){
                    board[i] = 0;
                }
                else board[i] = n;
            }
        }
        else printf ("Game size can't be less than 1\n");
    }
}
void printBoard(int board[]){
    int i;
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("+  Computer  |                                   |   Player   +\n");
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("|            | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |            |\n", board[12], board[11], board[10], board[9], board[8], board[7]);
    printf("|    %2d      |-----|-----|-----|-----|-----|-----|     %d       |\n", board[13], board[6]);
    printf("|            | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |            |\n", board[0], board[1], board[2], board[3], board[4], board[5]);
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("Cups:           1     2     3     4     5     6\n");
}

void gamePlay(int board[]){
    int first_turn = 1, turn=1, cup,i,largestnum=0,largestadress;
    while (turn!=0){
        largestadress=0;
        largestnum=0;
        cup=0;
        if (turn == 1){
            printf("Player's turn\n");
            while (cup < 1 || cup > 6){
                printf("Please enter the cup number you want to move: ");
                scanf("%d", &cup);
                getchar();
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
                if (cup+board[i]==13){
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
        if((board[0]==0 && board[1]==0 && board[2]==0 && board[3]==0 && board[4]==0 && board[5]==0) || (board[7]==0 && board[8]==0 && board[9]==0 && board[10]==0 && board[11]==0 && board[12]==0)){
            turn=0;
            if (board[6]>board[13]){
                printf("+-------------------------------------------------------------+\n");
                printf("+------------------- Player wins the game!!! ----------------+\n");
            }
            else if (board[6]<board[13]){
                printf("+-------------------------------------------------------------+\n");
                printf("+------------------- Computer wins the game!!! --------------+\n");
            }
            else{
                printf("+-------------------------------------------------------------+\n");
                printf("+------------------- The game is a draw!!! ------------------+\n");
            }
        }
    }
    
}

int move(int board[],int cup,int turn){
    int i, n, result;
    i = cup;
    if (turn == 1){
        result=2;
        n = board[cup-1];
        board[cup-1] = 0;
        for (n; n > 0; n--){
            if (i!=13){ /*board13 is computer's large cup*/
                board[i] += 1;
            }
            if (n ==1){
                if (i==6 ){                
                    printf("+-------------------------------------------------------------+\n");
                    printf("+------------------- Player's move again!!! ------------------+\n");
                    result=1;
                }
                else if(board[i]<1){
                    printBoard(board);
                    move(board, board[i], 1);
                }
            }
            i++;
            if (i == 14) i=0;
        }
    }
    if (turn == 2){        
        printf("Computer's move: %d\n",cup);
        result=1;
        n = board[cup];
        board[cup]=0;
        for (n; n > 0; n--){
            if (i!=6){ /*board6 is player's large cup*/
                board[i] += 1;                
            }
            i++;
            if (i == 14) i=0;
        }
        if (i==13 ){                
            printf("+-------------------------------------------------------------+\n");
            printf("+------------------ Computer's move again!!! -----------------+\n");
            result=2;
        }
        else if (board[i]>1 && i!=6 && i!= 13){
            printBoard(board);
            move(board, i, 2);
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
