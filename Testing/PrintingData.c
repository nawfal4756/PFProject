#include <stdio.h>

int main() {
    float data[12] = {25.6, 354.6, 874.5, 698, 12.4, 254.6, 8741.2, 74.2, 125.2, 325.1, 125.4, 123.5};
    int counter1;

    printf("%12s\t%12s\t%12s\n", "Month", "Amount Due", "Amount Paid");
    for (counter1 = 0; counter1 < 12; counter1++) {
        printf("%12s\t%12.2f\t%12.2f\n", "Jan 2019", data[counter1], data[counter1]);
    }
}