/*
* Write a program that turns a 1-byte number into a binary representation
* of itself using 8 LEDS.
*
* Extra. Write a program that takes an array of 1-byte numbers and displays them
* in binary using LEDS.
*/

#define BAUD_RATE   9600
#define PIN_0       13
#define PIN_1       12
#define PIN_2       11
#define PIN_3       10
#define PIN_4       9
#define PIN_5       8
#define PIN_6       7
#define PIN_7       6
#define DELAY_TIME  1000

unsigned char pin[8];

void setup() {
    Serial.begin(BAUD_RATE);
    pin[0] = PIN_0;
    pin[1] = PIN_1;
    pin[2] = PIN_2;
    pin[3] = PIN_3;
    pin[4] = PIN_4;
    pin[5] = PIN_5;
    pin[6] = PIN_6;
    pin[7] = PIN_7;
    for (int i = 0; i < sizeof(pin) / sizeof(pin[0]); i++) {
        pinMode(pin[i], OUTPUT);
    }

}

void displayBinary(char binary[]) {
    for (int i = 0; i < sizeof(pin) / sizeof(pin[0]); i++) {
        if (binary[i] == 1) {
            digitalWrite(pin[i], HIGH);
        } else {
            digitalWrite(pin[i], LOW);
        }
    }
    delay(DELAY_TIME);
    for (int i = 0; i < sizeof(pin) / sizeof(pin[0]); i++) {
        digitalWrite(pin[i], LOW);
    }
}

void getBinary(unsigned char number) {
    char binary[8];
    memset(binary, 1, sizeof(char));
    if (number > 9) {
        displayBinary(binary);
        // Serial.print("error");
        // Serial.println(number, DEC);
    } else {
        for (int i = 0; i < sizeof(binary) / sizeof(binary[0]); i++) {
            binary[i] = number & 1;
            number >>= 1;
        }
    }
    for (unsigned char i = 0; i < sizeof(binary) / sizeof(binary[0]); i++) {
        Serial.print(binary[i], DEC);
    }
    Serial.println();
    displayBinary(binary);
}

void extractNumber(int inputNumber) {
    while (inputNumber != 0) {
        getBinary((unsigned char) (inputNumber % 10));
        inputNumber /= 10;
    }
}

void loop() {

    for (unsigned char i = 0; i < 9; i++) {
        extractNumber(i);
        Serial.println(i, DEC);
        delay(DELAY_TIME);
    }
}