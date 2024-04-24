#include <stdio.h>

void initializeGame(int board[2][7]);
void printBoard(int board[2][7]);
void gamePlay(int board[2][7], int turn);
void move(int board[2][7],int cup,int turn);
int check_end(int board[2][7]);

int check_end(int board[2][7]){
    int ret;
    if ((board[0][0]==0 && board[0][1]==0 && board[0][2]==0 &&  board[0][3]==0 &&  board[0][4]==0 &&  board[0][5]==0 ) || (board[1][0]==0 && board[1][1]==0 && board[1][2]==0 &&  board[1][3]==0 &&  board[1][4]==0 &&  board[1][5]==0))
    {ret=1;}
    else ret=0;
    if (ret==1){
        if (board[0][6]>board[1][6]){
            printf("+-------------------------------------------------------------+\n");
            printf("+------------------- Player wins the game!!! -----------------+\n");
        }
        else if (board[0][6]<board[1][6]){
            printf("+-------------------------------------------------------------+\n");
            printf("+------------------- Computer wins the game!!! ---------------+\n");
        }
        else{
            printf("+-------------------------------------------------------------+\n");
            printf("+------------------- The game is a draw!!! -------------------+\n");
        }
    }
    return ret;
}

int main(){
    int board[2][7]; /* 0-5: player 1, 6: store 1, 7-12: player 2, 13: store 2*/
    initializeGame(board);
    printBoard(board);
    gamePlay(board, 1); /*1 for player. 2 for computer.*/
    return 0;
}

void initializeGame(int board[2][7]){
    int i,n=0;
    while (n<1){
        printf("Please enter the number of stones for each cup: ");
        scanf("%d", &n);
        if(n>=1) {
            for(i = 0; i < 7; i++){
                board[0][i] = n;
                board[1][i] = n;
            }
            board[0][6] = 0;
            board[1][6] = 0;
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

void gamePlay(int board[2][7] ,int turn){
    int cup=0,i,largestnum=0,largestadress,j;
    if (turn==1){
        printf("Player's turn\n");
        while (cup < 1 || cup > 6 || board[0][cup-1]==0){
            printf("Please enter the cup number you want to move: ");
            scanf("%d", &cup);
            getchar();
            if (cup < 1 || cup > 6 || board[0][cup-1]==0){
                printf("Invalid cup number\n");
            }
        }
        move(board, cup-1, turn);
    }

    else if (turn==2){
        printf("Computer's turn\n");
        for(i=0 ; i<6 ; i++){
            if (board[1][i]!=0){
                if (6-board[1][i]==0) largestnum=0,largestadress=i;
                if(largestnum < board[1][i])largestnum = board[1][i],largestadress=i;
            }
        }
        if (largestadress<13){
            move(board,largestadress+7,2);
        }
        else {
            for(i=0; i<6; i++) if (board[1][i]!=0) largestadress=i;
            move(board,largestadress+7,2);
        }
    }
}

void move(int board[2][7],int cup,int turn){
    int i,j,n;
    if(turn==1){
        j=cup+1;
        n=board[0][cup];
        board[0][cup]=0;
        for (i=0; i<n ; i++){
            if (j<7) board[0][j]+=1;
            else if(j>=7 && j<13) board[1][j-7] +=1;
            else i--;
            j++;
            if(j==14) j=0;
        }
        printBoard(board);
        j=j-1;
        if (check_end(board)==1) {gamePlay(board, 0);}
        else if(j==6) gamePlay(board,1);
        else if((j<7 && board[0][j] > 1) || ((j>=7 && j<13) && board[1][j-7] >1)) move(board, j,1);
        else gamePlay(board,2);
    }
    if (turn==2){
        j=cup+1;
        n=board[0][cup];
        board[0][cup]=0;
        for (i=0; i<n ; i++){
            if (j<6) board[0][j]+=1;
            else if(j>=7 && j<=13) board[1][j-7] +=1;
            else i--;
            j++;
            if(j==14) j=0;
        }
        printBoard(board);
        if (check_end(board)==1) {gamePlay(board, 0);}
        else if(j==0) gamePlay(board,2);
        else if((j<7 && board[0][j-1] > 1) || ((j>=7 && j<13) && board[1][j-8] >1)) move(board, j-1,2);
        else gamePlay(board, 1);
    }
}
