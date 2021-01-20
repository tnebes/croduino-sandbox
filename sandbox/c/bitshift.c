#include<stdio.h>
void main() {
    unsigned char a = 5;
    for (unsigned char i = 0; i < a; i++) {
        printf("%d ", a << 1);
        a <<= 1;
    }
}