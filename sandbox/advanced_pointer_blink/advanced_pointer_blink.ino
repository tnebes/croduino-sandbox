/*
 * Make a program that uses pointers
 * to blink LEDS.
 * The program blinks for delayTime -10.
 * Once delayTime is 0, blink the previous + the next light until you reach the end.
 * Once the end has been reached, restart the blinking process.
 */

#define LEDmax 13
#define LEDmin 6
#define BAUD_RATE 9600
#define DELAY_TIME 200
#define DELAY_TIME_MIN 0

char pins[8];

void setup() {
    char counter = LEDmin;
    for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); i++) {
        pins[i] = counter++;
        pinMode(pins[i], OUTPUT);
    }
    Serial.begin(BAUD_RATE);
}

void blinkLEDs(char *ptrNumberOfPins, int *ptrDelayTime) {
    for (char i = 0; i < *ptrNumberOfPins; i++) {
        digitalWrite(pins[i], HIGH);
    }
    Serial.println("hello");
    delay(*ptrDelayTime);
    for (char i = 0; i < *ptrNumberOfPins; i++) {
        digitalWrite(pins[i], LOW);
    }
    delay(*ptrDelayTime);
    *ptrDelayTime *= 0.9;

}

void advancedBlinkLEDs(char *ptrNumberOfPins, int *ptrDelayTime) {
    for (char i = 0; i < *ptrNumberOfPins; i += 2) {
        digitalWrite(pins[i], HIGH);
    }
    delay(*ptrDelayTime);
    for (char i = 0; i < *ptrNumberOfPins; i++) {
        digitalWrite(pins[i], LOW);
    }
    for (char i = 1; i < *ptrNumberOfPins; i += 2) {
        digitalWrite(pins[i], HIGH);
    }
    delay(*ptrDelayTime);
    for (char i = 1; i < *ptrNumberOfPins; i++) {
        digitalWrite(pins[i], LOW);
    }
    delay(*ptrDelayTime);
    *ptrDelayTime *= 0.9;
}

void loop() {
    static char numberOfPins = 1;
    static int delayTime = DELAY_TIME;
    advancedBlinkLEDs(&numberOfPins, &delayTime);


    if (delayTime <= DELAY_TIME_MIN) {
        delayTime = DELAY_TIME;
        numberOfPins++;
    }
    if (numberOfPins > sizeof(pins) / sizeof(pins[0])) {
        numberOfPins = 1;
    }
}