#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
        // If execl#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void long_running_task() {
    for (int i = 0; i < 5; i++) {
        printf("Child working: %d\n", i);
        sleep(1);
    }
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, State = Running\n", getpid());
        long_running_task();
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: PID = %d, State = Waiting\n", getpid());
        wait(NULL);
        printf("Parent process: State = Running (after child completion)\n");
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    return 0;
}() returns, it must have failed
        perror("execl");
        return 1;
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL); // Wait for child to finish
    } else {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    return 0;
}