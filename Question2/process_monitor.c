#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child process started. PID = %d\n", getpid());

        sleep(10);

        printf("Child process completed.\n");
        exit(0);
    }

    printf("Parent monitoring child process...\n");

    sleep(3);

    if (kill(pid, 0) == 0) {
        printf("Child process is still running. Terminating...\n");
        kill(pid, SIGKILL);
    }

    waitpid(pid, NULL, 0);

    printf("Child process cleaned up. No zombie process remains.\n");

    return 0;
}
