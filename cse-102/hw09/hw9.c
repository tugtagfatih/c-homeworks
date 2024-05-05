#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 1000

struct Forest {
    char Map[MAX_VALUE][MAX_VALUE];
    int Width;
    int Height;
    int Flower_X;
    int Flower_Y;
};

struct Botanist {
    int Coord_X;
    int Coord_Y;
    int Number_of_Bottle;
};

void init_game(struct Botanist *botanist, struct Forest *forest);
void display_forest(struct Botanist botanist, struct Forest forest);
int check_flower_count(struct Botanist *botanist, struct Forest *forest);
void search(struct Botanist *botanist, struct Forest *forest);
void check_botanist_position(struct Botanist *botanist, struct Forest *forest);
void check_any_move(struct Botanist *botanist, struct Forest *forest, char move);

int main(){
    struct Botanist Botanist;
    struct Forest Forest;
    init_game(&Botanist, &Forest);
    display_forest(Botanist, Forest);
    search(&Botanist, &Forest);
}

void init_game(struct Botanist *botanist, struct Forest *forest){
    FILE *initfile;
    initfile = fopen("init.txt", "r");
    if (initfile == NULL)printf("Error: File not found\n");
    int width, height, i,j;
    fscanf(initfile, "%d,%d", &width, &height);
    fscanf(initfile, "%d,%d,%d",&botanist->Coord_X, &botanist->Coord_Y, &botanist->Number_of_Bottle);
    forest->Width = width;
    forest->Height = height;
    for (i = 0; i < height; i++){
        for (j = 0; j < width*2; j++){
            fscanf(initfile, "%c", &forest->Map[i][j]);
        }
    }
    fclose(initfile);
    check_botanist_position(botanist, forest);
}

void display_forest(struct Botanist botanist, struct Forest forest){
    int i,j;
    for (i = 0; i < forest.Height; i++){
        for (j = 0; j < forest.Width*2; j++){
            if (forest.Map[i][j]!='\n') printf("%c", forest.Map[i][j]);
        }
        printf("\n");
    }
    printf("Bottle remaining: %d\n", botanist.Number_of_Bottle);
}

void search(struct Botanist *botanist, struct Forest *forest){
    int found_all_flowers = 0, flower_count = check_flower_count(botanist, forest);
    char move;
    while (!found_all_flowers){
        if (botanist->Number_of_Bottle == 0){
            printf("Game Over! No water left.\n");
            found_all_flowers = 1;
        }
        else if (flower_count == 0){
            printf("You have picked all the flowers! Game Over!\n");
            found_all_flowers = 1;
        }
        else {
            printf("Please select the next move (u: Up, d: Down, l: Left, r: Right): ");
            scanf("%c", &move);
            getchar();
            if (move=='u'){
                if (forest->Map[botanist->Coord_X-1][botanist->Coord_Y] == ' ' || forest->Map[botanist->Coord_X-1][botanist->Coord_Y] == 'X'){
                    if (forest->Map[botanist->Coord_X-1][botanist->Coord_Y] == 'X'){
                        forest->Map[botanist->Coord_X-1][botanist->Coord_Y] = ' ';
                        botanist->Number_of_Bottle--;
                        flower_count--;
                    }
                    forest->Map[botanist->Coord_X][botanist->Coord_Y] = '#';
                    forest->Map[botanist->Coord_X-1][botanist->Coord_Y] = 'B';
                    botanist->Coord_X--;
                    display_forest(*botanist, *forest);
                }
                else printf("Invalid move! Please try again.\n");
            }
            else if (move=='d'){
                if (forest->Map[botanist->Coord_X+1][botanist->Coord_Y] == ' ' || forest->Map[botanist->Coord_X+1][botanist->Coord_Y] == 'X'){
                    if (forest->Map[botanist->Coord_X+1][botanist->Coord_Y] == 'X'){
                        forest->Map[botanist->Coord_X+1][botanist->Coord_Y] = ' ';
                        botanist->Number_of_Bottle--;
                        flower_count--;
                    }
                    forest->Map[botanist->Coord_X][botanist->Coord_Y] = '#';
                    forest->Map[botanist->Coord_X+1][botanist->Coord_Y] = 'B';
                    botanist->Coord_X++;
                    display_forest(*botanist, *forest);
                }
                else printf("Invalid move! Please try again.\n");
            }
            else if (move=='l'){
                if (forest->Map[botanist->Coord_X][botanist->Coord_Y-2] == ' ' || forest->Map[botanist->Coord_X][botanist->Coord_Y-2] == 'X'){
                    if (forest->Map[botanist->Coord_X][botanist->Coord_Y-2] == 'X'){
                        forest->Map[botanist->Coord_X][botanist->Coord_Y-2] = ' ';
                        botanist->Number_of_Bottle--;
                        flower_count--;
                    }
                    forest->Map[botanist->Coord_X][botanist->Coord_Y] = '#';
                    forest->Map[botanist->Coord_X][botanist->Coord_Y-2] = 'B';
                    botanist->Coord_Y -= 2;
                    display_forest(*botanist, *forest);
                }
                else printf("Invalid move! Please try again.\n");
            }
            else if (move=='r'){
                if (forest->Map[botanist->Coord_X][botanist->Coord_Y+2] == ' ' || forest->Map[botanist->Coord_X][botanist->Coord_Y+2] == 'X'){
                    if (forest->Map[botanist->Coord_X][botanist->Coord_Y+2] == 'X'){
                        forest->Map[botanist->Coord_X][botanist->Coord_Y+2] = ' ';
                        botanist->Number_of_Bottle--;
                        flower_count--;
                    }
                    forest->Map[botanist->Coord_X][botanist->Coord_Y] = '#';
                    forest->Map[botanist->Coord_X][botanist->Coord_Y+2] = 'B';
                    botanist->Coord_Y += 2;
                    display_forest(*botanist, *forest);
                }
                else printf("Invalid move! Please try again.\n");
            }
            else printf("Invalid move! Please try again.\n");
            check_any_move(botanist, forest, move);
        }
    }
}

int check_flower_count(struct Botanist *botanist, struct Forest *forest){
    int i,j;
    int flower_count = 0;
    for (i = 0; i < forest->Height; i++){
        for (j = 0; j < forest->Width*2; j++){
            if (forest->Map[i][j] == 'X') flower_count++;
        }
    }
    return flower_count;
}

void check_botanist_position(struct Botanist *botanist, struct Forest *forest){
    int i,j;
    for(i=0;i<forest->Height;i++){
        for (j=0;j<forest->Width*2;j++){
            if (forest->Map[i][j] == 'B'){
                botanist->Coord_X = i;
                botanist->Coord_Y = j;
            }
        }
    }
}

void check_any_move(struct Botanist *botanist, struct Forest *forest, char move){
    if (forest->Map[botanist->Coord_X][botanist->Coord_Y+2] == '#' || forest->Map[botanist->Coord_X][botanist->Coord_Y+2] == 'T'){
        if (forest->Map[botanist->Coord_X][botanist->Coord_Y-2] == '#' || forest->Map[botanist->Coord_X][botanist->Coord_Y-2] == 'T'){
            if (forest->Map[botanist->Coord_X-1][botanist->Coord_Y] == '#' || forest->Map[botanist->Coord_X-1][botanist->Coord_Y] == 'T'){
                if (forest->Map[botanist->Coord_X+1][botanist->Coord_Y] == '#' || forest->Map[botanist->Coord_X+1][botanist->Coord_Y] == 'T'){
                    printf("Game Over! You are stuck in the forest.\n");
                    exit(0);
                }
            }
        }
    }
}