#include <stdio.h>
#define STUDENT_NUMBER 210104004306

/*Encryption key functions*/
int sumnumbers(long long num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
int tenplus() {
    long long num = STUDENT_NUMBER;
    while (num > 9) {
        num = sumnumbers(num);
    }
    return num;
}

int main() {
    int encryptionkey = tenplus();
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char character;
    while (scanf("%c", & character) != EOF){ 
    if (character == '/') {
            /* Check if the next character is '*'*/
            scanf("%c", & character);
            if (character == '*') {
                int count = 0;
                /* Count characters until "* /" is encountered */
                while (1) {
                    scanf("%c", & character);
                    if (character == '*') {
                        scanf("%c", & character);
                        if (character == '/') {
                            break;
                        } else if(character!= ' ') {
                            count++;
                        }
                    } else if(character!= ' '){
                        count++;
                    }
                }
                printf("^c%d", count);
            } else {
                printf("/%c", character);
            }
        } else {
            int i, inalphabet = 0; 
            for (i = 0; i < 61 ; i++) {
                if (character == alphabet[i]) {
                    i = (i + encryptionkey) % 61; /*We use mods so as not to exceed the character limit of the array*/
                    inalphabet = 1; 
                    break;
                }
            }
            if (inalphabet == 1) {
                printf("%c", alphabet[i]);
            } else {
                printf("%c", character);
            }
        }
    }
    return 0;
}