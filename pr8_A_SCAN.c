#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RQ[100], n, initial, size;
    int i, j, index = 0, current, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    printf("Enter total disk size: ");
    scanf("%d", &size);

    /* Sort requests */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    /* Find first request at or above the head */
    while (index < n && RQ[index] < initial)
        index++;

    current = initial;
    printf("Seek sequence: %d", current);

    /* Move toward higher cylinders */
    for (i = index; i < n; i++) {
        total += abs(RQ[i] - current);
        current = RQ[i];
        printf(" -> %d", current);
    }

    /* Go to the last cylinder, then reverse */
    total += abs((size - 1) - current);
    current = size - 1;
    printf(" -> %d", current);

    /* Serve remaining requests while moving lower */
    for (i = index - 1; i >= 0; i--) {
        total += abs(RQ[i] - current);
        current = RQ[i];
        printf(" -> %d", current);
    }

    printf("\nTotal head movement: %d\n", total);
    return 0;
}