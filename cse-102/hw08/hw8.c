#include <stdio.h>
#include <string.h>
#define PERSON_NUMBER 24
#define MAX_VALUE_LENGTH 50

/*for part 2*/
#define MAX_COL_COUNT 50
#define MAX_ROW_COUNT 10
#define P1_STRING "***++++***++++***"
#define P2_STRING "+*+*+"
#define P3_STRING "+**+++****+++**+"

void clear_age_spaces(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]){
    int i,j, which_level;
    for (i=0; i<PERSON_NUMBER; i++){
        if (data[i][1][1] > '0' || data[i][1][1] < '9') which_level = 1;
        if (data[i][2][1] > '0' || data[i][2][1] < '9') which_level = 2;
        if (which_level == 1){
            if (data[i][1][0] == ' ') {
                data[i][1][0] = data[i][1][1];
                data[i][1][1] = data[i][1][2];
                data[i][1][2] = data[i][1][3];
                data[i][1][3] = '\0';
            }
        }
        else if (which_level == 2){
            if (data[i][2][0] == ' ') {
                data[i][2][0] = data[i][2][1];
                data[i][2][1] = data[i][2][2];
                data[i][2][2] = data[i][2][3];
                data[i][2][3] = '\0';
            }
        }
    }
}

void add_space_to_branches(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]){
    int i,j,k;
    char temp [MAX_VALUE_LENGTH+1] = " ";
    for (i=0; i<PERSON_NUMBER; i++){
        for (j=3; j<5; j++){
            if (data[i][j][0] != ' ') {
                strcat(temp, data[i][j]);
                strcpy(data[i][j], temp);
                temp[0] = ' ';
                for (k = 1; k < MAX_VALUE_LENGTH; k++){
                    temp[k] = '\0';
                }
            }
        }
    }
}

void read_data_from_file(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]) {
    FILE *file1 = fopen("input1.txt", "r");
    if (file1 == NULL) {
        printf("Failed to open file\n");
        return;
    }

    char temparray[MAX_VALUE_LENGTH];
    int i = 0, j = 0, m = 0;
    char tempchar;

    while ((tempchar = fgetc(file1)) != EOF) {
        if (tempchar == ',') {
            temparray[m] = '\000';
            strcpy(data[j][i], temparray);
            i++;
            m = 0;
            temparray[0] = '\000'; 
        } else if (tempchar == '\n') {
            temparray[m] = '\000';
            strcpy(data[j][i], temparray);
            j++;
            i = 0;
            m = 0;
            temparray[0] = '\000'; 
        } else {
            temparray[m] = tempchar;
            m++;
        }
    }

    if (m > 0) {
        temparray[m] = '\0';
        strcpy(data[j][i], temparray);
    }

    fclose(file1);
}

void print_array(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]){
    int i, j;
    printf("Name\t\t\t Surname\t\tAge\t\t\t Branch1\t\t Branch2\n");
    for (i = 0; i < PERSON_NUMBER; i++) {
        printf("%s", data[i][0]);
        if (strlen(data[i][0]) < 8 ) printf("\t\t\t");
        else if (strlen(data[i][0]) < 16 && strlen(data[i][0]) > 7) printf("\t\t");
        else if (strlen(data[i][0]) < 24 && strlen(data[i][0]) > 15) printf("\t");
        for (j = 1; j < 5 ; j++){            
            printf("%s", data[i][j]);
            if (strlen(data[i][j]) < 8 ) printf("\t\t\t");
            else if (strlen(data[i][j]) < 16 && strlen(data[i][j]) > 7) printf("\t\t");
            else if (strlen(data[i][j]) < 24 && strlen(data[i][j]) > 15) printf("\t");
        }
        printf("\n");
    }
}

void sort_by_age(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]) {
    int i, j = 2, k,l;
    for (i = 0; i < PERSON_NUMBER - 1; i++) {
        for (k = 0; k < PERSON_NUMBER - i - 1; k++) {
            if (strcmp(data[k][j], data[k+1][j]) > 0) {
                char temp[MAX_VALUE_LENGTH];
                for (l = 0; l < 5; l++) {
                    strcpy(temp, data[k][l]);
                    strcpy(data[k][l], data[k+1][l]);
                    strcpy(data[k+1][l], temp);
                }
            }
        }
    }
    print_array(data);
}

void sort_people_by_branch(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]) {
    int i, j = 3, k,l;
    for (i = 0; i < PERSON_NUMBER - 1; i++) {
        for (k = 0; k < PERSON_NUMBER - i - 1; k++) {
            if (strcmp(data[k][j], data[k+1][j]) > 0) {
                char temp[MAX_VALUE_LENGTH];
                for (l = 0; l < 5; l++) {
                    strcpy(temp, data[k][l]);
                    strcpy(data[k][l], data[k+1][l]);
                    strcpy(data[k+1][l], temp);
                }
            }
        }
    }
    print_array(data);
}

void filter_by_branch(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]) {
    int i, j,check=0;
    char branch[25];
    printf("Enter the branch: ");
    scanf("%s", branch);
    for (i = 0; i < PERSON_NUMBER; i++) {
        if (strstr(data[i][3], branch) != NULL || strstr(data[i][4], branch) != NULL){
            printf("%s", data[i][0]);
            check = 1;
            for (j = 1; j < 5 ; j++){
                printf("\t\t\t");
                printf("%s", data[i][j]);
            }
            printf("\n");
        }                
    }
    if (check == 0) printf("No such branch found\n");
}

