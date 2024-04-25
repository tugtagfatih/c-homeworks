#include <stdio.h>
char first_initial(FILE * id_fp, int id);
char last_initial(FILE * id_fp, int id);
int get_id_fi(FILE * id_fp, char first_initial);
int get_id_li(FILE * id_fp, char first_initial);
int all_average(int flag, int check_for_courseid, int courseid);
void print_grades(int id, int midterm1, int midterm2, int final);
int average_grade (FILE * into_fp, int id);

char first_initial(FILE * id_fp, int id){
    char tempchar;
    int readed_id, nextcharflag=0;
    id_fp = fopen("second 1.txt", "r");
    while (fscanf(id_fp, "%d", & readed_id) == 1) {
        while (fscanf(id_fp, "%c", & tempchar) != EOF && tempchar != '\n') {
            if (id == readed_id){
                if (nextcharflag ==1) return tempchar;
                if(tempchar == ';') nextcharflag++;
            }
        }
    }
    fclose(id_fp);
}

char last_initial(FILE * id_fp, int id){
    char tempchar, tempchar2;
    int readed_id, nextcharflag=0, count=0;
    id_fp = fopen ("second 1.txt", "r");
    while (fscanf(id_fp, "%d", & readed_id) == 1) {
        while (fscanf(id_fp, "%c", &tempchar) != EOF && tempchar != '\n') {
            if (nextcharflag==1) return tempchar;
            if (count==1 && tempchar == ';') nextcharflag++;
            if(count==0 && tempchar== ';') count++;
        }
    }
    fclose(id_fp);
}

int get_id_fi (FILE * id_fp, char first_initial){
    int id, nextcharflag=0, count=0;
    char tempchar;
    FILE *id_fi;
    id_fi = fopen("get_id_fi_file.txt", "w");
    id_fp = fopen("second 1.txt", "r");
    while (fscanf(id_fp, "%d", &id) == 1) {
        count = 0;
        while (fscanf(id_fp, "%c", &tempchar) != EOF && tempchar != '\n') {
            if (count == 1 && tempchar==first_initial) fprintf(id_fi, "%d\n", id); /*return id;*/
            count ++;
        }
    }
    fclose(id_fp);
    fclose(id_fi);
}

int get_id_li (FILE * id_fp, char first_initial){
    int id, count=0, flag=0, nextchar;
    char tempchar, tempchar2;
    FILE *id_li;
    id_li = fopen("get_id_li_file.txt", "w");
    id_fp = fopen("second 1.txt", "r");
    while (fscanf(id_fp, "%d", &id) == 1) {
        count=0;
        flag = 0;
        nextchar = 0;
        while (fscanf(id_fp, "%c", &tempchar) != EOF && tempchar != '\n') {
            if (tempchar == ';') {count++; nextchar++;}
            if (count==2 && nextchar == 1 && tempchar == first_initial) fprintf(id_li, "%d\n", id); /*return id*/
            if (tempchar != ';') nextchar = 0;

        }
    }
    fclose(id_li);
    fclose(id_fp);
}

int average_grade (FILE * into_fp, int id){    
    double st_midterm, lastnote;
    int id_scanned, midterm1, midterm2, final, course_id;
    int midterm_average = all_average(0, 0, 0);/*im calculating average of all of the students*/
    int final_average = all_average(1, 0, 0);
    into_fp = fopen("first 1.txt", "r");
    while (fscanf(into_fp, "%d;%d;%d;%d;%d", & id_scanned, & midterm1, & midterm2, & final, & course_id) == 5) {
        if (id_scanned == id) lastnote=(((midterm1+midterm2)/2)+final)/2; 
    }
    while (fscanf(into_fp, "%d;%d;%d;%d", & id_scanned, & midterm1, & final, & course_id) == 4) {
        if (id_scanned == id) lastnote= (midterm1 + final)/2;
    }
    return lastnote;
}

