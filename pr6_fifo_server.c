#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

int main()
{
    int fd, n, chars = 0, words = 0, lines = 0, inside = 0;
    char buff[1024], result[1024];

    mkfifo("myfifo1", 0666);
    mkfifo("myfifo2", 0666);

    fd = open("myfifo1", O_RDONLY);
    n = read(fd, buff, sizeof(buff) - 1);
    close(fd);

    if (n <= 0)
        return 1;

    buff[n] = '\0';
    printf("Data received from client:\n%s\n", buff);

    for (int i = 0; i < n; i++) {
        if (buff[i] != '\n')
            chars++;

        if (buff[i] == '\n')
            lines++;

        if (isspace((unsigned char)buff[i]))
            inside = 0;
        else if (!inside) {
            words++;
            inside = 1;
        }
    }

    if (buff[n - 1] != '\n')
        lines++;

    FILE *fp = fopen("opfile.txt", "w");
    fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n",
            chars, words, lines);
    fclose(fp);

    fp = fopen("opfile.txt", "r");
    n = fread(result, 1, sizeof(result) - 1, fp);
    fclose(fp);
    result[n] = '\0';

    fd = open("myfifo2", O_WRONLY);
    write(fd, result, strlen(result));
    close(fd);

    printf("Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    printf("Result saved in opfile.txt and sent to client.\n");

    return 0;
}