void filter_by_two_branches(char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH]) {
    int i, j;
    for (i = 0; i < PERSON_NUMBER; i++) {
        if (strstr(data[i][3], "COMPUTER SCIENCE") != NULL || strstr(data[i][4], "COMPUTER SCIENCE") != NULL){
            if (strstr(data[i][3], "MATHEMATICS") == NULL && strstr(data[i][4], "MATHEMATICS") == NULL){
                printf("%s", data[i][0]);
                for (j = 1; j < 5 ; j++){
                    printf("\t\t\t");
                    printf("%s", data[i][j]);
                }
                printf("\n");
            }
        }                
    }
}

/*FOR PART 2#############################################################################################################*/

void read_from_file(char stars[MAX_ROW_COUNT][MAX_COL_COUNT]) {
    FILE *file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%s", stars[i]) != EOF && i < MAX_ROW_COUNT) {
        i++;
    }

    fclose(file);
}

int row_counter(char stars[MAX_ROW_COUNT][MAX_COL_COUNT]){
    int i,j,k;
    int row_count = 0;
    for (i=0; i<MAX_ROW_COUNT; i++){
        if (stars[i][0] == '\0'){
            break;
        }
        row_count++;
    }
    return row_count;
}

void search_p1(char stars[MAX_ROW_COUNT][MAX_COL_COUNT],int num_rows, int matches [][2], int *match_count){
    char p1[] = P1_STRING;
    int i,j,k;
    for (i=0; i<num_rows; i++){
        for (j=0; j<MAX_COL_COUNT; j++){
            if (stars[i][j] == p1[0]){
                for (k=1; k<strlen(p1); k++){
                    if (stars[i][j+k] != p1[k]){
                        break;
                    }
                }
                if (k == strlen(p1)){
                    matches[*match_count][0] = i;
                    matches[*match_count][1] = j;
                    (*match_count)++;
                }
            }
        }
    }
}

void search_p2(char stars[MAX_ROW_COUNT][MAX_COL_COUNT],int num_rows, int matches [][2], int *match_count){
    char p2[] = P2_STRING;
    int i,j,k;
    for (i=0; i<num_rows; i++){
        for (j=0; j<MAX_COL_COUNT; j++){
            if (stars[i][j] == p2[0]){
                for (k=1; k<strlen(p2); k++){
                    if (stars[i+k][j] != p2[k]){
                        break;
                    }
                }
                if (k == strlen(p2)){
                    matches[*match_count][0] = i;
                    matches[*match_count][1] = j;
                    (*match_count)++;
                }
            }
        }
    }
}

void search_p3(char stars[MAX_ROW_COUNT][MAX_COL_COUNT],int num_rows, int matches [][2], int *match_count){
    char p3[] = P3_STRING;
    int i,j,k;
    for (i=0; i<num_rows; i++){
        for (j=0; j<MAX_COL_COUNT; j++){
            if (stars[i][j] == p3[0]){
                for (k=1; k<strlen(p3); k++){
                    if (stars[i+k][j+k] != p3[k]){
                        break;
                    }
                }
                if (k == strlen(p3)){
                    matches[*match_count][0] = i;
                    matches[*match_count][1] = j;
                    (*match_count)++;
                }
            }
        }
    }
}


void part1(){
    int menuexit,menuinput;
        char data[PERSON_NUMBER][5][MAX_VALUE_LENGTH];
        read_data_from_file(data);
        clear_age_spaces(data);
        add_space_to_branches(data);
        while (!menuexit){
            printf("*****Menu**********************************\n1. Sort and display all individuals by age\n2. Sort and display individulas in the branch by age\n3. Show individuals with the branch \n4. Show computer scientists who are not mathematicians\n5. Exit\nChoice: ");
            scanf ("%d", &menuinput);
            if (menuinput== 5) menuexit=1;
            else if (menuinput== 1) sort_by_age(data);
            else if (menuinput== 2) sort_people_by_branch(data);
            else if (menuinput== 3) filter_by_branch(data);
            else if (menuinput== 4) filter_by_two_branches(data);
            else printf("Invalid input\n");
        }
}

void part2(){
    int i,j,k;
    int matchesp1[MAX_ROW_COUNT][2], matchesp2[MAX_ROW_COUNT][2], matchesp3[MAX_ROW_COUNT][2];
    int match_countp1 = 0, match_countp2 = 0, match_countp3 = 0;
    char stars[MAX_ROW_COUNT][MAX_COL_COUNT];
    read_from_file(stars);
    int num_rows =row_counter(stars);
    search_p1(stars,num_rows,matchesp1,&match_countp1);
    for (i=0; i<match_countp1; i++){
        printf("P1 @ (%d,%d)\n", matchesp1[i][0]+1, matchesp1[i][1]+1);
    }
    search_p2(stars,num_rows,matchesp2,&match_countp2);
    for (i=0; i<match_countp2; i++){
        printf("P2 @ (%d,%d)\n", matchesp2[i][0]+1, matchesp2[i][1]+1);
    }
    search_p3(stars,num_rows,matchesp3,&match_countp3);
    for (i=0; i<match_countp3; i++){
        printf("P3 @ (%d,%d)\n", matchesp3[i][0]+1, matchesp3[i][1]+1);
    }
}

int main(){
    int mainmenuexit=0,mainmenuinput;
    while (!mainmenuexit){
        printf("*****Main Menu**********************************\n1. Part 1\n2. Part 2\n3. Exit\nChoice: ");
        scanf ("%d", &mainmenuinput);
        if (mainmenuinput== 3) mainmenuexit=1;
        else if (mainmenuinput== 1) part1();
        else if (mainmenuinput== 2) part2();
        else printf("Invalid input\n");
    }
    return 0;
}