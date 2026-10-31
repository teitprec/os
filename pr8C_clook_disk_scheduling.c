#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RQ[100], n, head, total = 0;
    int i, j, index = 0, current;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

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

    /* First request at or above the head */
    while (index < n && RQ[index] < head)
        index++;

    current = head;
    printf("Seek sequence: %d", current);

    /* Move toward higher requests */
    for (i = index; i < n; i++) {
        total += abs(RQ[i] - current);
        current = RQ[i];
        printf(" -> %d", current);
    }

    /* Jump to the lowest request, then continue upward */
    if (index > 0) {
        total += abs(current - RQ[0]);
        current = RQ[0];
        printf(" -> %d", current);

        for (i = 1; i < index; i++) {
            total += abs(RQ[i] - current);
            current = RQ[i];
            printf(" -> %d", current);
        }
    }

    printf("\nTotal head movement: %d\n", total);
    return 0;
}
