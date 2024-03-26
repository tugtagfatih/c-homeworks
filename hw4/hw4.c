#include <stdio.h>

char first_initial(FILE * filef, int id, char letter);
char last_initial(FILE * filef, int id, char letter);
int get_id_fi();
int get_id_li();
int average_grade(int flag, int check_for_courseid, int courseid);
void print_grades(int id, int midterm1, int midterm2, int final);

int main() {
    int exitflag = 0, id, midterm1, midterm2, final, course_id, department;
    double midterm_average = 0, final_average = 0, st_midterm;
    int exam_count = 0, midterm_sum = 0, final_sum = 0;
    midterm1 = -1, midterm2 = -1, final = -1;

    FILE * firstfile;
    FILE * secondfile;
    char menuinput;
    int menu_printed = 0;
    while (!exitflag) {
        if (!menu_printed) {
            printf("\n -------------------------------------------------------------------------\n");
            printf("'p' : Print all the users pass or fail. \n'n': Print only the user with a specific first initial. \n'g': Calculate the GPA of a given student. \n'c': Print whether each user passed or failed the same class. \n't': Print the number of classes for the instructor. \n'd': Print the department of all persons according to the role. \n'l': Print the course_id of a given student. \n'e': Quit the program. \nPlease choose a program: ");
            menu_printed = 1;
        }
        scanf("%c", & menuinput);
        getchar();

        switch (menuinput) {
            /*CASE P ----------------------------- CASE P */
        case 'p':
            firstfile = fopen("first 1.txt", "r");

            while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
                print_grades(id, midterm1, midterm2, final);
            }
            while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
                print_grades(id, midterm1, -1, final);
            }
            fclose(firstfile);
            menu_printed = 0;
            break;
            /*CASE N ----------------------------- CASE N*/
        case 'n':
            menu_printed = 0;
            break;

        case 'g':
            int id_forgpa;
            midterm_average = average_grade(0, 0, 0);
            final_average = average_grade(1, 0, 0);
            printf("Please write an id number: ");
            scanf("%d", & id_forgpa);
            firstfile = fopen("first 1.txt", "r");

            while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
                if (id == id_forgpa) {
                    print_grades(id, midterm1, midterm2, final);
                }
            }
            while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
                if (id == id_forgpa) {
                    print_grades(id, midterm1, -1, final);
                }
            }
            fclose(firstfile);
            menu_printed = 0;

            break;

        case 'c':
            int course_id_check;
            printf("Please write a course id: ");
            scanf("%d", & course_id);
            printf("average final grade of the course %d is %d\n", course_id, average_grade(1, 1, course_id));
            printf("average midterm grade of the course %d is %d\n", course_id, average_grade(0, 1, course_id));
            menu_printed = 0;
            break;

        case 't':
            int instructor_id = 0, hash;
            printf("Please write instructor id: ");
            scanf("%d", & instructor_id);
            firstfile = fopen("first 1.txt", "r");
            while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {}
            while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {}
            while (fscanf(firstfile, "%d;%d;%d", & id, & hash, & department) == 3) {
                if (instructor_id == id) printf("Number of class for %d is %d", instructor_id, hash);
            }
            fclose(firstfile);
            menu_printed = 0;
            break;

        case 'd':
            char firstletter, tempchar1, tempchar2;
            int tempint;
            secondfile = fopen("second 1.txt", "r");
            printf("Please write a letter (s for student, i for instructor): ");
            scanf("%c", & firstletter);
            while (fscanf(secondfile, "%d;%c;%c;%c;%d", & id, & tempchar1, & tempchar2, & firstletter, & tempint) == 5) {
                printf("%d %s %s %c %d", id, tempchar1, tempchar2, firstletter, tempint);
            }

            fclose(secondfile);
            menu_printed = 0;
            break;
        }

    }
}

int average_grade(int flag, int check_for_courseid, int courseid) {
    FILE * filef;
    int exitflag = 0, id, midterm1, midterm2, final, course_id, department;
    double midterm_average = 0, final_average = 0, st_midterm;
    int exam_count = 0, midterm_sum = 0, final_sum = 0;
    midterm1 = -1, midterm2 = -1, final = -1;
    filef = fopen("first 1.txt", "r");
    if (filef == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    if (check_for_courseid == 1) {
        while (fscanf(filef, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
            if (courseid == course_id) {
                midterm_sum = (midterm_sum + st_midterm) / 2;
                final_sum = final_sum + final;
                exam_count++;
            }
        }
        while ((fscanf(filef, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) && (courseid == course_id)) {
            if (courseid == course_id) {
                midterm_sum = midterm_sum + midterm1;
                final_sum = final_sum + final;
                exam_count++;
            }

        }
    }
    if (check_for_courseid == 0) {
        while (fscanf(filef, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
            midterm_sum = (midterm_sum + st_midterm) / 2;
            final_sum = final_sum + final;
            exam_count++;
        }
        while (fscanf(filef, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
            midterm_sum = midterm_sum + midterm1;
            final_sum = final_sum + final;
            exam_count++;
        }
    }

    midterm_average = ((double) midterm_sum) / ((double) exam_count);
    final_average = ((double) final_sum) / ((double) exam_count);
    fclose(filef);
    if (flag == 1) return final_average;
    if (flag == 0) return midterm_average;
    else printf("Error");
}

void print_grades(int id, int midterm1, int midterm2, int final) {
    int midterm_average = average_grade(0, 0, 0);
    int final_average = average_grade(1, 0, 0);
    double st_midterm;
    if (midterm2 > -1) {
        st_midterm = ((double) midterm1 + (double) midterm2) / 2;
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
    } else {
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
}
