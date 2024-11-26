#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
        // If execl() returns, it must have failed
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