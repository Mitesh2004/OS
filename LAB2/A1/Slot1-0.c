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
}






















/*
#include <stdio.h>

int n, m; // Number of processes and resources
int Allocation[10][10], Max[10][10], Need[10][10], Available[10];

void acceptMatrix(int matrix[10][10], const char* name) {
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

void displayMatrix(int matrix[10][10], const char* name) {
    printf("\n%s matrix:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void displayAvailable() {
    printf("\nAvailable resources:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", Available[i]);
    }
    printf("\n");
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

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display Allocation and Max\n");
        printf("2. Display Need matrix\n");
        printf("3. Display Available\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMatrix(Allocation, "Allocation");
                displayMatrix(Max, "Max");
                break;
            case 2:
                displayMatrix(Need, "Need");
                break;
            case 3:
                displayAvailable();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

}*/
