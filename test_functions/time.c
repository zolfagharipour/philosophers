#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval tv;

    // Get current time
    gettimeofday(&tv, NULL);

    // Print seconds and microseconds
    printf("Seconds: %ld\n", tv.tv_sec);
    printf("Microseconds: %ld\n", tv.tv_usec);

    return 0;
}

