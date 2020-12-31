#include <stdio.h>
#include <stdbool.h>

bool StarConsumer(bool timePayment[12]);

int main() {
    bool data[12] = {true, true, true, true, true, false, true, true, true, true, true, true};

    if (StarConsumer(data)) {
        printf("True");
    }
    else {
        printf("False");
    }
}

bool StarConsumer(bool timePayment[12]) {
    int counter1, falseData = 0;
    
    for (counter1 = 0; counter1 < 12; counter1++) {
        if (timePayment[counter1] == false) {
            falseData = 1;
            break;
        }
    }

    if (falseData == 1) {
        return false;
    }

    return true;
}