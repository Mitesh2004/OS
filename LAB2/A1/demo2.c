#include <stdio.h>
#include <stdbool.h>

int n, m; // Number of processes and resources
int Allocation[10][10], Max[10][10], Need[10][10], Available[10];

void acceptMatrix(int matrix[10][10], const char *name) {
    printf("\nEnter values for %s matrix:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%s[%d][%d]: ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void acceptAvailable() {
    printf("\nEnter Available resources:\n");
    for (int i = 0; i < m; i++) {
        printf("Available[%d]: ", i);
        scanf("%d", &Available[i]);
    }
}

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

bool isSafe() {
    int Work[10], Finish[10] = {0};
    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }

    int safeSequence[10], index = 0;
    bool found;

    for (int count = 0; count < n; count++) {
        found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        break;
                    }
                }

                if (j == m) { // All resources can be allocated
                    for (int k = 0; k < m; k++) {
                        Work[k] += Allocation[i][k];
                    }
                    safeSequence[index++] = i;
                    Finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return false;
        }
    }

    printf("\nSystem is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

bool requestResources(int processID, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > Need[processID][i]) {
            printf("\nError: Request exceeds Need.\n");
            return false;
        }
        if (request[i] > Available[i]) {
            printf("\nError: Request exceeds Available resources.\n");
            return false;
        }
    }

    // Temporarily allocate resources
    for (int i = 0; i < m; i++) {
        Available[i] -= request[i];
        Allocation[processID][i] += request[i];
        Need[processID][i] -= request[i];
    }

    if (isSafe()) {
        printf("\nRequest granted.\n");
        return true;
    } else {
        printf("\nRequest cannot be granted as it leads to an unsafe state.\n");
        // Rollback
        for (int i = 0; i < m; i++) {
            Available[i] += request[i];
            Allocation[processID][i] -= request[i];
            Need[processID][i] += request[i];
        }
        return false;
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    acceptMatrix(Allocation, "Allocation");
    acceptMatrix(Max, "Max");
    acceptAvailable();
    calculateNeed();

    // Display the Need matrix
    printf("\nNeed matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }

    int processID;
    printf("\nEnter the process number for the request (0 to %d): ", n - 1);
    scanf("%d", &processID);

    int request[10];
    printf("\nEnter the request for resources:\n");
    for (int i = 0; i < m; i++) {
        printf("Request[%d]: ", i);
        scanf("%d", &request[i]);
    }

    requestResources(processID, request);

    return 0;
}


/*
#include <stdio.h>
#include <stdbool.h>

int n, m; // Number of processes and resources

// Accept matrix
void Matrix(int matrix[n][m], const char* name) {
    printf("\nEnter values for %s matrix (row by row):\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%s[%d][%d]: ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Accept available resources
void acceptAvailable(int Available[m]) {
    printf("\nEnter the available resources for each resource type:\n");
    for (int i = 0; i < m; i++) {
        printf("Available[%d]: ", i);
        scanf("%d", &Available[i]);
    }
}

// Calculate Need matrix
void calculateNeed(int Need[n][m], int Max[n][m], int Allocation[n][m]) {
    printf("\nCalculating Need matrix as: Need = Max - Allocation\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    printf("Need matrix calculated successfully.\n");
}

// Display matrix
void displayMatrix(int matrix[n][m], const char* name) {
    printf("\n%s matrix:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Display available resources
void displayAvailable(int Available[m]) {
    printf("\nAvailable resources:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", Available[i]);
    }
    printf("\n");
}

// Check if request can be granted
bool requestCanBeGranted(int request[n][m], int Available[m], int Allocation[n][m], int Need[n][m], int process_id) {
    // Check if request is less than or equal to Need and Available
    for (int i = 0; i < m; i++) {
        if (request[process_id][i] > Need[process_id][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[process_id][i] > Available[i]) {
            printf("Error: Not enough resources available.\n");
            return false;
        }
    }
    
    // Pretend to allocate the resources and check for safety
    for (int i = 0; i < m; i++) {
        Available[i] -= request[process_id][i];
        Allocation[process_id][i] += request[process_id][i];
        Need[process_id][i] -= request[process_id][i];
    }

    // Safety check (Safety Algorithm)
    bool finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = Available[i];
    }

    bool progress;
    do {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < m; j++) {
                        work[j] += Allocation[i][j];
                    }
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress);

    // Check if all processes can finish
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("System is in an unsafe state after the request.\n");
            return false;
        }
    }

    printf("System is in a safe state after the request.\n");
    return true;
}

int main() {
    // Input number of processes and resource types
    printf("Banker's Algorithm: Resource Allocation Program\n");
    printf("------------------------------------------------\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    // Declare matrices with dynamic size
    int Allocation[n][m], Max[n][m], Need[n][m], Available[m];

    // Accept values for Allocation, Max matrices and Available resources
    printf("\nStep 1: Input Allocation matrix:\n");
    Matrix(Allocation, "Allocation");

    printf("\nStep 2: Input Max matrix:\n");
    Matrix(Max, "Max");

    printf("\nStep 3: Input Available resources:\n");
    acceptAvailable(Available);

    // Calculate the Need matrix
    printf("\nStep 4: Calculate Need matrix:\n");
    calculateNeed(Need, Max, Allocation);

    // Display all matrices and available resources
    printf("\nStep 5: Display Results\n");
    printf("------------------------\n");
    displayMatrix(Allocation, "Allocation");
    displayMatrix(Max, "Max");
    displayMatrix(Need, "Need");
    displayAvailable(Available);

    // Step 6: Accept a request for a process
    int process_id;
    printf("\nEnter the process ID to request resources (0 to %d): ", n-1);
    scanf("%d", &process_id);

    int request[m];
    printf("Enter the resource request for process %d:\n", process_id);
    for (int i = 0; i < m; i++) {
        printf("Request[%d]: ", i);
        scanf("%d", &request[i]);
    }

    // Check if the request can be granted
    if (requestCanBeGranted(request, Available, Allocation, Need, process_id)) {
        printf("\nResources granted successfully to Process %d.\n", process_id);
    } else {
        printf("\nResources cannot be granted to Process %d.\n", process_id);
    }

    printf("\nProgram executed successfully.\n");
    return 0;
}*/
