#include <stdio.h>

int A[10][10], M[10][10], N[10][10], Av[10], Safe[10], Finish[10], nop, nor;

void AcceptData(int X[][10]) {
	for (int i = 0; i < nop; i++) {
		printf("P%d\n", i);
		for (int j = 0; j < nor; j++) {
			printf("%c: ", 65 + j);
			scanf("%d", &X[i][j]);
		}
	}
}

void AcceptAvailability() {
	for (int i = 0; i < nor; i++) {
		printf("%c: ", 65 + i);
		scanf("%d", &Av[i]);
	}
}

void DisplayData() {
	printf("\n\tAllocation\tMax\tNeed\n");
	for (int i = 0; i < nop; i++) {
		printf("P%d\t", i);
		for (int j = 0; j < nor; j++) printf("%4d", A[i][j]);
		printf("\t");
		for (int j = 0; j < nor; j++) printf("%4d", M[i][j]);
		printf("\t");
		for (int j = 0; j < nor; j++) printf("%4d", N[i][j]);
		printf("\n");
	}
	printf("\nAvailable: ");
	for (int j = 0; j < nor; j++) printf("%4d", Av[j]);
	printf("\n");
}

void CalcNeed() {
	for (int i = 0; i < nop; i++) 
		for (int j = 0; j < nor; j++) 
			N[i][j] = M[i][j] - A[i][j];
}

int checkNeed(int pno) {
	for (int i = 0; i < nor; i++) 
		if (N[pno][i] > Av[i]) return 0;
	return 1;
}

void Banker() {
	int flag = 0, k = 0, i = 0;
	while (flag < 2) {
		if (!Finish[i]) {
			if (checkNeed(i)) {
				printf("\nAllocating to P%d\n", i);
				for (int j = 0; j < nor; j++) {
					Av[j] -= N[i][j];
					A[i][j] = M[i][j];
				}
				Safe[k++] = i;
				Finish[i] = 1;
			} else {
				printf("\nNeed of P%d cannot be satisfied.\n", i);
			}
		}
		i = (i + 1) % nop;
		if (i == 0) flag++;
	}
	if (k == nop) {
		printf("\nSystem is in safe state\nSafe Sequence: ");
		for (int i = 0; i < k; i++) printf("P%d -> ", Safe[i]);
		printf("\b)\n");
	} else {
		printf("\nSystem is not in safe state\n");
	}
}

int main() {
	printf("Enter No. of Processes & Resources: ");
	scanf("%d %d", &nop, &nor);
	printf("Enter Allocation\n");
	AcceptData(A);
	printf("Enter Max Requirement\n");
	AcceptData(M);
	printf("Enter Available Resources\n");
	AcceptAvailability();
	CalcNeed();
	DisplayData();
	Banker();
	return 0;
}
