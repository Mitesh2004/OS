#include <stdio.h>

int A[10][10], M[10][10], N[10][10], Av[10], Safe[10], Finish[10], nop, nor;

void inputMatrix(int mat[][10], const char *label) {
    printf("Enter %s Matrix:\n", label);
    for (int i = 0; i < nop; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < nor; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void inputArray(int arr[], const char *label) {
    printf("Enter %s Array:\n", label);
    for (int i = 0; i < nor; i++) {
        scanf("%d", &arr[i]);
    }
}

void calculateNeed() {
    for (int i = 0; i < nop; i++) {
        for (int j = 0; j < nor; j++) {
            N[i][j] = M[i][j] - A[i][j];
        }
    }
}

int checkNeed(int pno) {
    for (int i = 0; i < nor; i++) {
        if (N[pno][i] > Av[i]) return 0;
    }
    return 1;
}

void banker() {
    int count = 0;
    for (int i = 0; i < nop; i++) Finish[i] = 0;

    while (count < nop) {
        int found = 0;
        for (int i = 0; i < nop; i++) {
            if (!Finish[i] && checkNeed(i)) {
                for (int j = 0; j < nor; j++) {
                    Av[j] += A[i][j];
                }
                Safe[count++] = i;
                Finish[i] = 1;
                found = 1;
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return;
        }
    }

    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < count; i++) {
        printf("P%d ", Safe[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &nop, &nor);

    inputMatrix(A, "Allocation");
    inputMatrix(M, "Max");
    inputArray(Av, "Availability");

    calculateNeed();
    banker();

    return 0;
}
