/*
 * Program adjusts itself to the nearest wall or maximal distance
 * Program tracks whether the ultrasonic sensor has been triggered.
 * If the trigger distance increases, the person is entering
 * If the trigger distance decreases, the person is entering
 * The program will light up a LED upon detection
 * The program will output a string which will tell whether a person left or entered
 */

// digital pins
#define TRIGGER_PIN         2
#define ECHO_PIN            3
#define PING_LED_PIN        4
#define PING_DELAY_TIME     10
#define ADJUST_DELAY_TIME   150
#define NUM_OF_ADJUSTMENTS  10

long maxDistance;

// setting up pins and communication via serial
// starts the self adjustment method
void setup() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PING_LED_PIN, OUTPUT);

    // establishing serial connection to main
    Serial.begin(9600);
    // self-adjustment
    maxDistance = adjust();
    Serial.print((int) maxDistance);
}

long sendPing() {
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(PING_DELAY_TIME);
    digitalWrite(TRIGGER_PIN, LOW);
}

long getDistance() {
    sendPing();
    long distance = pulseIn(ECHO_PIN, HIGH);
    delayMicroseconds(PING_DELAY_TIME);
    return distance;
}

boolean isTriggered() {
    return getDistance() < maxDistance;
}

long adjust() {
    digitalWrite(PING_LED_PIN, HIGH);
    delay(1000);
    long sum = 0;
    for (int i = 0; i <= NUM_OF_ADJUSTMENTS; i++) {
        digitalWrite(PING_LED_PIN, HIGH);
        sum += getDistance();
        Serial.write((int) sum);
        Serial.write("\n");
        delay(ADJUST_DELAY_TIME);
        digitalWrite(PING_LED_PIN, LOW);
        delay(ADJUST_DELAY_TIME);
    }
    return (sum / NUM_OF_ADJUSTMENTS);
}


void loop(){
    if (isTriggered()) {
        Serial.print((int) getDistance());
        Serial.print("\n");
    }
}



