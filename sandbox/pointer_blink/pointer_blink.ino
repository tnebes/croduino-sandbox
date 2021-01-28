/*
 * Show what pointers are in the most contrived way possible
 */

#define LED     13

void setup() {
    pinMode(LED, OUTPUT);
}

void BlinkLED(int pin, int *delayTime, int *state) {
    digitalWrite(pin, *state);
    delay(*delayTime);
    *delayTime = *delayTime - 10;
    *state = !(*state); 
}

void loop() {
    static int delayTime = 500;
    static int state = HIGH;
    BlinkLED(LED, &delayTime, &state);
    if (delayTime < 0) {
        delayTime = 500;
    }
}