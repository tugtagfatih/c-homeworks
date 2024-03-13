#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initalize_game();
void print_board();
void move_player();
char lab[255], movement;
int i=0, ects=0, player_point , endgameflag=0, movement_count=0;

int main(){
    srand(time(NULL));
    initalize_game();
    
    while (!endgameflag){
        printf("Use W (Up), A (Left), S (Down), D (Right) to move\n\n");
        print_board();
        printf("Total ECTS: %d\n", ects);      
        move_player();
    }
}


void print_board(){
    int loop_v=0, loop_h=0;
    lab[player_point] == '.';
    int loopv=0, looph=0, i=0, j=0, two_counter=0, two_max=24, one_counter=0, one_max=7;
    for (loopv; loopv<=15; loopv++){
        for (looph; looph <=15; looph++){
            i++;
            j++;
            if ((loopv>=4 && loopv<=12 && i >=4 && j==4) || (loopv>=4 && loopv<=12 && i >=4 && j==12) || ((loopv==4 || loopv==12) && (i ==4 || (j<=12 && j >=4)))){ /*outer walls*/
                lab[i] = '#';
            }
            if ((loopv>=6 && loopv<=10 && i >=6 && j==6) || (loopv>=6 && loopv<=10 && i >=6 && j==10) || ((loopv==6 || loopv==10) && (i ==6 || (j<=10 && j >=6)))){ /*outer walls*/
                lab[i] = '#';
            }
        }
        looph =0, j=0;
    }
    i=0;
    lab[player_point]= 'P';
    lab[255]='X';
    for (loop_v; loop_v<=15; loop_v++){
        for(loop_h; loop_h<=15;loop_h++){
            printf("%c ", lab[i]);
            i++;
        }
        printf("\n");
        loop_h=0;
    }
}

void move_player(){
    printf("Enter your move: ");
    scanf("%c", &movement);
    if (movement == 'd' && player_point % 16 != 15){
        if( (ects >=24 || (player_point!= 121 && player_point!= 137 && player_point!= 153 )) && (ects >=55 || (player_point!= 91 && player_point!= 107 && player_point!= 123 &&player_point!= 139 && player_point!= 155 && player_point!= 171 && player_point!= 187))){
            if (lab[player_point+1] == '1' || lab[player_point+1] == '2') ects = ects +8;
            lab[player_point] = '.';
            player_point++;
            movement_count++;
        }
        else printf("Insufficient ects, please try again. \n");
    }
    else if (movement =='a' && player_point % 16 !=0 ){
        if( ( ects>=24 || (player_point != 119 && player_point != 135 && player_point != 151)) && (ects >=55 || (player_point != 85 && player_point != 101 && player_point != 117 && player_point != 133 && player_point != 149 && player_point != 165 && player_point != 181 ))){
            if (lab[player_point-1] == '1' || lab[player_point-1] == '2') ects = ects +8;
            lab[player_point] = '.';
            player_point--;
            movement_count++;
        }
        else printf("Insufficient ects, please try again. \n");
    }
    else if (movement == 'w' && player_point > 15){
        if ( (ects>=24 || (player_point!= 119 && player_point!= 120 && player_point!= 121 )) && (ects >= 55 || (player_point != 85 && player_point != 86 && player_point != 87 && player_point != 88 && player_point != 89 && player_point != 90 && player_point != 91 ))){
            if (lab[player_point-16] == '1' || lab[player_point-16] == '2') ects = ects +8;
            lab[player_point] = '.';
            player_point= player_point-16;
            movement_count++;
        }
        else printf("Insufficient ects, please try again. \n");
    }
    else if (movement == 's' && player_point < 240){
        if ( (ects>=24 || (player_point!= 151 && player_point!= 152 && player_point!= 153 )) && (ects >= 55 || (player_point != 181 && player_point != 182 && player_point != 183 && player_point != 184 && player_point != 185 && player_point != 186 && player_point != 187 ))){
            if (lab[player_point +16] == '1' || lab[player_point+16] == '2') ects = ects +8;
            lab[player_point] = '.';
            player_point = player_point + 16;
            movement_count++;
        }
        else printf("Insufficient ects, please try again. \n");
    }
    else printf("Invalid Input, please try again \n");
    if (player_point == 255){
        endgameflag=1;
        printf("Congratulations \n Movement Number: %d \n", movement_count);
    }
}

void initalize_game(){
    for(i; i<255;i++) lab[i]= '.';
    lab[255]='X';
    player_point=136;
    int loopv=0, looph=0, i=0, j=0, two_counter=0, two_max=24, one_counter=0, one_max=7;
    for (loopv; loopv<=15; loopv++){
        for (looph; looph <=15; looph++){
            i++;
            j++;
            if ((loopv>=4 && loopv<=12 && i >=4 && j==4) || (loopv>=4 && loopv<=12 && i >=4 && j==12) || ((loopv==4 || loopv==12) && (i ==4 || (j<=12 && j >=4)))){ /*outer walls*/
                lab[i] = '#';
            }
            if ((loopv>=6 && loopv<=10 && i >=6 && j==6) || (loopv>=6 && loopv<=10 && i >=6 && j==10) || ((loopv==6 || loopv==10) && (i ==6 || (j<=10 && j >=6)))){ /*inner walls*/
                lab[i] = '#';
            }
            if ((loopv>=5 && loopv<=11 && i >=5 && j==5) || (loopv>=5 && loopv<=11 && i >=5 && j==11) || ((loopv==5 || loopv==11) && (i ==5 || (j<=11 && j >=5)))){
                int two_creator = rand() %6; /*There are 24 different squares where the numbers 2 can appear, and since there should be 4, I give the probability 1/6.*/
                two_max--;
                if (two_counter<=2 && (two_creator == 5 || two_max <=3)){
                    lab[i] = '2';
                    two_counter++;
                }
            }
            if ((loopv>=7 && loopv<=9 && i >=7 && j==7) || (loopv>=7 && loopv<=9 && i >=7 && j==9) || ((loopv==7 || loopv==9) && (i ==7|| (j<=9 && j >=7)))){
                int one_creator = rand() %2;
                one_max--;
                if (one_counter <4 && (one_creator ==1 || one_max <=3)){
                    lab[i] = '1';
                    one_counter++;
                }
            }           
        }
        looph =0, j=0;
    }
}