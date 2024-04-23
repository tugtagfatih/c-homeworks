#include <stdio.h>

void initializeGame(int board[2][7]);
void printBoard(int board[2][7]);
void gamePlay(int board[2][7]);
int move(int board[2][7],int cup,int turn);

void initializeGame(int board[2][7]){
    int i,n=0;
    while (n<1){
        printf("Please enter the number of stones for each cup: ");
        scanf("%d", &n);
        if(n>1) {
            for(i = 0; i < 7; i++){
                if (i == 6){
                    board[0][i] = 0;
                    board[1][i] = 0;
                }
                else {
                    board[0][i] = n;
                    board[1][i] = n;
                }
            }
        }
        else printf ("Game size can't be less than 1\n");
    }
}

void printBoard(int board[2][7]){
    int i;
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("+  Computer  |                                   |   Player   +\n");
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("|            | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |            |\n", board[1][5], board[1][4], board[1][3], board[1][2], board[1][1], board[1][0]);
    printf("|    %2d      |-----|-----|-----|-----|-----|-----|     %2d     |\n", board[1][6], board[0][6]);
    printf("|            | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |            |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5]);
    printf("+------------+-----+-----+-----+-----+-----+-----+------------+\n");
    printf("Cups:           1     2     3     4     5     6\n");
}

void gamePlay(int board[2][7]){
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
                if (board[1][i-7]!=0 && 6-board[1][i-7]==0 ){
                    printf("Computer's move: %d\n",i-6);
                    move(board, cup, turn);
                    break;
                }
                if (board[1][i-7]>largestnum){
                    largestnum=board[1][i-7];
                    largestadress=i;
                }
            }
            if (largestadress==0) largestadress=7;
            while (1) {
                if (board[1][largestadress-7]==0){
                    largestadress++;
                    if (largestadress==13) largestadress=7;
                }
                else break;
            }
            printf("Computer's move: %d\n",largestadress-6);
            turn=move(board, largestadress, turn);
        }
        if((board[0][0]==0 && board[0][1]==0 && board[0][2]==0 && board[0][3]==0 && board[0][4]==0 && board[0][5]==0) || (board[1][0]==0 && board[1][1]==0 && board[1][2]==0 && board[1][3]==0 && board[1][4]==0 && board[1][5]==0)){
            turn=0;
            if (board[0][6]>board[1][6]){
                printf("+-------------------------------------------------------------+\n");
                printf("+------------------- Player wins the game!!! ----------------+\n");
            }
            else if (board[0][6]<board[1][6]){
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

int move(int board[2][7],int cup,int turn){
    int i,j, n, result;
    int otherplayer=0;
    i = cup;
    if (turn == 1){
        result=2;
        n = board[0][cup-1];
        board[0][cup-1] = 0;
        for (j=0; j < n; j++){
            if (i<7){
                board[0][i] += 1;
            }
            else if (i>=7 && i<13){
                board[1][i-7] += 1;
            }
            else n++; /*when i==13*/
            i++;
            if (i == 14) i=0;
        }
        if ((board[0][i] >1 || board[1][i-7] >1)&& i!=7){
            printf("Next move is: %d\n",i);
            printBoard(board);
            move(board, i, turn);
        }
        else if (i==7){
            result=1;
        }
    }
    if (turn == 2){        
        /*printf("Computer's move: %d\n",cup);*/
        result=1;
        n = board[1][cup-7];
        board[1][cup-7]=0;
        i=cup+1;
        for (n; n > 0; n--){
            if (i<6){
                board[0][i] += 1;
            }
            else if (i>6 && i<=13){
                board[1][i-7] += 1;
            }
            else n++;
            i++;
            if (i == 14) i=0;
        }
        if (i==0){
            result=2;
        }
        else if (board[1][i-7] >1 || board[0][i] >1){
            printBoard(board);
            move(board, i, turn);
        }
    }
    printBoard(board);
    return result;
}
int main(){
    int board[2][7]; /* 0-5: player 1, 6: store 1, 7-12: player 2, 13: store 2*/
    initializeGame(board);
    printBoard(board);
    gamePlay(board);
    return 0;
}
