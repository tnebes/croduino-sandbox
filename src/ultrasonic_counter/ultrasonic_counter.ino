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
const int triggerPin = 2;
const int echoPin = 3;
const int pingLEDPin = 4;
const float delayTime = 0.1;
long max_distance;
int counter = 0;

void setup() {
    // setting up pins.
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(pingLEDPin, OUTPUT);

    // establishing serial connection to main
    Serial.begin(9600);
    // self-adjustment
    adjust();
}

int adjust() {
    int startupDelay = 3000;
    //indicator light on.
    digitalWrite(pingLEDPin, HIGH);
    delay(startupDelay);
    digitalWrite(pingLEDPin, LOW);
    
    max_distance = determineMaxDistance();
}

long determineMaxDistance() {
    long sum = 0;
    int numberOfMeasurements = 10;

    for (int i = 0; i < numberOfMeasurements; i++) {
        digitalWrite(pingLEDPin, HIGH);
        sum += detect();
        delay(100);
        digitalWrite(pingLEDPin, LOW);
        delay(100);
    }
    return sum / numberOfMeasurements;
}

long detect() {
    onePing();
    return pulseIn(echoPin, HIGH);
}

void onePing() {
    // send a pulse
    digitalWrite(triggerPin, HIGH);
    // wait for ping to be sent
    delay(delayTime);
    // one ping finished
    digitalWrite(triggerPin, LOW);
}

void loop() {
    if (detect() < max_distance * 0.9) {
        Serial.print(counter++);
		Serial.print("\n");
        digitalWrite(pingLEDPin, HIGH);
        while (detect() < max_distance * 0.9) {
            delay(50);
        }
        digitalWrite(pingLEDPin, LOW);
    }
}