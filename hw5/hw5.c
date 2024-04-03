#include <stdio.h>

#define MAX_TEXT_SIZE 500
#define NUMBER_OF_NEWS 4

int newslist[NUMBER_OF_NEWS];

void fill_newslists() {
    int i = 0;
    FILE * readed_ids;
    readed_ids = fopen("readed_news_id.txt", "r");
    while (fscanf(readed_ids, "%d", & newslist[i]) != EOF) {
        i++;
    }
}

void print_first_line(FILE * file) {
    char line[MAX_TEXT_SIZE];
    if (fgets(line, MAX_TEXT_SIZE, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}

void print_all_page(FILE * file) {
    char line[MAX_TEXT_SIZE];
    while (fgets(line, MAX_TEXT_SIZE, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
    printf("\n");
}

int check_readed(int news_id) {
    FILE * readed_ids;
    readed_ids = fopen("readed_news_id.txt", "r");
    int i, newslist[NUMBER_OF_NEWS], flag = 0;
    for (i = 0; i < NUMBER_OF_NEWS; i++) {
        while (fscanf(readed_ids, "%d", & newslist[i]) != EOF) {
            if (newslist[i] == news_id) flag = 1;
        }
    }
    return flag;
}

void add_readed_list(int news_id) {
    FILE *readed_ids;
    int array_size, i=0, exit=0;
    readed_ids = fopen("readed_news_id.txt", "a");
    i=0;
    for (i; i<NUMBER_OF_NEWS || !exit; i++){
        if (newslist[i]==news_id) exit=1;
        if (newslist[i] == 0) break;
    }
    if (exit==0){        
        fprintf(readed_ids, "%d\n", news_id);
    }
    fclose(readed_ids);
}

void menu_a() {
    FILE * newsfile;
    int choice_for_read, if_readed;
    char yes_or_no;
    printf("Which news do you want to read?: ");
    scanf("%d", & choice_for_read);
    getchar();
    switch (choice_for_read) {
    case 1:
        if_readed = check_readed(1);
        if (if_readed) {
            printf("This new is readed. Do you want to read again? Yes(1) / No(0): ");
            scanf("%d", & yes_or_no);
            if (yes_or_no == 1) if_readed = 0;
        }
        if (!if_readed) {
            newsfile = fopen("news/1.txt", "r");
            add_readed_list(1);
            print_all_page(newsfile);
        }
        break;
    case 2:
        if_readed = check_readed(2);
        if (if_readed) {
            printf("This new is readed. Do you want to read again? Yes(1) / No(0): ");
            scanf("%d", & yes_or_no);
            if (yes_or_no == 1) if_readed = 0;
        }
        if (!if_readed) {
            newsfile = fopen("news/2.txt", "r");
            add_readed_list(2);
            print_all_page(newsfile);
        }
        break;
    case 3:
        if_readed = check_readed(3);
        if (if_readed) {
            printf("This new is readed. Do you want to read again? Yes(1) / No(0): ");
            scanf("%d", & yes_or_no);
            if (yes_or_no == 1) if_readed = 0;
        }
        if (!if_readed) {
            newsfile = fopen("news/3.txt", "r");
            add_readed_list(3);
            print_all_page(newsfile);
        }
        break;
    case 4:
        if_readed = check_readed(4);
        if (if_readed) {
            printf("This new is readed. Do you want to read again? Yes(1) / No(0): ");
            scanf("%d", & yes_or_no);
            if (yes_or_no == 1) if_readed = 0;
        }
        if (!if_readed) {
            newsfile = fopen("news/4.txt", "r");
            add_readed_list(4);
            print_all_page(newsfile);
        }
        break;
    default:
        printf("Invalid option\n");
        break;
    }
}

void menu() {
    fill_newslists();
    int pp;
    for (pp = 0; pp < NUMBER_OF_NEWS; pp++) {
        printf("%d", newslist[pp]);
    }

    int exitflag = 0, print_menu_option = 1;
    int read_checker[NUMBER_OF_NEWS];
    char choice, menuinput, line[MAX_TEXT_SIZE];
    while (!exitflag || print_menu_option) {
        print_menu_option = 0;
        FILE * newsfile;
        printf("***********************Daily Press***********************\n");
        printf("1: ");
        newsfile = fopen("news/1.txt", "r");
        print_first_line(newsfile);
        printf("2: ");
        newsfile = fopen("news/2.txt", "r");
        print_first_line(newsfile);
        printf("3: ");
        newsfile = fopen("news/3.txt", "r");
        print_first_line(newsfile);
        printf("4: ");
        newsfile = fopen("news/4.txt", "r");
        print_first_line(newsfile);

        printf("What do you want to do? \na.Read a new \nb.List the readed news \nc.Get decrypted information from the news \nPlease select a option: ");
        scanf(" %c", &menuinput);
        getchar();
        if (menuinput == 'a') {
            menu_a();
        } else if (menuinput == 'b') {
            int i, check;
            for (i = 0; i <= NUMBER_OF_NEWS; i++) {
                check = check_readed(i);
                if (check) printf("%d. new is readed \n", i);
            }
        } else if (menuinput == 'c') {

        } else {

        }
        printf("Do you want to continue? Yes(y)/No(n): ");
        scanf("%c", & choice);
        if (choice == 'N' || choice == 'n') exitflag = 1;
        else if (choice == 'Y' || choice == 'y') {
            exitflag = 0;
            print_menu_option = 1;
        } else printf("Wrong imput program will be terminated Good Bye!");
    }
}

int main() {
    menu();
}