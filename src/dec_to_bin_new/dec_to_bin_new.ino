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
#define DELAY_TIME  250
#define MAX_NUMBER  10
#define ARRAYLENGTH(x) (sizeof(x) / sizeof(x[0]))

char pin[8];

void setup() 
{
    Serial.begin(BAUD_RATE);
    pin[0] = PIN_0;
    pin[1] = PIN_1;
    pin[2] = PIN_2;
    pin[3] = PIN_3;
    pin[4] = PIN_4;
    pin[5] = PIN_5;
    pin[6] = PIN_6;
    pin[7] = PIN_7;
    for (int i = 0; i < ARRAYLENGTH(pin); i++) {
        pinMode(pin[i], OUTPUT);
    }

}

void loop() 
{
    char buff[4];
    int charsRead;
    int val;

    if (Serial.available() > 0) {
        charsRead = Serial.readBytesUntil('\n', buff, 3);
        buff[charsRead] = '\0';
        val = atoi(buff);
        if (val > -1 && val < 256) {
            DisplayBinaryDigit(val);
        }
    } 
}

void DisplayBinaryDigit(byte num) {
    for (int i = 0; i < ARRAYLENGTH(pin); i++) {
        if (bitRead(num, i) == 1) {
            digitalWrite(pin[i], HIGH);
        } else {
            digitalWrite(pin[i], LOW);
        }
    }
}