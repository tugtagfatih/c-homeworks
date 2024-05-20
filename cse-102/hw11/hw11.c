#include <stdio.h>
#include <string.h>


struct Hospital{
    char *name;
    char citiesServed[3];
};

struct Hospital hospitals[] = {
    {"Hospital - 1", "ABC"},
    {"Hospital - 2", "CDF"},
    {"Hospital - 3", "EBA"},
    {"Hospital - 4", "DGH"},
    {"Hospital - 5", "AE"},
    {"Hospital - 6", "DB"},
    {"Hospital - 7", "FE"}
};

void numHospitals(char cities[], int n);
int countPaths(int x, int y);
void part1();
void part2();
void part3();

void main(){
    int menuinput, menuexit = 0;
    while (!menuexit){
        printf("1. Part 1\n2. Part 2\n3. Part 3\n4. Exit\n");
        scanf("%d", &menuinput);
        switch (menuinput){
            case 1:
                part1();
                break;
            case 2:
                part2();
                break;
            case 3:
                part3();
                break;
            case 4:
                menuexit = 1;
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    }
}
void part1(){
    int startX, startY;
    printf("Enter the street number: ");
    scanf("%d", &startX);
    printf("Enter the avenue number: ");
    scanf("%d", &startY);

    int numPaths = countPaths(startX, startY);
    printf("Number of different shortest paths: %d\n", numPaths);
}


void part2(){ 
    char cities[]= "ABCDEFGH";
    int n;
    printf("Enter the number of hospitals: ");
    scanf("%d", &n);
    numHospitals(cities, n);

}
void part3(){

}

int isAllCitiesServed(struct Hospital hospitals[], int n, int cities[], int numCities, int index) {
    int i;
    if (index == n) {
        for (i = 0; i < numCities; i++) {
            if (!cities[i]) {
                return 0;
            }
        }
        return 1;
    }

    for (i = 0; i < strlen(hospitals[index].citiesServed); i++) {
        cities[hospitals[index].citiesServed[i] - 'A'] = 1;
    }

    return isAllCitiesServed(hospitals, n, cities, numCities, index + 1);
}

void numHospitals(char cities[], int n) {

    int citiesServed[8] = {0};

    if (isAllCitiesServed(hospitals, n, citiesServed, 8, 0)) {
        printf("All cities are served by at least one hospital.\n");
    } else {
        printf("Not all cities are served by a hospital.\n");
    }
}






















int countPaths(int x, int y) {
    if (x == 1 && y == 1)
        return 1;
    
    int paths = 0;
    if (x > 0)
        paths += countPaths(x - 1, y);
    if (y > 0)
        paths += countPaths(x, y - 1);
    
    return paths;
}