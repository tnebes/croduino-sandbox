/*
 * Program adjusts itself to the nearest wall or maximal distance
 * Program tracks whether the ultrasonic sensor has been triggered.
 * If the trigger distance increases, the person is entering
 * If the trigger distance decreases, the person is entering
 * The program will light up a LED upon detection
 * The program will output a string which will tell whether a person left or entered
 */

// digital pins
#define TRIGGER_PIN     2
#define ECHO_PIN        3
#define PING_LED_PIN    4
#define DELAY_TIME      0.1
// global variables
long max_distance;
int counter = 0;

// setting up pins and communication via serial
// starts the self adjustment method
void setup() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PING_LED_PIN, OUTPUT);

    // establishing serial connection to main
    Serial.begin(9600);
    // self-adjustment
    adjust();
}

// determine the distance at which the sensor gets triggered.
int adjust() {
    const int STARTUP_DELAY = 3000;
    //indicator light on.
    digitalWrite(PING_LED_PIN, HIGH);
    // wait 3 seconds
    delay(STARTUP_DELAY);
    digitalWrite(PING_LED_PIN, LOW);
    
    max_distance = determineMaxDistance();
}

long determineMaxDistance() {
    long sum = 0;
    const int NUMBER_OF_MEASUREMENTS = 10;

    for (int i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        digitalWrite(PING_LED_PIN, HIGH);
        sum += detect();
        delay(100);
        digitalWrite(PING_LED_PIN, LOW);
        delay(100);
    }
    // return average of 10 measurements and add margin of error of 10%
    return (sum / NUMBER_OF_MEASUREMENTS) * 0.9;
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

boolean triggered() {
    // send a ping and return whether something has been detected
    onePing();
    if (pulseIn(ECHO_PIN, HIGH) < max_distance) {
        return true;
    }
    return false;
}



void loop() {
    
    if (triggered) {
        Serial.print("Triggered!\n");
        long initialDistance = detect();
        long distance;
        do {
            distance = detect();
        } while (distance > 0 || distance < max_distance);

        if (initialDistance > distance) {
            Serial.print("Person left.\n");
        } else if (initialDistance < distance) {
            Serial.print("Person entered.'\n");
        } else {
            Serial.print("Person went paralel.\n");
        }
        
        
    }

}




