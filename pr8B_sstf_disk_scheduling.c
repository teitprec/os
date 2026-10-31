#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RQ[100], done[100] = {0};
    int n, head, total = 0, i;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Seek sequence: %d", head);

    for (int count = 0; count < n; count++) {
        int index = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] &&
                (index == -1 ||
                 abs(RQ[i] - head) < abs(RQ[index] - head) ||
                 (abs(RQ[i] - head) == abs(RQ[index] - head) &&
                  RQ[i] > RQ[index]))) {
                index = i;
            }
        }

        total += abs(RQ[index] - head);
        head = RQ[index];
        done[index] = 1;

        printf(" -> %d", head);
    }

    printf("\nTotal head movement: %d\n", total);
    return 0;
}
