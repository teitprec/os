#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipe1[2], pipe2[2];
    char path[256], buffer[1024];
    ssize_t n;
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        return 1;
    }

    printf("Enter file path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = '\0';

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {                 /* Parent */
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], path, strlen(path) + 1);
        close(pipe1[1]);

        printf("\nFile content:\n");
        while ((n = read(pipe2[0], buffer, sizeof(buffer))) > 0)
            write(STDOUT_FILENO, buffer, n);

        close(pipe2[0]);
        wait(NULL);
    } else {                       /* Child */
        close(pipe1[1]);
        close(pipe2[0]);

        n = read(pipe1[0], path, sizeof(path) - 1);
        close(pipe1[0]);

        if (n <= 0)
            exit(1);

        path[n] = '\0';

        FILE *file = fopen(path, "r");
        if (file == NULL) {
            char message[] = "Could not open file.\n";
            write(pipe2[1], message, strlen(message));
        } else {
            while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)
                write(pipe2[1], buffer, n);

            fclose(file);
        }

        close(pipe2[1]);
        exit(0);
    }

    return 0;
}