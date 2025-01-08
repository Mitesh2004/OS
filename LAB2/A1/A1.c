/*
#include <stdio.h>

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

    printf("\nProgram executed successfully.\n");
    return 0;
}*/


#include <stdio.h>
#include <stdbool.h>

int n, m; // Number of processes and resources

// Accept matrix for Allocation and Max (row by row)
void inputMatrix(int matrix[n][m], const char* name) {
    printf("\nEnter %s matrix (row by row):\n", name);
    for (int i = 0; i < n; i++) {
        printf("Enter row %d values: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Accept Available resources
void inputAvailable(int Available[m]) {
    printf("\nEnter available resources:\n");
    for (int i = 0; i < m; i++) {
        printf("Available[%d]: ", i);
        scanf("%d", &Available[i]);
    }
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

// Display Available resources
void displayAvailable(int Available[m]) {
    printf("\nAvailable resources:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", Available[i]);
    }
    printf("\n");
}

// Calculate Need matrix
void calculateNeed(int Need[n][m], int Max[n][m], int Allocation[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

// Check if request can be granted
bool isRequestSafe(int Request[m], int Available[m], int Allocation[n][m], int Need[n][m], int process_id) {
    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[process_id][i] || Request[i] > Available[i]) return false;
    }

    // Simulate resource allocation
    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[process_id][i] += Request[i];
        Need[process_id][i] -= Request[i];
    }

    // Check system safety
    int work[m];
    bool finish[n];
    for (int i = 0; i < m; i++) work[i] = Available[i];
    for (int i = 0; i < n; i++) finish[i] = false;

    while (true) {
        bool progress = false;
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
                    for (int j = 0; j < m; j++) work[j] += Allocation[i][j];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
        if (!progress) break;
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) return false;
    }

    return true;
}

// Resource request handling
void resourceRequest(int Allocation[n][m], int Max[n][m], int Available[m], int Need[n][m], int process_id) {
    int Request[m];
    printf("\nEnter request for process %d: ", process_id);
    for (int i = 0; i < m; i++) {
        scanf("%d", &Request[i]);
    }

    if (isRequestSafe(Request, Available, Allocation, Need, process_id)) {
        printf("\nRequest granted.\n");
    } else {
        printf("\nRequest cannot be granted (unsafe state).\n");
    }
}

int main() {
    // Input number of processes and resource types
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    // Declare matrices
    int Allocation[n][m], Max[n][m], Need[n][m], Available[m];

    // Accept values for Allocation, Max matrices and Available resources
    inputMatrix(Allocation, "Allocation");
    inputMatrix(Max, "Max");
    inputAvailable(Available);

    // Calculate the Need matrix
    calculateNeed(Need, Max, Allocation);

    // Display matrices and Available resources
    displayMatrix(Allocation, "Allocation");
    displayMatrix(Max, "Max");
    displayMatrix(Need, "Need");
    displayAvailable(Available);

    // Resource request for a process
    int process_id;
    printf("\nEnter process ID (0 to %d): ", n-1);
    scanf("%d", &process_id);
    resourceRequest(Allocation, Max, Available, Need, process_id);

    return 0;
}