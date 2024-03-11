#include <stdio.h>
#define MAX_VALUE 50 /*The biggest number in all of the files is 49*/
#define EXPECTED_NUMBERS_OF_VALUE 200 /*There can be a maximum of 200 errors in a data file containing 50 entries, so I set this to 200, but if more data is to be entered, the number must be increased.*/

int main(){
    int menuinput, exitflag =0, x,y,c;
    FILE *datafile;
    char char1;
    while(!exitflag){
        printf ("-------------homework 2 menu---------------\n\n");
        printf ("1-Part 1\n2-Part 2\n3-Part 3\n4- Exit \nPlease select a program: ");
        scanf ("%d", &menuinput);

        if (menuinput==1){
            int maxX0=0, minX0=MAX_VALUE,maxY0=0,minY0=MAX_VALUE ,maxX1=0,minX1=MAX_VALUE,maxY1=0,minY1=MAX_VALUE;
            datafile =fopen("data.txt", "r");
            while (fscanf(datafile, "%d %d %d", &x, &y, &c) == 3) {
                if(c==0){
                    if(x>maxX0){maxX0=x;}
                    if(x<minX0){minX0=x;}
                    if(y>maxY0){maxY0=y;}
                    if(y<minY0){minY0=y;}
                }
                else if(c==1){
                    if(x>maxX1){maxX1=x;}
                    if(x<minX1){minX1=x;}
                    if(y>maxY1){maxY1=y;}
                    if(y<minY1){minY1=y;}
                }
            }
            printf("Minimum and Maximum X and Y values: \nClass 0: X in [%d %d], Y in [%d %d] \nClass 1:X in [%d %d], Y in [%d %d]\n", minX0, maxX0, minY0, maxY0, minX1, maxX1, minY1,maxY1);
            fclose(datafile);
        }
        else if (menuinput==2){
            int count_for_percent, state, dx, dy, bestx, besty,R1,R2,R3,R4,bestR1, bestR2, bestR3, bestR4, error_count,line_count, best_error=EXPECTED_NUMBERS_OF_VALUE;
            
            /*calculating number of lines*/
            datafile =fopen("data.txt", "r");
            while (fscanf(datafile, "%*[^\n]%*c") != EOF) {
                line_count++;
            }
            fclose(datafile);

            for (int i =0;i<= MAX_VALUE;i++){ /*this loop for all of the dx values*/
                dx = i;
                for( int j =0; j<= MAX_VALUE ; j++){ /*this loop for all of the dy values*/
                    dy=j;
                    for(state=0; state <15; state++){ /*this loop for all combinations of spaces*/
                        error_count=0;
                        if(state ==0)R1=0, R2=0, R3=0, R4=0;
                        else if(state ==1)R1=0, R2=0, R3=0, R4=1;
                        else if(state ==2)R1=0, R2=0, R3=1, R4=0;
                        else if(state ==3)R1=0, R2=0, R3=1, R4=1;
                        else if(state ==4)R1=0, R2=1, R3=0, R4=0;
                        else if(state ==5)R1=0, R2=1, R3=0, R4=1;
                        else if(state ==6)R1=0, R2=1, R3=1, R4=0;
                        else if(state ==7)R1=0, R2=1, R3=1, R4=1;
                        else if(state ==8)R1=1, R2=0, R3=0, R4=0;
                        else if(state ==9)R1=1, R2=0, R3=0, R4=1;
                        else if(state ==10)R1=1, R2=0, R3=1, R4=0;
                        else if(state ==11)R1=1, R2=0, R3=1, R4=1;
                        else if(state ==12)R1=1, R2=1, R3=0, R4=0;
                        else if(state ==13)R1=1, R2=1, R3=0, R4=1;
                        else if(state ==14)R1=1, R2=1, R3=1, R4=0;
                        else if(state ==15)R1=1, R2=1, R3=1, R4=1;
                        datafile =fopen("data.txt", "r");
                        while (fscanf(datafile, "%d %d %d", &x, &y, &c) == 3){
                            if(dx<=x && dy>y && c == 0 ) if (state > 7) {error_count++;}
                            if(dx<=x && dy>y && c == 1 ) if (state <=7) {error_count++;}
                            if(dx>x && dy>y && c == 0 ) if (state > 4 || (state < 7 && state >=11)) {error_count++;}
                            if(dx>x && dy>y && c == 1 ) if ((state <=4 && state >=7) || state < 11) {error_count++;}
                            if(dx<=x && dy<=y && c == 0 ) if(state !=0 || state !=1 || state != 4 || state != 5 || state != 8 || state != 9 || state !=12 || state != 13) {error_count++;}
                            if(dx<=x && dy<=y && c == 1 ) if(state ==0 || state ==1 || state == 4 || state == 5 || state == 8 || state == 9 || state ==12 || state == 13) {error_count++;}
                            if(dx>x && dy<=y && c == 0 ) if(state % 2 == 1 || state == 0) {error_count++;}
                            if(dx>x && dy<=y && c == 1 ) if(state % 2 == 0 || state == 0) {error_count++;}
                        }
                    }
                    if (error_count < best_error){                            
                        best_error = error_count;
                        bestR1= R1;
                        bestR2= R2;
                        bestR3= R3;
                        bestR4= R4;
                    }
                    fclose(datafile);
                }                    
            }
            int error_percent=((best_error*100)/line_count);
            printf("Best success rate is: %d%% and best classes is: R1=%d R2=%d R3=%d R4=%d \n", 100-error_percent, bestR1, bestR2, bestR3, bestR4);
        }
        else if (menuinput==3){
        }
        else if (menuinput==4){exitflag=1;}
        else{printf("Incorrect input. Please try again \n");}
    }
}
