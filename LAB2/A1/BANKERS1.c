#include <stdio.h>

#define MAX 10

int n, m; // Number of processes and resource types
int Allocation[MAX][MAX], Max[MAX][MAX], Need[MAX][MAX], Available[MAX];
int Request[MAX], Finish[MAX], SafeSeq[MAX];

// Accept matrix row by row
void acceptMatrix(int matrix[MAX][MAX], char *name) {
    printf("Enter %s Matrix (row by row):\n", name);
    for (int i = 0; i < n; i++) {
        printf("Enter resources for Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Accept available resources
void acceptAvailable() {
    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }
}

// Calculate the Need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

// Helper function to check if Need <= Work
int canExecute(int process, int Work[]) {
    for (int j = 0; j < m; j++) {
        if (Need[process][j] > Work[j]) return 0;
    }
    return 1;
}

// Simplified Safety Algorithm
int safetyAlgorithm() {
    int Work[MAX], count = 0;
    for (int i = 0; i < m; i++) Work[i] = Available[i];
    for (int i = 0; i < n; i++) Finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!Finish[i] && canExecute(i, Work)) {
                for (int j = 0; j < m; j++) Work[j] += Allocation[i][j];
                SafeSeq[count++] = i;
                Finish[i] = 1;
                found = 1;
            }
        }
        if (!found) return 0; // No process could proceed → Unsafe
    }
    return 1; // Safe
}

// Simplified Resource Request Algorithm
void resourceRequest() {
    int process;
    printf("Enter Process Number (0-%d): ", n - 1);
    scanf("%d", &process);

    printf("Enter Request for Process P%d:\n", process);
    for (int i = 0; i < m; i++) scanf("%d", &Request[i]);

    // Check if the request is valid
    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[process][i]) {
            printf("Error: Request exceeds maximum need.\n");
            return;
        }
        if (Request[i] > Available[i]) {
            printf("Resources not available, Process must wait.\n");
            return;
        }
    }

    // Temporarily allocate requested resources
    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[process][i] += Request[i];
        Need[process][i] -= Request[i];
    }

    // Check if the system is safe
    if (safetyAlgorithm()) {
        printf("Request can be granted. Safe Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("Request cannot be granted. Reverting changes.\n");
        for (int i = 0; i < m; i++) {
            Available[i] += Request[i];
            Allocation[process][i] -= Request[i];
            Need[process][i] += Request[i];
        }
    }
}

// Display Allocation, Max, Need matrices and Available resources
void displayMatrices() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", Allocation[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", Max[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", Need[i][j]);
        printf("\n");
    }
    printf("Available Resources: ");
    for (int i = 0; i < m; i++) printf("%d ", Available[i]);
    printf("\n");

    // Check if the system is in a safe state
    if (safetyAlgorithm()) {
        printf("System is Safe. Safe Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("System is Unsafe!\n");
    }
}

// Main function
int main() {
    int choice;

    printf("Enter number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    acceptMatrix(Allocation, "Allocation");
    acceptMatrix(Max, "Max");
    calculateNeed();
    acceptAvailable();
    displayMatrices();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Accept Request and Apply Banker's Algorithm\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                resourceRequest();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}




/*
#include <stdio.h>

#define MAX 10

int n, m; // Number of processes and resource types
int Allocation[MAX][MAX], Max[MAX][MAX], Need[MAX][MAX], Available[MAX];
int Request[MAX], Finish[MAX], SafeSeq[MAX];

void acceptMatrix(int matrix[MAX][MAX], char* name) {
    printf("Enter %s Matrix:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void acceptAvailable() {
    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++) {
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

void displayMatrices() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", Allocation[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", Max[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", Need[i][j]);
        printf("\n");
    }
    printf("Available Resources: ");
    for (int i = 0; i < m; i++) printf("%d ", Available[i]);
    printf("\n");
}

int safetyAlgorithm() {
    int Work[MAX], count = 0;
    for (int i = 0; i < m; i++) Work[i] = Available[i];
    for (int i = 0; i < n; i++) Finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) Work[k] += Allocation[i][k];
                    SafeSeq[count++] = i;
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }
    return 1;
}

void resourceRequest() {
    int process;
    printf("Enter Process Number (0-%d): ", n - 1);
    scanf("%d", &process);

    printf("Enter Request for Process P%d:\n", process);
    for (int i = 0; i < m; i++) scanf("%d", &Request[i]);

    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[process][i]) {
            printf("Error: Request exceeds maximum need.\n");
            return;
        }
        if (Request[i] > Available[i]) {
            printf("Resources not available, Process must wait.\n");
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[process][i] += Request[i];
        Need[process][i] -= Request[i];
    }

    if (safetyAlgorithm()) {
        printf("Request can be granted. Safe Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("Request cannot be granted. Reverting changes.\n");
        for (int i = 0; i < m; i++) {
            Available[i] += Request[i];
            Allocation[process][i] -= Request[i];
            Need[process][i] += Request[i];
        }
    }
}

int main() {
    int choice;

    printf("Enter number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Accept Allocation\n");
        printf("2. Accept Max\n");
        printf("3. Calculate Need\n");
        printf("4. Accept Available\n");
        printf("5. Display Matrices\n");
        printf("6. Accept Request and Apply Banker's Algorithm\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: acceptMatrix(Allocation, "Allocation"); break;
            case 2: acceptMatrix(Max, "Max"); break;
            case 3: calculateNeed(); printf("Need matrix calculated.\n"); break;
            case 4: acceptAvailable(); break;
            case 5: displayMatrices(); break;
            case 6: resourceRequest(); break;
            case 7: return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}
*/