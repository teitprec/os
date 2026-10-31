#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd, n;
    char buff[1024] = "", line[256], result[1024];

    mkfifo("myfifo1", 0666);
    mkfifo("myfifo2", 0666);

    printf("Enter sentences (finish with Ctrl+D):\n");

    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (strlen(buff) + strlen(line) >= sizeof(buff) - 1) {
            printf("Input is too long.\n");
            return 1;
        }
        strcat(buff, line);
    }

    fd = open("myfifo1", O_WRONLY);
    write(fd, buff, strlen(buff));
    close(fd);

    fd = open("myfifo2", O_RDONLY);
    n = read(fd, result, sizeof(result) - 1);
    close(fd);

    if (n > 0) {
        result[n] = '\0';
        printf("\nResult:\n%s", result);
    }

    return 0;
}