#include <stdio.h>

int counter = 0;

void setup() {
    int number = 5;
    int *ptrNumber;

    Serial.begin(9600);
    Serial.print("The lvalue for ptrNumber is: ");
    Serial.print((long) &ptrNumber, DEC);
    Serial.print(" and the rvalue is ");
    Serial.print((long) ptrNumber, DEC);
    Serial.print("\n");

    ptrNumber = &number;
    *ptrNumber = 10;

    Serial.print("The lvalue for number is: ");
    Serial.print((long) &number, DEC);
    Serial.print(" and the rvalue is ");
    Serial.print((long) number, DEC);
}

void loop() {
    
}