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

int getInput(int *which) {
    char c;
    int temp = -1;
    *which = temp;
    while (true) {
        if (Serial.available() > 0) {
            c = Serial.read();
            if (isDigit(c)) {
                temp = c - '0';
                if (temp >= 0 && temp < 4) {
                    *which = temp;
                    return 1;
                }
            }
            return 0;
        }
    }
}

void LightLEDs(int combo)
{
    switch (combo)
    {
    case 0:
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        break;
    case 1:
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        break;
    case 2:
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        break;
    case 3:
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        break;
    default:
        Serial.println("Control should never get here");
        break;
    }
}

void loop()
{
    int flag;
    int LEDValue;

    Serial.println();
    flag = getInput(&LEDValue);
    Serial.print("flag = ");
    Serial.print(flag);
    Serial.print("\tLEDValue = ");
    Serial.print(LEDValue);
    LightLEDs(LEDValue);
}