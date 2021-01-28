/*
 * 
 * Write a program that calls a function named getInput()
 * to acquire a single-digit number from the user via the Serial monitor.
 * The numeric value from the user has the following interpretation:
 * 0 LED
 * 1 LED1 lit
 * 2 LED2 lit
 * 3 both LEDs lit
 * 
 * Any other entry should keep the LEDS in whatever their current state is.
 * the only two values that can be returned from the function are 0 or 1.
 * 
*/

#define LED1 13
#define LED2 12


void setup() {
    Serial.begin(9600);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
}

void loop() {
    
}