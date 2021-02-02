/*
 * Using pointer arithmetic can be hazardous to your health.
 * 
 * Dr Purdum, Nov. 24, 2014
 */

#include <string.h>

void setup() {
    Serial.begin(9600);
    
    char buffer[50];
    char *ptr;
    int i;
    int length;

    strcpy(buffer, "This is a test string");
    ptr = buffer;
    length = strlen(buffer);
    Serial.print("The lvalue for ptr is: ");
    Serial.print((unsigned int)&ptr);
    Serial.print(" and the rvalue is ");
    Serial.println((unsigned int)ptr);
    // recommended way of printing a char array
    while (*ptr) {
        Serial.print(*ptr++);
    }
    Serial.println();
    // unrecommended way of printing char array
    for (i = 0; i < length; i++) {
        Serial.print(*(ptr + i));
    }
}

void loop(){

}
