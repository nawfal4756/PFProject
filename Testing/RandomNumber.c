#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    float temp;
    int counter;

    
    srand(time(0));
    for (counter = 0; counter < 12; counter++) {    
        do {
            temp = rand() % 501;
            printf("%f\n", temp);
        } while (temp < 25 || temp > 500);
    }
    
    
}