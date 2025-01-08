#include <stdio.h>

int A[10][10], M[10][10], N[10][10], Av[10], Safe[10], Finish[10], nor, nop;

void AcceptData(int X[][10]) {
    int i, j;
    for (i = 0; i < nop; i++) {
        printf("P%d\n", i);
        for (j = 0; j < nor; j++) {
            printf("%c: ", 65 + j);
            scanf("%d", &X[i][j]);
        }
    }
}

void AcceptAvailability() {
    int i;
    for (i = 0; i < nor; i++) {
        printf("%c: ", 65 + i);
        scanf("%d", &Av[i]);
    }
}

void DisplayData() {
    int i, j;
    printf("\n\tAllocation\t\tMax\t\tNeed\n");
    printf("\t");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < nor; j++)
            printf("%4c", 65 + j);
        printf("\t");
    }
    for (i = 0; i < nop; i++) {
        printf("\nP%d\t", i);
        for (j = 0; j < nor; j++)
            printf("%4d", A[i][j]);
        printf("\t");
        for (j = 0; j < nor; j++)
            printf("%4d", M[i][j]);
        printf("\t");
        for (j = 0; j < nor; j++)
            printf("%4d", N[i][j]);
    }
    printf("\nAvailable\n");
    for (j = 0; j < nor; j++)
        printf("%4d", Av[j]);
}

void CalcNeed() {
    int i, j;
    for (i = 0; i < nop; i++)
        for (j = 0; j < nor; j++)
            N[i][j] = M[i][j] - A[i][j];
}

int checkNeed(int pno) {
    int i;
    for (i = 0; i < nor; i++)
        if (N[pno][i] > Av[i])
            return 0;
    return 1;
}

void Banker() {
    int i = 0, j, k = 0, flag = 0;
    for (i = 0; i < nop; i++)
        Finish[i] = 0;

    while (flag < 2) {
        if (!Finish[i]) {
            printf("\nNeed%d(", i);
            for (j = 0; j < nor; j++)
                printf("%d,", N[i][j]);
            if (!checkNeed(i)) {
                printf("\b)>Available(");
                for (j = 0; j < nor; j++)
                    printf("%d,", Av[j]);
                printf("\b)");
                printf("\nNeed Cannot be satisfied, consider next process");
            } else {
                printf("\b)<=Available(");
                for (j = 0; j < nor; j++)
                    printf("%d,", Av[j]);
                printf("\b)");
                printf("\nNeed can be satisfied, so allocate required resources");
                printf("\nAllocation%d\t\tAvailable\t\tNeed%d\n", i, i);
                for (j = 0; j < nor; j++) {
                    Av[j] -= N[i][j];
                    A[i][j] += N[i][j];
                    N[i][j] = 0;
                }
                for (j = 0; j < nor; j++)
                    printf("%6d", A[i][j]);
                printf("\t");
                for (j = 0; j < nor; j++)
                    printf("%6d", Av[j]);
                printf("\t");
                for (j = 0; j < nor; j++)
                    printf("%6d", N[i][j]);
                printf("\nAfter P%d terminates it will release all its resources", i);
                for (j = 0; j < nor; j++) {
                    Av[j] += A[i][j];
                    A[i][j] = 0;
                }
                Safe[k++] = i;
                Finish[i] = 1;
            }
        }
        if ((i + 1) % nop == 0)
            flag++;
        i = (i + 1) % nop;
    }
    if (k == nop) {
        printf("\nSystem is in a safe state...");
        printf("\nSafe Sequence: ");
        for (i = 0; i < k; i++)
            printf("P%d->", Safe[i]);
        printf("\b ");
    } else {
        printf("\nSystem is not in a safe state...");
    }
}

void main() {
    printf("\nEnter No. of Processes & No. of Resources: ");
    scanf("%d %d", &nop, &nor);
    printf("Enter Allocation\n");
    AcceptData(A);
    printf("Enter Max Requirement\n");
    AcceptData(M);
    printf("Enter Availability\n");
    AcceptAvailability();
    CalcNeed();
    DisplayData();
    Banker();
}
