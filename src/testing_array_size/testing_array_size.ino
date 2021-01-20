/*
* Write a program that loops through an array and checks whether the int is a prime.
* If the int is a prime, send the number on serial and light the found LED for 1 second.
* While the program is searching, the red led should stay on.
* Once the array has been exhausted, simulate program termination
*/
#define GREEN_LED       10
#define RED_LED         12
#define DELAY           50
#define TEST_NUMBER     1250
#define SERIAL_BAUD     9600

void setup() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    Serial.begin(SERIAL_BAUD);
}

/*
* Blinks a light on a pin for a given duration
*/
void blinkLight(int light, int duration) {
    digitalWrite(light, HIGH);
    delay(duration);
    digitalWrite(light, LOW);
    delay(duration);
}

/*
* Simulates program termination
*/
void die() {
    Serial.println("DEAD");
    while(true) {
        ;
    }
}

void loop(){

    bool primes[TEST_NUMBER + 1];
    memset(primes, false, sizeof(primes));

    // using Sieve of Eratosthenes
    for (int i = 2; i <= TEST_NUMBER; i++) {
        for (int j = 2; j <= TEST_NUMBER / i; j++) {
            if (!primes[i * j]) {
                primes[i * j] = true;
            }
        }
    }

    /* 
    * Displays the primes in order from lowest to highest
    */
    for (int i = 2; i < sizeof(primes) / sizeof(primes[0]); i++) {
        digitalWrite(RED_LED, HIGH);
        // Serial.print("\tnot prime:");
        if (!primes[i]) {
            digitalWrite(RED_LED, LOW);
            Serial.println(i, DEC);
            Serial.println();
            blinkLight(GREEN_LED, DELAY);
        }
    }

    die();
    
}