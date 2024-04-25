#include <stdio.h>
#define MAX_REPEAT 10
#define MAX_ARRAY_SIZE 150
#define MAX_MODES 20

void print_histogram(int number_array[], int a, int b){
    int max_y = (b - a);
    int array_size = find_size_of_array(number_array);
    int i = 0, j=0;
    int temp_array[array_size],k=0;
    for (i = 0; i < array_size; i++) {
        temp_array[i] = 0;
    }
    for (i = 0; i < array_size &&!k; i++) {
        if(number_array[i] >= a && number_array[i] <= b){
            temp_array[j] = number_array[i];
            j++;
        }
        if(number_array[i] == -1){
            k=1;
        }
    }
    temp_array[j] = -1;
    for (i = 0; i < j; i++) {
        printf("%d ", temp_array[i]);
    }
    for (i = 0; i < array_size; i++) {
        number_array[i] = 0;
    }
    k=1;
    for (i = 0; i < array_size &&k; i++) {
        number_array[i] = temp_array[i];
        if(temp_array[i] == -1){
            k=0;
        }
    }
    array_size = find_size_of_array(number_array);
    printf("Array size: %d\n", array_size);
    int stars_array[array_size];
    for (i = 0; i < array_size; i++) {
        stars_array[i] = 0;
    }

    for (i = 0; i <= (b-a); i++) {
        for(j = 0; j < array_size;j++){
            if(number_array[j] == a+i){
                stars_array[i]++;
            }
        }
    }
    for (i = 0; i <= (b-a); i++) {
        printf("%d ", stars_array[i]);
    }
    int biggest_number = 0;
    for (i = 0; i <= (b-a); i++) {
        if (stars_array[i] > biggest_number) {
            biggest_number = stars_array[i];
        }
    }
    printf("biggest number: %d\n", biggest_number);
    for (i = biggest_number; i >0;i--){
        for(j=0; j<=(b-a) ; j++){
            if(stars_array[j]>=i) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
}

int find_size_of_array(int number_array[]) {
    int i = 0;
    while (number_array[i] != -1) {
        i++;
    }
    return i;
}

void calculate_average(int number_array[]){
    int array_size = find_size_of_array(number_array);
    int i, sum = 0;
    for(i=0; i<array_size; i++){
        sum += number_array[i];
    }
    printf("Average: %.2f\n",(float)sum/array_size);
}

void calculate_mode(int number_array[]){
    int array_size = find_size_of_array(number_array);
    int i, j, max_count = 0, modecount = 0;
    int modes[MAX_MODES];
    for (i = 0; i < MAX_MODES; i++) {
        modes[i] = 0;
    }
    for(i=0; i<array_size; i++){
        int count = 0;
        for(j=0; j<array_size; j++){
            if(number_array[i] == number_array[j]){
                count++;
            }
        }
        if(count > max_count){
            max_count = count;
            for (j = 0; j < MAX_MODES; j++) {
                modes[j] = 0;
            }
            modes[0] = number_array[i];
            modecount = 1;
        } else if(count == max_count && modes[0] != number_array[i]){
            modes[modecount] = number_array[i];
            modecount++;
        }
    }
    printf("Modes: ");
    for (i = 0; i < modecount; i++) {
        if (modes[i] != 0) printf("%d ", modes[i]);
    }
    printf("\n");
}

void calculate_median(int number_array[]){
    int array_size = find_size_of_array(number_array);
    int i, j, temp;
    for(i=0; i<array_size; i++){
        for(j=0; j<array_size; j++){
            if(number_array[i] < number_array[j]){
                temp = number_array[i];
                number_array[i] = number_array[j];
                number_array[j] = temp;
            }
        }
    }
    if(array_size % 2 == 0){
        printf("Median: %.2f\n", (float)(number_array[array_size/2] + number_array[array_size/2 - 1])/2);
    }
    else{
        printf("Median: %d\n", number_array[array_size/2]);
    }
}

int main() {
    int number_array[] = {88,69,192,154,112,52,81,125,131,146,76,130,100,124,123,110,181,103,93,66,174,130,89,62,74,61,122,70,183,169,186,68,189,176,172,98,178,52,172,106,149,198,187,199,121,107,106,99,158,147,115,132,74,152,144,98,164,63,116,144,182,100,163,170,75,134,66,52,135,188,108,81,185,92,77,103,148,134,152,105,78,64,187,103,166,128,149,127,141,65,71,121,113,182,90,138,113,104,138,198,91,196,78,73,86,104,126,184,188,75,88,63,89,73,116,53,149,63,130,88,78,149,159,141,130,197,76,192,101,164,189,142,157,65,164,193,119,87,174,104,113,60,115,150,81,182,153,180,195,83,67,70,180,176,159,108,173,183,99,71,146,85,161,100,98,124,93,167,162,64,68,74,74,134,172,105,113,125,83,105,156,100,123,133,74,79,191,195,61,89,65,157,125,176,56,173,100,97,138,59,110,154,83,134,85,52,188,148,127,70,50,80,118,123,164,140,152,152,134,163,192,149,117,114,123,122,84,171,169,170,180,78,124,60,161,159,62,146,105,138,164,105,166,81,179,129,172,128,81,103,89,70,50,156,132,123,77,166,91,195,136,70,70,57,80,179,166,90,124,70,178,87,124,142,117,102,70,86,178,99,139,66,117,137,171,199,57,198,163,98,190,98,118,58,103,146,187,68,185,-1};
    int a = 0, b = 0, i, j = 0, max_y, difference, flag = 0;
    while (a < 50 || b > 200) {
        printf("Enter A and B values (50 <= A <= B <= 200): ");
        scanf("%d %d", &a, &b);
        if (a < 50 || b > 200)
            printf("A must be at least 50, and B must not exceed 200. Please try again.\n");
    }
    print_histogram(number_array, a, b);
    printf ("1- Updating Histogram By Adding New Numbers \n0- Doing Mathematical Operations \nPlease enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {        
        int i, array_last= find_size_of_array(number_array);
        number_array[array_last] = 0;
        for(i=0 ; i<5; i++){
            printf("Enter a number to add to the array: ");
            scanf("%d", &number_array[array_last]);
            if(number_array[array_last] == -1){
                break;
            }
            array_last++;
        }
        if(number_array[array_last] == -1){
        }
        else if(number_array[array_last+1]==0){
            number_array[array_last+1]=-1;
        }
    print_histogram(number_array, a,b);
    }
    else if (choice == 0)
    {
        calculate_average(number_array);        
        calculate_mode(number_array);
        calculate_median(number_array);
    }
}
