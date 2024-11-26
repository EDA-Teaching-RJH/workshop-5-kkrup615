#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process (Consumer)
        close(pipefd[1]); // Close unused write end
        printf("Child: Waiting for data...\n");
        int bytes_read = read(pipefd[0], buffer, BUFFER_SIZE);
        printf("Child: Received message: %s\n", buffer);
        close(pipefd[0]);
    } else {
        // Parent process (Producer)
        close(pipefd[0]); // Close unused read end
        const char *message = "Hello from parent!";
        printf("Parent: Sending message...\n");
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        wait(NULL); // Wait for child to finish
    }
    return 0;
}