int all_average(int flag, int check_for_courseid, int courseid) {
    FILE * id_fp;
    int exitflag = 0, id, midterm1, midterm2, final, course_id, department;
    double midterm_average = 0, final_average = 0, st_midterm;
    int exam_count = 0, midterm_sum = 0, final_sum = 0;
    midterm1 = -1, midterm2 = -1, final = -1;
    id_fp = fopen("first 1.txt", "r");
    if (check_for_courseid == 1) {
        while (fscanf(id_fp, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
            st_midterm = ((double) midterm1 / (double) midterm2) / 2;
            if (courseid == course_id) {
                midterm_sum = (midterm_sum + st_midterm) / 2;
                final_sum = final_sum + final;
                exam_count++;
            }
        }
        while ((fscanf(id_fp, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) && (courseid == course_id)) {
            if (courseid == course_id) {
                midterm_sum = midterm_sum + midterm1;
                final_sum = final_sum + final;
                exam_count++;
            }

        }
    }
    if (check_for_courseid == 0) {
        while (fscanf(id_fp, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
            st_midterm = ((double) midterm1 / (double) midterm2) / 2;
            midterm_sum = (midterm_sum + st_midterm) / 2;
            final_sum = final_sum + final;
            exam_count++;
        }
        while (fscanf(id_fp, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
            st_midterm = midterm1;
            midterm_sum = midterm_sum + midterm1;
            final_sum = final_sum + final;
            exam_count++;
        }
    }

    midterm_average = ((double) midterm_sum) / ((double) exam_count);
    final_average = ((double) final_sum) / ((double) exam_count);
    fclose(id_fp);
    if (flag == 1) return final_average;
    if (flag == 0) return midterm_average;
    else printf("Error");
}

void print_grades(int id, int midterm1, int midterm2, int final) {
    int midterm_average = all_average(0, 0, 0);
    int final_average = all_average(1, 0, 0);
    double st_midterm;
    if (midterm2 > -1) {
        st_midterm = ((double) midterm1 + (double) midterm2) / 2;
        if ((st_midterm < 40 && st_midterm < midterm_average) || (final < 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: F - Fail \n", id, st_midterm, final);
        }
        else if ((st_midterm < 40 && st_midterm < midterm_average) || (final > 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: D - 2.5 - Success \n", id, st_midterm, final);
        }
        else if ((st_midterm < 40 && st_midterm < midterm_average) || (final > 40 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: C - 3 - Success \n", id, st_midterm, final);
        }
        else if ((st_midterm > 40 && st_midterm > midterm_average) || (final > 40 && final < 90 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: B - 3.5 - Success \n", id, st_midterm, final);
        }
        else if ((st_midterm > 40 && st_midterm > midterm_average) || (final > 40 && final > 90)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: A - 4 - Success \n", id, st_midterm, final);
        }
    } else {
        st_midterm = midterm1;
        if ((st_midterm < 40 && st_midterm < midterm_average) || (final < 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: F - Fail \n", id, st_midterm, final);
        }
        else if ((st_midterm < 40 && st_midterm < midterm_average) || (final > 40 && final < final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: D - 2.5 - Success \n", id, st_midterm, final);
        }
        else if ((st_midterm < 40 && st_midterm < midterm_average) || (final > 40 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: C - 3 - Success \n", id, st_midterm, final);
        }
        else if ((st_midterm > 40 && st_midterm > midterm_average) || (final > 40 && final < 90 && final > final_average)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: B - 3.5 - Success \n", id, st_midterm, final);
        }
        else if ((st_midterm > 40 && st_midterm > midterm_average) || (final > 40 && final > 90)) {
            printf("Student id: %d, Him/Her Midterm Average: %.2f, Final: %d, Him/Her Grade is: A - 4 - Success \n", id, st_midterm, final);
        }
    }
}

int main() {
    int exitflag = 0, midterm1 = -1, midterm2 = -1, final = -1, course_id, department, menu_printed = 0, exam_count = 0, midterm_sum = 0, final_sum = 0, instructor_id = 0, hash, course_id_check, count, nextchar_flag, print_dep, not_print, check_for_l;
    long long id, id_forgpa, case_l_id;
    double midterm_average = 0, final_average = 0, st_midterm;
    char menuinput, firstletter, tempchar;
    FILE * firstfile;
    FILE * secondfile;
    /*for test the functions*/
    printf("averagegrade: %d \n", average_grade(firstfile, 220015009));
    printf("first initial t  = %c \n", (first_initial(secondfile, 220015011)));
    printf("last initial  m = %c \n", (last_initial(secondfile, 220015011)));
    get_id_fi(secondfile, 'd');
    get_id_li(secondfile, 'l' );

    while (!exitflag) {
        if (!menu_printed) {
            printf("\n -------------------------------------------------------------------------\n");
            printf("'p' : Print all the users pass or fail. \n'n': Print only the user with a specific first initial. \n'g': Calculate the GPA of a given student. \n'c': Print whether each user passed or failed the same class. \n't': Print the number of classes for the instructor. \n'd': Print the department of all persons according to the role. \n'l': Print the course_id of a given student. \n'e': Quit the program. \nPlease choose a program: ");
            menu_printed = 1;
        }
        scanf("%c", & menuinput);
        getchar();

        switch (menuinput) {
        case 'e':
            exitflag = 1;
            break;

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

        case 'n':
            printf("Please enter a letter: ");
            int id_for_case_n, nextcharflag=0, count=0;
            char tempchar, given_letter;
            scanf ("%c", &given_letter);
            getchar();
            firstfile = fopen("first 1.txt", "r");
            secondfile = fopen("second 1.txt", "r");
            while (fscanf(secondfile, "%d", &id_for_case_n) == 1) {
                count = 0;
                while (fscanf(secondfile, "%c", &tempchar) != EOF && tempchar != '\n') {
                    if (count == 1 && tempchar==given_letter){
                        firstfile = fopen("first 1.txt", "r");
                        while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
                            if(id_for_case_n == id) {print_grades(id, midterm1, midterm2, final); } 
                        }
                        while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
                            if(id_for_case_n == id) { print_grades(id, midterm1, -1, final);}
                        }                        
                        fclose(firstfile);                        
                    }
                    count++;
                }
            }
            fclose(secondfile);
            
            menu_printed = 0;
            break;

        case 'g':
            printf("Please write an id number: ");
            scanf("%d", & id_forgpa);
            firstfile = fopen("first 1.txt", "r");
            while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
                if (id == id_forgpa) {
                    printf ( "%d 's GPA is %d", id,average_grade(firstfile, id));
                }
            }
            while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
                if (id == id_forgpa) {
                    printf ( "%d 's GPA is %d", id,average_grade(firstfile, id));
                }
            }
            fclose(firstfile);
            menu_printed = 0;
            break;

        case 'c':
            printf("Please write a course id: ");
            scanf("%d", & course_id);
            printf("average final grade of the course %d is %d\n", course_id, all_average(1, 1, course_id));
            printf("average midterm grade of the course %d is %d\n", course_id, all_average(0, 1, course_id));
            menu_printed = 0;
            break;
        case 't':
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
            secondfile = fopen("second 1.txt", "r");
            printf("Please write a letter (s for student, i for instructor): ");
            scanf(" %c", & firstletter);
            getchar();
            while (fscanf(secondfile, "%d", & id) == 1) {
                count = 0;
                nextchar_flag = 0;
                print_dep = 0;
                not_print = 1;
                while (fscanf(secondfile, "%c", & tempchar) != EOF && tempchar != '\n') {
                    if (nextchar_flag == 1 && tempchar == firstletter) printf("\nid: %d department: ", id);
                    else if (nextchar_flag == 1 && tempchar != firstletter) not_print = 0;
                    if (print_dep == 1 && not_print) printf("%c", tempchar);
                    if (nextchar_flag == 1) nextchar_flag = 0;
                    if (tempchar == ';') count++;
                    if (tempchar == ';' && count == 3) nextchar_flag++;
                    if (tempchar == ';' && count == 4) print_dep++;
                }
            }
            fclose(secondfile);
            menu_printed = 0;
            break;
        case 'l':
            printf("Please enter a id: ");
            scanf("%d", & case_l_id);
            check_for_l = 0;
            getchar();
            firstfile = fopen("first 1.txt", "r");
            while (fscanf(firstfile, "%d;%d;%d;%d;%d", & id, & midterm1, & midterm2, & final, & course_id) == 5) {
                if (case_l_id == id) {
                    printf("course id is: ", course_id);
                    check_for_l = 1;
                }
            }
            while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & final, & course_id) == 4) {
                if (case_l_id == id) {
                    printf("course id is: %d", course_id);
                    check_for_l = 1;
                }
            }
            while (fscanf(firstfile, "%d;%d;%d;%d", & id, & midterm1, & course_id) == 3) {
                if (case_l_id == id) {
                    printf("Please give a student id");
                }
            }
            if (check_for_l == 0) printf("Given ID is not correct.");
            fclose(firstfile);
            menu_printed = 0;
            break;
        }
    }
}