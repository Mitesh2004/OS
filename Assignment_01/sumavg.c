#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000

int main(int argc, char *argv[]) {
    int rank, size, sum = 0, total;
    int data[N], part[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = N / size;
   // int part[chunk]; 

    if (rank == 0) {
        for (int i = 0; i < N; i++) data[i] = rand() % 100;
    }

    MPI_Scatter(data, chunk, MPI_INT, part, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++) sum += part[i];

    MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double avg = (double)total / N;
        printf("Sum: %d\n", total);
        printf("Average: %.2f\n", avg);
    }

    MPI_Finalize();
}

