#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

void cpu_intensive_task() {
 for (long i = 0; i < 1000000000; i++) {
 // Perform some meaningless calculation
 double result = 3.14159 * i;
 }
}


int main() {
    int priority = nice(0);
    printf("Initial priority: %d\n", priority);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    cpu_intensive_task();
    gettimeofday(&end, NULL);

    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Time taken with default priority: %f seconds\n", time_taken);
    priority = nice(10);
    printf("New priority: %d\n", priority);
    gettimeofday(&start, NULL);
    cpu_intensive_task();
    gettimeofday(&end, NULL);

    time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Time taken with lower priority: %f seconds\n", time_taken);
    return 0;
}