#include<stdio.h>

void displayBinary(char binary[]) {
    printf("Binary size is: %d", sizeof(*binary));
    for (int i = 0; i < sizeof(*binary) / sizeof(binary[0]); i++) {
        printf("%d", binary[i]);
    }
    printf("\t");
}

void getBinary(unsigned char number) {
    char binary[8];
    if (number > 9) {
        displayBinary(binary);
        // Serial.print("error");
        // Serial.println(number, DEC);
    } else {
        for (int i = 0; i < sizeof(binary) / sizeof(binary[0]); i++) {
            binary[i] = (char) (number & 1);
            number >>= 1;
        }
    }
    for (unsigned char i = 0; i < sizeof(*binary) / sizeof(binary[0]); i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
    displayBinary(binary);
}

void extractNumber(int inputNumber) {
    while (inputNumber != 0) {
        getBinary((unsigned char) (inputNumber % 10));
        inputNumber /= 10;
    }
}

void main() {

    for (unsigned char i = 10; i < 20; i++) {
        extractNumber(i);
    }
}