#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to calculate the need matrix
void calculateNeed(int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state and find the safe sequence
bool isSafe(int processes, int resources) {
    bool finish[MAX_PROCESSES] = { false };
    int work[MAX_RESOURCES];
    int safeSeq[MAX_PROCESSES];
    
    // Initialize work with available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0; // Number of processes that can finish

    while (count < processes) {
        bool found = false;

        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool canAllocate = true;

                // Check if resources are sufficient
                for (int j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // If resources are sufficient, simulate allocation
                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[p][j];
                    }
                    finish[p] = true; // Mark process as finished
                    safeSeq[count++] = p; // Record the safe sequence
                    found = true; // Found a process that can finish
                }
            }
        }

        // If no process was found that can finish, we are in a deadlock
        if (!found) {
            return false; // Deadlock detected
        }
    }

    // Print safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true; // No deadlock, safe state
}

int main() {
    int numProcesses, numResources;

    // User input for number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter number of resources: ");
    scanf("%d", &numResources);

    // User input for allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // User input for maximum demand matrix
    printf("Enter max demand matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // User input for available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    calculateNeed(numProcesses, numResources);

    // Check for deadlock and print safe sequence if no deadlock is detected
    if (isSafe(numProcesses, numResources)) {
        printf("No deadlock detected.\n");
    } else {
        printf("Deadlock detected!\n");
    }

    return 0;
}
