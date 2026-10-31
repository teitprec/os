#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int a[50], n, i, j, temp;
    pid_t pid;

    printf("Enter array size: ");
    scanf("%d", &n);

    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid = fork();

    if (pid == 0) {
        /* Child: ascending order */
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++)
                if (a[i] > a[j]) {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }

        printf("____________child Process: _________");
        printf("\nSort element in ascending orde\n");
        for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");
    } else if (pid > 0) {
        wait(NULL);

        /* Parent: descending order */
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++)
                if (a[i] < a[j]) {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }

        printf("____________parent Process: _________");
        printf("\nSort element in descending orde\n");
        for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");
    } else {
        printf("Fork failed\n");
    }

    return 0;
}
