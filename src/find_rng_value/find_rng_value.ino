/*
 * Use the random number generator and look for a specific value to be produced. When the desired
 * value is found, the code should light the “found it” LED for one second, send a message to the PC via the
 * Serial monitor, and report the value of the loop counter. However, each time we cycle through the positive
 * values for the int variable that is controlling the loop, we should light the other LED for one second and send
 * a message back to the PC
 * 
*/

#define MAX_RNG_VALUE   5000
#define MIN_RNG_VALUE   0
#define TARGET_VALUE    2500
#define SEARCH_LED_PIN  12
#define FOUND_LED_PIN   10
#define DELAY_TIME      1000
#define RECYCLE_LIMIT   5

int counter = 0;
long randomNumber;
int recycleCounter = 0;

void setup() {
    // setting up the pins and the serial connection
    pinMode(SEARCH_LED_PIN, OUTPUT);
    pinMode(FOUND_LED_PIN, OUTPUT);
    Serial.begin(9600);
    // guaranteed to give us a random seed.
    randomSeed(analogRead(A0));
}

long generateRandomLong() {
    return random(MIN_RNG_VALUE, MAX_RNG_VALUE);
}

// fake program termination
void end() {
    while(true) {
        ;
    }
}

void toggleLED(int ledPin, int duration) {
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW);
}

void loop() {
    randomNumber = generateRandomLong();
    if (randomNumber == TARGET_VALUE) {
        Serial.print("Counter = ");
        Serial.print(counter, DEC);
        Serial.print(" recycleCounter = ");
        Serial.println(recycleCounter, DEC);
        toggleLED(FOUND_LED_PIN, DELAY_TIME);
    }

    counter++;

    // if integer overflow
    if (counter < 0) {
        counter = 0;
        recycleCounter++;
        Serial.print("recycleCounter = ");
        Serial.println(recycleCounter, DEC);
        toggleLED(SEARCH_LED_PIN, DELAY_TIME);
    }

    if (recycleCounter == RECYCLE_LIMIT) {
        end();
    }
}