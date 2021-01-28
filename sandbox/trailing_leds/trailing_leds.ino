#define LEDmax          13
#define LEDmin          6
#define BAUD_RATE       9600
#define DELAY_TIME      200
#define DELAY_TIME_MIN  0
#define STARTING_PIN    0

char pins[8];

void setup() {
    char counter = LEDmin;
    for (int i = 0; i < sizeof(pins) / sizeof(pins[0]); i++) {
        pins[i] = counter++;
        pinMode(pins[i], OUTPUT);
    }
    Serial.begin(BAUD_RATE);
}

void blinkLEDsDelay(int *ptrDelayTime, char *ptrCurrentPin) {
    blinkLEDs(ptrDelayTime, ptrCurrentPin);
    *ptrDelayTime *= 0.9;
    *ptrCurrentPin += 1;
}

void blinkLEDs(int *ptrDelayTime, char *ptrCurrentPin) {
    digitalWrite(pins[*ptrCurrentPin], HIGH);
    delay(*ptrDelayTime);
    digitalWrite(pins[*ptrCurrentPin], LOW);
    delay(*ptrDelayTime);
}

void loop() {
    static char currentPin = STARTING_PIN;
    static char numberOfPins = 1;
    static int delayTime = DELAY_TIME + numberOfPins * 5;
    blinkLEDsDelay(&delayTime, &currentPin);

    if (delayTime <= DELAY_TIME_MIN) {
        delayTime = DELAY_TIME + numberOfPins * 5;
        numberOfPins++;
        currentPin = numberOfPins - 1;
    }
    if (numberOfPins > sizeof(pins) / sizeof(pins[0])) {
        numberOfPins = 1;
    }
    if (currentPin >= numberOfPins) {
        currentPin = 0;
    }
}