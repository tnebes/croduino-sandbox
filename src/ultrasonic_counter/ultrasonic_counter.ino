/*
 * Upon activation, adjusts the distance to obstacle.
 * Marked by blinking LED.
 * If none is found, assume it's infinite.
 * Once adjustment is completed, stop blinking.
 * 
 * from this point on, every X loops transmits the counter
 * over serial.
 * 
 */

// digital pins
#define triggerPin = 2;
#define echoPin = 3;
#define pingLEDPin = 4;
#define delayTime = 0.1;
long max_distance;
int counter = 0;

void setup() {
    // setting up pins.
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PING_LED_PIN, OUTPUT);

    // establishing serial connection to main
    Serial.begin(9600);
    // self-adjustment
    adjust();
}

int adjust() {
    int startupDelay = 3000;
    //indicator light on.
    digitalWrite(PING_LED_PIN, HIGH);
    delay(startupDelay);
    digitalWrite(PING_LED_PIN, LOW);
    
    max_distance = determineMaxDistance();
}

long determineMaxDistance() {
    long sum = 0;
    int numberOfMeasurements = 10;

    for (int i = 0; i < numberOfMeasurements; i++) {
        digitalWrite(PING_LED_PIN, HIGH);
        sum += detect();
        delay(100);
        digitalWrite(PING_LED_PIN, LOW);
        delay(100);
    }
    return sum / numberOfMeasurements;
}

long detect() {
    onePing();
    return pulseIn(ECHO_PIN, HIGH);
}

void onePing() {
    // send a pulse
    digitalWrite(TRIGGER_PIN, HIGH);
    // wait for ping to be sent
    delay(DELAY_TIME);
    // one ping finished
    digitalWrite(TRIGGER_PIN, LOW);
}

void loop() {
    if (detect() < max_distance * 0.9) {
        Serial.print(counter++);
		Serial.print("\n");
        digitalWrite(PING_LED_PIN, HIGH);
        while (detect() < max_distance * 0.9) {
            delay(50);
        }
        digitalWrite(PING_LED_PIN, LOW);
    }
}