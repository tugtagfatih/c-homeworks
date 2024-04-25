#include <stdio.h>
#define STUDENT_NUMBER 210104004306

/* Encryption key functions*/
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
    while (scanf("%c", &character) != EOF) {
        if (character == '^') {
            /* Check if the next character is 'c'*/
            scanf("%c", &character);
            if (character == 'c') {
                int count;
                scanf("%d", &count);
                printf("/* There are %d characters as comment */", count);
            } else {
                printf("(%c", character);
            }
        } else {
            int i, inalphabet = 0;
            for (i = 0; i < 61; i++) {
                if (character == alphabet[i]) {
                    if (i < encryptionkey){
                        i=i+61;
                    }
                    i -= encryptionkey;
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
