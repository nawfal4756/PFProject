#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    float temp;
    
    srand(time(0));
    do {
        temp = rand() % 501;
        printf("%f\n", temp);
    } while (temp < 25 || temp > 500);
    
}