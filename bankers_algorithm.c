/*
 * Operating System Mini Project
 * Title: Banker's Algorithm Simulation for Deadlock Avoidance
 * Language: C
 *
 * The program reads Allocation, Maximum and Available resource data,
 * calculates the Need matrix, and checks whether a safe sequence exists.
 */

#include <stdio.h>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 10

int main(void)
{
    int n, m;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int i, j, count = 0, found;

    printf("============================================\n");
    printf(" BANKER'S ALGORITHM - DEADLOCK AVOIDANCE\n");
    printf("============================================\n");

    printf("Enter number of processes (1-%d): ", MAX_PROCESSES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter number of resource types (1-%d): ", MAX_RESOURCES);
    if (scanf("%d", &m) != 1 || m < 1 || m > MAX_RESOURCES) {
        printf("Invalid number of resource types.\n");
        return 1;
    }

    printf("\nEnter Allocation matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            if (scanf("%d", &allocation[i][j]) != 1 || allocation[i][j] < 0) {
                printf("Invalid allocation value. Use non-negative integers.\n");
                return 1;
            }
        }
    }

    printf("\nEnter Maximum matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            if (scanf("%d", &maximum[i][j]) != 1 ||
                maximum[i][j] < allocation[i][j]) {
                printf("Invalid maximum value. Each Max value must be >= Allocation.\n");
                return 1;
            }
        }
    }

    printf("\nEnter Available resources (%d values): ", m);
    for (j = 0; j < m; j++) {
        if (scanf("%d", &available[j]) != 1 || available[j] < 0) {
            printf("Invalid available resource value.\n");
            return 1;
        }
    }

    /* Calculate Need = Maximum - Allocation */
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix (Max - Allocation):\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    /* Work initially contains the currently available resources. */
    for (j = 0; j < m; j++) {
        work[j] = available[j];
    }

    /*
     * Safety algorithm:
     * Find an unfinished process whose Need <= Work.
     * Assume it completes, then release its Allocation into Work.
     */
    while (count < n) {
        found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canFinish = 1;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = 0;
                        break;
                    }
                }

                if (canFinish) {
                    for (j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    if (count == n) {
        printf("\nResult: SYSTEM IS IN A SAFE STATE.\n");
        printf("Safe sequence: ");
        for (i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if (i < n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("\nResult: SYSTEM IS IN AN UNSAFE STATE.\n");
        printf("No safe sequence exists for the supplied data.\n");
        printf("Processes that could finish in this check: ");
        for (i = 0; i < n; i++) {
            if (finish[i]) {
                printf("P%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}
