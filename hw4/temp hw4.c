#include <stdio.h>

char first_initial(FILE * filef, int id, char letter);
char last_initial(FILE * filef, int id, char letter);
int get_id_fi(FILE * filef, char first_initial);
int get_id_li();
int midterm_averagef(FILE* filef);
int final_averagef(FILE* filef);

int main() {
    int exitflag = 0, id, midterm1, midterm2, final, course_id, department;

    FILE * firstfile;
    FILE * secondfile;
    char menuinput;
    while (!exitflag) {
        printf("'p' : Print all the users pass or fail. \n'n': Print only the user with a specific first initial. \n'g': Calculate the GPA of a given student. \n'c': Print whether each user passed or failed the same class. \n't': Print the number of classes for the instructor. \n'd': Print the department of all persons according to the role. \n'l': Print the course_id of a given student. \n'e': Quit the program. \nPlease choose a program: ");
        scanf("%c", & menuinput);
        switch (menuinput) {
            /*CASE P ----------------------------- CASE P */
        case 'p':
        
    firstfile = fopen("first 1.txt", "r");
    double st_midterm;
    int final_average = final_averagef(firstfile);
    int midterm_average = midterm_averagef(firstfile);
    while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
        st_midterm = ((double) midterm1 / (double) midterm2) / 2;
        if ((st_midterm < 40 && st_midterm < midterm_average) && (final < 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: F - Fail \n", id, st_midterm, final);
        }
        if ((st_midterm < 40 && st_midterm < midterm_average) && (final > 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: D - 2.5 - Success \n", id, st_midterm, final);
        }
        if ((st_midterm < 40 && st_midterm < midterm_average) && (final > 40 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: C - 3 - Success \n", id, st_midterm, final);
        }
        if ((st_midterm > 40 && st_midterm > midterm_average) && (final > 40 && final < 90 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: B - 3.5 - Success \n", id, st_midterm, final);
        }
        if ((st_midterm > 40 && st_midterm > midterm_average) && (final > 40 && final > 90)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: A - 4 - Success \n", id, st_midterm, final);
        }
    }
    while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
        st_midterm = midterm1;
        if ((st_midterm < 40 && st_midterm < midterm_average) && (final < 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: F - Fail \n", id, st_midterm, final);
        }
        if ((st_midterm < 40 && st_midterm < midterm_average) && (final > 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: D - 2.5 - Success \n", id, st_midterm, final);
        }
        if ((st_midterm < 40 && st_midterm < midterm_average) && (final > 40 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: C - 3 - Success \n", id, st_midterm, final);
        }
        if ((st_midterm > 40 && st_midterm > midterm_average) && (final > 40 && final < 90 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: B - 3.5 - Success \n", id, st_midterm, final);
        }
        if ((st_midterm > 40 && st_midterm > midterm_average) && (final > 40 && final > 90)) {
            printf("Student id: %d, Him/Her Midterm Average: %f, Final: %d, Him/Her Grade is: A - 4 - Success \n", id, st_midterm, final);
        }
    }

            break;
            /*CASE N ----------------------------- CASE N*/
        case 'n':
            char first_letter;
            printf("Please write a letter: ");
            scanf(" %c", & first_letter);
            get_id_fi(secondfile, first_letter);
            break;
            /*CASE G ------------------------------ CASE G*/
        case 'g':
        }

    }
}

int get_id_fi(FILE *filef, char first_initial){
    char name,temp,temp1;
    int temp2,temp3;
    filef=fopen("second 1.txt", "r");
    
    while(fscanf(filef, "%d;%s;%s;%s;%d", &temp2, name, temp, temp1, &temp3)>=0){
        if(name == first_initial){
            printf("%d %s\n",temp2,name);
        }
    }
    fclose(filef);
    return 0;
}

int midterm_averagef(FILE* filef) {

    double midterm_average = 0, st_midterm;
    int exam_count = 0, midterm_sum = 0, final_sum = 0,id,midterm1,midterm2,final,course_id;
    filef = fopen("first 1.txt", "r");
    while (fscanf(filef, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
        midterm_sum = midterm_sum + st_midterm;
        exam_count++;
    }
    while (fscanf(filef, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
        midterm_sum = midterm_sum + midterm1;
        exam_count++;
    }
    midterm_average = ((double) midterm_sum + (double) exam_count) / 2;
    fclose(filef);
    return midterm_average;
}

int final_averagef(FILE* filef) {
    double final_average = 0;
    int exam_count = 0, final_sum = 0,id,midterm1,midterm2,final,course_id;
    filef = fopen("first 1.txt", "r");
    while (fscanf(filef, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
        final_sum = final_sum + final;
        exam_count++;
    }
    while (fscanf(filef, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
        final_sum = final_sum + final;
        exam_count++;
    }
    final_average = ((double) final_sum) / ((double) exam_count);
    fclose(filef);
    return final_average;
}
