/*#include <stdio.h>

int main() {
    char binary[9];
    int decimal, checkbinaryisokay;
    while (1) {
        printf("Enter an 8-bit binary number: ");
        scanf("%s", binary);
        checkbinaryisokay = check_eight_bit_binary(binary);
        if (checkbinaryisokay) {
            printf("Decimal: %d\n", eight_bit_binary_to_decimal(binary));
            break;
        }
        printf("Invalid binary number\n");
    }
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);
    printf("Binary: %s\n", decimal_to_eight_bit_binary(decimal, binary));
    return 0;
}
*/
#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 256
#define REGISTER_SIZE 8
#define PC_SIZE 16
#define IR_SIZE 24

// Define the structure for the simulator
struct Simulator {
    char A[REGISTER_SIZE];
    char B[REGISTER_SIZE];
    int PC;
    char IR[IR_SIZE];
    char memory[MEMORY_SIZE][REGISTER_SIZE];
};

int check_eight_bit_binary(char *binary) {
    int i;
    for (i = 0; i < 8; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int to_binary(int decimal, char *binary) {
    int i;
    for (i = 7; i >= 0; i--) {
        binary[i] = decimal % 2 + '0';
        decimal /= 2;
    }
    binary[8] = '\0';
    return binary;
}

int to_decimal(char *binary) {
    int i;
    int decimal = 0;
    for (i = 0; i < 8; i++) {
        decimal = decimal * 2 + binary[i] - '0';
    }
    return decimal;
}

// Function to fetch instruction
void fetch_instruction(struct Simulator *simulator) {
    int i;
    for (i = 0; i < 8; i++) {
        simulator->IR[i] = simulator->memory[simulator->PC][i];
    }
    simulator->IR[8] = '\0';
    simulator->PC++;
}

// Function to decode instruction
void decode_instruction(struct Simulator *simulator) {
    
}

// Function to execute instruction
void execute_instruction(struct Simulator *simulator) {
    // Implementation here
}

// Function to store result
void store_result(struct Simulator *simulator) {
    // Implementation here
}

// Main function
int main() {
    struct Simulator simulator;
    // Initialize simulator

    while (1) {
        fetch_instruction(&simulator);
        decode_instruction(&simulator);
        execute_instruction(&simulator);
        store_result(&simulator);
    }

    return 0;
}
