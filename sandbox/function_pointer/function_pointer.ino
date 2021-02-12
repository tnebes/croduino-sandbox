/*
Purpose: Show how to use a pointer to function
Dr. Purdum, December 21, 2014
*/

#define BAUD 9600

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int number = 50;
    int (*funcPtr)(int n);
    funcPtr = DisplayValue;
    number = (*funcPtr)(number);
    Serial.print("After return from function, number = ");
    Serial.println(number);
    Serial.flush();
    exit(0);
}

int DisplayValue(int value) 
{
    Serial.print("In function, value = ");
    Serial.println(value);
    return value * value;
}