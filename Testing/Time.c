#include <stdio.h>
#include <time.h>

int main() {
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    printf("Month: %d\n", time1->tm_mon + 1);
    printf("Year: %d\n", time1->tm_year + 1900);
}