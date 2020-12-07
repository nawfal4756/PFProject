#include <stdio.h>
#include <stdbool.h>

bool SSGCConsumerIDVerification(unsigned long long int consumerID);

int main() {
    unsigned long long int consumerId;

    printf("Enter consumer id: ");
    scanf("%llu", &consumerId);

    if(SSGCConsumerIDVerification(consumerId)) {
        printf("True");
    }
    else {
        printf("False");
    }
}

bool SSGCConsumerIDVerification(unsigned long long int consumerID) {
    if (consumerID >= 1000000000 && consumerID <= 9999999999) {
        return true;
    }
    else {
        return false;
    }
}